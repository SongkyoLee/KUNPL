//===========
// DCHit.hh
//===========

#ifndef DC_HIT_H
#define DC_HIT_H 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class DCHit: public G4VHit {
	private:
	G4int parentID;
	G4int particleID;
	G4int detID;
	G4ThreeVector xyz;
	G4ThreeVector mom;
	G4ThreeVector xyz_voxel;
	G4double EDep;
	G4double ToF;
	
	public:
	DCHit();
	DCHit(G4int &motherID, G4int &pid, G4int &det, G4ThreeVector &pos, G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t);
	virtual ~DCHit();

	// copy constructor & assignment operator
	DCHit(const DCHit &right);
	const DCHit &operator=(const DCHit &right);

	// new/delete operators
	void *operator new(size_t);
	void operator delete(void *aHit);

	// set/get functions
	G4int GetParentID() const { return parentID; };
	G4int GetParticleID() const { return particleID; };
	G4int GetDetID() const { return detID; };
	const G4ThreeVector &GetPosition() const { return xyz; };
	const G4ThreeVector &GetMomentum() const { return mom; };
	const G4ThreeVector &GetVoxelPosition() const { return xyz_voxel; };
	G4double GetEDep() const { return EDep; };
	G4double GetToF() const { return ToF; };

	// method
	virtual void Draw();
	virtual void Print();
};

inline DCHit::DCHit(const DCHit& right)
:G4VHit()
{
	parentID = right.parentID;
	particleID = right.particleID;
	detID = right.detID;
	xyz = right.xyz;
	mom = right.mom;
	xyz_voxel = right.xyz_voxel;
	EDep = right.EDep;
	ToF = right.ToF;
}

inline const DCHit &DCHit::operator=(const DCHit &right)
{
	parentID = right.parentID;
	particleID = right.particleID;
	detID = right.detID;
	xyz = right.xyz;
	mom = right.mom;
	xyz_voxel = right.xyz_voxel;
	EDep = right.EDep;
	ToF = right.ToF;
	return *this;
}

// externally instanciated
extern G4Allocator<DCHit> DCHitAllocator;

inline void *DCHit::operator new(size_t)
{
	void *aHit = (void *)DCHitAllocator.MallocSingle();
	return aHit;
}

inline void DCHit::operator delete(void *aHit)
{
	DCHitAllocator.FreeSingle((DCHit *) aHit);
}
#endif
