#ifndef EVENT_HH
#define EVENT_HH

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4UserEventAction.hh"
#include "construction.hh"
#include "detector.hh"

#include "G4AnalysisManager.hh"
// #include "g4root.hh"
#include "run.hh"
#include <vector>

class MyEventAction : public G4UserEventAction {
public:
  MyEventAction(MyRunAction *run);
  ~MyEventAction();

  virtual void BeginOfEventAction(const G4Event *);
  virtual void EndOfEventAction(const G4Event *);
  void GetPrimaryParticle(const G4Event *event);
  G4int GetEvID() { return evID; }

private:
  MyRunAction *fRun;
  G4int evID;
};

#endif
