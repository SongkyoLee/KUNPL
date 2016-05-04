#include "DetHit.hh"

//allocator
G4Allocator<DetHit> DetHitAllocator;

DetHit::DetHit()
:voxelX(0), voxelY(0), voxelZ(0), energyDeposit(0), globalTime(0) // KYO
{
}

DetHit::DetHit(G4int x, G4int y, G4int z, G4double edep, G4double gtime) // KYO
:voxelX(x), voxelY(y), voxelZ(z), energyDeposit(edep), globalTime(gtime) // KYO
{
}

DetHit::~DetHit()
{
}

