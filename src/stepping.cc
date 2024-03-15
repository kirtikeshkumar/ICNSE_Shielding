#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4int evID = fEventAction->GetEvID();

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	/*G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume(); //modify this, the pointer is null currently.
	*/
	G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
	
	G4Track *track =step->GetTrack();
	G4String particleName = track->GetParticleDefinition()->GetParticleName();
	
	/*if(copyNo == 0 and step->GetTrack()->GetTrackID()==1){			//to check for primary neutrons 
		fEventAction->AddNum();
	}*/
	
	if(copyNo == 0){
		G4cout<<"Particle "<<particleName<<" has entered in event "<<evID<<G4endl;
		//if(particleName=="neutron" and track->GetTrackID()==1){G4cout<<"This was a primary neutron"<<G4endl;}
		if(particleName=="neutron"){
			G4ThreeVector vertpos=track->GetVertexPosition();
			G4cout<<"TrackID: "<<track->GetTrackID()<<G4endl;
			G4cout<<"ParentID: "<<track->GetParentID()<<G4endl;
			G4cout<<"Created at: "<<vertpos[0]<<", "<<vertpos[1]<<", "<<vertpos[2]<<G4endl;
			G4cout<<"Created by: "<<track->GetCreatorProcess()<<G4endl;
		}
	}
	
	

	//G4double particleTotEnergy = track->GetTotalEnergy();
	G4double particleKinEnergy = track->GetKineticEnergy();
	G4double particleTime = step->GetPreStepPoint()->GetGlobalTime();
	
	if(copyNo==0){
		if(particleName=="neutron"){
			fEventAction->AddNumNeutronEvt();
			//G4cout<<"Neutron Total Energy: "<<particleTotEnergy<<G4endl;
			//G4cout<<"Neutron Kinetic Energy: "<<particleKinEnergy<<G4endl;
			man->FillNtupleIColumn(1, 0, evID);
			man->FillNtupleDColumn(1, 2, particleKinEnergy);
			man->FillNtupleDColumn(1, 3, particleTime/ns);
			man->AddNtupleRow(1);
		}
		else if(particleName=="gamma"){
			fEventAction->AddNumGammaEvt();
			//G4cout<<"Gamma Total Energy: "<<particleTotEnergy<<G4endl;
			//G4cout<<"Gamma Kinetic Energy: "<<particleKinEnergy<<G4endl;
			man->FillNtupleIColumn(0, 0, evID);
			man->FillNtupleDColumn(0, 2, particleKinEnergy);
			man->FillNtupleDColumn(0, 3, particleTime/ns);
			man->AddNtupleRow(0);
		}
		else if(particleName=="e-"){
			fEventAction->AddNumElectronEvt();
			man->FillNtupleIColumn(4, 0, evID);
			man->FillNtupleDColumn(4, 2, particleKinEnergy);
			man->FillNtupleDColumn(4, 3, particleTime/ns);
			man->AddNtupleRow(4);
		}
		else if(particleName=="e+"){
			fEventAction->AddNumPositronEvt();	
			man->FillNtupleIColumn(5, 0, evID);
			man->FillNtupleDColumn(5, 2, particleKinEnergy);
			man->FillNtupleDColumn(5, 3, particleTime/ns);
			man->AddNtupleRow(5);
		}
		else if(particleName=="nu_e"){
			fEventAction->AddNumNu_eEvt();
			man->FillNtupleIColumn(2, 0, evID);
			man->FillNtupleDColumn(2, 2, particleKinEnergy);
			man->FillNtupleDColumn(2, 3, particleTime/ns);
			man->AddNtupleRow(2);
		}
		else if(particleName=="anti_nu_e"){
			fEventAction->AddNumaNu_eEvt();
			man->FillNtupleIColumn(3, 0, evID);
			man->FillNtupleDColumn(3, 2, particleKinEnergy);
			man->FillNtupleDColumn(3, 3, particleTime/ns);
			man->AddNtupleRow(3);
		}
		else{fEventAction->AddNumOtherEvt();}
	}
	
	/*if(volume != fScoringVolume){
		return;
	}*/
	/*G4double edep = step->GetTotalEnergyDeposit();
	fEventAction->AddEdep(edep);*/
	/*
	 
	*/
	
}
