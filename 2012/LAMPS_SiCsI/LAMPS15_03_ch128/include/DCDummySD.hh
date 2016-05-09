//----------------------------------------------
// DCDummySD.hh
//----------------------------------------------

#ifndef DCDummySD_h
#define DCDummySD_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;

class DCDummySD : public G4VSensitiveDetector
{
public:
  DCDummySD();
  ~DCDummySD() {};
  
  void Initialize(G4HCofThisEvent* ) {};
  G4bool ProcessHits(G4Step* ,G4TouchableHistory*) {return false;}
  void EndOfEvent(G4HCofThisEvent*) {};
  void clear() {};
  void DrawAll() {};
  void PrintAll() {};
};

DCDummySD::DCDummySD() : G4VSensitiveDetector("dummySD")
{}
#endif
