#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "DetSD.hh"
#include "DetHit.hh"

DetSD::DetSD(const G4String &name)
:G4VSensitiveDetector(name)
{
  collectionName.insert("DetHitsCollection");
}

DetSD::~DetSD()
{
}

void DetSD::Initialize(G4HCofThisEvent* HCTE)
{
  hitsCollection
  = new G4THitsCollection<DetHit>(SensitiveDetectorName, 
				collectionName[0]) ;
  G4int hcid
  = G4SDManager::GetSDMpointer() -> GetCollectionID(collectionName[0]);
  HCTE-> AddHitsCollection(hcid, hitsCollection);
}

G4bool DetSD::ProcessHits(G4Step *aStep, G4TouchableHistory *ROHist)
{
  if (!ROHist) return false;

  G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
  if (energyDeposit ==0.) return false;

  if ((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName()
	=="detPV") && (energyDeposit !=0.)) //if data is in the physical volume?
  {
    G4int voxelZ = ROHist -> GetReplicaNumber(0);
    G4int voxelY = ROHist -> GetReplicaNumber(1);
    G4int voxelX = ROHist -> GetReplicaNumber(2);
    G4double globalTime = aStep -> GetPreStepPoint() -> GetGlobalTime(); //SKChanged..

    DetHit *aHit = 
	new DetHit(voxelX, voxelY, voxelZ, energyDeposit, globalTime); //SKChanged
    hitsCollection -> insert(aHit);
  }

  return true;
}

void DetSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
