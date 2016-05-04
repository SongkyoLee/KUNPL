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
    G4double xLength; //SKChanged..
    G4double yLength; //SK
    G4double zLength; //SK
    G4double travelLength; //SK

    G4double minTime;
    G4double minLength;
};
#endif
