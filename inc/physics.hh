/*This is the header physics file where we define required class and its
 * constructor and destructor function*/

#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4DecayPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4IonPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VModularPhysicsList.hh"
#include "Shielding.hh"

class MyPhysicsList : public G4VModularPhysicsList {
public:
  MyPhysicsList();
  ~MyPhysicsList();
};

#endif
