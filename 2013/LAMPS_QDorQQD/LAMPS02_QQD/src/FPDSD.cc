//==========
// FPDSD.cc
//==========

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "FPDSD.hh"
#include "FPDHit.hh"

FPDSD::FPDSD(const G4String &name)
:G4VSensitiveDetector(name)
{
	G4String hitCollectionName = "FPDHitCollection";
	collectionName.insert(hitCollectionName);
}

FPDSD::~FPDSD()
{
}

void FPDSD::Initialize(G4HCofThisEvent *HCTE)
{
	hitCollection = new G4THitsCollection<FPDHit>(SensitiveDetectorName, collectionName[0]);

	G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
	HCTE -> AddHitsCollection(hcid, hitCollection);
}

G4bool FPDSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
//	if (!ROhist)	return false;

	G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
	if (energyDeposit == 0.)	return false;

	// FPD
	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "FPD_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
//		G4double z_voxel = 0;
//		G4double y_voxel = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
//		G4double x_voxel = 0; //
//		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		FPDHit *aHit = new FPDHit(parentID, pid, prePos, preMom, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	return true;
}

void FPDSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
