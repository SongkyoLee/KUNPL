#ifndef DETHIT_h
#define DETHIT_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class DetHit:public G4VHit
{
private:
    G4double energyDeposit;
    G4ThreeVector hitPosition;
    G4int detNum;
    G4int copyNo;
    
public:
    DetHit();
    DetHit(G4double, G4ThreeVector, G4int, G4int);
    virtual ~DetHit();
    
    DetHit(const DetHit &right);
    const DetHit &operator=(const DetHit &right);
    
    void *operator new(size_t);
    void operator delete(void *aHit);
    
    G4double GetEdep() const{return energyDeposit;};
    G4ThreeVector GetHitPosition() const{return hitPosition;};
    G4int GetdetNum() const{return detNum;}
    G4int GetcopyNo() const{return copyNo;}
};

inline DetHit::DetHit(const DetHit &right):G4VHit()
{
    energyDeposit = right.energyDeposit;
    hitPosition = right.hitPosition;
    detNum = right.detNum;
    copyNo = right.copyNo;
}

inline const DetHit &DetHit::operator=(const DetHit &right)
{
    energyDeposit = right.energyDeposit;
    hitPosition = right.hitPosition;
    detNum = right.detNum;
    copyNo = right.copyNo;
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
