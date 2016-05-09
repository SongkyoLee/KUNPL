//===========
// FPDHit.cc
//===========

#include "FPDHit.hh"

// allocator
G4Allocator<FPDHit> FPDHitAllocator;

FPDHit::FPDHit()
:parentID(0), particleID(0), xyz(0, 0, 0), mom(0, 0, 0), EDep(0), ToF(0)
{
}

FPDHit::FPDHit(G4int &motherID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4double &e, G4double &t)
:parentID(motherID), particleID(pid), xyz(pos), mom(p), EDep(e), ToF(t)
{
}

FPDHit::~FPDHit()
{
}

void FPDHit::Draw()
{
}

void FPDHit::Print()
{
}
