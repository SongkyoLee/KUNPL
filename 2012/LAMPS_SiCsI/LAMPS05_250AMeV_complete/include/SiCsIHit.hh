//=====================
// SiCsIHit.hh - KYO
//=====================

#ifndef SICSIHIT_h
#define SICSIHIT_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class SiCsIHit: public G4VHit {
	private:
	G4int parentID;
	G4int particleID;
	G4ThreeVector prexyz;
	G4ThreeVector postxyz;
	G4ThreeVector mom;
	G4ThreeVector xyz_voxel;
	G4double EDep;
	G4double ToF;
	G4int detNum;
	
	public:
	SiCsIHit();
	SiCsIHit(G4int &motherID, G4int &pid, G4ThreeVector &prepos, G4ThreeVector &postpos,
	 G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t, G4int &num);
	virtual ~SiCsIHit();

	// copy constructor & assignment operator
	SiCsIHit(const SiCsIHit &right);
	const SiCsIHit &operator=(const SiCsIHit &right);

	// new/delete operators
	void *operator new(size_t);
	void operator delete(void *aHit);

	// set/get functions
	G4int GetParentID() const { return parentID; };
	G4int GetParticleID() const { return particleID; };
	const G4ThreeVector &GetPrePosition() const { return prexyz; };
	const G4ThreeVector &GetPostPosition() const { return postxyz; };
	const G4ThreeVector &GetMomentum() const { return mom; };
	const G4ThreeVector &GetVoxelPosition() const { return xyz_voxel; };
	G4double GetEDep() const { return EDep; };
	G4double GetToF() const { return ToF; };
	G4double GetdetNum() const {return detNum; };

	// method
	virtual void Draw();
	virtual void Print();
};

inline SiCsIHit::SiCsIHit(const SiCsIHit& right)
:G4VHit()
{
	parentID = right.parentID;
	particleID = right.particleID;
	prexyz = right.prexyz;
	postxyz = right.postxyz;
	mom = right.mom;
	xyz_voxel = right.xyz_voxel;
	EDep = right.EDep;
	ToF = right.ToF;
	detNum = right.detNum;
}

inline const SiCsIHit &SiCsIHit::operator=(const SiCsIHit &right)
{
	parentID = right.parentID;
	particleID = right.particleID;
	prexyz = right.prexyz;
	postxyz = right.postxyz;
	mom = right.mom;
	xyz_voxel = right.xyz_voxel;
	EDep = right.EDep;
	ToF = right.ToF;
	detNum = right.detNum;
	return *this;
}

// externally instanciated
extern G4Allocator<SiCsIHit> SiCsIHitAllocator;

inline void *SiCsIHit::operator new(size_t)
{
	void *aHit = (void *)SiCsIHitAllocator.MallocSingle();
	return aHit;
}

inline void SiCsIHit::operator delete(void *aHit)
 {
	SiCsIHitAllocator.FreeSingle((SiCsIHit *) aHit);
}
#endif

