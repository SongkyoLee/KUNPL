//===========
// FPDHit.hh
//===========

#ifndef FPD_HIT_H
#define FPD_HIT_H 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class FPDHit: public G4VHit {
	private:
	G4int parentID;
	G4int particleID;
	G4ThreeVector xyz;
	G4ThreeVector mom;
//	G4ThreeVector xyz_voxel;
	G4double EDep;
	G4double ToF;
	
	public:
	FPDHit();
	FPDHit(G4int &motherID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4double &e, G4double &t);
	virtual ~FPDHit();

	// copy constructor & assignment operator
	FPDHit(const FPDHit &right);
	const FPDHit &operator=(const FPDHit &right);

	// new/delete operators
	void *operator new(size_t);
	void operator delete(void *aHit);

	// set/get functions
	G4int GetParentID() const { return parentID; };
	G4int GetParticleID() const { return particleID; };
	const G4ThreeVector &GetPosition() const { return xyz; };
	const G4ThreeVector &GetMomentum() const { return mom; };
	G4double GetEDep() const { return EDep; };
	G4double GetToF() const { return ToF; };

	// method
	virtual void Draw();
	virtual void Print();
};

inline FPDHit::FPDHit(const FPDHit& right)
:G4VHit()
{
	parentID = right.parentID;
	particleID = right.particleID;
	xyz = right.xyz;
	mom = right.mom;
	EDep = right.EDep;
	ToF = right.ToF;
}

inline const FPDHit &FPDHit::operator=(const FPDHit &right)
{
	parentID = right.parentID;
	particleID = right.particleID;
	xyz = right.xyz;
	mom = right.mom;
	EDep = right.EDep;
	ToF = right.ToF;
	return *this;
}

// externally instanciated
extern G4Allocator<FPDHit> FPDHitAllocator;

inline void *FPDHit::operator new(size_t)
{
	void *aHit = (void *)FPDHitAllocator.MallocSingle();
	return aHit;
}

inline void FPDHit::operator delete(void *aHit)
{
	FPDHitAllocator.FreeSingle((FPDHit *) aHit);
}
#endif
