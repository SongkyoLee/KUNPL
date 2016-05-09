#include "G4VPhysicalVolume.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TouchableHistory.hh"
#include "G4SDManager.hh"
#include "DetSD.hh"
#include "DetHit.hh"
#include "TString.h"
TString a;

G4int i;

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

G4bool DetSD::ProcessHits(G4Step *aStep, G4TouchableHistory *)
{
    G4double energyDeposit = aStep -> GetTotalEnergyDeposit();
    if(energyDeposit == 0.) return false;
    
    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetLogicalVolume() -> GetName() == "detSiLV")&&(energyDeposit !=0.))
    {
        G4ThreeVector hitPosition = aStep->GetPreStepPoint()->GetPosition();
        G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep -> GetPreStepPoint() ->GetTouchable());
        G4int copyNo = theTouchable->GetVolume()->GetCopyNo();
        
        G4int detNum = 1;
        
        DetHit *aHit = new DetHit(energyDeposit, hitPosition, detNum, copyNo);
        hitsCollection -> insert(aHit);
    }
    
    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetLogicalVolume() -> GetName() == "detCsILV")&&(energyDeposit !=0.))
    {
        G4ThreeVector hitPosition = aStep->GetPreStepPoint()->GetPosition();
        G4TouchableHistory* theTouchable = (G4TouchableHistory*)(aStep -> GetPreStepPoint() ->GetTouchable());
        G4int copyNo = theTouchable->GetVolume()->GetCopyNo();
        
        G4int detNum = 2;
        
        DetHit *aHit = new DetHit(energyDeposit, hitPosition, detNum, copyNo);
        hitsCollection -> insert(aHit);
    }
    
    return true;
}

void DetSD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}
