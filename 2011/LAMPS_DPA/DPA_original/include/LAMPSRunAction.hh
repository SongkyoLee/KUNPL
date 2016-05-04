// ====================================================================
//   LAMPSRunAction.hh
// ====================================================================
#ifndef LAMPS_RUN_ACTION_H
#define LAMPS_RUN_ACTION_H

#include "G4UserRunAction.hh"
#include "Randomize.hh"

class G4Run;

class LAMPSRunAction : public G4UserRunAction {
public:
  //  LAMPSRunAction()
  LAMPSRunAction();
  virtual ~LAMPSRunAction();

  virtual void BeginOfRunAction(const G4Run* aRun);
  virtual void EndOfRunAction(const G4Run* aRun);
private:
};

#endif
