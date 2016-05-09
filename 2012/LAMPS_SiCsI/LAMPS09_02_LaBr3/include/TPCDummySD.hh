//----------------------------------------------
// TPCDummySD.hh
//----------------------------------------------

#ifndef TPCDummySD_h
#define TPCDummySD_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;

class TPCDummySD : public G4VSensitiveDetector
{
public:
  TPCDummySD();
  ~TPCDummySD() {};
  
  void Initialize(G4HCofThisEvent* ) {};
  G4bool ProcessHits(G4Step* ,G4TouchableHistory*) {return false;}
  void EndOfEvent(G4HCofThisEvent*) {};
  void clear() {};
  void DrawAll() {};
  void PrintAll() {};
};

TPCDummySD::TPCDummySD() : G4VSensitiveDetector("dummySD")
{}
#endif
