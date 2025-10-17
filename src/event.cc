#include "event.hh"

MyEventAction::MyEventAction(MyRunAction *run) : fRun(run) {}

MyEventAction::~MyEventAction() {}

void MyEventAction::BeginOfEventAction(const G4Event *anEvent) {
  evID = anEvent->GetEventID();

  // GetPrimaryParticle(anEvent);

  /*NaISD->CleanDetector();
  GeSD->CleanDetector();*/

  /*num = 0;
  numgamma_evt = 0;
  numneutron_evt = 0;
  numelectron_evt = 0;
  numpositron_evt = 0;
  numnu_e_evt = 0;
  numanu_e_evt = 0;
  numother_evt = 0;
  fEdep = 0.;
  if (evID % 100000 == 0) {
    std::cout << "event: " << evID << std::endl;
  }*/
}

/*void MyEventAction::GetPrimaryParticle(const G4Event *event) {
  G4PrimaryVertex *vertex = event->GetPrimaryVertex();
  if (!vertex) {
    G4cerr << "No primary vertex!" << G4endl;
    return;
  }

  // Get the primary particle from the vertex (assumes one primary per vertex)
  G4PrimaryParticle *primary = vertex->GetPrimary();
  if (!primary) {
    G4cerr << "No primary particle!" << G4endl;
    return;
  }

  // Get particle info
  G4int pdgCode = primary->GetPDGcode();
  G4ParticleDefinition *particleDef =
      G4ParticleTable::GetParticleTable()->FindParticle(pdgCode);
  G4String name = (particleDef ? particleDef->GetParticleName() : "Unknown");

  // Get energy
  G4double px = primary->GetPx();
  G4double py = primary->GetPy();
  G4double pz = primary->GetPz();
  G4double p = std::sqrt(px * px + py * py + pz * pz);
  G4double mass = particleDef ? particleDef->GetPDGMass() : 0.0;
  G4double energy = std::sqrt(p * p + mass * mass);
  G4double cosTheta = -1.0 * pz / p;
  G4double thetaRad = std::acos(cosTheta);
  G4double thetaDeg = thetaRad * (180.0 / CLHEP::pi);

  // std::cout << name << " " << mass << " " << energy << " " << thetaDeg
  //           << std::endl;

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleIColumn(3, 0, evID);
  man->FillNtupleSColumn(3, 1, name);
  man->FillNtupleDColumn(3, 2, energy);
  man->FillNtupleDColumn(3, 3, thetaDeg);
  man->AddNtupleRow(3);
}*/

void MyEventAction::EndOfEventAction(const G4Event *anEvent) {
  if (evID % 100 == 0) {
    std::cout << "Event: " << evID << std::endl;
  }
  // G4AnalysisManager *man = G4AnalysisManager::Instance();
}
