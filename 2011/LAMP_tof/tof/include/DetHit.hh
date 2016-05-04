#ifndef DETHIT_h
#define DETHIT_h 1

#include "G4ThreeVector.hh"
#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"

class DetHit : public G4VHit
{
  private :
    G4int voxelX, voxelY, voxelZ;
    G4double energyDeposit;
    G4double globalTime; // KYO	

  public :
    DetHit();
    DetHit(G4int, G4int, G4int, G4double, G4double); // KYO
    virtual ~ DetHit();

    DetHit(const DetHit &right);
    const DetHit &operator = (const DetHit &right);

    // new /delete operators
    void* operator new(size_t);
    void operator delete(void *aHit);

    // set /get functions
    G4int GetVoxelX() const { return voxelX; };
    G4int GetVoxelY() const { return voxelY; };
    G4int GetVoxelZ() const { return voxelZ; };
    G4double GetEdep() const { return energyDeposit; };
    G4double GetGtime() const { return globalTime; };// KYO
};

inline DetHit::DetHit(const DetHit &right)
:G4VHit()
{
  voxelX = right.voxelX;
  voxelY = right.voxelY;
  voxelZ = right.voxelZ;
  energyDeposit = right.energyDeposit;
  globalTime = right.globalTime; // KYO
}

inline const DetHit &DetHit::operator=(const DetHit &right)
{
  voxelX = right.voxelX;
  voxelY = right.voxelY;
  voxelZ = right.voxelZ;
  energyDeposit = right.energyDeposit;
  globalTime = right.globalTime; // KYO
  return *this;
}

extern G4Allocator<DetHit> DetHitAllocator;

inline void *DetHit::operator new(size_t)
{
  void* aHit = (void*)DetHitAllocator.MallocSingle();
  return aHit;
}

inline void DetHit::operator delete(void *aHit)
{
  DetHitAllocator.FreeSingle((DetHit*) aHit);
}
#endif
