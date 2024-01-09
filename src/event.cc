#include "event.hh"

MyEventAction::MyEventAction(MyRunAction* run)
{
	fRun = run;
	fEdep = 0.;
	num=0;
}	

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event* anEvent)
{
	num=0;
	numgamma_evt=0;
	numneutron_evt=0;
	numelectron_evt=0;
	numpositron_evt=0;
	numnu_e_evt=0;
	numanu_e_evt=0;
	numother_evt=0;
	fEdep = 0.;
	G4int evID = anEvent->GetEventID();
	if(evID%10000==0){
		G4cout<<"event: "<<evID<<G4endl;
	}
}

void MyEventAction::EndOfEventAction(const G4Event* anEvent)
{
	/*if((fEdep-0.0)<=1E-9){
		G4cout << "Energy deposition: "<< fEdep << G4endl;
	}*/
	
	G4int evID = anEvent->GetEventID();
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	AddNumNeutron(numneutron_evt);
	AddNumGamma(numgamma_evt);
	AddNumElectron(numelectron_evt);
	AddNumPositron(numpositron_evt);
	AddNumNu_e(numnu_e_evt);
	AddNumaNu_e(numanu_e_evt);
	AddNumOther(numother_evt);
	
	if(numneutron_evt != 0 or numgamma_evt !=0){
		//fill gamma details
		man->FillNtupleIColumn(0, 0, evID);
		man->FillNtupleIColumn(0, 1, numgamma_evt);
		man->AddNtupleRow(0);
		
		//fill neutron details
		man->FillNtupleIColumn(1, 0, evID);
		man->FillNtupleIColumn(1, 1, numneutron_evt);
		man->AddNtupleRow(1);
		
	}
	
	if(evID % 1000000 ==0){
		fRun->PrintStatus();
	}
	
	
	
	if(num!=0){
		G4cout << "Number of Particles in Event: "<< evID << " is "<< num << G4endl;
	}
	//man->FillNtupleDColumn(0, 0, fEdep);
	
	//man->AddNtupleRow(0);
	
	
}
