#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{

	G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	//G4bool IsEnter = step->GetPreStepPoint()->GetStepStatus() == fGeomBoundary;
	//G4bool IsKill = step->GetPostStepPoint()->GetStepStatus() == fGeomBoundary;
	
	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume(); //modify this, the pointer is null currently.
	
	G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
	if(copyNo == 8 and step->GetTrack()->GetParentID()==0){
	//if(volume == fScoringVolume){
		fEventAction->AddNum();
	}
	
	G4Track *track =step->GetTrack();
	G4String particleName = track->GetDefinition()->GetParticleName();

	if(copyNo==8){
		if(particleName=="neutron"){fEventAction->AddNumNeutron();}
		else if(particleName=="gamma"){fEventAction->AddNumGamma();}
		else if(particleName=="e-"){fEventAction->AddNumNeutron();}
		else if(particleName=="e+"){fEventAction->AddNumNeutron();}
		else if(particleName=="nu_e"){fEventAction->AddNumNeutron();}
		else if(particleName=="anti_nu_e"){fEventAction->AddNumNeutron();}
		else{fEventAction->AddNumOther();}
	}
	
	
	if(volume != fScoringVolume){
		return;
	}
	
	
	G4double edep = step->GetTotalEnergyDeposit();
	fEventAction->AddEdep(edep);
	/*
	 
	*/
	
}
