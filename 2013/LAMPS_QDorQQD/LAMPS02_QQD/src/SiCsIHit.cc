//===================
// SiCsIHit.cc - KYO
//===================

#include "SiCsIHit.hh"

//allocator
G4Allocator<SiCsIHit>  SiCsIHitAllocator;

SiCsIHit::SiCsIHit()
:parentID(0), particleID(0), xyz(0,0,0), mom(0,0,0), EDep(0), ToF(0), detNum(0)
{
}

SiCsIHit::SiCsIHit(G4int &motherID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4double &e, G4double &t, G4int &num)
:parentID(motherID), particleID(pid), xyz(pos), mom(p), EDep(e), ToF(t), detNum(num)
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

