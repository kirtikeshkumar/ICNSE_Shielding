/*
// This class is defined to keep track of the decay chains.
// Each decay particle is tracked as a seperate branch.
// Decay chains are tracked using DecayID.
// This does not handle spontaneous fission decays properly
*/

#ifndef TRACKINFO_HH
#define TRACKINFO_HH

#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Track.hh"
#include "G4Allocator.hh"
#include "G4VUserTrackInformation.hh"

class trackInformation : public G4VUserTrackInformation
{
public:
    // Defines how the track information is initialized
    enum class Type
    {
        Init, // Primary track / beginning of a decay chain
        Copy, // Ordinary secondary: inherit parent information
        Decay // Daughter produced by radioactive decay
    };

    trackInformation();
    trackInformation(const G4Track *parentTrack, const G4Track *currentTrack, Type type = Type::Copy);
    trackInformation(const trackInformation *aTrackInfo);
    virtual ~trackInformation();

    inline void *operator new(size_t);                          // this defines how the "new" operator will allocate memory for pointers of this type
    inline void operator delete(void *aTrackInfo);              // this defines how the "delete" operator will clear memory for pointers of this type
    trackInformation &operator=(const trackInformation &right); // this defines the behaviour of the "=" operator

    void incrementDecayID();
    void incrementBranchID();
    void SetBranchID(const G4Track *aTrack);
    void Print();

    int GetDecayID();
    int GetBranchID();
    int GetParentBranchID();
    double GetDecayTime();
    double GetOrigDecayTime();
    const G4ParticleDefinition *GetDecayParent() const;
    double GetTrackEndTime();
    const G4ParticleDefinition *GetBranch();
    bool GetAssignmentFlag();

    void UpdateTrackEndTime(double TET);

private:
    // following are to be shared to all daughters
    int DecayID;                             // Identifies if it is primary particle decay or any chain decay
    int BranchID;                            // Identifies which branch of the decay the present track corresponds to
    int ParentBranchID;                      // Identifies the BranchID of parent for tracking decay chains
    double origDecayTime;                    // The time of first decaying nucleii
    double DecayTime;                        // The time of decay
    const G4ParticleDefinition *DecayParent; // The decaying particle
    double trackEndTime;                     // End Time of track. For Energy deposition tracking purposes.
    bool AssignmentFlag;                     // To ensure proper branch and parent id assignments
    const G4ParticleDefinition *BranchName;
};

extern G4ThreadLocal
    G4Allocator<trackInformation> *aTrackInformationAllocator; // the allocator maintains a pool memory. it is useful if something is created and deleted multiple times

inline void *trackInformation::operator new(size_t)
{
    if (!aTrackInformationAllocator)
        aTrackInformationAllocator = new G4Allocator<trackInformation>;
    return (void *)aTrackInformationAllocator->MallocSingle();
}

inline void trackInformation::operator delete(void *aTrackInfo)
{
    aTrackInformationAllocator->FreeSingle((trackInformation *)aTrackInfo);
}

#endif
