//============
// LANDHit.cc
//============

#include "LANDHit.hh"

// allocator
G4Allocator<LANDHit> LANDHitAllocator;

LANDHit::LANDHit()
:parentID(0), particleID(0), xyz(0, 0, 0), mom(0, 0, 0), detID(0), EDep(0), ToF(0)
{
}

LANDHit::LANDHit(G4int &motherID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4int &detPos, G4double &e, G4double &t)
:parentID(motherID), particleID(pid), xyz(pos), mom(p), detID(detPos), EDep(e), ToF(t)
{
}

LANDHit::~LANDHit()
{
}

void LANDHit::Draw()
{
}

void LANDHit::Print()
{
}
