#include "shielding_Hit.hh"
#include <iostream>
shielding_Hit::shielding_Hit()
    : fEdep(0.), fLocation(G4ThreeVector(0., 0., 0.)), fCopyNum(0), fTime(0) {}

shielding_Hit::~shielding_Hit() {}

void shielding_Hit::Set(double edep, G4ThreeVector location, int copynum,
                        double tme, G4int parent) {
  // std::cout <<"@@@@@@@@@@@@@ INSIDE SET @@@@@@@@@@@@@@" << std::endl;
  fEdep = edep;
  fLocation = location;
  fCopyNum = copynum;
  fTime = tme;
  fparent = parent;
}

void shielding_Hit::Print() {
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