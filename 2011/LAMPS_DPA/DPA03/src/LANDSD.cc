//===========
// LANDSD.cc
//===========

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "LANDSD.hh"
#include "LANDHit.hh"

LANDSD::LANDSD(const G4String &name, G4String ARMNAME)
:G4VSensitiveDetector(name), armName(ARMNAME)
{
	G4String hitCollectionName = "LANDHitCollection_" + armName;
	collectionName.insert(hitCollectionName);
}

LANDSD::~LANDSD()
{
}

void LANDSD::Initialize(G4HCofThisEvent *HCTE)
{
	hitCollection = new G4THitsCollection<LANDHit>(SensitiveDetectorName, collectionName[0]);

	G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
	HCTE -> AddHitsCollection(hcid, hitCollection);
}

G4bool LANDSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
//	if (!ROhist)	return false;

	G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
	if (energyDeposit == 0.)	return false;

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SA1_HORIZONTAL_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4int detID = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		LANDHit *aHit = new LANDHit(parentID, pid, prePos, preMom, detID, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "detID: " << detID << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SA1_VERTICAL_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4int detID = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		LANDHit *aHit = new LANDHit(parentID, pid, prePos, preMom, detID, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "detID: " << detID << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SA2_HORIZONTAL_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4int detID = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		LANDHit *aHit = new LANDHit(parentID, pid, prePos, preMom, detID, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "detID: " << detID << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SA2_VERTICAL_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding(); 
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4int detID = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		LANDHit *aHit = new LANDHit(parentID, pid, prePos, preMom, detID, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "detID: " << detID << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "VC1_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4int detID = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		LANDHit *aHit = new LANDHit(parentID, pid, prePos, preMom, detID, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "detID: " << detID << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "VC2_PV") && (energyDeposit != 0.)) {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4int detID = aStep -> GetPreStepPoint() -> GetTouchableHandle() -> GetCopyNumber();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();

		LANDHit *aHit = new LANDHit(parentID, pid, prePos, preMom, detID, energyDeposit, time);
		hitCollection -> insert(aHit);

//		G4cout << "pid: " << pid << " " << "prePos: " << prePos << " " << "preMom: " << preMom << G4endl;
//		G4cout << "stepLength: " << stepLength << " " << "detID: " << detID << " " << "eDep: " << energyDeposit
//			<< " " << "time: " << time << G4endl;
	}

	return true;
}

void LANDSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
