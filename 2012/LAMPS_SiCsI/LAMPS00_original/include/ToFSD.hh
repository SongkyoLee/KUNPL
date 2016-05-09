//==========
// ToFSD.hh
//==========
#ifndef ToFSD_H
#define ToFSD_H 1

#include "G4VSensitiveDetector.hh"
#include "ToFHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class ToFSD: public G4VSensitiveDetector {
	private:
	G4String armName;
	G4THitsCollection<ToFHit> *hitCollection;

	public:
	ToFSD(const G4String& name, G4String ARMNAME);
	virtual ~ToFSD();

	virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
	virtual void Initialize(G4HCofThisEvent *HCTE);
	virtual void EndOfEvent(G4HCofThisEvent *HCTE);
};
#endif
