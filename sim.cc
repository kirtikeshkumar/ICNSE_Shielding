/*This is the main simulation file*/

/*Including all the required header files*/
#include "G4ios.hh"
#include <fstream>
#include <iostream>
#include <math.h>

#include "G4MTRunManager.hh"
#include "G4RunManager.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4VisManager.hh"

// #include "MyShielding.hh"
#include "Shielding.hh"
#include "action.hh"
#include "construction.hh"
#include "physics.hh"
// #include <G4OpticalPhysics.hh>

/*The main function where all the objects are initialized and all the commands
 * needed are performed*/

int main(int argc, char **argv) {
  // creating a G4RunManager instance to initialize all our required objects and
  // functions
  /*
  #ifdef G4MULTITHREADED
    G4MTRunManager *runManager = new G4MTRunManager();
  #else
    G4RunManager *runManager = new G4RunManager();
  #endif
   */
#ifdef USE_MT
  G4MTRunManager *runManager = new G4MTRunManager();
#else
  G4RunManager *runManager = new G4RunManager();
#endif

  // G4RunManager *runManager = new G4RunManager();
  // runManager->SetVerboseLevel(0);

  // Initializing the detector construction, physics implementation and action
  // initialization files
  if (argc > 2) {
    runManager->SetUserInitialization(
        new MyDetectorConstruction(argv[2], argv[3]));
  } else {
    std::cout << "NUMBEROFARG" << argc << std::endl;
    runManager->SetUserInitialization(new MyDetectorConstruction());
  }
  G4VModularPhysicsList *physicsList = new Shielding;
  runManager->SetUserInitialization(physicsList);
  // runManager->SetUserInitialization(new MyPhysicsList());
  runManager->SetUserInitialization(new MyActionInitialization());

  // creating an instance of the UI Executive and Vis Manager for UI and
  // visualization of our world
  G4UIExecutive *ui = 0;

  if (argc == 1) {
    ui = new G4UIExecutive(argc, argv, "tcsh");
    // ui = new G4UIExecutive(argc, argv);
  }

  G4VisManager *visManager = new G4VisExecutive();
  visManager->Initialize();

  G4UImanager *UImanager = G4UImanager::GetUIpointer();
  // runManager->Initialize();
  if (ui) {
    UImanager->ApplyCommand("/control/execute vis.mac");
    // finally we start the session
    ui->SessionStart();
  } else {
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  }

  return 0;
}
