//----------------------------------------------
// SiCsIDummySD.hh - KYO
//----------------------------------------------

#ifndef SiCsIDummySD_h
#define SiCsIDummySD_h 1

#include "G4VSensitiveDetector.hh"
class G4Step;

class SiCsIDummySD : public G4VSensitiveDetector
{
public:
  SiCsIDummySD();
  ~SiCsIDummySD() {};
  
  void Initialize(G4HCofThisEvent* ) {};
  G4bool ProcessHits(G4Step* ,G4TouchableHistory*) {return false;}
  void EndOfEvent(G4HCofThisEvent*) {};
  void clear() {};
  void DrawAll() {};
  void PrintAll() {};
};

SiCsIDummySD::SiCsIDummySD() : G4VSensitiveDetector("dummySD")
{}
#endif
