#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "G4AnalysisManager.hh"

class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction();
	~MyRunAction();
	
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
	
	void AddNumNeutron(){numneutron++;}
	void AddNumGamma(){numgamma++;}
	void AddNumElectron(){numelectron++;}
	void AddNumPositron(){numpositron++;}
	void AddNumNu_e(){numnu_e++;}
	void AddNumaNu_e(){numanu_e++;}
	void AddNumOther(){numother++;}
	void PrintStatus();
private:
	G4int numneutron,numgamma,numelectron,numpositron,numnu_e,numanu_e,numother;
};

#endif
