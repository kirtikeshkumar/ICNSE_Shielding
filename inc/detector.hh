#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4PhysicsOrderedFreeVector.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"
#include "HitCollections.hh"
#include "shielding_Hit.hh"
// #include "construction.hh"

#include "G4AnalysisManager.hh"
#include "G4VProcess.hh"
// #include "g4root.hh"
#include "HitCollections.hh"
#include "vector"
#include <map>
#include "trackInfo.hh"

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
  MySensitiveDetector(G4String);
  ~MySensitiveDetector();
  virtual void Initialize(G4HCofThisEvent *);
  virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
  virtual void EndOfEvent(G4HCofThisEvent *);

private:
  G4int evID;
  // G4PhysicsOrderedFreeVector *quEff;
  int fGeHitCollectionId;
  int fNaIHitCollectionId;
  NaIHitCollection *fNaiHitCollection;
  GeHitCollection *fGeHitCollection;
};

#endif
