#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{

	G4AnalysisManager *man = G4AnalysisManager::Instance();
	
	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	//G4bool IsEnter = step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary;
	//G4bool IsKill = step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary;
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume(); //modify this, the pointer is null currently.
	
	G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
	/*if(copyNo == 8 and step->GetTrack()->GetParentID()==0){
		fEventAction->AddNum();
	}*/
	
	G4Track *track =step->GetTrack();
	G4String particleName = track->GetDefinition()->GetParticleName();

	//G4double particleTotEnergy = track->GetTotalEnergy();
	G4double particleKinEnergy = track->GetKineticEnergy();
	
	if(copyNo==8){
		if(particleName=="neutron"){
			fEventAction->AddNumNeutronEvt();
			//G4cout<<"Neutron Total Energy: "<<particleTotEnergy<<G4endl;
			//G4cout<<"Neutron Kinetic Energy: "<<particleKinEnergy<<G4endl;
			man->FillNtupleDColumn(1, 2, particleKinEnergy);
		}
		else if(particleName=="gamma"){
			fEventAction->AddNumGammaEvt();
			//G4cout<<"Gamma Total Energy: "<<particleTotEnergy<<G4endl;
			//G4cout<<"Gamma Kinetic Energy: "<<particleKinEnergy<<G4endl;
			man->FillNtupleDColumn(0, 2, particleKinEnergy);
		}
		else if(particleName=="e-"){
			fEventAction->AddNumElectronEvt();
			man->FillNtupleDColumn(4, 2, particleKinEnergy);
		}
		else if(particleName=="e+"){
			fEventAction->AddNumPositronEvt();	
			man->FillNtupleDColumn(5, 2, particleKinEnergy);
		}
		else if(particleName=="nu_e"){
			fEventAction->AddNumNu_eEvt();
			man->FillNtupleDColumn(2, 2, particleKinEnergy);
		}
		else if(particleName=="anti_nu_e"){
			fEventAction->AddNumaNu_eEvt();
			man->FillNtupleDColumn(3, 2, particleKinEnergy);
		}
		else{fEventAction->AddNumOtherEvt();}
	}
	
	
	if(volume != fScoringVolume){
		return;
	}
	
	
	G4double edep = step->GetTotalEnergyDeposit();
	fEventAction->AddEdep(edep);
	/*
	 
	*/
	
}
