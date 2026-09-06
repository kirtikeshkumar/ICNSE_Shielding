/*In this file we define the particle that we want to generate from the primary
 * generator*/

/*Including the generator header file with all the required classes and
 * functions*/
#include "generator.hh"

/*Constructor and destruction function of the primary generator which creates a
 * new instance of the particle gun and deletes the particle gun respectively.*/
MyPrimaryGenerator::MyPrimaryGenerator()
{

  fMessenger = new G4GenericMessenger(this, "/CRY/", "Cosmic Ray Generator");
  fMessenger->DeclareProperty("inputFile", cryInputFile, "CRY Input File");

  fParticleGun = new G4ParticleGun(1);

  // /*Getting the attributes of our particle(proton) from the G4ParticleTable
  //  * using FindParticle function.*/
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
  // // G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
  // G4ParticleDefinition *particle = particleTable->FindParticle("gamma");

  fParticleGun->SetParticleDefinition(particle);
  // fParticleGun->SetParticleEnergy(1.0 * MeV);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
  delete fParticleGun;
  delete cryGen;
  delete inputFileCmd;
}

void MyPrimaryGenerator::LoadCRY()
{
  if (cryGen)
    delete cryGen;

  std::ifstream infile(cryInputFile);
  if (!infile)
  {
    G4Exception("MyPrimaryGenerator::LoadCRY", "CRY001", FatalException,
                ("Cannot open CRY input file: " + cryInputFile).c_str());
  }

  std::string setupLine;
  std::string setupString;

  while (std::getline(infile, setupLine))
  {
    if (setupLine.empty())
      continue; // skip blank lines
    if (setupLine[0] == '#')
      continue;                                                 // optional: skip comments
    setupLine.erase(setupLine.find_last_not_of(" \r\n\t") + 1); // trim right
    setupString += setupLine + " ";                             // preserve line structure
  }
  auto crySetup = new CRYSetup(setupString, CRY_DATA_PATH);
  cryGen = new CRYGenerator(crySetup);
}

void MyPrimaryGenerator::BoxSource(G4double halfLength)
{
  // Choose random face: 0=+X, 1=-X, 2=+Y, 3=-Y, 4=+Z, 5=-Z
  G4int face = static_cast<G4int>(G4UniformRand() * 6);
  // std::cout << "face: " << face << std::endl;

  G4double u = (2 * G4UniformRand() - 1) * halfLength;
  G4double v = (2 * G4UniformRand() - 1) * halfLength;
  switch (face)
  {
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
}

void MyPrimaryGenerator::CylinderVolumeSource(G4ThreeVector loc,
                                              G4double halfHt, G4double radius,
                                              G4ThreeVector axis)
{
  G4double r = radius * std::sqrt(G4UniformRand());
  G4double phi = 2.0 * CLHEP::pi * G4UniformRand();
  G4double z = (2.0 * G4UniformRand() - 1.0) * halfHt;

  G4double x = r * std::cos(phi);
  G4double y = r * std::sin(phi);
  if (axis == G4ThreeVector(0., 0., 1.))
    position.set(x, y, z);
  if (axis == G4ThreeVector(0., 1., 0.))
    position.set(x, z, y);
  if (axis == G4ThreeVector(1., 0., 0.))
    position.set(z, x, y);
  position = position + loc;
}

/*In this function we define which particle we need from our particle gun and
 * define its properties.*/
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
  // G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

  /*Defining the position and momentum of the particle using G4ThreeVector to
   * define and SetParticle function to define the properties*/
  // G4ThreeVector position(0., 25. * cm, 0.);
  // G4ThreeVector direction(0., -1., 0.);

  // BoxSource(53.1 * cm);
  CylinderVolumeSource(G4ThreeVector(0., 0., -17.1 * cm), 0.25 * cm, 0.05 * cm);
  fParticleGun->SetParticlePosition(position);
  // fParticleGun->SetParticleMomentumDirection(direction);
  // fParticleGun->SetParticleMomentum(0.0*MeV);
  // fParticleGun->SetParticleEnergy(1.0 * MeV);
  // fParticleGun->SetParticleDefinition(particle);

  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

  if (particle == G4Geantino::Geantino() ||
      particle->GetParticleName() == "Cs137")
  {
    // particle->GetParticleName() == "Na22"
    // ||particle->GetParticleName() == "Sr90"
    G4double randVal = G4UniformRand();
    G4int Z, A;
    // if (randVal < 0.5) {
    // Z = 11;
    // A = 22;
    Z = 55;
    A = 137;
    // } else {
    //   Z = 38;
    //   A = 90;
    // }

    G4double charge = 0. * eplus;
    G4double energy = 0. * keV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);

    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    fParticleGun->SetParticleMomentum(0.0 * MeV);
    fParticleGun->SetParticlePosition(position);
  }

  /*if (!cryGen && !cryInputFile.empty()) {
    LoadCRY();
  }

  if (!cryGen) {
    G4Exception("MyPrimaryGenerator", "CRY002", FatalException,
                "CRY generator not initialized. Use /CRY/inputFile.");
  }

  cryGen->genEvent(&cryParticles);

  for (auto p : cryParticles) {
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *def = particleTable->FindParticle(p->PDGid());
    if (!def)
      continue;

    fParticleGun->SetParticleDefinition(def);
    fParticleGun->SetParticlePosition(G4ThreeVector(p->x(), p->y(), 1.) * m);
    // std::cout << "Particle Position: " << p->x() << " " << p->y() <<
    // std::endl;
    fParticleGun->SetParticleMomentumDirection(
        G4ThreeVector(p->u(), p->v(), p->w()));
    // std::cout << "Particle Momentum: " << p->u() << " " << p->v() << " "
    //           << p->w() << std::endl;
    fParticleGun->SetParticleEnergy(p->ke() * MeV);
    // std::cout << "Particle Energy: " << p->ke() << std::endl;
    fParticleGun->GeneratePrimaryVertex(anEvent);
  }
  */

  // for (auto p : cryParticles)
  //   delete p;
  // cryParticles.clear();

  /*Here we generate the particle*/

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
