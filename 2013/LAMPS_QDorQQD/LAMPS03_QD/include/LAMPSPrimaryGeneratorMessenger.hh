//=================================
// LAMPSPrimaryGeneratorMessenger.hh 
//=================================

#ifndef LAMPSPrimaryGeneratorMessenger_h
#define LAMPSPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class LAMPSPrimaryGeneratorAction;
class G4UIcommand;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;
class G4UIcmdWithoutParameter;
class G4UIcmdWithAString;
class G4UIcmdWith3Vector;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4RunManager;

class LAMPSPrimaryGeneratorMessenger: public G4UImessenger
{
public:
	LAMPSPrimaryGeneratorMessenger(LAMPSPrimaryGeneratorAction*, G4RunManager*);
	~LAMPSPrimaryGeneratorMessenger();
	
	void SetNewValue(G4UIcommand*, G4String);

private:
	LAMPSPrimaryGeneratorAction*	LAMPSPGA;
	G4RunManager* runManager;

	G4ParticleTable*						particleTable;
	G4UIcmdWithoutParameter*		list;
	G4UIcmdWithoutParameter*		run;
	G4UIcmdWithoutParameter*		runAll;
	G4UIcmdWith3VectorAndUnit*	gunPosition;
	G4UIcmdWithAString*					particle;
	G4UIcommand*								ion;
	G4UIcmdWithADoubleAndUnit*	KineticEnergy;
	G4UIcmdWithADoubleAndUnit*	KineticEnergyPerNucleon;
	G4UIcmdWithADouble*					Momentum;
	G4UIcmdWithADouble*					MomentumPerNucleon;
	G4UIcmdWith3Vector*					MomentumDirection;
	G4UIcmdWithAnInteger*				useEventFile;
	G4UIcmdWithAnInteger*				eventEnergy;
	G4UIcmdWithAnInteger*				eventModel;
	G4UIcmdWithAnInteger*				eventNum;
	G4UIcmdWithAnInteger*		useRandom;//KYO
	G4UIcmdWithADoubleAndUnit*	rndmKineticEnergy; //KYO
	G4UIcmdWith3Vector*		rndm_p_direction; //KYO
	G4UIcmdWith3Vector*		rndm_p_direction_2; //KYO
};
#endif
