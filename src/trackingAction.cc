#include "trackingAction.hh"
#include "trackInfo.hh"

#include "G4Track.hh"
#include "G4TrackingManager.hh"

trackingAction::trackingAction() : G4UserTrackingAction() { ; }

void trackingAction::PreUserTrackingAction(const G4Track *aTrack)
{
  //   G4cout << "START TRACK: "
  //          << aTrack->GetParticleDefinition()->GetParticleName()
  //          << " TrackID = " << aTrack->GetTrackID()
  //          << " ParentID = " << aTrack->GetParentID() << G4endl;
  if (!(static_cast<trackInformation *>(aTrack->GetUserInformation())))
  {
    auto *info =
        new trackInformation(nullptr, aTrack, trackInformation::Type::Init);

    fpTrackingManager->SetUserTrackInformation(info);
  }
  if (!(static_cast<trackInformation *>(aTrack->GetUserInformation())
            ->GetAssignmentFlag()))
  {
    static_cast<trackInformation *>(aTrack->GetUserInformation())
        ->SetBranchID(aTrack);
  }
  if (!(static_cast<trackInformation *>(aTrack->GetUserInformation())->GetBranch()))
  {
    (static_cast<trackInformation *>(aTrack->GetUserInformation()))->SetBranch(aTrack);
  }
  if (!(static_cast<trackInformation *>(aTrack->GetUserInformation())->GetDecayParent()))
  {
    (static_cast<trackInformation *>(aTrack->GetUserInformation()))->SetDecayParent(aTrack);
  }
}

void trackingAction::PostUserTrackingAction(const G4Track *originalTrack)
{
  G4TrackVector *secondaries = fpTrackingManager->GimmeSecondaries();

  auto *info =
      static_cast<trackInformation *>(originalTrack->GetUserInformation());

  //   if (info)
  //     info->UpdateTrackEndTime(originalTrack->GetGlobalTime() / s);

  // std::cout << "\n\n";
  // std::cout << "#########################################################"
  //           << std::endl;
  // std::cout << "--------------------ORIGINAL TRACK-----------------------"
  //           << std::endl;
  // std::cout << "#########################################################"
  //           << std::endl;
  // std::cout << "TrackID = " << originalTrack->GetTrackID() << " Particle ="
  //           << originalTrack->GetParticleDefinition()->GetParticleName()
  //           << std::endl;
  // info->Print();

  if (!secondaries)
    return;

  for (auto *secondary : *secondaries)
  {
    const G4VProcess *creator = secondary->GetCreatorProcess();

    // if (creator)
    //   std::cout << creator->GetProcessName() << std::endl;

    if (creator && (creator->GetProcessName() == "RadioactiveDecay" ||
                    creator->GetProcessName() == "Radioactivation"))
    {
      secondary->SetUserInformation(new trackInformation(
          originalTrack, secondary, trackInformation::Type::Decay));
      G4AnalysisManager *man = G4AnalysisManager::Instance();
      int evID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
      G4ThreeVector location = originalTrack->GetPosition();
#ifdef USE_CRY
      man->FillNtupleIColumn(3, 0, evID);
      G4String decaypartname = originalTrack->GetParticleDefinition() ? originalTrack->GetParticleDefinition()->GetParticleName() : "Primary";
      man->FillNtupleSColumn(3, 1, decaypartname);
      man->FillNtupleDColumn(3, 2, location.x());
      man->FillNtupleDColumn(3, 3, location.y());
      man->FillNtupleDColumn(3, 4, location.z());
      // man->FillNtupleSColumn(3, 5, secondary->GetCreatorProcess()->GetProcessName());
      man->AddNtupleRow(3);
#endif
    }
    else
    {
      secondary->SetUserInformation(
          new trackInformation(originalTrack, secondary));
    }

    // std::cout << "#########################################################"
    //           << std::endl;
    // std::cout << "--------------------SECONDARY TRACK----------------------"
    //           << std::endl;
    // std::cout << "#########################################################"
    //           << std::endl;
    // std::cout << "Secondary TrackID = " << secondary->GetTrackID()
    //           << " ParentID = " << secondary->GetParentID() << " Particle = "
    //           << secondary->GetParticleDefinition()->GetParticleName()
    //           << std::endl;
    // static_cast<trackInformation
    // *>(secondary->GetUserInformation())->Print();
  }
}