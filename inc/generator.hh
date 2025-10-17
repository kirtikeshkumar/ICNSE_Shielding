/*In this header file we define the required functions for the generator file*/

/*First we include all the required header files like G4ParticleGun and
 * G4SystemOfUnits*/
#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4AffineTransform.hh"
#include "G4AnalysisManager.hh"
#include "G4Geantino.hh"
#include "G4GeneralParticleSource.hh"
#include "G4IonTable.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VSolid.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4VoxelLimits.hh"
#include "Randomize.hh"
#include "construction.hh"
#include <G4ThreeVector.hh>

/*We define the PrimaryGenerator class which will be used to construct our
 * ParticleGun*/

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction {
public:
  MyPrimaryGenerator();
  MyPrimaryGenerator(MyDetectorConstruction *det);
  ~MyPrimaryGenerator();

  /*GeneratePrimaries function to generate the particle we desire*/
  virtual void GeneratePrimaries(G4Event *anEvent);

private:
  G4GeneralParticleSource *fParticleSource;
  MyDetectorConstruction *fDetector;
  G4ParticleGun *fParticleGun;
  G4ThreeVector generatePointInShell(G4ThreeVector halfLength,
                                     G4double thickness);
};

#endif
