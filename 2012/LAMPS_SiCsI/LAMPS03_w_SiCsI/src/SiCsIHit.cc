//===================
// SiCsIHit.cc - KYO
//===================

#include "SiCsIHit.hh"

//allocator
G4Allocator<SiCsIHit>  SiCsIHitAllocator;

SiCsIHit::SiCsIHit()
:parentID(0), particleID(0), prexyz(0,0,0), postxyz(0,0,0), mom(0,0,0), xyz_voxel(0,0,0),
 EDep(0), ToF(0), detNum(0)
{
}

SiCsIHit::SiCsIHit(G4int &motherID, G4int &pid, G4ThreeVector &prepos, G4ThreeVector &postpos,
G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t, G4int &num)
:parentID(motherID), particleID(pid), prexyz(prepos), postxyz(postpos),
 mom(p), xyz_voxel(v_pos), EDep(e), ToF(t), detNum(num)
{
}

SiCsIHit::~SiCsIHit()
{
}

void SiCsIHit::Draw()
{
}

void SiCsIHit::Print()
{
}

