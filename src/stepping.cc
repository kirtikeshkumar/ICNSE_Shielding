#include "stepping.hh"

MySteppingAction::MySteppingAction(MyEventAction *eventAction) {
  fEventAction = eventAction;
}

MySteppingAction::~MySteppingAction() {}

void MySteppingAction::UserSteppingAction(const G4Step *step) {
  G4int evID = fEventAction->GetEvID();

  G4AnalysisManager *man = G4AnalysisManager::Instance();

  const std::vector<const G4Track *> *secondaries =
      step->GetSecondaryInCurrentStep();
  //   G4Track *track = step->GetTrack();
  //   G4String pname = track->GetDefinition()->GetParticleName();
  //   G4double Ek = track->GetKineticEnergy() / keV;
  //   G4ThreeVector pos = track->GetPosition();
  //   std::cout << pname << " with Energy: " << Ek
  //             << " keV tracked in event: " << evID << " at position: " << pos
  //             << std::endl;
  if (secondaries && !secondaries->empty()) {
    G4int nsec = secondaries->size();
    for (G4int i = 0; i < nsec; ++i) {
      //       std::cout << nsec << "secondaries generated at "
      //                 << step->GetPreStepPoint()->GetGlobalTime() / s <<
      //                 std::endl;
      const G4Track *tr = (*secondaries)[i];
      if (!tr)
        continue;
      G4String pname = tr->GetDefinition()->GetParticleName();
      G4double Ek = tr->GetKineticEnergy() / keV;
      G4ThreeVector pos = tr->GetPosition();
      G4int parentID = tr->GetParentID();
      G4String creator = "unknown";
      if (tr->GetCreatorProcess())
        creator = tr->GetCreatorProcess()->GetProcessName();

      //       std::cout << pname << " with Energy: " << Ek
      //                 << " keV tracked in event: " << evID << " at position:
      //                 " << pos
      //                 << std::endl;

      // Optionally filter to radioactivity-created secondaries
      if (creator == "RadioactiveDecay" || creator == "Decay") {
        // Put appropriate columns / ntuple index per your ntuple layout:
        man->FillNtupleIColumn(8, 0, evID);
        man->FillNtupleSColumn(8, 1, pname);
        man->FillNtupleDColumn(8, 2, Ek);
        man->FillNtupleDColumn(8, 3, pos.x());
        man->FillNtupleDColumn(8, 4, pos.y());
        man->FillNtupleDColumn(8, 5, pos.z());
        man->AddNtupleRow(8);
        // std::cout << pname << " with Energy: " << Ek
        //           << " keV generated in Pb210 Decay in event: " << evID
        //           << " at position: " << pos << std::endl;
      }
    }
  }

  //   G4AnalysisManager *man = G4AnalysisManager::Instance();

  /*G4LogicalVolume *volume =
  step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  const MyDetectorConstruction *detectorConstruction = static_cast<const
  MyDetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

  G4LogicalVolume *fScoringVolume = detectorConstruction->GetScoringVolume();
  //modify this, the pointer is null currently.
  */
  //   G4int copyNo =
  //   step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

  //   G4Track *track = step->GetTrack();
  //   G4String particleName =
  //   track->GetParticleDefinition()->GetParticleName();

  /*if(copyNo == 0 and step->GetTrack()->GetTrackID()==1){
  //to check for primary neutrons fEventAction->AddNum();
  }*/

  /*
  // if (copyNo == 0)
  // {
  // 	G4cout << "Particle " << particleName << " has entered in event " <<
  // evID << G4endl;
  // 	// if(particleName=="neutron" and track->GetTrackID()==1){G4cout<<"This
  // was a primary neutron"<<G4endl;}
  // 	// if (particleName == "neutron")
  // 	// {

  // 	// 	G4ThreeVector vertpos = track->GetVertexPosition();
  // 	// 	G4cout << "TrackID: " << track->GetTrackID() << G4endl;
  // 	// 	G4cout << "ParentID: " << track->GetParentID() << G4endl;
  // 	// 	G4cout << "Created at: " << vertpos[0] << ", " << vertpos[1] <<
  // ", " << vertpos[2] << G4endl;
  // 	// 	// G4cout<<"Created by:
  // "<<track->GetCreatorProcess()->GetProcessName()<<G4endl;
  // 	// }
  // }
  */

  /*if (copyNo == 0) {
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
}*/
}
