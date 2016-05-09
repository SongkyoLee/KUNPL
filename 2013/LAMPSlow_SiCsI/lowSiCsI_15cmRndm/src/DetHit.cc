#include "DetHit.hh"

G4Allocator<DetHit> DetHitAllocator;

DetHit::DetHit()
:energyDeposit(0), hitPosition(G4ThreeVector(0,0,0)), detNum(0), copyNo(0)
{
}

DetHit::DetHit(G4double edep, G4ThreeVector xyz, G4int n, G4int c)
:energyDeposit(edep), hitPosition(xyz), detNum(n), copyNo(c)
{
}

DetHit::~DetHit()
{
}
