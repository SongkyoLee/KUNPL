#ifndef examplePrimaryGeneratorAction_h
#define examplePrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"

class G4ParticleGun ;

class examplePrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
private:
    G4ParticleGun* particleGun ;
    
public:
    examplePrimaryGeneratorAction();
    ~examplePrimaryGeneratorAction();
    
    virtual void GeneratePrimaries (G4Event* anEvent );
//		G4double energyInit; // KYO
		G4double GetEnergyInit(); // KYO
    
private:
    G4ThreeVector gunPosition;
    G4ParticleDefinition* particle;
    G4ThreeVector momentumDirection;
    G4double kineticEnergy;
		G4double energyInit; // KYO
};
#endif
