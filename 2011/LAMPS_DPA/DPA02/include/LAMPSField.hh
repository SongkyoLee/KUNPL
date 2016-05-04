// ====================================================================
//   LAMPSField.hh
// ====================================================================
#ifndef LAMPS_FIELD_H
#define LAMPS_FIELD_H

#include "globals.hh"
#include "G4MagneticField.hh"

const double solenoidOffset = 1617.0;

const int MAX_DIM_X_TOSCA = 31;
const int MAX_DIM_Y_TOSCA = 31;
const int MAX_DIM_Z_TOSCA = 51;

#define BFIELD_GRID_X 20.0
#define BFIELD_GRID_Y 20.0
#define BFIELD_GRID_Z 20.0

class LAMPSField : public G4MagneticField {
private:
  double xTosca[MAX_DIM_X_TOSCA];
  double yTosca[MAX_DIM_Y_TOSCA];
  double zTosca[MAX_DIM_Z_TOSCA];
  double bTosca[3][MAX_DIM_X_TOSCA][MAX_DIM_Y_TOSCA][MAX_DIM_Z_TOSCA];
  
public:
  LAMPSField() { }
  LAMPSField(char* fname);
  ~LAMPSField() { }
  
  void GetFieldValue(const  G4double Point[3],  G4double* Bfield ) const;

};

#endif
