#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"

#include "exampleEventAction.hh"
#include "DetHit.hh"

#include <fstream>
#include <iomanip>

extern std::ofstream ofs;

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

//	G4int particleNum = LAMPSPGA -> GetParticleNumber(); //KYO
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
		G4int parentID = (*HC_Det)[i] -> GetParentID();
		G4int pID = (*HC_Det)[i] -> GetParticleID();
		G4ThreeVector prePos = (*HC_Det)[i] -> GetPrePosition();
		G4ThreeVector postPos = (*HC_Det)[i] -> GetPostPosition();
		G4ThreeVector pos_voxel = (*HC_Det)[i] -> GetVoxelPosition();
		G4double EDep = (*HC_Det)[i] -> GetEDep();
		G4double ToF = (*HC_Det)[i] -> GetToF();
		G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(10) << parentID
            << std::setw(10) << pID
            << std::setw(15) << prePos.x()
            << std::setw(15) << prePos.y()
            << std::setw(15) << prePos.z()
            //<< std::setw(10) << postPos.x()
            //<< std::setw(10) << postPos.y()
            //<< std::setw(10) << postPos.z()
            << std::setw(10) << EDep
            << std::setw(10) << ToF
            << std::setw(10) << detNum << G4endl;
        }
    }

    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection2");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        
        for(G4int i = 0; i != numHits; i++)
        {
		G4int parentID = (*HC_Det)[i] -> GetParentID();
		G4int pID = (*HC_Det)[i] -> GetParticleID();
		G4ThreeVector prePos = (*HC_Det)[i] -> GetPrePosition();
		G4ThreeVector postPos = (*HC_Det)[i] -> GetPostPosition();
		G4ThreeVector pos_voxel = (*HC_Det)[i] -> GetVoxelPosition();
		G4double EDep = (*HC_Det)[i] -> GetEDep();
		G4double ToF = (*HC_Det)[i] -> GetToF();
		G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(10) << parentID
            << std::setw(10) << pID
            << std::setw(15) << prePos.x()
            << std::setw(15) << prePos.y()
            << std::setw(15) << prePos.z()
            //<< std::setw(10) << postPos.x()
            //<< std::setw(10) << postPos.y()
            //<< std::setw(10) << postPos.z()
            << std::setw(10) << EDep
            << std::setw(10) << ToF
            << std::setw(10) << detNum << G4endl;
        }
    }

    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection3");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        
        for(G4int i = 0; i != numHits; i++)
        {
		G4int parentID = (*HC_Det)[i] -> GetParentID();
		G4int pID = (*HC_Det)[i] -> GetParticleID();
		G4ThreeVector prePos = (*HC_Det)[i] -> GetPrePosition();
		G4ThreeVector postPos = (*HC_Det)[i] -> GetPostPosition();
		G4ThreeVector pos_voxel = (*HC_Det)[i] -> GetVoxelPosition();
		G4double EDep = (*HC_Det)[i] -> GetEDep();
		G4double ToF = (*HC_Det)[i] -> GetToF();
		G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(10) << parentID
            << std::setw(10) << pID
            << std::setw(15) << prePos.x()
            << std::setw(15) << prePos.y()
            << std::setw(15) << prePos.z()
            //<< std::setw(10) << postPos.x()
            //<< std::setw(10) << postPos.y()
            //<< std::setw(10) << postPos.z()
            << std::setw(10) << EDep
            << std::setw(10) << ToF
            << std::setw(10) << detNum << G4endl;
        }
    }

    hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection4");
    HC_Det = (G4THitsCollection<DetHit>*)(HCTE -> GetHC(hitsCollectionID));
    
    if(HC_Det)
    {
        G4int numHits = HC_Det -> entries();
        
        for(G4int i = 0; i != numHits; i++)
        {
		G4int parentID = (*HC_Det)[i] -> GetParentID();
		G4int pID = (*HC_Det)[i] -> GetParticleID();
		G4ThreeVector prePos = (*HC_Det)[i] -> GetPrePosition();
		G4ThreeVector postPos = (*HC_Det)[i] -> GetPostPosition();
		G4ThreeVector pos_voxel = (*HC_Det)[i] -> GetVoxelPosition();
		G4double EDep = (*HC_Det)[i] -> GetEDep();
		G4double ToF = (*HC_Det)[i] -> GetToF();
		G4int detNum = (*HC_Det)[i] -> GetdetNum();
            
            std::ofstream outFile("edep.out", std::ios::app);
            outFile << std::setw(10) << parentID
            << std::setw(10) << pID
            << std::setw(15) << prePos.x()
            << std::setw(15) << prePos.y()
            << std::setw(15) << prePos.z()
           // << std::setw(10) << postPos.x()
           // << std::setw(10) << postPos.y()
           // << std::setw(10) << postPos.z()
            << std::setw(10) << EDep
            << std::setw(10) << ToF
            << std::setw(10) << detNum << G4endl;
        }
    }
}

