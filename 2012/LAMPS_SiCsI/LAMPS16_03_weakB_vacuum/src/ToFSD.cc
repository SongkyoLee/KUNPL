//==========
// ToFSD.cc
//==========

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "ToFSD.hh"
#include "ToFHit.hh"

ToFSD::ToFSD(const G4String &name, G4String ARMNAME)
:G4VSensitiveDetector(name), armName(ARMNAME)
{
	G4String hitCollectionName = "ToFHitCollection_" + armName;
	collectionName.insert(hitCollectionName);
}

ToFSD::~ToFSD()
{
}

void ToFSD::Initialize(G4HCofThisEvent *HCTE)
{
	hitCollection = new G4THitsCollection<ToFHit>(SensitiveDetectorName, collectionName[0]);

	G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
	HCTE -> AddHitsCollection(hcid, hitCollection);
}

G4bool ToFSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
//	if (!ROhist)	return false;

	G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
	if (energyDeposit == 0.)	return false;

	// TOF_WALL_DPA1_PV and TOF_WALL_DPA2_PV
	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "TOF_WALL_DPA1_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = 0;
		G4double y_voxel = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double x_voxel = 0; // TOF_WALL_DPA1_PV
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		ToFHit *aHit = new ToFHit(parentID, pid, prePos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "voxel pos: " << pos_voxel << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "TOF_WALL_DPA2_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = 0;
		G4double y_voxel = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double x_voxel = 1; // TOF_WALL_DPA2_PV
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		ToFHit *aHit = new ToFHit(parentID, pid, prePos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "voxel pos: " << pos_voxel << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	return true;
}

void ToFSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
