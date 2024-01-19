#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"

#include "G4AnalysisManager.hh"
//#include "g4root.hh"

class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction();
	~MyRunAction();
	
	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);
	
	void AddNumNeutron(G4int a){numneutron += a;}
	void AddNumGamma(G4int a){numgamma += a;}
	void AddNumElectron(G4int a){numelectron += a;}
	void AddNumPositron(G4int a){numpositron += a;}
	void AddNumNu_e(G4int a){numnu_e += a;}
	void AddNumaNu_e(G4int a){numanu_e += a;}
	void AddNumOther(G4int a){numother += a;}
	void PrintStatus();
private:
	G4int numneutron,numgamma,numelectron,numpositron,numnu_e,numanu_e,numother;
};

#endif
