/*This file is for initializing the primary generator */

#include "action.hh"
/* The constructor and destructor*/
MyActionInitialization::MyActionInitialization() {}

MyActionInitialization::MyActionInitialization(MyDetectorConstruction *det)
    : fDetector(det) {}

MyActionInitialization::~MyActionInitialization() {}

/*function to create an instance of the primary generator and initialize it*/

void MyActionInitialization::Build() const
{
#ifdef SETUP_DECAY
  MyPrimaryGenerator *generator = new MyPrimaryGenerator(fDetector);
  SetUserAction(generator);
#else
  MyPrimaryGenerator *generator = new MyPrimaryGenerator();
  SetUserAction(generator);
#endif
  // MyRunAction *runAction = new MyRunAction(generator);
  MyRunAction *runAction = new MyRunAction();
  SetUserAction(runAction);

  MyEventAction *eventAction = new MyEventAction(runAction);
  SetUserAction(eventAction);

  SetUserAction(new trackingAction);

  // MySteppingAction *steppingAction = new MySteppingAction(eventAction);
  // SetUserAction(steppingAction);
}

void MyActionInitialization::BuildForMaster() const
{
  MyRunAction *runAction = new MyRunAction();
  SetUserAction(runAction);
}
