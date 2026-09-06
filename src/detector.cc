#include "detector.hh"
#include <G4ThreeVector.hh>
#include <G4TrackVector.hh>
#include <G4Types.hh>
#include <cmath>
MySensitiveDetector::MySensitiveDetector(G4String name)
    : G4VSensitiveDetector(name), fNaIHitCollectionId(-1),
      fNaiHitCollection(nullptr)
{

  collectionName.insert("naiHitCollection");
  // collectionName.insert("geHitCollection");
  // G4cout << "G4WT" << G4Threading::G4GetThreadId() << " > SD CONSTRUCTOR"
  //        << " this=" << this << " name=" << name << G4endl;
}

MySensitiveDetector::~MySensitiveDetector() {}

void MySensitiveDetector::Initialize(G4HCofThisEvent *hce)
{
  // Creating hitcollection

  // G4cout << "G4WT" << G4Threading::G4GetThreadId() << " > Initialize"
  //        << " this=" << this
  //        << " fNaiHitCollection(before)=" << fNaiHitCollection << G4endl;

  fNaiHitCollection =
      new NaIHitCollection(SensitiveDetectorName, collectionName[0]);

  fNaIHitCollectionId = GetCollectionID(0);

  hce->AddHitsCollection(fNaIHitCollectionId, fNaiHitCollection);

  // G4cout << "G4WT" << G4Threading::G4GetThreadId() << " > Initialize DONE"
  //        << " this=" << this
  //        << " fNaiHitCollection(after)=" << fNaiHitCollection
  //        << " HCID=" << fNaIHitCollectionId << G4endl;
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep,
                                        G4TouchableHistory *ROhist)
{

  // Constants for fiducializing HPGe Detector using Logistic curve
  // Results in Dead layer and transition layer thickness similar to CONUS
  double L = 1.0;
  double k = -1.0 * 700.;
  double r0 = 4.19;
  double z0 = 3.94;

  G4Track *track = aStep->GetTrack();

  G4StepPoint *postStep = aStep->GetPostStepPoint();
  const G4VTouchable *touchable = aStep->GetPostStepPoint()->GetTouchable();
  // G4AnalysisManager *man = G4AnalysisManager::Instance();
  G4int copyNo =
      aStep->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();
  // G4String volName = touchable->GetVolume()->GetLogicalVolume()->GetName();
  G4VPhysicalVolume *physVol = touchable->GetVolume();
  G4ThreeVector posDetector = physVol->GetTranslation();
  const G4VProcess *depositionprocess =
      aStep->GetPostStepPoint()->GetProcessDefinedStep();
  G4String procName;
  if (depositionprocess)
  {
    procName = depositionprocess->GetProcessName();
  }

  evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  G4String particleName = track->GetParticleDefinition()->GetParticleName();
  G4double edep = aStep->GetTotalEnergyDeposit() / keV;
  // G4double particleKinEnergy = aStep->GetPreStepPoint()->GetKineticEnergy() /
  // keV;
  G4double particleTime = aStep->GetPostStepPoint()->GetGlobalTime() / s;
  G4String matName = aStep->GetPostStepPoint()->GetMaterial()->GetName();
  G4int parent = track->GetParentID();

  // SD stuff
  if (matName == "Ge")
  {
    // Get the position of the point relative to the detector coordinates
    G4ThreeVector globalPos = postStep->GetPosition();
    G4ThreeVector localPos =
        touchable->GetHistory()->GetTopTransform().TransformPoint(globalPos);
    G4double r = std::sqrt(localPos.x() / cm * localPos.x() / cm +
                           localPos.y() / cm * localPos.y() / cm);
    G4double z = localPos.z() / cm;

    // Generate the energy deposition profile using logistic on r and z
    double rprob = 1.0 - (L / (1.0 + std::exp(k * (r - r0))));
    double zprob = 1.0;
    if (z > 0.)
    {
      zprob = 1.0 - (L / (1.0 + std::exp(k * (z - z0))));
    }
    double netprob = rprob * zprob;
    edep = edep * netprob;
  }

  if (edep > 0.00001)
  {
    shielding_Hit *newHit = new shielding_Hit;
#ifdef SETUP_DECAY
    trackInformation *info = (trackInformation *)(track->GetUserInformation());
    // std::cout << "Processing Hit in Decay Mode" << std::endl;
    G4String parentPart, branchName;
    if (info->GetBranch())
      branchName = info->GetBranch()->GetParticleName();
    else
      branchName = "Primary";

    if (info->GetDecayParent())
      parentPart = info->GetDecayParent()->GetParticleName();
    else
      parentPart = "Primary";

    // if (branchName != "Primary" and branchName != "Na22" and branchName !=
    // "Ne22" and branchName != "Ne22[1274.577]" and branchName != "e+" and
    // branchName != "gamma")
    //   std::cout << "Branch: " << branchName << " has parent: " << parentPart
    //   << std::endl;

    newHit->Set(edep, copyNo, info->GetBranchID(), info->GetParentBranchID(),
                info->GetTimeFromDecay(), info->GetDecayTime(),
                info->GetOrigDecayTime(), parentPart, branchName);
#elif defined(USE_CRY)
    trackInformation *info = (trackInformation *)(track->GetUserInformation());
    G4String parentPart, branchName;
    if (info->GetBranch())
      branchName = info->GetBranch()->GetParticleName();
    else
      branchName = "Primary";

    if (info->GetDecayParent())
      parentPart = info->GetDecayParent()->GetParticleName();
    else if (track->GetParentID() == 0)
      parentPart = track->GetParticleDefinition()->GetParticleName();
    else
      parentPart = "Primary";

    newHit->Set(edep, copyNo, info->GetBranchID(), info->GetParentBranchID(),
                info->GetTimeFromDecay(), info->GetDecayTime(),
                info->GetOrigDecayTime(), parentPart, branchName);
#else
    newHit->Set(edep, postStep->GetPosition(), copyNo, particleTime, parent,
                particleName, procName);
#endif
    G4String volName = physVol->GetLogicalVolume()->GetName();
    if (newHit)
    {
      if (volName == "logicNaI")
      {
        // G4cout << "ProcessHits" << " thread=" << G4Threading::G4GetThreadId()
        //        << " this=" << this << " fNaiHitCollection=" <<
        //        fNaiHitCollection
        //        << G4endl;
        fNaiHitCollection->insert(newHit);
      }
      if (volName == "logicHPGe")
        fGeHitCollection->insert(newHit);
    }
  }

  return true;
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
// Data remains accessible for your EventAction
// std::cout << "=============== ENDOFEVENT ======================="
//           << std::endl;
#if !defined(SETUP_DECAY) and !defined(USE_CRY)
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  std::map<int, double> EvtEDep;
  std::map<int, G4String> MatMapHit;
  std::map<int, int> MapNumHitPrimary;
  for (unsigned int i = 0; i < fNaiHitCollection->entries(); i++)
  {
    shielding_Hit *hit = (*fNaiHitCollection)[i];
    MatMapHit[hit->GetHitCopyNum()] = "NaI";
    EvtEDep[hit->GetHitCopyNum()] += hit->GetHitEDep();
    if (hit->isHitPrimary())
    {
      MapNumHitPrimary[hit->GetHitCopyNum()] += 1;
    }
    // man->FillNtupleIColumn(0, 0, evID);
    // man->FillNtupleIColumn(0, 1, hit->GetHitCopyNum());
    // man->FillNtupleDColumn(0, 2, hit->GetHitLocationX());
    // man->FillNtupleDColumn(0, 3, hit->GetHitLocationY());
    // man->FillNtupleDColumn(0, 4, hit->GetHitLocationZ());
    // man->FillNtupleDColumn(0, 5, hit->GetHitTime());
    // man->FillNtupleDColumn(0, 6, hit->GetHitEDep());
    // man->FillNtupleSColumn(0, 7, hit->GetParticleName());
    // man->FillNtupleSColumn(0, 8, hit->GetDepositionProcess());
    // man->AddNtupleRow(0);
    // hit->Print();
  }

  for (const auto &[key, val] : EvtEDep)
  {
    man->FillNtupleIColumn(1, 0, evID);
    man->FillNtupleIColumn(1, 1, key);
    man->FillNtupleSColumn(1, 2, MatMapHit[key]);
    man->FillNtupleDColumn(1, 3, val);
    man->FillNtupleIColumn(1, 4, MapNumHitPrimary[key]);
    man->AddNtupleRow(1);
    // std::cout << key << " : " << value << " : " << MatMapHit[key] <<
    // std::endl;
  }

// std::cout << "=============== ENDOFEVENT ======================="
//           << std::endl;
// std::cout << "Size of NaI Hit Collection : " <<
// fNaiHitCollection->entries()
//           << std::endl;
// std::cout << "Size of Ge Hit Collection : " <<
// fGeHitCollection->entries()
//           << std::endl;
// std::cout << "================== NaI Hits ====================" <<
// std::endl;
// for (unsigned int i = 0; i < fNaiHitCollection->entries(); i++)
// {
//   shielding_Hit *hit = (*fNaiHitCollection)[i];
//   hit->Print();
// }

// std::cout << "================ GE Hits ======================" <<
// std::endl;
// for (unsigned int i = 0; i < fGeHitCollection->entries(); i++) {
//   shielding_Hit *hit = (*fGeHitCollection)[i];
//   hit->Print();
// }
#else
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  std::map<int, G4String> MatMapHit; // to differentiate between detectors
  std::map<int, std::map<G4String, double>>
      BrEDep; // to differentiate between branches
  std::map<int, std::map<G4String, std::vector<double>>> branchTimes;
  // std::map<int, std::map<G4String, double>> branchDecayTime;
  // std::map<int, std::map<G4String, double>> branchOrigDecayTime;
  std::map<int, std::map<G4String, G4String>> branchParent;
  for (unsigned int i = 0; i < fNaiHitCollection->entries(); i++)
  {
    shielding_Hit *hit = (*fNaiHitCollection)[i];
    G4String brname = hit->GetHitBranchName() + " " + hit->GetDecayParticle();
    int cnum = hit->GetHitCopyNum();
    MatMapHit[cnum] = "NaI";
    BrEDep[cnum][brname] += hit->GetHitEDep();
    branchTimes[cnum][brname].push_back(hit->GetHitTime());
    branchTimes[cnum][brname].push_back(hit->GetDecayTime());
    branchTimes[cnum][brname].push_back(hit->GetOrigDecayTime());
    branchParent[cnum][brname] = hit->GetDecayParticle();
    // branchDecayTime[hit->GetHitCopyNum()]
    //                [hit->GetHitBranchName() + " " + hit->GetDecayParticle()]
    //                =
    //                    hit->GetDecayTime();
    // std::cout << std::endl;
  }

  for (const auto &[copykey, edepmap] : BrEDep)
  {
    for (const auto &[branchkey, val] : edepmap)
    {
      // std::cout << evID << " : " << copykey << " : " << branchkey << " : "
      //           << val << " : " << branchTime[copykey][branchkey] << " : "
      //           << branchDecayTime[copykey][branchkey] << std::endl;
      man->FillNtupleIColumn(0, 0, evID);
      man->FillNtupleIColumn(0, 1, copykey);
      man->FillNtupleSColumn(0, 2, MatMapHit[copykey]);
      man->FillNtupleDColumn(0, 3, val);
      man->FillNtupleSColumn(0, 4, branchkey);
      man->FillNtupleDColumn(0, 5, branchTimes[copykey][branchkey][0]);
      man->FillNtupleDColumn(0, 6, branchTimes[copykey][branchkey][1]);
      man->FillNtupleDColumn(0, 7, branchTimes[copykey][branchkey][2]);
      man->FillNtupleSColumn(0, 8, branchParent[copykey][branchkey]);
      man->AddNtupleRow(0);
    }
  }

#endif
#ifdef USE_CRY
  std::map<int, double> EvtEDep;
  std::map<int, G4String> MatMapHit1;
  std::map<int, int> MapNumHitPrimary;
  for (unsigned int i = 0; i < fNaiHitCollection->entries(); i++)
  {
    shielding_Hit *hit = (*fNaiHitCollection)[i];
    MatMapHit1[hit->GetHitCopyNum()] = "NaI";
    EvtEDep[hit->GetHitCopyNum()] += hit->GetHitEDep();
    if (hit->isHitPrimary())
    {
      MapNumHitPrimary[hit->GetHitCopyNum()] += 1;
    }
  }
  for (const auto &[key, val] : EvtEDep)
  {
    man->FillNtupleIColumn(1, 0, evID);
    man->FillNtupleIColumn(1, 1, key);
    man->FillNtupleSColumn(1, 2, MatMapHit1[key]);
    man->FillNtupleDColumn(1, 3, val);
    man->FillNtupleIColumn(1, 4, MapNumHitPrimary[key]);
    man->AddNtupleRow(1);
    // std::cout << key << " : " << value << " : " << MatMapHit[key] <<
    // std::endl;
  }
#endif
}
