//=================================
// LAMPSPrimaryGeneratorMessenger.cc
//=================================

#include "G4RunManager.hh"
#include "G4ParticleGunMessenger.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "LAMPSPrimaryGeneratorAction.hh"
#include "LAMPSPrimaryGeneratorMessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <iomanip>
#include <sstream>

LAMPSPrimaryGeneratorMessenger::LAMPSPrimaryGeneratorMessenger(LAMPSPrimaryGeneratorAction* LAMPSGun, G4RunManager* runPointer)
:LAMPSPGA(LAMPSGun), runManager(runPointer)
{
	particleTable = G4ParticleTable::GetParticleTable();

	list = new G4UIcmdWithoutParameter("/lamps/list", this);
	list -> SetGuidance("Show available particles");
	list -> AvailableForStates(G4State_PreInit, G4State_Idle);

	run = new G4UIcmdWithoutParameter("/lamps/run", this);
	run -> SetGuidance("Run the event!");
	run -> AvailableForStates(G4State_PreInit, G4State_Idle);

	runAll = new G4UIcmdWithoutParameter("/lamps/runAll", this);
	runAll -> SetGuidance("Run all events of the selected energy!");
	runAll -> AvailableForStates(G4State_PreInit, G4State_Idle);

	gunPosition = new G4UIcmdWith3VectorAndUnit("/lamps/gun", this);
	gunPosition -> SetGuidance("Set particle gun position (default:0 0 0 cm)");
	gunPosition -> SetParameterName("x", "y", "z", true);
	gunPosition -> SetDefaultValue(G4ThreeVector(0, 0, 0));
	gunPosition -> SetDefaultUnit("cm");
	gunPosition -> AvailableForStates(G4State_PreInit, G4State_Idle);

	particle = new G4UIcmdWithAString("/lamps/particle", this);
	particle -> SetGuidance("Set incident particle (default: proton)");
	particle -> SetParameterName("ParticleName", true);
	particle -> SetDefaultValue("proton");
	particle -> SetCandidates("neutron proton deuteron triton He3 alpha pi+ pi- C12 Li6 Li7 Ar40 Au197");
	particle -> AvailableForStates(G4State_PreInit, G4State_Idle);

	G4UIparameter *parameter;
	ion = new G4UIcommand("/lamps/ion", this);
	ion -> SetGuidance("Set incident ion with Z and A. You should enter Z followed by A. (ex. if the ion is alpha, then 2 4.) (default: 1 1)");
	parameter = new G4UIparameter("A", 'i', true);
	parameter -> SetDefaultValue(1);
	ion -> SetParameter(parameter);
	parameter = new G4UIparameter("Z", 'i', true);
	parameter -> SetDefaultValue(1);
	ion -> SetParameter(parameter);
	ion -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
	KineticEnergy = new G4UIcmdWithADoubleAndUnit("/lamps/KE", this);
	KineticEnergy -> SetGuidance("Set kinetic energy (default: 100 MeV)");
	KineticEnergy -> SetParameterName("Energy", true);
	KineticEnergy -> SetDefaultUnit("MeV");
	KineticEnergy -> SetDefaultValue(100);
	KineticEnergy -> SetUnitCandidates("eV keV MeV GeV TeV");
	KineticEnergy -> AvailableForStates(G4State_PreInit, G4State_Idle);

	KineticEnergyPerNucleon = new G4UIcmdWithADoubleAndUnit("/lamps/KEpu", this);
	KineticEnergyPerNucleon -> SetGuidance("Set Kinetic energy per nucleon (default: 100 MeV)");
	KineticEnergyPerNucleon -> SetParameterName("EnergyPerNucleon", true);
	KineticEnergyPerNucleon -> SetDefaultUnit("MeV");
	KineticEnergyPerNucleon -> SetDefaultValue(100);
	KineticEnergyPerNucleon -> SetUnitCandidates("eV keV MeV GeV TeV");
	KineticEnergyPerNucleon -> AvailableForStates(G4State_PreInit, G4State_Idle);

	Momentum = new G4UIcmdWithADouble("/lamps/p", this);
	Momentum -> SetGuidance("Set momentum in GeV/c. (default: 0.3 GeV/c)");
	Momentum -> SetParameterName("p", true);
	Momentum -> SetDefaultValue(0.3);
	Momentum -> AvailableForStates(G4State_PreInit, G4State_Idle);

	MomentumPerNucleon = new G4UIcmdWithADouble("/lamps/ppu", this);
	MomentumPerNucleon -> SetGuidance("Set momentum per nucelon in GeV/c. (default: 0.3 GeV/c)");
	MomentumPerNucleon -> SetParameterName("MomentumPerNucleon", true);
	MomentumPerNucleon -> SetDefaultValue(0.3);
	MomentumPerNucleon -> AvailableForStates(G4State_PreInit, G4State_Idle);
	
	MomentumDirection = new G4UIcmdWith3Vector("/lamps/p_direction", this);
	MomentumDirection -> SetGuidance("Automatically normalize to be unity (default:0 0 1)");
	MomentumDirection -> SetParameterName("px", "py", "pz", true);
	MomentumDirection -> SetDefaultValue(G4ThreeVector(0, 0, 1));
	MomentumDirection -> AvailableForStates(G4State_PreInit, G4State_Idle);

	useEventFile = new G4UIcmdWithAnInteger("/lamps/useEventFile", this);
	useEventFile -> SetGuidance("Use event file made by event generator (default:0)");
	useEventFile -> SetParameterName("use", true);
	useEventFile -> SetDefaultValue(0);
	useEventFile -> AvailableForStates(G4State_PreInit, G4State_Idle);

	eventEnergy = new G4UIcmdWithAnInteger("/lamps/eventEnergy", this);
	eventEnergy -> SetGuidance("Select energy in MeV (default:150)");
	eventEnergy -> SetParameterName("eventEnergy", true);
	eventEnergy -> SetDefaultValue(150);
	eventEnergy -> AvailableForStates(G4State_PreInit, G4State_Idle);

	eventModel = new G4UIcmdWithAnInteger("/lamps/eventModel", this);
	eventModel -> SetGuidance("Select model by number: 0(Soft), 1(Hard) (default:1)");
	eventModel -> SetParameterName("eventModel", true);
	eventModel -> SetDefaultValue(1);
	eventModel -> AvailableForStates(G4State_PreInit, G4State_Idle);

	eventNum = new G4UIcmdWithAnInteger("/lamps/eventNum", this);
	eventNum -> SetGuidance("Select event number (default:0)");
	eventNum -> SetParameterName("eventNum", true);
	eventNum -> SetDefaultValue(0);
	eventNum -> AvailableForStates(G4State_PreInit, G4State_Idle);

	//KYO : for random beam //
	useRandom = new G4UIcmdWithAnInteger("/lamps/useRandom", this);
	useRandom -> SetGuidance("use [rndmKineticEnergy]&[rndm_p_direction]: 0(don't use) or 1(use)  (default:0)");
	useRandom -> SetParameterName("useRandom", true);
	useRandom -> SetDefaultValue(0);
	useRandom -> AvailableForStates(G4State_PreInit, G4State_Idle);

	rndmKineticEnergy = new G4UIcmdWithADoubleAndUnit("/lamps/rndmKE", this);
	rndmKineticEnergy -> SetGuidance("Select kinetic energy randomly from 0 to selected-value in MeV (defalut:300)");
	rndmKineticEnergy -> SetParameterName("rndmKineticEnergy", true);
	rndmKineticEnergy -> SetDefaultUnit("MeV");
	rndmKineticEnergy -> SetDefaultValue(300); //temporary
	rndmKineticEnergy -> SetUnitCandidates("eV keV MeV GeV TeV");
	rndmKineticEnergy -> AvailableForStates (G4State_PreInit, G4State_Idle);

	rndm_p_direction = new G4UIcmdWith3Vector("/lamps/rndm_p_direction", this);
	rndm_p_direction -> SetGuidance("Select pYmin, pYmax, PHI : pXmin and pYmax are minimum and maximum polar angle of momentum direction respectively in degrees. It will be rotated PHI degrees along the z axis (default:14 24 360)");
	rndm_p_direction -> SetParameterName("pYmin", "pYmax", "PHI", true); //temporary
	rndm_p_direction -> SetDefaultValue(G4ThreeVector(14, 24, 360)); //temporary
	rndm_p_direction -> AvailableForStates (G4State_PreInit, G4State_Idle);
}

LAMPSPrimaryGeneratorMessenger::~LAMPSPrimaryGeneratorMessenger()
{
	delete eventNum;
	delete eventModel;
	delete eventEnergy;
	delete useEventFile;
	delete MomentumDirection;
	delete MomentumPerNucleon;
	delete Momentum;
	delete KineticEnergyPerNucleon;
	delete KineticEnergy;
	delete ion;
	delete particle;
	delete gunPosition;
	delete runAll;
	delete run;
	delete list;
	delete useRandom; //KYO
	delete rndmKineticEnergy; //KYO
	delete rndm_p_direction; //KYO
}

void LAMPSPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
	if ( command == list )
	{
		G4int nPtcl = particleTable -> entries();
		for (G4int i = 0; i != nPtcl; i++)
		{
			G4cout << particleTable -> GetParticleName(i) << " ";
		}

		G4cout << G4endl;
	}
	else if ( command == run )
	{
		runManager -> BeamOn( LAMPSPGA -> GetNumTracks() );
	}
	else if ( command == runAll )
	{
		G4int numEvents;
		if (LAMPSPGA -> GetChoosenEventEnergy() == 150)
			numEvents = 5200;
		else
			numEvents = 10000;

		for (G4int i = 0; i != numEvents; i++) {
			LAMPSPGA -> SetChoosenEventNum( i );
			LAMPSPGA -> PrepareBeam();
			runManager -> BeamOn( LAMPSPGA -> GetNumTracks() );
			LAMPSPGA -> CloseOpenFile();
		}
	}
	else if ( command == gunPosition )
	{
		LAMPSPGA -> SetGunPosition( gunPosition -> GetNew3VectorValue(newValues) );
	}
	else if ( command == particle )
	{
		G4ParticleDefinition* pd;
		if ( newValues == "C12" )	pd = particleTable -> GetIon(6, 12, 0);
		else if ( newValues == "Li6" )	pd = particleTable -> GetIon(3, 6, 0);
		else if ( newValues == "Li7" )	pd = particleTable -> GetIon(3, 7, 0);
		else if ( newValues == "Ar40" )	pd = particleTable -> GetIon(18, 40, 0);
		else if ( newValues == "Au197" ) pd = particleTable -> GetIon(79, 197, 0);
		else				pd = particleTable -> FindParticle(newValues);

		LAMPSPGA -> SetParticle(pd);
	}
	else if ( command == ion )
	{
		G4int Z, A;
  
		std::stringstream is(newValues);
		is >> Z >> A;

		G4ParticleDefinition* pd = particleTable -> GetIon( Z, A, 0 );
		LAMPSPGA -> SetParticle(pd);
	}
	else if ( command == KineticEnergy )
	{
		G4double mc2 = LAMPSPGA -> GetParticleMassInGeV();
		G4int numNucleon = LAMPSPGA -> GetNumNucleon();
		G4double kinetic_energy = KineticEnergy -> GetNewDoubleValue(newValues);
		G4double pc = sqrt( (kinetic_energy/GeV + mc2)*(kinetic_energy/GeV + mc2) - mc2*mc2 );

		G4cout << G4endl;
		G4cout << std::setw(40) << "Initial Kinetic Energy: " << G4BestUnit(kinetic_energy, "Energy") << G4endl;
		G4cout << std::setw(40) << "Inition Kinetic Energy Per Nucleon: " << G4BestUnit(kinetic_energy/numNucleon, "Energy") << G4endl;
		G4cout << std::setw(40) << "Initial Momentum: " << G4BestUnit(pc*GeV, "Energy") << "/c" << G4endl;
		G4cout << std::setw(40) << "Initial Momentum Per Nucleon: " << G4BestUnit(pc*GeV/numNucleon, "Energy") << "/c" << G4endl;
		G4cout << G4endl;

		LAMPSPGA -> SetKineticEnergy(kinetic_energy);
		LAMPSPGA -> ShowMomentum(pc);
	}
	else if ( command == KineticEnergyPerNucleon )
	{
		G4double mc2 = LAMPSPGA -> GetParticleMassInGeV();
		G4int numNucleon = LAMPSPGA -> GetNumNucleon();
		G4double kinetic_energy_per_nucleon = KineticEnergyPerNucleon -> GetNewDoubleValue(newValues);
		G4double kinetic_energy = kinetic_energy_per_nucleon * numNucleon;
		G4double pc = sqrt( (kinetic_energy/GeV + mc2)*(kinetic_energy/GeV + mc2) - mc2*mc2 );

		G4cout << G4endl;
		G4cout << std::setw(40) << "Initial Kinetic Energy: " << G4BestUnit(kinetic_energy, "Energy") << G4endl;
		G4cout << std::setw(40) << "Inition Kinetic Energy Per Nucleon: " << G4BestUnit(kinetic_energy_per_nucleon, "Energy") << G4endl;
		G4cout << std::setw(40) << "Initial Momentum: " << G4BestUnit(pc*GeV, "Energy") << "/c" << G4endl;
		G4cout << std::setw(40) << "Initial Momentum Per Nucleon: " << G4BestUnit(pc*GeV/numNucleon, "Energy") << "/c" << G4endl;
		G4cout << G4endl;

		LAMPSPGA -> SetKineticEnergy(kinetic_energy);
		LAMPSPGA -> ShowMomentum(pc);
	}
	else if ( command == Momentum )
	{
		G4int numNucleon = LAMPSPGA -> GetNumNucleon();
		G4double pc = Momentum -> GetNewDoubleValue(newValues);
		G4double mc2 = LAMPSPGA -> GetParticleMassInGeV();
		G4double kinetic_energy = ( sqrt(pc*pc + mc2*mc2) - mc2 )*GeV; // MeV

		G4cout << G4endl;
		G4cout << std::setw(40) << "Initial Kinetic Energy: " << G4BestUnit(kinetic_energy, "Energy") << G4endl;
		G4cout << std::setw(40) << "Inition Kinetic Energy Per Nucleon: " << G4BestUnit(kinetic_energy/numNucleon, "Energy") << G4endl;
		G4cout << std::setw(40) << "Initial Momentum: " << G4BestUnit(pc*GeV, "Energy") << "/c" << G4endl;
		G4cout << std::setw(40) << "Initial Momentum Per Nucleon: " << G4BestUnit(pc*GeV/numNucleon, "Energy") << "/c" << G4endl;
		G4cout << G4endl;
		
		LAMPSPGA -> SetKineticEnergy(kinetic_energy);
		LAMPSPGA -> ShowMomentum(pc);
	}
	else if ( command == MomentumPerNucleon )
	{
		G4int numNucleon = LAMPSPGA -> GetNumNucleon();
		G4double pc_per_nucleon = MomentumPerNucleon -> GetNewDoubleValue(newValues);
		G4double pc = pc_per_nucleon * numNucleon;
		G4double mc2 = LAMPSPGA -> GetParticleMassInGeV();
		G4double kinetic_energy = ( sqrt(pc*pc + mc2*mc2) - mc2 )*GeV; // MeV

		G4cout << G4endl;
		G4cout << std::setw(40) << "Initial Kinetic Energy: " << G4BestUnit(kinetic_energy, "Energy") << G4endl;
		G4cout << std::setw(40) << "Inition Kinetic Energy Per Nucleon: " << G4BestUnit(kinetic_energy/numNucleon, "Energy") << G4endl;
		G4cout << std::setw(40) << "Initial Momentum: " << G4BestUnit(pc*GeV, "Energy") << "/c" << G4endl;
		G4cout << std::setw(40) << "Initial Momentum Per Nucleon: " << G4BestUnit(pc_per_nucleon*GeV, "Energy") << "/c" << G4endl;
		G4cout << G4endl;
		
		LAMPSPGA -> SetKineticEnergy(kinetic_energy);
		LAMPSPGA -> ShowMomentum(pc);
	}
	else if ( command == MomentumDirection )
	{
		LAMPSPGA -> SetMomentumDirection( MomentumDirection -> GetNew3VectorValue(newValues) );
	}
	else if ( command == useEventFile )
	{
		LAMPSPGA -> SetUseEventFile( useEventFile -> GetNewIntValue(newValues) );
	}
	else if ( command == eventEnergy )
	{
		LAMPSPGA -> SetEnergy( eventEnergy -> GetNewIntValue(newValues) );
		LAMPSPGA -> PrepareBeam();
	}
	else if ( command == eventModel )
	{
		LAMPSPGA -> SetModel( eventModel -> GetNewIntValue(newValues) );
		LAMPSPGA -> PrepareBeam();
	}
	else if ( command == eventNum )
	{
		LAMPSPGA -> SetChoosenEventNum( eventNum -> GetNewIntValue(newValues) );
		LAMPSPGA -> PrepareBeam();
	}
	//KYO
	else if ( command == useRandom )
	{
		LAMPSPGA -> SetUseRandom( useRandom-> GetNewIntValue(newValues) );
	}

	else if ( command == rndmKineticEnergy )
	{
		G4double mc2 = LAMPSPGA -> GetParticleMassInGeV();
		G4int numNucleon = LAMPSPGA -> GetNumNucleon();
		G4double kinetic_energy = rndmKineticEnergy -> GetNewDoubleValue(newValues);
		G4double pc = sqrt( (kinetic_energy/GeV + mc2)*(kinetic_energy/GeV + mc2) - mc2*mc2 );

		G4cout << G4endl;
		G4cout << std::setw(40) << "Range of the Initial Kinetic Energy: 0 - " << G4BestUnit(kinetic_energy, "Energy") << G4endl;
		G4cout << std::setw(40) << "Range of the Inition Kinetic Energy Per Nucleon: 0 - " << G4BestUnit(kinetic_energy/numNucleon, "Energy") << G4endl;
		G4cout << std::setw(40) << "Range of the Initial Momentum: 0 - " << G4BestUnit(pc*GeV, "Energy") << "/c" << G4endl;
		G4cout << std::setw(40) << "Range of the Initial Momentum Per Nucleon: 0 - " << G4BestUnit(pc*GeV/numNucleon, "Energy") << "/c" << G4endl;
		G4cout << G4endl;

		LAMPSPGA -> SetRndmKineticEnergy(kinetic_energy);
		LAMPSPGA -> ShowMomentum(pc);
	}
	else if ( command == rndm_p_direction )
	{
		LAMPSPGA -> SetRndm_p_direction( rndm_p_direction -> GetNew3VectorValue(newValues) );//temporary
	}

}
