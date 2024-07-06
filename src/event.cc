#include "event.hh"

MyEventAction::MyEventAction(MyRunAction *run)
{
	fRun = run;
	fEdep = 0.;
	num = 0;
}

MyEventAction::~MyEventAction()
{
}

void MyEventAction::BeginOfEventAction(const G4Event *anEvent)
{
	num = 0;
	numgamma_evt = 0;
	numneutron_evt = 0;
	numelectron_evt = 0;
	numpositron_evt = 0;
	numnu_e_evt = 0;
	numanu_e_evt = 0;
	numother_evt = 0;
	fEdep = 0.;
	evID = anEvent->GetEventID();
	if (evID % 100000 == 0)
	{
		G4cout << "event: " << evID << G4endl;
	}
}

void MyEventAction::EndOfEventAction(const G4Event *anEvent)
{

	AddNumNeutron(numneutron_evt);
	AddNumGamma(numgamma_evt);
	AddNumElectron(numelectron_evt);
	AddNumPositron(numpositron_evt);
	AddNumNu_e(numnu_e_evt);
	AddNumaNu_e(numanu_e_evt);
	AddNumOther(numother_evt);

	if (evID % 1000000 == 0)
	{
		G4cout << G4endl << G4endl;
		G4cout << " Printing from event " << evID << G4endl;
		fRun->PrintStatus();
	}
}
