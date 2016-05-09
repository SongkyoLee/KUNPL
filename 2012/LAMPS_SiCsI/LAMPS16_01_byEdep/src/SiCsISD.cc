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

SiCsISD::SiCsISD(const G4String &name, G4String DETNAME)
:G4VSensitiveDetector(name), detName(DETNAME)
{
    G4String hitCollectionName = "SiCsIHitCollection_" + detName;
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
   
    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SiF_PV")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
		G4int copyNum = aStep -> GetPreStepPoint() ->  GetTouchableHandle() -> GetCopyNumber();
		G4int detNum = 1;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, preMom, energyDeposit, time, copyNum, detNum);
		hitCollection -> insert(aHit);
		}
   
    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SiS_PV")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
		G4int copyNum = aStep -> GetPreStepPoint() ->  GetTouchableHandle() -> GetCopyNumber();
		G4int detNum = 2;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, preMom, energyDeposit, time, copyNum, detNum);
		hitCollection -> insert(aHit);
		}

    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SiT_PV")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
		G4int copyNum = aStep -> GetPreStepPoint() ->  GetTouchableHandle() -> GetCopyNumber();
		G4int detNum = 3;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, preMom, energyDeposit, time, copyNum, detNum);
		hitCollection -> insert(aHit);
		}

    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "CsI_PV")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
		G4int copyNum = aStep -> GetPreStepPoint() ->  GetTouchableHandle() -> GetCopyNumber();
		G4int detNum = 4;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, preMom, energyDeposit, time, copyNum, detNum);
		hitCollection -> insert(aHit);
		}

    if((aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() == "SiV_PV")&&(energyDeposit !=0.))
    {
		G4String particleName = aStep -> GetTrack() -> GetDefinition() -> GetParticleName();
		G4int parentID = aStep -> GetTrack() -> GetParentID();
		G4int pid = aStep -> GetTrack() -> GetDefinition() -> GetPDGEncoding();
		G4ThreeVector prePos = aStep -> GetPreStepPoint() -> GetPosition();
		G4ThreeVector preMom = aStep -> GetPreStepPoint() -> GetMomentum();
		G4double time = aStep -> GetPreStepPoint() -> GetGlobalTime();
		G4int copyNum = aStep -> GetPreStepPoint() ->  GetTouchableHandle() -> GetCopyNumber();
		G4int detNum = 5;

		SiCsIHit *aHit = new SiCsIHit(parentID, pid, prePos, preMom, energyDeposit, time, copyNum, detNum);
		hitCollection -> insert(aHit);
		}

    return true;
}

void SiCsISD::EndOfEvent(G4HCofThisEvent *HCTE)
{
}

