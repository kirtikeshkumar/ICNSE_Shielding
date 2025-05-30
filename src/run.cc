#include "run.hh"

MyRunAction::MyRunAction() {
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->CreateNtuple("Germanium", "Germanium");
  man->CreateNtupleIColumn("Event");
  man->CreateNtupleIColumn("CopyNum");
  man->CreateNtupleDColumn("Time");
  man->CreateNtupleDColumn("EnergyDep");
  man->FinishNtuple(0);

  man->CreateNtuple("NaI", "NaI");
  man->CreateNtupleIColumn("Event");
  man->CreateNtupleIColumn("CopyNum");
  man->CreateNtupleDColumn("Time");
  man->CreateNtupleDColumn("EnergyDep");
  man->FinishNtuple(1);
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
