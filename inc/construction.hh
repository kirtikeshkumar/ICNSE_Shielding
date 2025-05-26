/*This is the construction header file where we define the class, variables and
 * functions required for the construction of the environment and the detector*/

// First we include all the necessary header files
#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4Box.hh"
#include "G4GenericMessenger.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4OpticalSurface.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSolid.hh"
#include "G4VUserDetectorConstruction.hh"

#include <sstream>
#include <string>

// Here we define the DetectorConstruction class and its variables and functions
class MyDetectorConstruction : public G4VUserDetectorConstruction {
public:
  MyDetectorConstruction(); // The constructor and destructor function of the
                            // class
  MyDetectorConstruction(std::string mat, std::string th);
  ~MyDetectorConstruction();

  G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

  // This is the Construct function of the type G4VPhysicalVolume which is used
  // to construct the detector and environment with the required dimenstions and
  // properties
  virtual G4VPhysicalVolume *Construct();

private:
  // Here we define three variables for the Size of the Environment, the size of
  // the detector and the position of the detector inside the environment

  G4Box *solidWorld, *solid;
  std::vector<G4Box *> solidSheet;
  G4VSolid *detVol;
  G4LogicalVolume *logicWorld, *logicdetVol, *logic, *logicHPGe, *logicNaI;
  std::vector<G4LogicalVolume *> logicSheet;
  G4VPhysicalVolume *physWorld, *physdetVol, *phys;
  std::vector<G4VPhysicalVolume *> physSheet, physHPGe, physNaI;

  G4Material *worldMat, *myTolueneMat, *BoratedPE, *HDPE, *Lead, *Copper,
      *Vaccum, *Steel, *Germanium, *NaI;
  G4Material *sheildMat;

  std::map<G4String, G4Material *> MatMap;
  std::vector<G4Material *> LogicArrangement;

  void DefineMaterials();

  virtual void ConstructSDandField();

  G4GenericMessenger *fMessenger;

  G4LogicalVolume *fScoringVolume;

  void ConstructSingleSheet();
  void ConstructHPGeSetup();
  G4LogicalVolume *ConstructHPGe();
  G4LogicalVolume *ConstructNaI();

  G4VSolid *ConstructShell(double xsz, double ysz, double zsz, double thickness,
                           double offset);

  G4double xWorld, yWorld, zWorld, xloc, netWidth;
  std::vector<float> width;
  std::vector<G4String> shieldMats;

  G4String shieldmats, wdth;
  int ConfigNum;

  G4OpticalSurface *mirrorSurface;
};

#endif
