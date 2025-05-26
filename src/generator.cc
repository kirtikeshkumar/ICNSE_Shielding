/*In this file we define the particle that we want to generate from the primary
 * generator*/

/*Including the generator header file with all the required classes and
 * functions*/
#include "generator.hh"

/*Constructor and destruction function of the primary generator which creates a
 * new instance of the particle gun and deletes the particle gun respectively.*/
MyPrimaryGenerator::MyPrimaryGenerator() {
  fParticleGun = new G4ParticleGun(1);

  /*Getting the attributes of our particle(proton) from the G4ParticleTable
   * using FindParticle function.*/
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  // G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
  // G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
  G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
}

MyPrimaryGenerator::~MyPrimaryGenerator() { delete fParticleGun; }

/*In this function we define which particle we need from our particle gun and
 * define its properties.*/
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();
  // Creating particles on a 50cm side length box
  G4double halfLength = 25.0 * cm;
  // Choose random face: 0=+X, 1=-X, 2=+Y, 3=-Y, 4=+Z, 5=-Z
  G4int face = static_cast<G4int>(G4UniformRand() * 6);
  std::cout << "face: " << face << std::endl;
  G4ThreeVector position, direction;
  G4double u = (2 * G4UniformRand() - 1) * halfLength;
  G4double v = (2 * G4UniformRand() - 1) * halfLength;
  switch (face) {
  case 0: // +X face → inward = -x
    position.set(halfLength, u, v);
    direction.set(-1., (2 * G4UniformRand() - 1), (2 * G4UniformRand() - 1));
    break;
  case 1: // -X face → inward = +x
    position.set(-halfLength, u, v);
    direction.set(1., (2 * G4UniformRand() - 1), (2 * G4UniformRand() - 1));
    break;
  case 2: // +Y face → inward = -y
    position.set(u, halfLength, v);
    direction.set((2 * G4UniformRand() - 1), -1., (2 * G4UniformRand() - 1));
    break;
  case 3: // -Y face → inward = +y
    position.set(u, -halfLength, v);
    direction.set((2 * G4UniformRand() - 1), 1., (2 * G4UniformRand() - 1));
    break;
  case 4: // +Z face → inward = -z
    position.set(u, v, halfLength);
    direction.set((2 * G4UniformRand() - 1), (2 * G4UniformRand() - 1), -1.);
    break;
  case 5: // -Z face → inward = +z
    position.set(u, v, -halfLength);
    direction.set((2 * G4UniformRand() - 1), (2 * G4UniformRand() - 1), 1.);
    break;
  }
  direction = direction.unit();

  /*Defining the position and momentum of the particle using G4ThreeVector to
   * define and SetParticle function to define the properties*/
  //   G4ThreeVector pos(0., 0., 0.);
  //   G4ThreeVector mom(1., 0., 0.);

  fParticleGun->SetParticlePosition(position);
  fParticleGun->SetParticleMomentumDirection(direction);
  // fParticleGun->SetParticleMomentum(0.0*MeV);
  fParticleGun->SetParticleEnergy(1.0 * MeV);
  fParticleGun->SetParticleDefinition(particle);
  /*if(particle == G4Geantino::Geantino())
  {
          G4int Z = 55;
          G4int A = 137;

          G4double charge = 0.*eplus;
          G4double energy = 0.*keV;

          G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A,
  energy);

          fParticleGun->SetParticleDefinition(ion);
          fParticleGun->SetParticleCharge(charge);
  }*/
  /*Here we generate the particle*/
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
