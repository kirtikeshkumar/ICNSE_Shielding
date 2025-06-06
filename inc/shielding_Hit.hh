#ifndef SHIELDING_HIT_HH
#define SHIELDING_HIT_HH

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
class shielding_Hit : public G4VHit {
public:
  shielding_Hit();
  void Set(double edep, G4ThreeVector location, int copynum, double tme,
           G4int parent);
  virtual ~shielding_Hit();
  void Print();
  int GetHitCopyNum();
  bool isHitPrimary();
  double GetHitTime();
  double GetHitEDep();
  G4ThreeVector GetHitLocation();
  double GetHitLocationX();
  double GetHitLocationY();
  double GetHitLocationZ();

private:
  double fEdep;
  G4ThreeVector fLocation;
  int fCopyNum;
  double fTime;
  G4int fparent;
};

#endif
