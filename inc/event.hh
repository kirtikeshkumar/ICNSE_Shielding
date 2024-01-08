#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"
//#include "g4root.hh"
#include "run.hh"

class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction(MyRunAction* run);
	~MyEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	void AddEdep(G4double edep){ fEdep += edep; }
	void AddNum(){num++;}
	
	void AddNumNeutron(){fRun->AddNumNeutron();}
	void AddNumGamma(){fRun->AddNumGamma();}
	void AddNumElectron(){fRun->AddNumElectron();}
	void AddNumPositron(){fRun->AddNumPositron();}
	void AddNumNu_e(){fRun->AddNumNu_e();}
	void AddNumaNu_e(){fRun->AddNumaNu_e();}
	void AddNumOther(){fRun->AddNumOther();}
	
private:
	MyRunAction* fRun;
	G4double fEdep;
	G4int num;
};

#endif
