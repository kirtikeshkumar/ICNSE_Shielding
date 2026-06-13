#include "detector.hh"
#include <G4ThreeVector.hh>
#include <G4TrackVector.hh>
#include <G4Types.hh>
#include <cmath>
MySensitiveDetector::MySensitiveDetector(G4String name)
    : G4VSensitiveDetector(name),
      fNaIHitCollectionId(-1), fNaiHitCollection(nullptr)
{

  collectionName.insert("naiHitCollection");
  // collectionName.insert("geHitCollection");
}

MySensitiveDetector::~MySensitiveDetector() {}

void MySensitiveDetector::Initialize(G4HCofThisEvent *hce)
{
  // Creating hitcollection

  fNaiHitCollection =
      new NaIHitCollection(SensitiveDetectorName, collectionName[0]);

  fNaIHitCollectionId = GetCollectionID(0);
  hce->AddHitsCollection(fNaIHitCollectionId, fNaiHitCollection);
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
  G4double particleTime = aStep->GetPostStepPoint()->GetGlobalTime() / ns;
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

  if (edep > 0.001)
  {
    shielding_Hit *newHit = new shielding_Hit;
    newHit->Set(edep, postStep->GetPosition(), copyNo, particleTime, parent,
                particleName, procName);
    G4String volName = physVol->GetLogicalVolume()->GetName();
    if (newHit)
    {
      if (volName == "logicNaI")
        fNaiHitCollection->insert(newHit);
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
}
