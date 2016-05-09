//===========
// DCHit.cc
//===========

#include "DCHit.hh"

// allocator
G4Allocator<DCHit> DCHitAllocator;

DCHit::DCHit()
:parentID(0), particleID(0), detID(0), xyz(0, 0, 0), mom(0, 0, 0), xyz_voxel(0, 0, 0), EDep(0), ToF(0)
{
}

DCHit::DCHit(G4int &motherID, G4int &pid, G4int &det, G4ThreeVector &pos, G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t)
:parentID(motherID), particleID(pid), detID(det), xyz(pos), mom(p), xyz_voxel(v_pos), EDep(e), ToF(t)
{
}

DCHit::~DCHit()
{
}

void DCHit::Draw()
{
}

void DCHit::Print()
{
}
