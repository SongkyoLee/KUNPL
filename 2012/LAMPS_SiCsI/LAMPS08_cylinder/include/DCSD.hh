//==========
// DCSD.hh
//==========
#ifndef DCSD_H
#define DCSD_H 1

#include "G4VSensitiveDetector.hh"
#include "DCHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class DCSD: public G4VSensitiveDetector {
	private:
	G4String armName;
	G4THitsCollection<DCHit> *hitCollection;

	public:
	DCSD(const G4String& name, G4String ARMNAME);
	virtual ~DCSD();

	virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
	virtual void Initialize(G4HCofThisEvent *HCTE);
	virtual void EndOfEvent(G4HCofThisEvent *HCTE);
};
#endif
