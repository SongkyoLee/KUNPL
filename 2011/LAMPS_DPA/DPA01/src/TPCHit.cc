//===========
// TPCHit.cc
//===========

#include "TPCHit.hh"

// allocator
G4Allocator<TPCHit> TPCHitAllocator;

TPCHit::TPCHit()
:parentID(0), particleID(0), xyz(0, 0, 0), mom(0, 0, 0), xyz_voxel(0, 0, 0), EDep(0), ToF(0)
{
}

TPCHit::TPCHit(G4int &motherID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t)
:parentID(motherID), particleID(pid), xyz(pos), mom(p), xyz_voxel(v_pos), EDep(e), ToF(t)
{
}

TPCHit::~TPCHit()
{
}

void TPCHit::Draw()
{
}

void TPCHit::Print()
{
}
