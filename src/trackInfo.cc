#include "trackInfo.hh"
#include "G4Exception.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<trackInformation> *aTrackInformationAllocator = 0;

trackInformation::trackInformation() : G4VUserTrackInformation()
{
  DecayID = -1;
  BranchID = -1;
  ParentBranchID = -1;
  DecayTime = -1.;
  origDecayTime = -1.;
  timeFromDecay = -1.;
  DecayParent = 0;
  creatorProcess = "Generator";
  trackEndTime = -1;
  AssignmentFlag = false;
  BranchName = 0;
}

trackInformation::trackInformation(const trackInformation *aTrackInfo)
{
  DecayID = aTrackInfo->DecayID;
  BranchID = aTrackInfo->BranchID;
  ParentBranchID = aTrackInfo->ParentBranchID;
  DecayTime = aTrackInfo->DecayTime;
  timeFromDecay = aTrackInfo->timeFromDecay;
  origDecayTime = aTrackInfo->origDecayTime;
  DecayParent = aTrackInfo->DecayParent;
  // trackEndTime = aTrackInfo->trackEndTime;
  AssignmentFlag = aTrackInfo->AssignmentFlag;
  BranchName = aTrackInfo->BranchName;
  creatorProcess = aTrackInfo->creatorProcess;
}

trackInformation::trackInformation(const G4Track *parentTrack,
                                   const G4Track *currentTrack, Type type)
    : G4VUserTrackInformation()
{
  if (type == Type::Init)
  {
    DecayID = -1;
    BranchID = currentTrack->GetTrackID();
    ParentBranchID = 0;
    DecayTime = -1;
    origDecayTime = -1;
    timeFromDecay = -1.;
    DecayParent = 0;
    trackEndTime = -1;
    BranchName = 0;
    AssignmentFlag = false;
    creatorProcess = "Generator";
  }
  else
  {
    trackInformation *aTrackInfo =
        (trackInformation *)(parentTrack->GetUserInformation());
    if (!aTrackInfo)
    {
      G4Exception("trackInformation::trackInformation", "TrackInfo001",
                  FatalException, "Parent track has no track information.");
    }

    // std::cout << "CurrTrackLocalTime: " << currentTrack->GetLocalTime() / ns
    //           << " ParentTrackLocalTime: " << parentTrack->GetLocalTime() /
    //           ns
    //           << std::endl;

    if (type == Type::Copy) // no new decay daughters created.
    {
      DecayID = aTrackInfo->DecayID;
      BranchID = aTrackInfo->BranchID;
      ParentBranchID = aTrackInfo->ParentBranchID;
      DecayTime = aTrackInfo->DecayTime;
      origDecayTime = aTrackInfo->origDecayTime;
      DecayParent = aTrackInfo->DecayParent;
      timeFromDecay =
          (currentTrack->GetLocalTime() + parentTrack->GetLocalTime()) / ns +
          aTrackInfo->timeFromDecay;
      // trackEndTime =
      //     (currentTrack->GetLocalTime() + parentTrack->GetLocalTime()) / ns;
      BranchName = aTrackInfo->BranchName;
      AssignmentFlag = aTrackInfo->AssignmentFlag;
      creatorProcess = aTrackInfo->creatorProcess;
    }
    else if (type == Type::Decay) // new decay has created daughters.
    {
      DecayID = aTrackInfo->DecayID + 1;
      BranchID = currentTrack->GetTrackID();
      ParentBranchID = aTrackInfo->BranchID;
      if (DecayID <= 1)
        DecayTime = parentTrack->GetLocalTime() / ms;
      else
        DecayTime = parentTrack->GetLocalTime() / ms + aTrackInfo->DecayTime;
      if (aTrackInfo->origDecayTime < 0.)
        origDecayTime = parentTrack->GetLocalTime() / s;
      else
        origDecayTime = aTrackInfo->origDecayTime;
      timeFromDecay = currentTrack->GetLocalTime() / ns;
      DecayParent = parentTrack->GetParticleDefinition();
      origDecayParent = parentTrack->GetParticleDefinition();
      // trackEndTime = (currentTrack->GetLocalTime()) / ns;
      AssignmentFlag = false;
      BranchName = currentTrack->GetParticleDefinition();
      creatorProcess = currentTrack->GetCreatorProcess()->GetProcessName();
    }
  }
}

trackInformation::~trackInformation() { ; }

void trackInformation::incrementDecayID() { DecayID += 1; }

void trackInformation::Print()
{
  G4cout << "----------------------------------------" << G4endl;
  G4cout << "DecayID        : " << DecayID << G4endl;
  G4cout << "BranchID       : " << BranchID << G4endl;
  G4cout << "ParentBranchID : " << ParentBranchID << G4endl;
  G4cout << "origDecayTime  : " << origDecayTime << " s" << G4endl;
  G4cout << "DecayTime      : " << DecayTime << " ms" << G4endl;
  G4cout << "CurrentTime    : " << timeFromDecay << " ns" << G4endl;
  G4cout << "DecayParent    : "
         << (DecayParent ? DecayParent->GetParticleName() : "None") << G4endl;
  // G4cout << "trackEndTime   : " << trackEndTime << " ns" << G4endl;
  G4cout << "BranchName   : "
         << (BranchName ? BranchName->GetParticleName() : "None") << G4endl;
  G4cout << "----------------------------------------" << G4endl;
}

int trackInformation::GetDecayID() { return DecayID; }
int trackInformation::GetBranchID() { return BranchID; }
int trackInformation::GetParentBranchID() { return ParentBranchID; }
double trackInformation::GetDecayTime() { return DecayTime; }
double trackInformation::GetTimeFromDecay() { return timeFromDecay; }
double trackInformation::GetOrigDecayTime() { return origDecayTime; }
const G4ParticleDefinition *trackInformation::GetDecayParent() const
{
  return DecayParent;
}
// double trackInformation::GetTrackEndTime() { return trackEndTime; }
const G4ParticleDefinition *trackInformation::GetBranch() { return BranchName; }
bool trackInformation::GetAssignmentFlag() { return AssignmentFlag; }

void trackInformation::SetBranchID(const G4Track *aTrack)
{
  BranchID = aTrack->GetTrackID();
  AssignmentFlag = true;
}

void trackInformation::SetBranch(const G4Track *aTrack)
{
  // BranchID = aTrack->GetTrackID();
  BranchName = aTrack->GetParticleDefinition();
  AssignmentFlag = true;
}

void trackInformation::SetDecayParent(const G4Track *aTrack)
{
  // BranchID = aTrack->GetTrackID();
  DecayParent = aTrack->GetParticleDefinition();
  AssignmentFlag = true;
}

void trackInformation::UpdateTrackEndTime(double TET) { trackEndTime = TET; }
