//=========================
// LAMPSDetectorMessenger.hh
//=========================

#ifndef LAMPSDetectorMessenger_h
#define LAMPSDetectorMessenger_h 1

#include "LAMPSDetectorConstruction.hh"
#include "G4UImessenger.hh"
#include "globals.hh"

class LAMPSDetectorConstruction;
class G4UIcmdWithADoubleAndUnit;

class LAMPSDetectorMessenger: public G4UImessenger
{
public:
	LAMPSDetectorMessenger(LAMPSDetectorConstruction*);
	~LAMPSDetectorMessenger();
	
	void SetNewValue(G4UIcommand*, G4String);

private:
	LAMPSDetectorConstruction*	LAMPSDC;
	G4UIcmdWithADoubleAndUnit*	changeDPStrength;
};

#endif
