#include "detector.hh"
#include "HitCollections.h"
#include "shielding_Hit.h"
#include "G4SDManager.hh"
MySensitiveDetector::MySensitiveDetector(G4String name)
    : G4VSensitiveDetector(name), fGeHitCollectionId(-1), fNaIHitCollectionId(-1), fNaiHitCollection(nullptr),
      fGeHitCollection(nullptr)
{

  collectionName.insert("naiHitCollection");
  collectionName.insert("geHitCollection");
}

MySensitiveDetector::~MySensitiveDetector() {}

void MySensitiveDetector::Initialize(G4HCofThisEvent *hce)
{
  EDep.clear();
  FirstHitTime.clear();
  LastHitTime.clear();
  numHits.clear();

  // Creating hitcollection

  fNaiHitCollection = new NaIHitCollection(SensitiveDetectorName, collectionName[0]);
  fGeHitCollection  = new GeHitCollection(SensitiveDetectorName, collectionName[0]);

  fNaIHitCollectionId = GetCollectionID(0);
  fGeHitCollectionId  = GetCollectionID(1);
  hce->AddHitsCollection(fNaIHitCollectionId, fNaiHitCollection);
  hce->AddHitsCollection(fGeHitCollectionId, fGeHitCollection);
}

void MySensitiveDetector::CleanDetector()
{
  EDep.clear();
  FirstHitTime.clear();
  LastHitTime.clear();
  numHits.clear();
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  G4Track *track                = aStep->GetTrack();
  G4StepPoint *postStep         = aStep->GetPostStepPoint();
  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
  G4AnalysisManager *man        = G4AnalysisManager::Instance();
  G4int copyNo                  = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
  // G4String volName = touchable->GetVolume()->GetLogicalVolume()->GetName();
  G4VPhysicalVolume *physVol = touchable->GetVolume();
  G4ThreeVector posDetector  = physVol->GetTranslation();

  // G4int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  // G4String particleName = track->GetParticleDefinition()->GetParticleName();
  G4double edep = aStep->GetTotalEnergyDeposit() / keV;
  // G4double particleKinEnergy = aStep->GetPreStepPoint()->GetKineticEnergy() / keV;
  G4double particleTime = aStep->GetPreStepPoint()->GetGlobalTime() / ns;
  G4String matName      = aStep->GetPreStepPoint()->GetMaterial()->GetName();

/*  EDep[copyNo] += edep;
  numHits[copyNo] += 1;
  if (FirstHitTime.find(copyNo) == FirstHitTime.end()) {
    FirstHitTime[copyNo] = particleTime;
  }
  if (LastHitTime.find(copyNo) == LastHitTime.end()) {
    LastHitTime[copyNo] = particleTime;
  } else {
    LastHitTime[copyNo] = std::max(LastHitTime[copyNo], particleTime);
  }
*/
  // SD stuff
  shielding_Hit *newHit = new shielding_Hit;
  newHit->Set(edep, postStep->GetPosition(), copyNo, particleTime);
  G4String volName = physVol->GetLogicalVolume()->GetName();
  if(newHit){
  if (volName == "logicNaI") fNaiHitCollection->insert(newHit);
  if (volName == "logicHPGe") fGeHitCollection->insert(newHit);
}

  //   std::cout << "Particle: " << particleName  << " with Energy: " <<
  //   particleKinEnergy << " keV deposited:" << edep  << " in: " << matName <<
  //   "_" << copyNo << std::endl;

  //   G4int parent = track->GetParentID();
  //   G4String creatorProcess;
  //   if (track->GetCreatorProcess()) {
  //     creatorProcess = track->GetCreatorProcess()->GetProcessName();
  //   } else if (parent == 0) {
  //     creatorProcess = "primary";
  //   }

  // track->SetTrackStatus(fStopAndKill);
  /*
    if (particleName == "neutron") {
      // fEventAction->AddNumNeutronEvt();
      //  G4cout<<"Neutron Total Energy: "<<particleTotEnergy<<G4endl;
      //  G4cout<<"Neutron Kinetic Energy: "<<particleKinEnergy<<G4endl;
      // G4cout<<"Creator "<<particleName<<": "<<creatorProcess<<G4endl;
      man->FillNtupleIColumn(1, 0, evID);
      man->FillNtupleDColumn(1, 2, particleKinEnergy);
      man->FillNtupleDColumn(1, 3, particleTime / ns);
      man->FillNtupleSColumn(1, 4, creatorProcess);
      man->AddNtupleRow(1);
    } else if (particleName == "gamma") {
      // fEventAction->AddNumGammaEvt();
      //  G4cout<<"Gamma Total Energy: "<<particleTotEnergy<<G4endl;
      //  G4cout<<"Gamma Kinetic Energy: "<<particleKinEnergy<<G4endl;
      // G4cout<<"Creator "<<particleName<<": "<<creatorProcess<<G4endl;
      man->FillNtupleIColumn(0, 0, evID);
      man->FillNtupleDColumn(0, 2, particleKinEnergy);
      man->FillNtupleDColumn(0, 3, particleTime / ns);
      man->FillNtupleSColumn(0, 4, creatorProcess);
      man->AddNtupleRow(0);
    } else if (particleName == "e-") {
      // fEventAction->AddNumElectronEvt();
      // G4cout<<"Creator "<<particleName<<": "<<creatorProcess<<G4endl;
      man->FillNtupleIColumn(4, 0, evID);
      man->FillNtupleDColumn(4, 2, particleKinEnergy);
      man->FillNtupleDColumn(4, 3, particleTime / ns);
      man->FillNtupleSColumn(4, 4, creatorProcess);
      man->AddNtupleRow(4);
    } else if (particleName == "e+") {
      // fEventAction->AddNumPositronEvt();
      // G4cout<<"Creator "<<particleName<<": "<<creatorProcess<<G4endl;
      man->FillNtupleIColumn(5, 0, evID);
      man->FillNtupleDColumn(5, 2, particleKinEnergy);
      man->FillNtupleDColumn(5, 3, particleTime / ns);
      man->FillNtupleSColumn(5, 4, creatorProcess);
      man->AddNtupleRow(5);
    } else if (particleName == "nu_e") {
      // fEventAction->AddNumNu_eEvt();
      // G4cout<<"Creator "<<particleName<<": "<<creatorProcess<<G4endl;
      man->FillNtupleIColumn(2, 0, evID);
      man->FillNtupleDColumn(2, 2, particleKinEnergy);
      man->FillNtupleDColumn(2, 3, particleTime / ns);
      man->FillNtupleSColumn(2, 4, creatorProcess);
      man->AddNtupleRow(2);
    } else if (particleName == "anti_nu_e") {
      // fEventAction->AddNumaNu_eEvt();
      // G4cout<<"Creator "<<particleName<<": "<<creatorProcess<<G4endl;
      man->FillNtupleIColumn(3, 0, evID);
      man->FillNtupleDColumn(3, 2, particleKinEnergy);
      man->FillNtupleDColumn(3, 3, particleTime / ns);
      man->FillNtupleSColumn(3, 4, creatorProcess);
      man->AddNtupleRow(3);
    } else {
      // fEventAction->AddNumOtherEvt();
    }*/

  return true;
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent *)
{
  // Data remains accessible for your EventAction
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  std::cout << "=============== ENDOFEVENT =======================" << std::endl;
  std::cout << "Size of NaI Hit Collection : " << fNaiHitCollection->entries() << std::endl;
  std::cout << "Size of Ge Hit Collection : " << fGeHitCollection->entries() << std::endl;
 		std::cout << "================== NaI Hits ====================" << std::endl; 
  for (unsigned int i = 0; i < fNaiHitCollection->entries(); i++) {
    shielding_Hit *hit = (*fNaiHitCollection)[i];
    hit->Print();
  }
  
		std::cout << "================ GE Hits ======================" << std::endl; 
  for (unsigned int i = 0; i < fGeHitCollection->entries(); i++) {
    shielding_Hit *hit = (*fGeHitCollection)[i];
    hit->Print();
  }

}
