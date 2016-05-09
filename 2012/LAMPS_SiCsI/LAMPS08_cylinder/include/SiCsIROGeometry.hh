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
			G4double);
    ~SiCsIROGeometry();
    
private:
    G4VPhysicalVolume *Build();
    
   //world volume parameters
    G4double X_EXPHALL;
    G4double Y_EXPHALL;
    G4double Z_EXPHALL;
   //SiCsI parameters
    G4double RIN_Si;
    G4double ROUT_Si;
    G4double RIN_CsI;
    G4double ROUT_CsI;
    G4double DPHI_SiCsI;
    G4double DZ_Si;
    G4double DZ_CsI;
    G4double DZ_Si_OFFSET;
    G4double X_VOXEL_SIZE_SiCsI;
    G4double Y_VOXEL_SIZE_SiCsI;
    G4double Z_VOXEL_SIZE_SiCsI;

};
#endif

