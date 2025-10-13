/*In this header file we define the required functions for the generator file*/

/*First we include all the required header files like G4ParticleGun and G4SystemOfUnits*/
#ifndef GENERATOR_HH
#define GENERATOR_HH

#include "G4VUserPrimaryGeneratorAction.hh"
#include "construction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"
#include "G4Geantino.hh"
#include "G4IonTable.hh"
#include "Randomize.hh"

/*We define the PrimaryGenerator class which will be used to construct our ParticleGun*/

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction
{
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
	void generatePbSelfActivity(G4Event *anEvent);
};

#endif
