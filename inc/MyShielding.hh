#include "G4SystemOfUnits.hh"
#include "Shielding.hh"

class MyShielding : public Shielding {
public:
  MyShielding() : Shielding() {}

  void SetCuts() override;
};