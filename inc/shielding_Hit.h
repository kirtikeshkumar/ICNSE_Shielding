#ifndef SHIELDING_HIT_HH
#define SHIELDING_HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
class shielding_Hit : public G4VHit {

public:
double fEdep;
G4ThreeVector fLocation;
int fCopyNum;
double fTime;


public:
    shielding_Hit();
    void Set(double edep, G4ThreeVector location, int copynum, double tme);
    virtual ~shielding_Hit();
    void Print(){
std::cout <<fEdep <<" : " << fLocation <<" : " << fCopyNum <<" : " << fTime << std::endl;
}
    
};

#endif
