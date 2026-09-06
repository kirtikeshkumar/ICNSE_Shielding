#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class trackingAction : public G4UserTrackingAction
{
public:
    trackingAction();
    virtual ~trackingAction() {};

    virtual void PreUserTrackingAction(const G4Track *);
    virtual void PostUserTrackingAction(const G4Track *);
};

#endif