#include "shielding_Hit.h"
#include <iostream>
shielding_Hit::shielding_Hit():fEdep(0.),fLocation(G4ThreeVector(0.,0.,0.)),fCopyNum(0),fTime(0) {}

shielding_Hit::~shielding_Hit() {}

void shielding_Hit::Set(double edep, G4ThreeVector location, int copynum, double tme)
{
  //std::cout <<"@@@@@@@@@@@@@ INSIDE SET @@@@@@@@@@@@@@" << std::endl;
  fEdep     = edep;
  fLocation = location;
  fCopyNum  = copynum;
  fTime     = tme;
}
