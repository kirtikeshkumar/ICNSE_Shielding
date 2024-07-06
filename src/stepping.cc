#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction)
{
	fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction()
{
}

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
	G4int evID = fEventAction->GetEvID();

	G4AnalysisManager *man = G4AnalysisManager::Instance();

	/*G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

	const MyDetectorConstruction *detectorConstruction = static_cast<const MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

	G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume(); //modify this, the pointer is null currently.
	*/
	G4int copyNo = step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

	G4Track *track = step->GetTrack();
	G4String particleName = track->GetParticleDefinition()->GetParticleName();

	/*if(copyNo == 0 and step->GetTrack()->GetTrackID()==1){			//to check for primary neutrons
		fEventAction->AddNum();
	}*/

	if (copyNo == 0)
	{
		G4cout << "Particle " << particleName << " has entered in event " << evID << G4endl;
		// if(particleName=="neutron" and track->GetTrackID()==1){G4cout<<"This was a primary neutron"<<G4endl;}
		// if (particleName == "neutron")
		// {

		// 	G4ThreeVector vertpos = track->GetVertexPosition();
		// 	G4cout << "TrackID: " << track->GetTrackID() << G4endl;
		// 	G4cout << "ParentID: " << track->GetParentID() << G4endl;
		// 	G4cout << "Created at: " << vertpos[0] << ", " << vertpos[1] << ", " << vertpos[2] << G4endl;
		// 	// G4cout<<"Created by: "<<track->GetCreatorProcess()->GetProcessName()<<G4endl;
		// }
	}

	if (copyNo == 0)
	{
		if (particleName == "neutron")
		{
			fEventAction->AddNumNeutronEvt();
		}
		else if (particleName == "gamma")
		{
			fEventAction->AddNumGammaEvt();
		}
		else if (particleName == "e-")
		{
			fEventAction->AddNumElectronEvt();
		}
		else if (particleName == "e+")
		{
			fEventAction->AddNumPositronEvt();
		}
		else if (particleName == "nu_e")
		{
			fEventAction->AddNumNu_eEvt();
		}
		else if (particleName == "anti_nu_e")
		{
			fEventAction->AddNumaNu_eEvt();
		}
		else
		{
			fEventAction->AddNumOtherEvt();
		}
	}
}
