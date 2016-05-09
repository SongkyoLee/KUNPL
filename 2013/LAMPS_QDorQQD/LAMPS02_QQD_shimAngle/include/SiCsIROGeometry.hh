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
    G4double DZ_SiF;
    G4double DZ_SiS;
    G4double DZ_SiT;
    G4double DZ_OFFSET_SiF;
    G4double DZ_OFFSET_layer;
    G4double X_VOXEL_SIZE_SiCsI;
    G4double Y_VOXEL_SIZE_SiCsI;
    G4double Z_VOXEL_SIZE_SiCsI;
    G4double COVERAGE;
    G4double ANGLE1;
    G4double ANGLE2;
    G4int PADNUM;
};
#endif

