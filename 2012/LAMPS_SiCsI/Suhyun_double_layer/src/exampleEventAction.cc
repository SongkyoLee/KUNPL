#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "exampleEventAction.hh"
#include "DetHit.hh"

#include <fstream>
#include <iomanip>

exampleEventAction::exampleEventAction()
{
}

exampleEventAction::~exampleEventAction()
{
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
    
    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection1");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        
        for(G4int i = 0; i != numHits; i++)
        {
            G4int voxelX = (*HC_Det)[i] -> GetVoxelX();
            G4int voxelY = (*HC_Det)[i] -> GetVoxelY();
            G4int voxelZ = (*HC_Det)[i] -> GetVoxelZ();
            G4double energyDeposit = (*HC_Det)[i] -> GetEdep();
            G4int eventID = anEvent -> GetEventID();
            G4cout << eventID << G4endl;      
            G4ThreeVector hitPosition = (*HC_Det)[i] -> GetHitPosition();
            G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(15) << hitPosition.x()
            << std::setw(15) << hitPosition.y()
            << std::setw(15) << hitPosition.z()
            << std::setw(15) << energyDeposit
            << std::setw(15) << detNum
            << std::setw(15) << eventID <<G4endl;
        }
    }
    
    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection2");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        
        for(G4int i = 0; i != numHits; i++)
        {
            G4int voxelX = (*HC_Det)[i] -> GetVoxelX();
            G4int voxelY = (*HC_Det)[i] -> GetVoxelY();
            G4int voxelZ = (*HC_Det)[i] -> GetVoxelZ();
            G4double energyDeposit = (*HC_Det)[i] -> GetEdep();
            G4int eventID = anEvent -> GetEventID();
            G4cout << eventID << G4endl;      
            G4ThreeVector hitPosition = (*HC_Det)[i] -> GetHitPosition();
            G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(15) << hitPosition.x()
            << std::setw(15) << hitPosition.y()
            << std::setw(15) << hitPosition.z()
            << std::setw(15) << energyDeposit
            << std::setw(15) << detNum
            << std::setw(15) << eventID <<G4endl;
        }
    }
    
    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection3");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        
        for(G4int i = 0; i != numHits; i++)
        {
            G4int voxelX = (*HC_Det)[i] -> GetVoxelX();
            G4int voxelY = (*HC_Det)[i] -> GetVoxelY();
            G4int voxelZ = (*HC_Det)[i] -> GetVoxelZ();
            G4double energyDeposit = (*HC_Det)[i] -> GetEdep();
            G4int eventID = anEvent -> GetEventID();
            G4cout << eventID << G4endl;      
            G4ThreeVector hitPosition = (*HC_Det)[i] -> GetHitPosition();
            G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(15) << hitPosition.x()
            << std::setw(15) << hitPosition.y()
            << std::setw(15) << hitPosition.z()
            << std::setw(15) << energyDeposit
            << std::setw(15) << detNum
            << std::setw(15) << eventID <<G4endl;
        }
    }
    
    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection4");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        
        for(G4int i = 0; i != numHits; i++)
        {
            G4int voxelX = (*HC_Det)[i] -> GetVoxelX();
            G4int voxelY = (*HC_Det)[i] -> GetVoxelY();
            G4int voxelZ = (*HC_Det)[i] -> GetVoxelZ();
            G4double energyDeposit = (*HC_Det)[i] -> GetEdep();
            G4int eventID = anEvent -> GetEventID();
            G4cout << eventID << G4endl;      
            G4ThreeVector hitPosition = (*HC_Det)[i] -> GetHitPosition();
            G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(15) << hitPosition.x()
            << std::setw(15) << hitPosition.y()
            << std::setw(15) << hitPosition.z()
            << std::setw(15) << energyDeposit
            << std::setw(15) << detNum
            << std::setw(15) << eventID <<G4endl;
        }
    }
}

