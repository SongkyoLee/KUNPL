//==========
// TPCSD.hh
//==========
#ifndef TPCSD_H
#define TPCSD_H 1

#include "G4VSensitiveDetector.hh"
#include "TPCHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class TPCSD: public G4VSensitiveDetector {
	private:
	G4THitsCollection<TPCHit> *hitCollection;

	public:
	TPCSD(const G4String& name);
	virtual ~TPCSD();

	virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
	virtual void Initialize(G4HCofThisEvent *HCTE);
	virtual void EndOfEvent(G4HCofThisEvent *HCTE);
};
#endif
