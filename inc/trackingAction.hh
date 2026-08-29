#ifndef TRACKINGACTION_HH
#define TRACKINGACTION_HH

#include "G4UserTrackingAction.hh"

class trackingAction : public G4UserTrackingAction
{
public:
    trackingAction();
    virtual ~trackingAction() {};

    virtual void PreUserTrackingAction(const G4Track *);
    virtual void PostUserTrackingAction(const G4Track *);
};

#endif