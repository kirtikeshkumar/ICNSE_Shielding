#ifndef RUN_HH
#define RUN_HH

#include "G4Run.hh"
#include "G4SDManager.hh"
#include "G4UserRunAction.hh"
#include "detector.hh"
#include "generator.hh"

#include "G4AnalysisManager.hh"
// #include "g4root.hh"

class MyRunAction : public G4UserRunAction {
public:
  MyRunAction();
  MyRunAction(MyPrimaryGenerator *gen);
  ~MyRunAction();

  virtual void BeginOfRunAction(const G4Run *);
  virtual void EndOfRunAction(const G4Run *);
  MySensitiveDetector *GetNaISD() { return naiSD; }
  MySensitiveDetector *GetGeSD() { return geSD; }

private:
  G4SDManager *sdManager = nullptr;
  MySensitiveDetector *naiSD = nullptr;
  MySensitiveDetector *geSD = nullptr;
};

#endif
