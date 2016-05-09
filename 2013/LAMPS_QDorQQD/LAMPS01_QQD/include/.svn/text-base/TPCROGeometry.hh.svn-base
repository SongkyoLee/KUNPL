//-----------------------------------------
// TPCROGeometry.hh
//-----------------------------------------

#ifndef TPC_RO_GEOMETRY_h
#define TPC_RO_GEOMETRY_h 1

#include "G4VReadOutGeometry.hh"

class TPCROGeometry : public G4VReadOutGeometry
{
public:
	TPCROGeometry(G4String aString,
// For cylindrical world volume
//		      G4double R_DIM_EXPHALL,
//		      G4double Z_DIM_EXPHALL,
// For cubic world volume
		      G4double X_DIM_EXPHALL,
		      G4double Y_DIM_EXPHALL,
		      G4double Z_DIM_EXPHALL,
		      G4double Z_DIM_TPC_OFFSET,
		      G4double ROUT_DIM_TPC,
		      G4double RIN_DIM_TPC,
		      G4double Z_DIM_TPC,
		      G4double PHI_DIM_TPC,
		      G4double X_VOXEL_SIZE_DIM_TPC,
		      G4double Y_VOXEL_SIZE_DIM_TPC,
		      G4double Z_VOXEL_SIZE_DIM_TPC);

	~TPCROGeometry();

private:
	G4VPhysicalVolume* Build();

private:
	// World Volume Parameter - cube
	G4double X_EXPHALL;
	G4double Y_EXPHALL;
	G4double Z_EXPHALL;

	// World Volume Parameter - cylinder
//	G4double R_EXPHALL;
//	G4double DZ_EXPHALL;

	// TPC Parameter
	G4double Z_TPC_OFFSET;
	G4double ROUT_TPC;
	G4double RIN_TPC;
	G4double Z_TPC;
	G4double PHI_TPC;
	G4double X_VOXEL_SIZE_TPC;
	G4double Y_VOXEL_SIZE_TPC;
	G4double Z_VOXEL_SIZE_TPC;

	G4VPhysicalVolume* RO_TPC_Z_DIV_PV;
};
#endif
