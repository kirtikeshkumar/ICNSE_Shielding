/*In this file we define the particle that we want to generate from the primary
 * generator*/

/*Including the generator header file with all the required classes and
 * functions*/
#include "generator.hh"
#include <G4ThreeVector.hh>
#include <G4Types.hh>
#include <vector>

/*Constructor and destruction function of the primary generator which creates a
 * new instance of the particle gun and deletes the particle gun respectively.*/
MyPrimaryGenerator::MyPrimaryGenerator() {
  fParticleGun = new G4ParticleGun(1);

  /*Getting the attributes of our particle(proton) from the G4ParticleTable
   * using FindParticle function.*/
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  // G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
  // G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
  G4ParticleDefinition *particle = particleTable->FindParticle("neutron");

  /*Defining the position and momentum of the particle using G4ThreeVector to
   * define and SetParticle function to define the properties*/
  G4ThreeVector pos(0., 0., 0.);
  G4ThreeVector mom(1., 0., 0.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  //   fParticleGun->SetParticleMomentum(0.0*MeV);
  fParticleGun->SetParticleEnergy(1.0 * MeV);
  fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::MyPrimaryGenerator(MyDetectorConstruction *det)
    : fDetector(det) {
  fParticleGun = new G4ParticleGun(1);
  G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
}

MyPrimaryGenerator::~MyPrimaryGenerator() {
  delete fParticleGun;
  delete fParticleSource;
}

/*In this function we define which particle we need from our particle gun and
 * define its properties.*/
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) {
  // Get the logic volumes and thicknesses from the detector construction
  std::vector<G4LogicalVolume *> leadLVs = fDetector->GetLeadVolumes();
  std::vector<G4double> widths = fDetector->GetLeadThicknesses();
  if (leadLVs.empty() || widths.empty() || leadLVs.size() != widths.size()) {
    G4cerr << "Lead volumes / widths mismatch or empty." << G4endl;
    return;
  }
  // Evaluate the volumes for each layer to select the particle generating
  // volume
  double vol = 0;
  std::vector<G4double> volCumulative;
  std::vector<G4ThreeVector> startPoints;
  std::vector<G4ThreeVector> fullLengths;
  for (int ij = 0; ij < leadLVs.size(); ij++) {
    G4VSolid *solid = leadLVs[ij]->GetSolid();
    G4VoxelLimits limits;
    G4AffineTransform transform;
    G4double xmin, xmax, ymin, ymax, zmin, zmax;
    solid->CalculateExtent(kXAxis, limits, transform, xmin, xmax);
    solid->CalculateExtent(kYAxis, limits, transform, ymin, ymax);
    solid->CalculateExtent(kZAxis, limits, transform, zmin, zmax);
    G4ThreeVector startPoint(xmin, ymin, zmin);
    G4ThreeVector boxLength(xmax - xmin, ymax - ymin, zmax - zmin);
    startPoints.push_back(startPoint);
    fullLengths.push_back(boxLength);
    vol += (boxLength.x() * boxLength.y() * boxLength.z() -
            (boxLength.x() - 2.0 * widths[ij]) *
                (boxLength.y() - 2.0 * widths[ij]) *
                (boxLength.z() - 2.0 * widths[ij]));
    volCumulative.push_back(vol);
  }
  // now find the solid volume in which lead decays
  G4double randVolume = G4UniformRand() * vol;
  double chosenIndex = -1;
  for (int ij = 0; ij < volCumulative.size(); ij++) {
    if (randVolume < volCumulative[ij]) {
      chosenIndex = ij;
      break;
    }
  }
  // now define the particle location
  G4ThreeVector decayLocation =
      generatePointInShell(fullLengths[chosenIndex], widths[chosenIndex]);
  decayLocation += startPoints[chosenIndex];

  G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

  if (particle == G4Geantino::Geantino()) {
    G4int Z = 82;
    G4int A = 210;

    G4double charge = 0. * eplus;
    G4double energy = 0. * keV;

    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);

    fParticleGun->SetParticleDefinition(ion);
    fParticleGun->SetParticleCharge(charge);
    fParticleGun->SetParticlePosition(decayLocation);
    std::cout << "Generating Pb210 decay from: " << decayLocation << std::endl;
    if (leadLVs[chosenIndex]->GetSolid()->Inside(decayLocation) == kInside) {
      std::cout << " point is inside the solid " << chosenIndex << std::endl;
    }
  }
  /*Here we generate the particle*/
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

G4ThreeVector MyPrimaryGenerator::generatePointInShell(G4ThreeVector fullLength,
                                                       G4double thickness) {
  G4ThreeVector innerBox(fullLength.x() - 2.0 * thickness,
                         fullLength.y() - 2.0 * thickness,
                         fullLength.z() - 2.0 * thickness);

  // First generate a random x location using inverse cdf sampling
  // Inverse CDF sampling allows for getting the x position properly
  // distributed in one shot
  G4double norm = pow(fullLength.x(), 3) - pow(innerBox.x(), 3);
  G4double C1 = pow(fullLength.x(), 2) * thickness / norm;
  G4double C2 =
      (pow(fullLength.x(), 2) - pow(innerBox.x(), 2)) * (innerBox.x()) / norm;
  G4double xCDF = G4UniformRand();
  G4double x = 0, y = 0, z = 0;
  if (xCDF >= 0 && xCDF < C1) {
    x = xCDF / C1 * thickness;
  } else if (xCDF < C1 + C2) {
    x = (xCDF - C1) / C2 * innerBox.x() + thickness;
  } else {
    x = (xCDF - C1 - C2) / C1 * thickness + fullLength.x() - thickness;
  }
  //   From x, generate the corresponding y and z
  if (x < thickness || (fullLength.x() - x) < thickness) {
    y = G4UniformRand() * fullLength.y();
    z = G4UniformRand() * fullLength.z();
  } else if (fabs(0.5 * fullLength.x() - x) < 0.5 * innerBox.x()) {
    y = G4UniformRand() * 2.0 * thickness;
    z = G4UniformRand() * 2.0 * thickness;
    if (y > thickness)
      y += (fullLength.y() - thickness);
    if (z > thickness)
      z += (fullLength.z() - thickness);
  }
  G4ThreeVector position(x, y, z);
  return position;
}
