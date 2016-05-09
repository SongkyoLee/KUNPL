#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "DetSD.hh"
#include "DetHit.hh"

DetSD::DetSD(const G4String &name, G4String DETNUM)
:G4VSensitiveDetector(name), detNum(DETNUM)
{
    G4String hitsCollectionName = "DetHitsCollection" + detNum;
    collectionName.insert(hitsCollectionName);
}

DetSD::~DetSD()
{
}

void DetSD::Initialize(G4HCofThisEvent *HCTE)
{
    hitsCollection = new G4THitsCollection<DetHit>(SensitiveDetectorName, collectionName[0]);
    
    G4int hcid = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
    HCTE -> AddHitsCollection(hcid, hitsCollection);
}

G4bool DetSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
    if(!ROHist) return false;
    
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
		G4double z_voxel = (G4double) ROHist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROHist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROHist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 1;

		DetHit *aHit = new DetHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitsCollection -> insert(aHit);

		G4cout << "SiCsI pid = " <<pid << ", prePos = " << prePos << ", detNum = "<<detNum <<G4endl;

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
		G4double z_voxel = (G4double) ROHist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROHist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROHist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 3;

		DetHit *aHit = new DetHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitsCollection -> insert(aHit);
		G4cout << "SiCsI pid = " <<pid << ", prePos = " << prePos << ", detNum = "<<detNum <<G4endl;
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
		G4double z_voxel = (G4double) ROHist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROHist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROHist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 2;

		DetHit *aHit = new DetHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitsCollection -> insert(aHit);
		G4cout << "SiCsI pid = " <<pid << ", prePos = " << prePos << ", detNum = "<<detNum <<G4endl;
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
		G4double z_voxel = (G4double) ROHist -> GetReplicaNumber(0);
		G4double y_voxel = (G4double) ROHist -> GetReplicaNumber(1);
		G4double x_voxel = (G4double) ROHist -> GetReplicaNumber(2);
		G4ThreeVector pos_voxel = G4ThreeVector(x_voxel, y_voxel, z_voxel);
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
//		G4double stepLength = aStep -> GetStepLength();
		G4int detNum = 4;

		DetHit *aHit = new DetHit(parentID, pid, prePos, postPos, preMom, pos_voxel, energyDeposit, time, detNum);
		hitsCollection -> insert(aHit);
		G4cout << "SiCsI pid = " <<pid << ", prePos = " << prePos << ", detNum = "<<detNum <<G4endl;
	}
    return true;
}

void DetSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}

