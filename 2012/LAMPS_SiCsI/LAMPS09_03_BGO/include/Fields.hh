//===========
// Fields.hh
//===========
#ifndef FIELDS_H
#define FIELDS_H 1

#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

class Fields : public G4MagneticField {
private:
  G4double X_DIM;
  G4double Y_DIM;
  G4double Z_DIM;
  G4double CENTER_SHIFT;
  G4double DP_SHIFT;
  G4double ROT_ANGLE;
  G4double F_STRENGTH;

public:
  Fields(G4double X_DIM, G4double Y_DIM, G4double Z_DIM, G4double CENTER_SHIFT, G4double d_FROM_NEW_CENTER_DP, G4double ROT_ANGLE, G4double F_STRENGTH);
  void GetFieldValue(const  G4double Point[3],  G4double* Bfield ) const;
};

#endif
