//===========
// TPCHit.hh
//===========

#ifndef TPC_HIT_H
#define TPC_HIT_H 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class TPCHit: public G4VHit {
	private:
	G4int parentID;
	G4int particleID;
	G4ThreeVector xyz;
	G4ThreeVector mom;
	G4ThreeVector xyz_voxel;
	G4double EDep;
	G4double ToF;
	
	public:
	TPCHit();
	TPCHit(G4int &parentID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t);
	virtual ~TPCHit();

	// copy constructor & assignment operator
	TPCHit(const TPCHit &right);
	const TPCHit &operator=(const TPCHit &right);

	// new/delete operators
	void *operator new(size_t);
	void operator delete(void *aHit);

	// set/get functions
	G4int GetParentID() const { return parentID; };
	G4int GetParticleID() const { return particleID; };
	const G4ThreeVector &GetPosition() const { return xyz; };
	const G4ThreeVector &GetMomentum() const { return mom; };
	const G4ThreeVector &GetVoxelPosition() const { return xyz_voxel; };
	G4double GetEDep() const { return EDep; };
	G4double GetToF() const { return ToF; };

	// method
	virtual void Draw();
	virtual void Print();
};

inline TPCHit::TPCHit(const TPCHit& right)
:G4VHit()
{
	parentID = right.parentID; particleID = right.particleID;
	xyz = right.xyz;
	mom = right.mom;
	xyz_voxel = right.xyz_voxel;
	EDep = right.EDep;
	ToF = right.ToF;
}

inline const TPCHit &TPCHit::operator=(const TPCHit &right)
{
	parentID = right.parentID;
	particleID = right.particleID;
	xyz = right.xyz;
	mom = right.mom;
	xyz_voxel = right.xyz_voxel;
	EDep = right.EDep;
	ToF = right.ToF;
	return *this;
}

// externally instanciated
extern G4Allocator<TPCHit> TPCHitAllocator;

inline void *TPCHit::operator new(size_t)
{
	void *aHit = (void *)TPCHitAllocator.MallocSingle();
	return aHit;
}

inline void TPCHit::operator delete(void *aHit)
 {
	TPCHitAllocator.FreeSingle((TPCHit *) aHit);
}
#endif
