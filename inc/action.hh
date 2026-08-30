/*This is the header file of action initialization, here we mention all the
 * functions and variables needed for action initialization.*/

#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"

#include "construction.hh"
#include "event.hh"
#include "generator.hh"
#include "run.hh"
#include "stepping.hh"
#include "trackingAction.hh"

// defining the ActionInitialization class with the constructor,destrector and a
// build function to build the primary generator
class MyActionInitialization : public G4VUserActionInitialization
{
public:
  MyActionInitialization();
  MyActionInitialization(MyDetectorConstruction *det);
  ~MyActionInitialization();

  virtual void Build() const;
  virtual void BuildForMaster() const;

private:
  MyDetectorConstruction *fDetector;
};

#endif
