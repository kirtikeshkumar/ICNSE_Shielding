/*This file is required to integrate the necessary physics like Electromagnetism
 * and Optics*/
#include "physics.hh"

MyPhysicsList::MyPhysicsList() {
  RegisterPhysics(new G4EmLivermorePhysics());
  // RegisterPhysics (new G4OpticalPhysics());
  RegisterPhysics(new G4DecayPhysics());
  RegisterPhysics(new G4RadioactiveDecayPhysics());
  RegisterPhysics(new G4IonPhysics());
  //   RegisterPhysics(new Shielding());
  //   G4VModularPhysicsList *physicsList = new MyShielding;
}

MyPhysicsList::~MyPhysicsList() {}
