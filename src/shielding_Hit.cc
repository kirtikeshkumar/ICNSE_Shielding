#include "shielding_Hit.hh"
#include <G4String.hh>
#include <iostream>
shielding_Hit::shielding_Hit()
    : fEdep(0.), fLocation(G4ThreeVector(0., 0., 0.)), fCopyNum(0), fTime(0) {}

shielding_Hit::~shielding_Hit() {}

void shielding_Hit::Set(double edep, G4ThreeVector location, int copynum,
                        double tme, G4int parent, G4String part,
                        G4String proc)
{
  // std::cout <<"@@@@@@@@@@@@@ INSIDE SET @@@@@@@@@@@@@@" << std::endl;
  fEdep = edep;
  fLocation = location;
  fCopyNum = copynum;
  fTime = tme;
  fparent = parent;
  fparticle = part;
  fprocess = proc;
}

void shielding_Hit::Print()
{
  std::cout << fEdep << " : " << fLocation << " : " << fCopyNum << " : "
            << fTime << std::endl;
}

int shielding_Hit::GetHitCopyNum() { return fCopyNum; }
bool shielding_Hit::isHitPrimary() { return (fparent == 0); }
double shielding_Hit::GetHitTime() { return fTime; }
double shielding_Hit::GetHitEDep() { return fEdep; }
G4ThreeVector shielding_Hit::GetHitLocation() { return fLocation; }
double shielding_Hit::GetHitLocationX() { return fLocation.x(); }
double shielding_Hit::GetHitLocationY() { return fLocation.y(); }
double shielding_Hit::GetHitLocationZ() { return fLocation.z(); }
G4String shielding_Hit::GetParticleName() { return fparticle; }
G4String shielding_Hit::GetDepositionProcess() { return fprocess; }

#ifdef SETUP_DECAY
void shielding_Hit::Set(double edep, int copynum, int branchID, int parentBranch, double depTime, double decayTime, G4String parent, G4String branch)
{
  fEdep = edep;
  fCopyNum = copynum;
  fBranchID = branchID;
  fParentBranchID = parentBranch;
  fTime = depTime;
  fDecayTime = decayTime;
  fDecayParent = parent;
  fBranch = branch;
}

int shielding_Hit::GetHitBranchID() { return fBranchID; }
G4String shielding_Hit::GetHitBranchName() { return fBranch; }
int shielding_Hit::GetHitParentBranchID() { return fParentBranchID; }
double shielding_Hit::GetDecayTime() { return fDecayTime; }
G4String shielding_Hit::GetDecayParticle() { return fDecayParent; }
#endif