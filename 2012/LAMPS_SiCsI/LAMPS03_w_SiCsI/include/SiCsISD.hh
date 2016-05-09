//====================
// SiCsISD.hh - KYO
//====================

#ifndef SICSISD_H
#define SICSISD_H 1

#include "G4VSensitiveDetector.hh"
#include "SiCsIHit.hh"

class G4HCofThisEvent;
class G4Step;
class G4TouchableHistory;

class SiCsISD: public G4VSensitiveDetector {
	private:
	G4THitsCollection<SiCsIHit> *hitCollection;
	G4String detNum;

	public:
	SiCsISD(const G4String& name, G4String DETNUM);
	virtual ~SiCsISD();

	virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist);
	virtual void Initialize(G4HCofThisEvent *HCTE);
	virtual void EndOfEvent(G4HCofThisEvent *HCTE);
};
#endif

