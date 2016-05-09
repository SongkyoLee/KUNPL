//===========
// ToFHit.hh
//===========

#ifndef ToF_HIT_H
#define ToF_HIT_H 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class ToFHit: public G4VHit {
	private:
	G4int parentID;
	G4int particleID;
	G4ThreeVector xyz;
	G4ThreeVector mom;
	G4ThreeVector xyz_voxel;
	G4double EDep;
	G4double ToF;
	
	public:
	ToFHit();
	ToFHit(G4int &motherID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t);
	virtual ~ToFHit();

	// copy constructor & assignment operator
	ToFHit(const ToFHit &right);
	const ToFHit &operator=(const ToFHit &right);

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

inline ToFHit::ToFHit(const ToFHit& right)
:G4VHit()
{
	parentID = right.parentID;
	particleID = right.particleID;
	xyz = right.xyz;
	mom = right.mom;
	xyz_voxel = right.xyz_voxel;
	EDep = right.EDep;
	ToF = right.ToF;
}

inline const ToFHit &ToFHit::operator=(const ToFHit &right)
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
extern G4Allocator<ToFHit> ToFHitAllocator;

inline void *ToFHit::operator new(size_t)
{
	void *aHit = (void *)ToFHitAllocator.MallocSingle();
	return aHit;
}

inline void ToFHit::operator delete(void *aHit)
{
	ToFHitAllocator.FreeSingle((ToFHit *) aHit);
}
#endif
