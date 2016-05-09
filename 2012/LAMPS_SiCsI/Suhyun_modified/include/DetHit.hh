#ifndef DETHIT_h
#define DETHIT_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class DetHit:public G4VHit
{
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
    DetHit();
    DetHit(G4int &motherID, G4int &pid, G4ThreeVector &prepos, G4ThreeVector &postpos, G4ThreeVector &p, G4ThreeVector &v_pos, G4double &e, G4double &t, G4int &num);
    virtual ~DetHit();
    
    DetHit(const DetHit &right);
    const DetHit &operator=(const DetHit &right);
    
    void *operator new(size_t);
    void operator delete(void *aHit);
    
    G4int GetParentID() const { return parentID;};
	G4int GetParticleID() const { return particleID;};
    const G4ThreeVector &GetPrePosition() const{return prexyz;};
    const G4ThreeVector &GetPostPosition() const{return postxyz;};
    const G4ThreeVector &GetMomentum() const{return mom;};
    const G4ThreeVector &GetVoxelPosition() const{return xyz_voxel;};
    G4double GetEDep() const{return EDep;};
    G4double GetToF() const{return ToF;};
    G4int GetdetNum() const{return detNum;};

	virtual void Draw();
	virtual void Print();
};

inline DetHit::DetHit(const DetHit &right):G4VHit()
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

inline const DetHit &DetHit::operator=(const DetHit &right)
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

extern G4Allocator<DetHit> DetHitAllocator;

inline void *DetHit::operator new(size_t)
{
    void *aHit = (void *)DetHitAllocator.MallocSingle();
    return aHit;
}

inline void DetHit::operator delete(void *aHit)
{
    DetHitAllocator.FreeSingle((DetHit *)aHit);
}
#endif

