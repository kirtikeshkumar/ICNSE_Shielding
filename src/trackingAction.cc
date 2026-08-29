#include "trackingAction.hh"
#include "trackInfo.hh"

#include "G4TrackingManager.hh"
#include "G4Track.hh"

trackingAction::trackingAction()
    : G4UserTrackingAction()
{
    ;
}

void trackingAction::PreUserTrackingAction(const G4Track *aTrack)
{
    if (aTrack->GetParentID() == 0)
    {
        auto *info = new trackInformation(
            nullptr,
            aTrack,
            trackInformation::Type::Init);

        fpTrackingManager->SetUserTrackInformation(info);
    }
}

void trackingAction::PostUserTrackingAction(
    const G4Track *originalTrack)
{
    G4TrackVector *secondaries = fpTrackingManager->GimmeSecondaries();

    if (!secondaries)
        return;

    for (auto *secondary : *secondaries)
    {
        const G4VProcess *creator = secondary->GetCreatorProcess();

        if (creator && creator->GetProcessName() == "RadioactiveDecay")
        {
            secondary->SetUserInformation(
                new trackInformation(
                    originalTrack,
                    secondary,
                    trackInformation::Type::Decay));
        }
        else
        {
            secondary->SetUserInformation(
                new trackInformation(
                    originalTrack,
                    secondary));
        }
    }
}