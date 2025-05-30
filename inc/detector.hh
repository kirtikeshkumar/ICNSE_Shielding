#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4PhysicsOrderedFreeVector.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"

#include "G4AnalysisManager.hh"
// #include "g4root.hh"
#include "vector"
#include <map>

class MySensitiveDetector : public G4VSensitiveDetector {
public:
  MySensitiveDetector(G4String);
  ~MySensitiveDetector();
  virtual void Initialize(G4HCofThisEvent *);
  virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
  virtual void EndOfEvent(G4HCofThisEvent *);

  const std::map<int, G4double> &GetEDepMap_Ge() const { return EDepGe; }
  const std::map<int, G4double> &GetEDepMap_NaI() const { return EDepNaI; }
  const std::map<int, G4double> &GetFirstHitTimeMap_Ge() const {
    return FirstHitTimeGe;
  }
  const std::map<int, G4double> &GetFirstHitTimeMap_NaI() const {
    return FirstHitTimeNaI;
  }
  const std::map<int, G4double> &GetLastHitTimeMap_Ge() const {
    return LastHitTimeGe;
  }
  const std::map<int, G4double> &GetLastHitTimeMap_NaI() const {
    return LastHitTimeNaI;
  }

  const std::map<int, G4double> &GetEDepMap() const { return EDep; }
  const std::map<int, G4double> &GetFirstHitTimeMap() const {
    return FirstHitTime;
  }
  const std::map<int, G4double> &GetLastHitTimeMap() const {
    return LastHitTime;
  }

private:
  // G4PhysicsOrderedFreeVector *quEff;
  std::map<int, G4double> EDep, FirstHitTime, LastHitTime;
  std::map<int, G4double> EDepGe, EDepNaI;
  std::map<int, G4double> FirstHitTimeGe, FirstHitTimeNaI;
  std::map<int, G4double> LastHitTimeGe, LastHitTimeNaI;
};

#endif
