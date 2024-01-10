#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"

#include "G4AnalysisManager.hh"
//#include "g4root.hh"
#include "run.hh"
#include <vector>

class MyEventAction : public G4UserEventAction
{
public:
	MyEventAction(MyRunAction* run);
	~MyEventAction();
	
	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);
	
	void AddEdep(G4double edep){ fEdep += edep; }
	void AddNum(){num++;}
	
	void AddNumNeutron(G4int ne){fRun->AddNumNeutron(ne);}
	void AddNumGamma(G4int ne){fRun->AddNumGamma(ne);}
	void AddNumElectron(G4int ne){fRun->AddNumElectron(ne);}
	void AddNumPositron(G4int ne){fRun->AddNumPositron(ne);}
	void AddNumNu_e(G4int ne){fRun->AddNumNu_e(ne);}
	void AddNumaNu_e(G4int ne){fRun->AddNumaNu_e(ne);}
	void AddNumOther(G4int ne){fRun->AddNumOther(ne);}
	
	void AddNumNeutronEvt(){numneutron_evt++;}
	void AddNumGammaEvt(){numgamma_evt++;}
	void AddNumElectronEvt(){numelectron_evt++;}
	void AddNumPositronEvt(){numpositron_evt++;}
	void AddNumNu_eEvt(){numnu_e_evt++;}
	void AddNumaNu_eEvt(){numanu_e_evt++;}
	void AddNumOtherEvt(){numother_evt++;}
	
private:
	MyRunAction* fRun;
	G4double fEdep;
	G4int num;
	G4int numneutron_evt,numgamma_evt,numelectron_evt,numpositron_evt,numnu_e_evt,numanu_e_evt,numother_evt;
	std::vector<G4double> fEGamma, fENeutron;
};

#endif
