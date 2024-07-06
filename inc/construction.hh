/*This is the construction header file where we define the class, variables and functions required for the construction of the environment and the detector*/

// First we include all the necessary header files
#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4VSolid.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericMessenger.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

// Here we define the DetectorConstruction class and its variables and functions
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction(); // The constructor and destructor function of the class
	MyDetectorConstruction(char mat, std::string th);
	~MyDetectorConstruction();

	G4LogicalVolume *GetScoringVolume() const { return fScoringVolume; }

	// This is the Construct function of the type G4VPhysicalVolume which is used to construct the detector and environment with the required dimenstions and properties
	virtual G4VPhysicalVolume *Construct();

private:
	// Here we define three variables for the Size of the Environment, the size of the detector and the position of the detector inside the environment

	G4Box *solidWorld, *solidSheet;
	G4VSolid *detVol;
	G4LogicalVolume *logicWorld, *logicSheet, *logicdetVol;
	G4VPhysicalVolume *physWorld, *physSheet, *physdetVol;

	G4Material *worldMat, *myTolueneMat, *BoratedPE, *HDPE, *Lead, *Copper, *Vaccum, *Steel;
	G4Material *sheildMat;

	std::map<char, G4Material *>
		MatMap;
	std::vector<G4Material *> LogicArrangement;

	void DefineMaterials();

	virtual void ConstructSDandField();

	G4GenericMessenger *fMessenger;

	G4LogicalVolume *fScoringVolume;

	void ConstructSingleSheet();

	G4VSolid *ConstructShell(double xsz, double ysz, double zsz, double thickness, double offset);

	G4double xWorld, yWorld, zWorld, xloc, width;

	G4OpticalSurface *mirrorSurface;
};

#endif
