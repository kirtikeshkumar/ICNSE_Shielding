#include "trackInfo.hh"
#include "G4Exception.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal G4Allocator<trackInformation> *
    aTrackInformationAllocator = 0;

trackInformation::trackInformation()
    : G4VUserTrackInformation()
{
    DecayID = -1;
    BranchID = -1;
    ParentBranchID = -1;
    DecayTime = -1.;
    origDecayTime = -1;
    DecayParent = 0;
}

trackInformation::trackInformation(const trackInformation *aTrackInfo)
{
    DecayID = aTrackInfo->DecayID;
    BranchID = aTrackInfo->BranchID;
    ParentBranchID = aTrackInfo->ParentBranchID;
    DecayTime = aTrackInfo->DecayTime;
    origDecayTime = aTrackInfo->origDecayTime;
    DecayParent = aTrackInfo->DecayParent;
}

trackInformation::trackInformation(const G4Track *parentTrack, const G4Track *currentTrack, Type type) : G4VUserTrackInformation()
{
    if (type == Type::Init)
    {
        DecayID = -1;
        BranchID = currentTrack->GetTrackID();
        ParentBranchID = 0;
        DecayTime = -1;
        origDecayTime = -1;
        DecayParent = 0;
    }
    else
    {
        trackInformation *aTrackInfo = (trackInformation *)(parentTrack->GetUserInformation());
        if (!aTrackInfo)
        {
            G4Exception(
                "trackInformation::trackInformation",
                "TrackInfo001",
                FatalException,
                "Parent track has no track information.");
        }

        if (type == Type::Copy) // no new decay daughters created.
        {
            DecayID = aTrackInfo->DecayID;
            BranchID = aTrackInfo->BranchID;
            ParentBranchID = aTrackInfo->ParentBranchID;
            DecayTime = aTrackInfo->DecayTime;
            origDecayTime = aTrackInfo->origDecayTime;
            DecayParent = aTrackInfo->DecayParent;
        }
        else if (type == Type::Decay) // new decay has created daughters.
        {
            DecayID = aTrackInfo->DecayID + 1;
            BranchID = currentTrack->GetTrackID();
            ParentBranchID = aTrackInfo->BranchID;
            DecayTime = parentTrack->GetGlobalTime();
            if (aTrackInfo->origDecayTime < 0.)
                origDecayTime = DecayTime;
            else
                origDecayTime = aTrackInfo->origDecayTime;
            DecayParent = parentTrack->GetParticleDefinition();
        }
    }
}

trackInformation::~trackInformation()
{
    ;
}

void trackInformation::incrementDecayID() { DecayID += 1; }

int trackInformation::GetDecayID() { return DecayID; }
int trackInformation::GetBranchID() { return BranchID; }
int trackInformation::GetParentBranchID() { return ParentBranchID; }
double trackInformation::GetDecayTime() { return DecayTime; }
double trackInformation::GetOrigDecayTime() { return origDecayTime; }
const G4ParticleDefinition *trackInformation::GetDecayParent() const { return DecayParent; }
