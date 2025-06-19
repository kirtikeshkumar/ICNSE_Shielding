#include "run.hh"

MyRunAction::MyRunAction() {}

MyRunAction::MyRunAction(MyPrimaryGenerator *gen) {
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->CreateNtuple("Ge_Hits", "Ge_Hits");
  man->CreateNtupleIColumn("Event");
  man->CreateNtupleIColumn("CopyNum");
  man->CreateNtupleDColumn("locX");
  man->CreateNtupleDColumn("locY");
  man->CreateNtupleDColumn("locZ");
  man->CreateNtupleDColumn("Time");
  man->CreateNtupleDColumn("EnergyDep");
  man->CreateNtupleSColumn("Particle");
  man->CreateNtupleSColumn("Process");
  man->FinishNtuple(0);

  man->CreateNtuple("NaI_Hits", "NaI_hits");
  man->CreateNtupleIColumn("Event");
  man->CreateNtupleIColumn("CopyNum");
  man->CreateNtupleDColumn("locX");
  man->CreateNtupleDColumn("locY");
  man->CreateNtupleDColumn("locZ");
  man->CreateNtupleDColumn("Time");
  man->CreateNtupleDColumn("EnergyDep");
  man->CreateNtupleSColumn("Particle");
  man->CreateNtupleSColumn("Process");
  man->FinishNtuple(1);

  man->CreateNtuple("EventColl", "EventColl");
  man->CreateNtupleIColumn("EvNo");
  man->CreateNtupleIColumn("Copy");
  man->CreateNtupleSColumn("DetectorMat");
  man->CreateNtupleDColumn("EnergyDep");
  man->CreateNtupleIColumn("NumHitPrimary");
  man->FinishNtuple(2);
}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *run) {

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4int runID = run->GetRunID();

  std::stringstream strRunID;
  strRunID << runID;

  man->OpenFile("output" + strRunID.str() + ".root");
}

/*void MyRunAction::PrintStatus() {
  std::cout << "Num of Neutrons: " << numneutron << std::endl;
  std::cout << "Num of gammas: " << numgamma << std::endl;
  std::cout << "Num of e-: " << numelectron << std::endl;
  std::cout << "Num of e+: " << numpositron << std::endl;
  std::cout << "Num of nu_e: " << numnu_e << std::endl;
  std::cout << "Num of anti_nu_e: " << numanu_e << std::endl;
  std::cout << "Num of Others: " << numother << std::endl;
}*/

void MyRunAction::EndOfRunAction(const G4Run *) {
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  // PrintStatus();

  man->Write();
  man->CloseFile();
}
