//=========================
// LAMPSDetectorMessenger.cc
//=========================

#include "LAMPSDetectorConstruction.hh"
#include "LAMPSDetectorMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

LAMPSDetectorMessenger::LAMPSDetectorMessenger(LAMPSDetectorConstruction* val)
:LAMPSDC(val)
{
	changeDPStrength = new G4UIcmdWithADoubleAndUnit("/lamps/DPField", this);
	changeDPStrength -> SetGuidance("Set y-direction dipole magnet field strength (default: -1*tesla)");
	changeDPStrength -> SetParameterName("DP_F_STRENGTH", true);
	changeDPStrength -> SetDefaultUnit("tesla");
	changeDPStrength -> SetDefaultValue(-1);
	changeDPStrength -> AvailableForStates(G4State_PreInit, G4State_Idle);
}

LAMPSDetectorMessenger::~LAMPSDetectorMessenger()
{
	delete changeDPStrength;
}

void LAMPSDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
	if ( command == changeDPStrength )
	{
		G4double mField = changeDPStrength -> GetNewDoubleValue(newValue);
		LAMPSDC -> SetMagField( mField );
		
		G4cout << G4endl;
		G4cout <<  "Dipole Magnetic Field: " << mField*1000 << " T" << G4endl;
		G4cout << G4endl;
	}
}
