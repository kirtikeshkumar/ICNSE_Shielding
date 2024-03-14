/*This is the construction header file where we define the class, variables and functions required for the construction of the environment and the detector*/

//First we include all the necessary header files
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

//Here we define the DetectorConstruction class and its variables and functions
class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();//The constructor and destructor function of the class
	~MyDetectorConstruction();
	
	G4LogicalVolume *GetScoringVolume() const {return fScoringVolume;}
	
	//This is the Construct function of the type G4VPhysicalVolume which is used to construct the detector and environment with the required dimenstions and properties
	virtual G4VPhysicalVolume *Construct();
private:
//Here we define three variables for the Size of the Environment, the size of the detector and the position of the detector inside the environment
	
	G4Box *solidWorld;
	G4Box *detVol;
	G4LogicalVolume *logicWorld, *logicshell, *logicdetVol;
	G4VPhysicalVolume *physWorld, *physshell, *physdetVol;
	G4VPhysicalVolume *physshellMuVetoOut, *physshellHDPEOuter, *physshellBP, *physshellLead, *physshellHDPEInner, *physshellMuVetoIn, *physshellCuColdBox;
	G4LogicalVolume *logicshellMuVetoOut, *logicshellHDPEOuter, *logicshellBP, *logicshellLead, *logicshellHDPEInner, *logicshellMuVetoIn, *logicshellCuColdBox;
	G4VPhysicalVolume *physshell0,*physshell1,*physshell2,*physshell3,*physshell4,*physshell5,*physshell6,*physshell7;
	G4LogicalVolume *logicshell0, *logicshell1, *logicshell2, *logicshell3, *logicshell4, *logicshell5, *logicshell6, *logicshell7;
	G4VPhysicalVolume *physSteelPlate, *physUnderSideBP, *physUnderSideHDPE;
	G4LogicalVolume *logicSteelPlate, *logicUnderSideBP, *logicUnderSideHDPE;
	
	G4Material *worldMat, *myTolueneMat, *BoratedPE, *HDPE, *Lead, *Copper, *Vaccum, *Steel;
	

	void DefineMaterials();
	
	G4VSolid* ConstructShell(double xsz, double ysz, double zsz, double thickness, double offset);
	G4VSolid* SubtractBox(G4VSolid* sol, G4ThreeVector Boxsz, G4ThreeVector relPosSubVol);
	G4VSolid* SubtractBoxfrmShell(G4ThreeVector shellsz, double thickness, double offset, G4ThreeVector Boxsz, G4ThreeVector relPosSubVol);
	G4VSolid* SubtractBoxfrmShell(G4ThreeVector shellsz, double thickness, double offset, G4ThreeVector Boxsz);
	
	virtual void ConstructSDandField();
	
	G4GenericMessenger *fMessenger;
	
	G4LogicalVolume *fScoringVolume;
	
	void ConstructSetup();
	void ConstructSetupMod();
	void ConstructSetupV1();
	
	G4double xWorld,yWorld,zWorld,xloc;
	
	G4OpticalSurface *mirrorSurface;
};

#endif
