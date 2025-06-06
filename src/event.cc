#include "event.hh"

MyEventAction::MyEventAction(MyRunAction *run) : fRun(run) {}

MyEventAction::~MyEventAction() {}

void MyEventAction::BeginOfEventAction(const G4Event *anEvent) {
  evID = anEvent->GetEventID();

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

void MyEventAction::EndOfEventAction(const G4Event *anEvent) {
  if (evID % 100000 == 0) {
    std::cout << "Event: " << evID << std::endl;
  }
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  /*AddNumNeutron(numneutron_evt);
  AddNumGamma(numgamma_evt);
  AddNumElectron(numelectron_evt);
  AddNumPositron(numpositron_evt);
  AddNumNu_e(numnu_e_evt);
  AddNumaNu_e(numanu_e_evt);
  AddNumOther(numother_evt);

  if (evID % 1000000 == 0)
  {
    std::cout << std::endl
              << std::endl;
    // std::cout << " Printing from event " << evID << std::endl;
    // fRun->PrintStatus();
  }*/
}
