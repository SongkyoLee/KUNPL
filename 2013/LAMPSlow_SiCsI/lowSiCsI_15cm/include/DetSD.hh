#ifndef DETSD_h
#define DETSD_h 1

#include "G4VSensitiveDetector.hh"
#include "DetHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class DetSD: public G4VSensitiveDetector
{
private:
    G4THitsCollection<DetHit> *hitsCollection;
    G4String detName;
    
public:
    G4String detNum;
    DetSD(const G4String& name, G4String DETNUM);
    virtual ~DetSD();
    
    virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *);
    virtual void Initialize(G4HCofThisEvent *HCTE);
    virtual void EndOfEvent(G4HCofThisEvent *HCTE);
};
#endif
