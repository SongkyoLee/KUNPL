//=========================
// SiCsISD.cc - KYO
//=========================

#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"

#include "SiCsISD.hh"
#include "SiCsIHit.hh"

SiCsISD::SiCsISD(const G4String &name, G4String DETNUM)
:G4VSensitiveDetector(name), detNum(DETNUM)
{
    G4String hitCollectionName = "SiCsIHitCollection_" + detNum;
    collectionName.insert(hitCollectionName);
}

SiCsISD::~SiCsISD()
{
}

void SiCsISD::Initialize(G4HCofThisEvent *HCTE)
{
    hitCollection = new G4THitsCollection<SiCsIHit>(SensitiveDetectorName, collectionName[0]);
    G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);

    HCTE -> AddHitsCollection(hcid, hitCollection);
}

G4bool SiCsISD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    if(!ROhist) return false;
    
    G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
    if(energyDeposit == 0.) return false;
    
    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetLogicalVolume() -> GetName() 
        == "detLVS1")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
//		G4int detID = 0; // DCBD_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector postPos = aStep -> GetPostStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 1;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitCollection -> insert(aHit);

//		G4cout << "SD :: SiCsI pid = " << pid << ",  prePos = " << prePos <<",  detNum = "<<detNum <<G4endl;
	}
	
    
    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetLogicalVolume() -> GetName() 
        == "detLVS2")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
//		G4int detID = 0; // DCBD_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector postPos = aStep -> GetPostStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 3;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitCollection -> insert(aHit);
//		G4cout << "SiCsI pid = " << pid << ",  prePos = " << prePos <<",  detNum = "<<detNum <<G4endl;
	}
	
    
    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetLogicalVolume() -> GetName() 
        == "detLVC1")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
//		G4int detID = 0; // DCBD_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector postPos = aStep -> GetPostStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 2;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitCollection -> insert(aHit);
//		G4cout << "SiCsI pid = " << pid << ",  prePos = " << prePos <<",  detNum = "<<detNum <<G4endl;
	}

    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetLogicalVolume() -> GetName() 
        == "detLVC2")&&(energyDeposit !=0.))
	{
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
//		G4int detID = 0; // DCBD_IN_PV
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector postPos = aStep -> GetPostStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double z_voxel = (G4double) ROhist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROhist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROhist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 4;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitCollection -> insert(aHit);
//		G4cout << "SiCsI pid = " << pid << ",  prePos = " << prePos <<",  detNum = "<<detNum <<G4endl;
	}
    return true;
}

void SiCsISD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}

