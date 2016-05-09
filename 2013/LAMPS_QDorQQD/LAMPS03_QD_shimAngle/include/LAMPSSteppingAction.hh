//========================
// LAMPSSteppingAction.hh
//========================

#ifndef LAMPSSTEPPINGACTION_H
#define LAMPSSTEPPINGACTION_H 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4Step;

class LAMPSSteppingAction: public G4UserSteppingAction
{
	public:
	LAMPSSteppingAction();
	~LAMPSSteppingAction();

	void UserSteppingAction(const G4Step*);
};
#endif
