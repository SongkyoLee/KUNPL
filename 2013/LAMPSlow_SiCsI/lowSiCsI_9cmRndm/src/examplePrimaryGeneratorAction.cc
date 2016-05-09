#include "examplePrimaryGeneratorAction.hh"
#include "TMath.h"
#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "G4IonTable.hh"

examplePrimaryGeneratorAction::examplePrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun;
    
    gunPosition = G4ThreeVector(0, 0, 0);
    particleGun -> SetParticlePosition(gunPosition);
    
    momentumDirection = G4ThreeVector(0, 0, 1);
    particleGun -> SetParticleMomentumDirection(momentumDirection);

}

examplePrimaryGeneratorAction::~examplePrimaryGeneratorAction()
{
    delete particleGun;
}

void examplePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
		// generate 0-1 random numbers
    G4double rand1 = G4UniformRand();
    G4double rand2 = G4UniformRand();
    G4double rand3 = G4UniformRand();

		//Set random Kinetic Energy    
    //kineticEnergy = rand1*20*MeV; // 0-20MeV
		kineticEnergy = 20.*MeV;
    particleGun -> SetParticleEnergy(kineticEnergy);

		//Set random momentum direction
//    G4double polar = TMath::Tan(((9/23)*rand2)*degree);
		G4double polar = 2.*(9./23.)*rand2-(9./23.); // random from -(9/23) to (9/23)
//    G4double azimuthal = rand3*360;
    //momentumDirection = G4ThreeVector(0, polar, 1).rotateZ(azimuthal*degree);
    momentumDirection = G4ThreeVector(polar, polar, 1.);
//    momentumDirection = G4ThreeVector(0, 0, 1);
    particleGun -> SetParticleMomentumDirection(momentumDirection);
    particleGun -> GeneratePrimaryVertex(anEvent);
   
	G4cout << G4endl;
	G4cout << "========================= Random Beam =========================" << G4endl;
	G4cout << "Particle : " << std::setw(30) << particleGun -> GetParticleDefinition()->GetParticleName() << G4endl;

	  G4cout << std::setw(30) << "Momentum direction: " << momentumDirection  << G4endl;
	  //G4cout << std::setw(30) << "Momentum Per Nucleon: " << G4BestUnit(given_momentum*GeV/numNucleon, "Energy") << "/c/u" << G4endl;
	  G4cout << std::setw(30) << "Kinetic Energy: " << G4BestUnit(particleGun -> GetParticleEnergy(), "Energy") << G4endl;
	 // G4cout << std::setw(30) << "Kinetic Energy Per Nucleon: " << G4BestUnit((particleGun -> GetParticleEnergy())/numNucleon, "Energy") << "/u" << G4endl;
	  G4cout << "=============================================================" << G4endl;
	  G4cout << G4endl;

		energyInit = particleGun -> GetParticleEnergy();
}

G4double examplePrimaryGeneratorAction::GetEnergyInit()
{
	return energyInit;
}
