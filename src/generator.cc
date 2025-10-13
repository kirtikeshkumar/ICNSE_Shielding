/*In this file we define the particle that we want to generate from the primary generator*/

/*Including the generator header file with all the required classes and functions*/
#include "generator.hh"

/*Constructor and destruction function of the primary generator which creates a new instance of the particle gun and deletes the particle gun respectively.*/
MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1);

	/*Getting the attributes of our particle(proton) from the G4ParticleTable using FindParticle function.*/
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	// G4ParticleDefinition *particle = particleTable->FindParticle("geantino");
	// G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
	G4ParticleDefinition *particle = particleTable->FindParticle("neutron");

	/*Defining the position and momentum of the particle using G4ThreeVector to define and SetParticle function to define the properties*/
	G4ThreeVector pos(0., 0., 0.);
	G4ThreeVector mom(1., 0., 0.);

	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom);
	// fParticleGun->SetParticleMomentum(0.0*MeV);
	fParticleGun->SetParticleEnergy(1.0 * MeV);
	fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::MyPrimaryGenerator(MyDetectorConstruction *det)
	: fDetector(det)
{
	fParticleSource = new G4GeneralParticleSource();

	// Define Pb-210
	G4ParticleDefinition *pb210 = G4IonTable::GetIonTable()->GetIon(82, 210, 0.);
	fParticleSource->SetParticleDefinition(pb210);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
	delete fParticleSource;
}

/*In this function we define which particle we need from our particle gun and define its properties.*/
void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	// G4ParticleDefinition *particle = fParticleGun->GetParticleDefinition();

	/*if(particle == G4Geantino::Geantino())
	{
		G4int Z = 55;
		G4int A = 137;

		G4double charge = 0.*eplus;
		G4double energy = 0.*keV;

		G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z, A, energy);

		fParticleGun->SetParticleDefinition(ion);
		fParticleGun->SetParticleCharge(charge);
	}*/
	/*Here we generate the particle*/
	// fParticleGun->GeneratePrimaryVertex(anEvent);
	generatePbSelfActivity(anEvent);
}

void MyPrimaryGenerator::generatePbSelfActivity(G4Event *anEvent)
{
	const auto &leadList = fDetector->GetLeadVolumes();
	if (leadList.empty())
	{
		G4cerr << "No lead volumes found! Cannot generate Pb-210 events.\n";
		return;
	}

	// Pick a lead volume weighted by its mass (volume)
	G4double totalVol = 0.;
	for (auto &v : leadList)
		totalVol += v.volume;
	G4double rnd = G4UniformRand() * totalVol;

	const LeadVolumeInfo *chosen = nullptr;
	G4double acc = 0.;
	for (auto &v : leadList)
	{
		acc += v.volume;
		if (rnd <= acc)
		{
			chosen = &v;
			break;
		}
	}
	if (!chosen)
		chosen = &leadList.back();

	// Generate a random position within the chosen solid
	G4ThreeVector pos = chosen->solid->GetPointOnSurface(); // or GetPointInside() if defined

	// Set particle position and shoot
	fParticleSource->GetCurrentSource()->GetPosDist()->SetCentreCoords(pos);
	fParticleSource->GeneratePrimaryVertex(anEvent);

	G4cout << "Event Pb210 decay at: " << pos / cm << " cm in " << chosen->name << "\n";
}
