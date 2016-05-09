//========================
// LAMPSSteppingAction.cc
//========================

#include "LAMPSSteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"

LAMPSSteppingAction::LAMPSSteppingAction()
{
}


LAMPSSteppingAction::~LAMPSSteppingAction()
{
}


void LAMPSSteppingAction::UserSteppingAction(const G4Step *aStep)
{
	G4Track *theTrack = aStep -> GetTrack();
//	if (theTrack -> GetTrackStatus() != fAlive)
//		return;

	if (theTrack -> GetCurrentStepNumber() > 9000)
		theTrack -> SetTrackStatus(fStopAndKill);
}
