//==========
// TPCSD.cc
//==========

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "TPCSD.hh"
#include "TPCHit.hh"

TPCSD::TPCSD(const G4String &name)
:G4VSensitiveDetector(name)
{
	collectionName.insert("TPCHitCollection");
}

TPCSD::~TPCSD()
{
}

void TPCSD::Initialize(G4HCofThisEvent *HCTE)
{
	hitCollection = new G4THitsCollection<TPCHit>(SensitiveDetectorName, collectionName[0]);

	G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
	HCTE -> AddHitsCollection(hcid, hitCollection);
}

G4bool TPCSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	if (!ROhist)	return false;

	G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
	if (energyDeposit == 0.)	return false;

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "TPC_PV_IN") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector postPos = aStep -> GetPostStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		TPCHit *aHit = new TPCHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "voxel pos: " << pos_voxel << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	return true;
}

void TPCSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
