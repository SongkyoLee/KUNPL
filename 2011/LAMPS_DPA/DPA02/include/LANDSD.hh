//===========
// LANDSD.hh
//===========
#ifndef LANDSD_H
#define LANDSD_H 1

#include "G4VSensitiveDetector.hh"
#include "LANDHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class LANDSD: public G4VSensitiveDetector {
	private:
	G4String armName;
	G4THitsCollection<LANDHit> *hitCollection;

	public:
	LANDSD(const G4String& name, G4String ARMNAME);
	virtual ~LANDSD();

	virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
	virtual void Initialize(G4HCofThisEvent *HCTE);
	virtual void EndOfEvent(G4HCofThisEvent *HCTE);
};
#endif
