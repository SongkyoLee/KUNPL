//==========
// DCSD.cc
//==========

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "DCSD.hh"
#include "DCHit.hh"

DCSD::DCSD(const G4String &name, G4String ARMNAME)
:G4VSensitiveDetector(name), armName(ARMNAME)
{
	G4String hitCollectionName = "DCHitCollection_" + armName;
	collectionName.insert(hitCollectionName);
}

DCSD::~DCSD()
{
}

void DCSD::Initialize(G4HCofThisEvent *HCTE)
{
	hitCollection = new G4THitsCollection<DCHit>(SensitiveDetectorName, collectionName[0]);
	G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);

	HCTE -> AddHitsCollection(hcid, hitCollection);
}

G4bool DCSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
	if (!ROhist)	return false;

	G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
	if (energyDeposit == 0.)	return false;

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "DCBD_IN_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4int detID = 0; // DCBD_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		DCHit *aHit = new DCHit(parentID, pid, detID, prePos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "det ID: " << detID << " " << "voxel pos: " << pos_voxel << " " 
//			<< "eDep: " << energyDeposit << " " << "time: " << time << G4endl;
	}
		
	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "DCU1_IN_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = 0;
		G4int detID = 1; // DCU1_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		DCHit *aHit = new DCHit(parentID, pid, detID, prePos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "det ID: " << detID << " " << "voxel pos: " << pos_voxel << " " 
//			<< "eDep: " << energyDeposit << " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "DCD1_IN_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = 0;
		G4int detID = 2; // DCD1_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		DCHit *aHit = new DCHit(parentID, pid, detID, prePos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "det ID: " << detID << " " << "voxel pos: " << pos_voxel << " " 
//			<< "eDep: " << energyDeposit << " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "DCU2_IN_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = 0;
		G4int detID = 3; // DCU2_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		DCHit *aHit = new DCHit(parentID, pid, detID, prePos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "det ID: " << detID << " " << "voxel pos: " << pos_voxel << " " 
//			<< "eDep: " << energyDeposit << " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "DCD2_IN_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = 0;
		G4int detID = 4; // DCD2_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		DCHit *aHit = new DCHit(parentID, pid, detID, prePos, preMom, pos_voxel, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "det ID: " << detID << " " << "voxel pos: " << pos_voxel << " " 
//			<< "eDep: " << energyDeposit << " " << "time: " << time << G4endl;
	}

	return true;
}

void DCSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
