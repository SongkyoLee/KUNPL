// ====================================================================
//   LAMPSDetectorConstruction.hh
// ====================================================================
#ifndef LAMPS_DETECTOR_CONSTRUCTION_H
#define LAMPS_DETECTOR_CONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "G4ThreeVector.hh"

class LAMPSDetectorMessenger;
class Fields;

class LAMPSDetectorConstruction : public G4VUserDetectorConstruction {
private:
	LAMPSDetectorMessenger*	DetMessenger;
	G4double DP_VALUES[6];
	G4ThreeVector DP_VALUE_SHIFT2;
	G4FieldManager *fieldMgr;
	Fields* myDPfield;

	G4double mField;
public:
  LAMPSDetectorConstruction();
  ~LAMPSDetectorConstruction(); 

  // implement it.
  virtual G4VPhysicalVolume* Construct(); 

  void MagField(G4double, G4double, G4double, G4double, G4double, G4double, G4double);
  void SetMagField(G4double);
  G4double GetDPField();
};

#endif
