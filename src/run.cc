#include "run.hh"

MyRunAction::MyRunAction() {
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  // General Purpose Storage

  man->CreateNtuple("Gammas", "Gammas");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(0);

  man->CreateNtuple("Neutrons", "Neutrons");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(1);

  man->CreateNtuple("Neutrinos", "Neutrinos");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(2);

  man->CreateNtuple("antiNeutrinos", "antiNeutrinos");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(3);

  man->CreateNtuple("Electrons", "Electrons");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(4);

  man->CreateNtuple("Positrons", "Positrons");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(5);

  man->CreateNtuple("Alphas", "Alphas");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("fEnergy");
  man->CreateNtupleDColumn("fTime");
  man->FinishNtuple(6);

  // For Self Activity
  man->CreateNtuple("Primary", "Primary");
  man->CreateNtupleIColumn("fEvent");
  man->CreateNtupleDColumn("posX");
  man->CreateNtupleDColumn("posY");
  man->CreateNtupleDColumn("posZ");
  man->FinishNtuple(7);
}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *run) {

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4int runID = run->GetRunID();

  std::stringstream strRunID;
  strRunID << runID;

  man->OpenFile("output" + strRunID.str() + ".root");
}

void MyRunAction::EndOfRunAction(const G4Run *) {
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  man->Write();
  man->CloseFile();
}
