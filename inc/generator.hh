/*In this header file we define the required functions for the generator file*/

/*First we include all the required header files like G4ParticleGun and
 * G4SystemOfUnits*/
#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"

#include "G4Geantino.hh"
#include "G4GenericMessenger.hh"
#include "G4IonTable.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RandomTools.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"
#include <fstream>
#include <iostream>
#include "construction.hh"

#ifdef USE_CRY
#include "CRYGenerator.h"
#include "CRYParticle.h"
#include "CRYSetup.h"
#endif
/*We define the PrimaryGenerator class which will be used to construct our
 * ParticleGun*/

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
public:
  MyPrimaryGenerator();
  MyPrimaryGenerator(MyDetectorConstruction *det);
  ~MyPrimaryGenerator();

  /*GeneratePrimaries function to generate the particle we desire*/
  virtual void GeneratePrimaries(G4Event *);
  void BoxSource(G4double halfLength);
  void CylinderVolumeSource(G4ThreeVector loc, G4double halfHt, G4double radius);
  G4String GetParticleName();

private:
  MyDetectorConstruction *fDetector;
  G4ParticleGun *fParticleGun;
  G4ThreeVector position, direction;
  G4GenericMessenger *fMessenger;
#ifdef USE_CRY
  void LoadCRY();
  G4String cryInputFile;
  CRYGenerator *cryGen = nullptr;
  std::vector<CRYParticle *> cryParticles;
  G4UIcmdWithAString *inputFileCmd;
#endif
};

#endif
