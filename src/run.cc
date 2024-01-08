#include "run.hh"

MyRunAction::MyRunAction()
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	/*man->CreateNtuple("Photons","Photons");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->CreateNtupleDColumn("fWlen");
	man->FinishNtuple(0);*/
	
	/*man->CreateNtuple("LayersEdep","LayersEdep");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("PS_Out");
	man->CreateNtupleDColumn("HDPE_Out");
	man->CreateNtupleDColumn("BP");
	man->CreateNtupleDColumn("Pb");
	man->CreateNtupleDColumn("HDPE_In");
	man->CreateNtupleDColumn("PS_In");
	man->CreateNtupleDColumn("Cu");
	man->FinishNtuple(0);*/
	
	/*man->CreateNtuple("Hits","Hits");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("fX");
	man->CreateNtupleDColumn("fY");
	man->CreateNtupleDColumn("fZ");
	man->FinishNtuple(1);*/
	
	man->CreateNtuple("Scoring", "Scoring");
	man->CreateNtupleDColumn("fEdep");
	man->FinishNtuple(0);
	
	
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

void MyRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4cout<<"Num of Neutrons: "<<numneutron<<G4endl;
	G4cout<<"Num of gammas: "<<numgamma<<G4endl;
	G4cout<<"Num of e-: "<<numelectron<<G4endl;
	G4cout<<"Num of e+: "<<numpositron<<G4endl;
	G4cout<<"Num of nu_e: "<<numnu_e<<G4endl;
	G4cout<<"Num of anti_nu_e: "<<numanu_e<<G4endl;
	G4cout<<"Num of Others: "<<numother<<G4endl;
	
	man->Write();
	man->CloseFile();
}
