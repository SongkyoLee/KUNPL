//============
// LandHit.hh
//============

#ifndef LAND_HIT_H
#define LAND_HIT_H 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class LANDHit: public G4VHit {
	private:
	G4int parentID;
	G4int particleID;
	G4ThreeVector xyz;
	G4ThreeVector mom;
	G4int detID;
	G4double EDep;
	G4double ToF;
	
	public:
	LANDHit();
	LANDHit(G4int &motherID, G4int &pid, G4ThreeVector &pos, G4ThreeVector &p, G4int &detPos, G4double &e, G4double &t);
	virtual ~LANDHit();

	// copy constructor & assignment operator
	LANDHit(const LANDHit &right);
	const LANDHit &operator=(const LANDHit &right);

	// new/delete operators
	void *operator new(size_t);
	void operator delete(void *aHit);

	// set/get functions
	G4int GetParentID() const { return parentID; };
	G4int GetParticleID() const { return particleID; };
	const G4ThreeVector &GetPosition() const { return xyz; };
	const G4ThreeVector &GetMomentum() const { return mom; };
	const G4int &GetDetPosition() const { return detID; };
	G4double GetEDep() const { return EDep; };
	G4double GetToF() const { return ToF; };

	// method
	virtual void Draw();
	virtual void Print();
};

inline LANDHit::LANDHit(const LANDHit& right)
:G4VHit()
{
	parentID = right.parentID;
	particleID = right.particleID;
	xyz = right.xyz;
	mom = right.mom;
	detID = right.detID;
	EDep = right.EDep;
	ToF = right.ToF;
}

inline const LANDHit &LANDHit::operator=(const LANDHit &right)
{
	parentID = right.parentID;
	particleID = right.particleID;
	xyz = right.xyz;
	mom = right.mom;
	detID = right.detID;
	EDep = right.EDep;
	ToF = right.ToF;
	return *this;
}

// externally instanciated
extern G4Allocator<LANDHit> LANDHitAllocator;

inline void *LANDHit::operator new(size_t)
{
	void *aHit = (void *)LANDHitAllocator.MallocSingle();
	return aHit;
}

inline void LANDHit::operator delete(void *aHit)
{
	LANDHitAllocator.FreeSingle((LANDHit *) aHit);
}
#endif
