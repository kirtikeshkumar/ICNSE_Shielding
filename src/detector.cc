#include "detector.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
}

MySensitiveDetector::~MySensitiveDetector()
{
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	G4Track *track = aStep->GetTrack();
	track->SetTrackStatus(fStopAndKill);

	const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
	G4AnalysisManager *man = G4AnalysisManager::Instance();

	G4int copyNo = aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

	G4int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	G4String particleName = track->GetParticleDefinition()->GetParticleName();
	G4double particleKinEnergy = track->GetKineticEnergy();
	G4double particleTime = aStep->GetPreStepPoint()->GetGlobalTime();

	if (particleName == "neutron")
	{
		// fEventAction->AddNumNeutronEvt();
		//  G4cout<<"Neutron Total Energy: "<<particleTotEnergy<<G4endl;
		//  G4cout<<"Neutron Kinetic Energy: "<<particleKinEnergy<<G4endl;
		man->FillNtupleIColumn(1, 0, evID);
		man->FillNtupleDColumn(1, 2, particleKinEnergy);
		man->FillNtupleDColumn(1, 3, particleTime / ns);
		man->AddNtupleRow(1);
	}
	else if (particleName == "gamma")
	{
		// fEventAction->AddNumGammaEvt();
		//  G4cout<<"Gamma Total Energy: "<<particleTotEnergy<<G4endl;
		//  G4cout<<"Gamma Kinetic Energy: "<<particleKinEnergy<<G4endl;
		man->FillNtupleIColumn(0, 0, evID);
		man->FillNtupleDColumn(0, 2, particleKinEnergy);
		man->FillNtupleDColumn(0, 3, particleTime / ns);
		man->AddNtupleRow(0);
	}
	else if (particleName == "e-")
	{
		// fEventAction->AddNumElectronEvt();
		man->FillNtupleIColumn(4, 0, evID);
		man->FillNtupleDColumn(4, 2, particleKinEnergy);
		man->FillNtupleDColumn(4, 3, particleTime / ns);
		man->AddNtupleRow(4);
	}
	else if (particleName == "e+")
	{
		// fEventAction->AddNumPositronEvt();
		man->FillNtupleIColumn(5, 0, evID);
		man->FillNtupleDColumn(5, 2, particleKinEnergy);
		man->FillNtupleDColumn(5, 3, particleTime / ns);
		man->AddNtupleRow(5);
	}
	else if (particleName == "nu_e")
	{
		// fEventAction->AddNumNu_eEvt();
		man->FillNtupleIColumn(2, 0, evID);
		man->FillNtupleDColumn(2, 2, particleKinEnergy);
		man->FillNtupleDColumn(2, 3, particleTime / ns);
		man->AddNtupleRow(2);
	}
	else if (particleName == "anti_nu_e")
	{
		// fEventAction->AddNumaNu_eEvt();
		man->FillNtupleIColumn(3, 0, evID);
		man->FillNtupleDColumn(3, 2, particleKinEnergy);
		man->FillNtupleDColumn(3, 3, particleTime / ns);
		man->AddNtupleRow(3);
	}
	else
	{
		// fEventAction->AddNumOtherEvt();
	}
	return true;
}
