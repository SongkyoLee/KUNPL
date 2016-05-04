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
    G4double xLength; // KYO
    G4double yLength; // KYO
    G4double zLength; // KYO
    G4double travelLength; // KYO

    G4double minTime;
    G4double minLength;
};
#endif
