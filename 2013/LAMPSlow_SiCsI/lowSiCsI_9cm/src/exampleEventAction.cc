#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "exampleEventAction.hh"
#include "DetHit.hh"
#include "examplePrimaryGeneratorAction.hh" // KYO

#include <fstream>
#include <iomanip>

exampleEventAction::exampleEventAction(examplePrimaryGeneratorAction* PGAPointer):examplePGA(PGAPointer)
{
//	particleGun = new G4ParticleGun; // KYO
}

exampleEventAction::~exampleEventAction()
{
//	delete particleGun;
}

void exampleEventAction::BeginOfEventAction(const G4Event* anEvent)
{
}

void exampleEventAction::EndOfEventAction(const G4Event* anEvent)
{
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    G4HCofThisEvent* HCTE = anEvent -> GetHCofThisEvent();
    if (!HCTE) return;
    G4THitsCollection<DetHit>* HC_Det = NULL;
    
		//define variables
    G4int eventID = anEvent -> GetEventID(); //Event Number
//		G4double eInit = examplePGA -> energyInit; // emitted energy (generation level)
		G4double eInit = examplePGA -> GetEnergyInit(); // emitted energy (generation level)
    G4double edep1 = 0; // depositted energy in Si
    G4double edep2 = 0; // depositted energy in CsI
   
	 	// for Si 
    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection1");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        for(G4int i = 0; i != numHits; i++)
        {
            G4double energyDeposit1 = (*HC_Det)[i] -> GetEdep();
            edep1 += energyDeposit1;
        }
    }
    
		// for CsI
    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection2");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        for(G4int i = 0; i != numHits; i++)
        {
            G4double energyDeposit2 = (*HC_Det)[i] -> GetEdep();
            edep2 += energyDeposit2;
        }
    }
   
	 	// save as ASCII file 
    G4cout << "EventID : " << eventID << G4endl;
    G4cout << "eInit : " << eInit << G4endl;
    std::ofstream outFile("edep.out", std::ios::app);
    outFile
    << std::setw(15) << eventID
    << std::setw(15) << eInit
    << std::setw(15) << edep1
    << std::setw(15) << edep2
    << G4endl;
}
