
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

  hitsCollectionID = sdManager -> GetCollectionID("DetHitsCollection");
  HC_Det = (G4THitsCollection<DetHit> *)(HCTE -> GetHC(hitsCollectionID));

  if (HC_Det)
  {
    G4int numHits = HC_Det -> entries();

    for (G4int i=0; i != numHits; i++)
    {
      G4int voxelX = (*HC_Det)[i] ->GetVoxelX();
      G4int voxelY = (*HC_Det)[i] ->GetVoxelY();
      G4int voxelZ = (*HC_Det)[i] ->GetVoxelZ();
      G4double energyDeposit = (*HC_Det)[i] ->GetEdep();

      std::ofstream outFile("edep.out", std::ios::app); //app : add to the end of the file
      outFile << std::setw(5) << i+1 <<  std::setw(5) << voxelX
	      << std::setw(5) << voxelY << std::setw(5) << voxelZ 
              << std::setw(15) << energyDeposit << G4endl; //SKChanged.. : show Hitnumber
    }
  }
}
