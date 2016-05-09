#ifndef EXAMPLEEVENTACTION_h
#define EXAMPLEEVENTACTION_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh" // KYO
#include "examplePrimaryGeneratorAction.hh"

class G4Event;
class examplePrimaryGeneratorAction; // KYO

class exampleEventAction: public G4UserEventAction
{
public:
    exampleEventAction(examplePrimaryGeneratorAction* PGAPointer); // KYO
    virtual ~exampleEventAction();
    
    virtual void BeginOfEventAction(const G4Event* anEvent);
    virtual void EndOfEventAction(const G4Event* anEvent);
    
private:
    G4int hitsCollectionID;
		//G4ParticleGun* particleGun; //KYO
		examplePrimaryGeneratorAction *examplePGA;  // KYO
};
#endif
