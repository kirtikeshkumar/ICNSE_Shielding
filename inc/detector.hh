#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4PhysicsOrderedFreeVector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"
// #include "construction.hh"

#include "G4AnalysisManager.hh"
// #include "g4root.hh"
#include "vector"
#include <map>
#include "HitCollections.h"

class MySensitiveDetector : public G4VSensitiveDetector
{

int fGeHitCollectionId;
NaIHitCollection *fNaiHitCollection;

int fNaIHitCollectionId;
GeHitCollection *fGeHitCollection;

public:
  MySensitiveDetector(G4String);
  ~MySensitiveDetector();
  virtual void Initialize(G4HCofThisEvent *);
  virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
  virtual void EndOfEvent(G4HCofThisEvent *);

  const std::map<int, G4double> &GetEDepMap() const { return EDep; }
  const std::map<int, G4double> &GetFirstHitTimeMap() const
  {
    return FirstHitTime;
  }
  const std::map<int, G4double> &GetLastHitTimeMap() const
  {
    return LastHitTime;
  }
  const std::map<int, ushort> &GetNumHits() const
  {
    return numHits;
  }
  void CleanDetector();

private:
  // G4PhysicsOrderedFreeVector *quEff;
  std::map<int, G4double> EDep,
      FirstHitTime,
      LastHitTime;
  std::map<int, ushort> numHits;
};

#endif
