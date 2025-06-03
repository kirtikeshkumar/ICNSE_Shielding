#include "event.hh"

MyEventAction::MyEventAction(MyRunAction *run) : fRun(run) {}

MyEventAction::~MyEventAction() {}

void MyEventAction::BeginOfEventAction(const G4Event *anEvent)
{
  // std::cout << "#######################################################" << std::endl;
  // std::cout << "BeginEventAction" << std::endl;
  // std::cout << "#######################################################" << std::endl;
  // std::cout << std::endl;

  const MyDetectorConstruction *det = static_cast<const MyDetectorConstruction *>(
      G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  /*NaISD = det->GetNaISD();
  NaISD->CleanDetector();
  GeSD = det->GetGeSD();
  GeSD->CleanDetector();*/
  // std::cout << "#######################################################" << std::endl;
  // std::cout << "Recvd Detectors" << std::endl;
  // std::cout << "#######################################################" << std::endl;
  // std::cout << std::endl;
  evID = anEvent->GetEventID();
  
  /*NaISD->CleanDetector();
  GeSD->CleanDetector();*/

  /*num = 0;
  numgamma_evt = 0;
  numneutron_evt = 0;
  numelectron_evt = 0;
  numpositron_evt = 0;
  numnu_e_evt = 0;
  numanu_e_evt = 0;
  numother_evt = 0;
  fEdep = 0.;
  if (evID % 100000 == 0) {
    std::cout << "event: " << evID << std::endl;
  }*/
}

void MyEventAction::EndOfEventAction(const G4Event *anEvent)
{
  if (evID % 10 == 0)
  {
    std::cout << "Event: " << evID << std::endl;
  }
  G4AnalysisManager *man = G4AnalysisManager::Instance();
/*  if (GeSD)
  {
    const auto &edepMap = GeSD->GetEDepMap();
    const auto &firsttimeMap = GeSD->GetFirstHitTimeMap();
    const auto &lasttimeMap = GeSD->GetFirstHitTimeMap();
    const auto &numHitMap = GeSD->GetNumHits();
    for (const auto &[copyNo, edep] : edepMap)
    {
      // std::cout << "GeSD: " << evID << " " << copyNo << " " << edep << " " << firsttimeMap.at(copyNo) << " " << lasttimeMap.at(copyNo) << " " << numHitMap.at(copyNo) << std::endl;
      // G4ThreeVector pos = GeSD->GetPosition(copyNo);
      man->FillNtupleIColumn(0, 0, evID);
      man->FillNtupleIColumn(0, 1, copyNo);
      man->FillNtupleDColumn(0, 2, 0);
      man->FillNtupleDColumn(0, 3, 0);
      man->FillNtupleDColumn(0, 4, 0);
      man->FillNtupleDColumn(0, 5, firsttimeMap.at(copyNo));
      man->FillNtupleDColumn(0, 6, lasttimeMap.at(copyNo));
      man->FillNtupleIColumn(0, 7, numHitMap.at(copyNo));
      man->FillNtupleDColumn(0, 8, edep);
      man->AddNtupleRow(0);
    }
  }

  if (NaISD)
  {
    const auto &edepMap = NaISD->GetEDepMap();
    const auto &firsttimeMap = NaISD->GetFirstHitTimeMap();
    const auto &lasttimeMap = NaISD->GetFirstHitTimeMap();
    const auto &numHitMap = NaISD->GetNumHits();
    for (const auto &[copyNo, edep] : edepMap)
    {
      // std::cout << "NaISD: " << evID << " " << copyNo << " " << edep << " " << firsttimeMap.at(copyNo) << " " << lasttimeMap.at(copyNo) << " " << numHitMap.at(copyNo) << std::endl;
      // G4ThreeVector pos = NaISD->GetPosition(copyNo);
      man->FillNtupleIColumn(1, 0, evID);
      man->FillNtupleIColumn(1, 1, copyNo);
      man->FillNtupleDColumn(1, 2, 0);
      man->FillNtupleDColumn(1, 3, 0);
      man->FillNtupleDColumn(1, 4, 0);
      man->FillNtupleDColumn(1, 5, firsttimeMap.at(copyNo));
      man->FillNtupleDColumn(1, 6, lasttimeMap.at(copyNo));
      man->FillNtupleIColumn(1, 7, numHitMap.at(copyNo));
      man->FillNtupleDColumn(1, 8, edep);
      man->AddNtupleRow(1);
    }
  }
*/
  /*AddNumNeutron(numneutron_evt);
  AddNumGamma(numgamma_evt);
  AddNumElectron(numelectron_evt);
  AddNumPositron(numpositron_evt);
  AddNumNu_e(numnu_e_evt);
  AddNumaNu_e(numanu_e_evt);
  AddNumOther(numother_evt);

  if (evID % 1000000 == 0)
  {
    std::cout << std::endl
              << std::endl;
    // std::cout << " Printing from event " << evID << std::endl;
    // fRun->PrintStatus();
  }*/
}
