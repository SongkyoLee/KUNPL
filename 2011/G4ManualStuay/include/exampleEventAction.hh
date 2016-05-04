#ifndef EXAMPLEEVENTACTION_h
#define EXAMPLEEVENTACTION_h 1

#include "G4UserEventAction.hh"

class G4Event;

class exampleEventAction : public G4UserEventAction
{
  public :
    exampleEventAction();
    virtual ~ exampleEventAction();

    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);

 private :
    G4int hitsCollectionID;
};
#endif
