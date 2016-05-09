#include "examplePrimaryGeneratorAction.hh"
#include "TMath.h"
#include "Randomize.hh"

#include "G4ParticleGun.hh"
#include "G4Event.hh"
#include "G4IonTable.hh"
#include "G4UnitsTable.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

examplePrimaryGeneratorAction::examplePrimaryGeneratorAction()
{
    particleGun = new G4ParticleGun;
    
    gunPosition = G4ThreeVector(0, 0*cm, -30*cm);
    particleGun -> SetParticlePosition(gunPosition);
    
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* proton = particleTable -> FindParticle("proton");
    
    particleGun -> SetParticleDefinition(proton);
    
    kineticEnergy = 100*MeV;
    particleGun -> SetParticleEnergy(kineticEnergy);
}

examplePrimaryGeneratorAction::~examplePrimaryGeneratorAction()
{
    delete particleGun;
}

void examplePrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    
    G4double rand = G4UniformRand();
    G4double mz = TMath::Tan((14+10*rand)*degree);
    momentumDirection = G4ThreeVector(0, mz, 1);
    
    particleGun -> SetParticleMomentumDirection(momentumDirection);
    particleGun -> GeneratePrimaryVertex(anEvent);
}

