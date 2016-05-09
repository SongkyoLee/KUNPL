#include "DetHit.hh"

G4Allocator<DetHit> DetHitAllocator;

DetHit::DetHit()
:voxelX(0), voxelY(0), voxelZ(0), energyDeposit(0), hitPosition(G4ThreeVector(0,0,0)), detNum(0)
{
}

DetHit::DetHit(G4int x, G4int y, G4int z, G4double edep, G4ThreeVector xyz, G4int n)
:voxelX(x), voxelY(y), voxelZ(z), energyDeposit(edep), hitPosition(xyz), detNum(n)
{
}

DetHit::~DetHit()
{
}

