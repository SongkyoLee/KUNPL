//==========
// FPDSD.hh
//==========
#ifndef FPDSD_H
#define FPDSD_H 1

#include "G4VSensitiveDetector.hh"
#include "FPDHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class FPDSD: public G4VSensitiveDetector {
	private:
//	G4String armName;
	G4THitsCollection<FPDHit> *hitCollection;

	public:
//	FPDSD(const G4String& name, G4String ARMNAME);
	FPDSD(const G4String& name);
	virtual ~FPDSD();

	virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
	virtual void Initialize(G4HCofThisEvent *HCTE);
	virtual void EndOfEvent(G4HCofThisEvent *HCTE);
};
#endif
