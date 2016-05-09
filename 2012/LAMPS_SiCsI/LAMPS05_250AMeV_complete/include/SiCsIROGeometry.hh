//===============================
// SiCsIROGeometry.hh - KYO
//===============================

#ifndef SiCsIROGEOMETRY_h
#define SiCsIROGEOMETRY_h 1

#include "G4VReadOutGeometry.hh"

class SiCsIROGeometry: public G4VReadOutGeometry
{
public:
    SiCsIROGeometry(G4String aString,
			G4double,
			G4double,
			G4double,
			G4double,
			G4double,
			G4double,
			G4double,
			G4double,
			G4double,
			G4int);
    
    ~SiCsIROGeometry();
    
private:
    G4VPhysicalVolume *Build();
    
   //world volume parameters
    G4double X_EXPHALL;
    G4double Y_EXPHALL;
    G4double Z_EXPHALL;
   //SiCsI parameters
    G4double detS;
    G4double detC;
    G4double distS;
    G4double coverage;
    G4double angle1;
    G4double angle2;
    G4int pad;
};
#endif

