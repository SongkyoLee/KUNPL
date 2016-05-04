//-----------------------------------------
// DCROGeometry.hh
//-----------------------------------------

#ifndef DC_RO_GEOMETRY_h
#define DC_RO_GEOMETRY_h 1

#include "G4VReadOutGeometry.hh"
#include "G4ThreeVector.hh"

class DCROGeometry : public G4VReadOutGeometry
{
public:
	DCROGeometry(G4String aString,
// For cylindrical world volume
//		      G4double R_DIM_EXPHALL,
//		      G4double Z_DIM_EXPHALL,
// For cubic world volume
		      G4double X_DIM_EXPHALL,
		      G4double Y_DIM_EXPHALL,
		      G4double Z_DIM_EXPHALL,
		      G4double X_VOXEL_SIZE_DIM_DC,
		      G4double Y_VOXEL_SIZE_DIM_DC,
		      G4double Z_VOXEL_SIZE_DIM_DC,
		      G4double WIDTH_DCBD_DIM,
		      G4double HEIGHT_DCBD_DIM,
		      G4double THICKNESS_DCBD_DIM,
		      G4ThreeVector POS_DCBD_DIM,
		      G4double ROT_ANGLE_DCA1_DIM,
		      G4double WIDTH_DCU1_DIM,
		      G4double HEIGHT_DCU1_DIM,
		      G4double THICKNESS_DCU1_DIM,
		      G4ThreeVector POS_DCU1_DIM,
		      G4double WIDTH_DCD1_DIM,
		      G4double HEIGHT_DCD1_DIM,
		      G4double THICKNESS_DCD1_DIM,
		      G4ThreeVector POS_DCD1_DIM,
		      G4double ROT_ANGLE_DCA2_DIM,
		      G4double WIDTH_DCU2_DIM,
		      G4double HEIGHT_DCU2_DIM,
		      G4double THICKNEESS_DCU2_DIM,
		      G4ThreeVector POS_DCU2_DIM,
		      G4double WIDTH_DCD2_DIM,
		      G4double HEIGHT_DCD2_DIM,
		      G4double THICKNEESS_DCD2_DIM,
		      G4ThreeVector POS_DCD2_DIM
		      );

	~DCROGeometry();

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

	// DC Parameter
	G4double X_VOXEL_SIZE_DC;
	G4double Y_VOXEL_SIZE_DC;
	G4double Z_VOXEL_SIZE_DC;

	// Drift Chamber Before Dipole Magnet
	G4double WIDTH_DCBD;
	G4double HEIGHT_DCBD;
	G4double THICKNESS_DCBD;
	G4ThreeVector POS_DCBD;

	// Drift Chambers of Dipole Arm 1
	G4double ROT_ANGLE_DPA1;
	G4double WIDTH_DCU1; // upstream
	G4double HEIGHT_DCU1;
	G4double THICKNESS_DCU1;
	G4ThreeVector POS_DCU1;
	G4double WIDTH_DCD1; // downstream
	G4double HEIGHT_DCD1;
	G4double THICKNESS_DCD1;
	G4ThreeVector POS_DCD1;

	// Drift Chamber of Dipole Arm 2
	G4double ROT_ANGLE_DPA2;
	G4double WIDTH_DCU2; // upstream
	G4double HEIGHT_DCU2;
	G4double THICKNESS_DCU2;
	G4ThreeVector POS_DCU2;
	G4double WIDTH_DCD2; // downstream
	G4double HEIGHT_DCD2;
	G4double THICKNESS_DCD2;
	G4ThreeVector POS_DCD2;
};
#endif
