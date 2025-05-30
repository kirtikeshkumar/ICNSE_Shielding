#include "MyShielding.hh"

void MyShielding::SetCuts() {
  // Define your production cuts here
  G4double cutForGamma = 0.1 * mm; // e.g., 10 microns
  G4double cutForElectron = 0.1 * mm;
  G4double cutForPositron = 0.1 * mm;

  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");

  // Optionally call the base class for default behavior
  Shielding::SetCuts();
}
