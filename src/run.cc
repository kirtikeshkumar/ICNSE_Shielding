#include "run.hh"

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	man->CreateNtuple("Gammas","Gammas");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleIColumn("fnum");
	man->CreateNtupleDColumn("fEnergy");
	man->CreateNtupleDColumn("fTime");
	man->FinishNtuple(0);
	
	man->CreateNtuple("Neutrons","Neutrons");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleIColumn("fnum");
	man->CreateNtupleDColumn("fEnergy");
	man->CreateNtupleDColumn("fTime");
	man->FinishNtuple(1);
	
	man->CreateNtuple("Neutrinos","Neutrinos");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleIColumn("fnum");
	man->CreateNtupleDColumn("fEnergy");
	man->CreateNtupleDColumn("fTime");
	man->FinishNtuple(2);
	
	man->CreateNtuple("antiNeutrinos","antiNeutrinos");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleIColumn("fnum");
	man->CreateNtupleDColumn("fEnergy");
	man->CreateNtupleDColumn("fTime");
	man->FinishNtuple(3);
	
	man->CreateNtuple("Electrons","Electrons");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleIColumn("fnum");
	man->CreateNtupleDColumn("fEnergy");
	man->CreateNtupleDColumn("fTime");
	man->FinishNtuple(4);
	
	man->CreateNtuple("Positrons","Positrons");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleIColumn("fnum");
	man->CreateNtupleDColumn("fEnergy");
	man->CreateNtupleDColumn("fTime");
	man->FinishNtuple(5);
	
	
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
	numgamma=0;
	numneutron=0;
	numelectron=0;
	numpositron=0;
	numnu_e=0;
	numanu_e=0;
	numother=0;
	
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4int runID = run->GetRunID();
	
	std::stringstream strRunID;
	strRunID << runID;
	
	man->OpenFile("output"+strRunID.str()+".root");
	
	
	
}

void MyRunAction::PrintStatus()
{
	G4cout<<"Num of Neutrons: "<<numneutron<<G4endl;
	G4cout<<"Num of gammas: "<<numgamma<<G4endl;
	G4cout<<"Num of e-: "<<numelectron<<G4endl;
	G4cout<<"Num of e+: "<<numpositron<<G4endl;
	G4cout<<"Num of nu_e: "<<numnu_e<<G4endl;
	G4cout<<"Num of anti_nu_e: "<<numanu_e<<G4endl;
	G4cout<<"Num of Others: "<<numother<<G4endl;
}

void MyRunAction::EndOfRunAction(const G4Run* )
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	PrintStatus();
	
	man->Write();
	man->CloseFile();
}
