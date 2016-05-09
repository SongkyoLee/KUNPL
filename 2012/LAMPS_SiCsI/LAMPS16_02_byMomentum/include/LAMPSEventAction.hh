// ====================================================================
//   LAMPSEventAction.hh
// ====================================================================
#ifndef LAMPS_EVENT_ACTION_H
#define LAMPS_EVENT_ACTION_H 

#include "G4UserEventAction.hh"

class G4Event;
class LAMPSAnaRoot;
class LAMPSPrimaryGeneratorAction;

class LAMPSEventAction : public G4UserEventAction {
public:
  LAMPSEventAction(LAMPSAnaRoot* rootPointer, LAMPSPrimaryGeneratorAction* PGAPointer);
  virtual ~LAMPSEventAction();

  virtual void BeginOfEventAction(const G4Event* anEvent);
  virtual void EndOfEventAction(const G4Event* anEvent);
private:
  G4int hitCollectionID;
  LAMPSAnaRoot *anaRoot;
  LAMPSPrimaryGeneratorAction *LAMPSPGA;
  bool useEventFile;
};

#endif
