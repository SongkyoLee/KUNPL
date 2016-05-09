//-----------------------------------------
// TPCROGeometry,cc
//-----------------------------------------

#include "TPCROGeometry.hh"
#include "TPCDummySD.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UnionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"

TPCROGeometry::TPCROGeometry(G4String aString,
// For cylindrical world volume
//			     G4double R_DIM_EXPHALL,
//			     G4double DZ_DIM_EXPHALL,
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
			     G4double Z_VOXEL_SIZE_DIM_TPC):
	G4VReadOutGeometry(aString),
// For cylindrical world volume
//	R_EXPHALL(R_DIM_EXPHALL),
//	DZ_EXPHALL(DZ_DIM_EXPHALL),
// For cubic world volume
	X_EXPHALL(X_DIM_EXPHALL),
	Y_EXPHALL(Y_DIM_EXPHALL),
	Z_EXPHALL(Z_DIM_EXPHALL),
	Z_TPC_OFFSET(Z_DIM_TPC_OFFSET),
	ROUT_TPC(ROUT_DIM_TPC),
	RIN_TPC(RIN_DIM_TPC),
	Z_TPC(Z_DIM_TPC),
	PHI_TPC(PHI_DIM_TPC),
	X_VOXEL_SIZE_TPC(X_VOXEL_SIZE_DIM_TPC),
	Y_VOXEL_SIZE_TPC(Y_VOXEL_SIZE_DIM_TPC),
	Z_VOXEL_SIZE_TPC(Z_VOXEL_SIZE_DIM_TPC)
{
}

TPCROGeometry::~TPCROGeometry()
{
}

G4VPhysicalVolume* TPCROGeometry::Build()
{
	// A dummy material is used to fill the volumes of the readout geometry.
	G4Material* dummyMat = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);

	//------------------------------------------
	// World Volume of ReadOut Geometry - Genie
	//------------------------------------------

	// For cylindrical world volume
//	G4Tubs* RO_expHallSolid = new G4Tubs("RO_EXP_HALL_TPC", 0., R_EXPHALL, DZ_EXPHALL, 0., 360.*deg);

	// For cubic world volume
	G4Box* RO_expHallSolid = new G4Box("RO_EXP_HALL", X_EXPHALL, Y_EXPHALL, Z_EXPHALL);
	G4LogicalVolume* RO_expHallLV = new G4LogicalVolume(RO_expHallSolid, dummyMat, "RO_EXP_HALL_TPC_LV");
	G4PVPlacement* RO_expHall = new G4PVPlacement(0, G4ThreeVector(), "RO_EXP_HALL_TPC_PV", RO_expHallLV, 0, false, 0);

	G4VisAttributes* RO_expHallVisAtt = new G4VisAttributes(false, G4Colour(1., 1., 1.));
	RO_expHallLV -> SetVisAttributes(RO_expHallVisAtt);

	//------------------------------
	// TPC ReadOut Geometry - Genie
	//------------------------------

	const G4int NUM_VOXEL_X_TPC = (G4int)(2*ROUT_TPC/X_VOXEL_SIZE_TPC);
	const G4int NUM_VOXEL_Y_TPC = (G4int)(2*ROUT_TPC/Y_VOXEL_SIZE_TPC);
	const G4int NUM_VOXEL_Z_TPC = (G4int)(2*Z_TPC/Z_VOXEL_SIZE_TPC);
//	G4cout << NUM_VOXEL_X_TPC << "  " << NUM_VOXEL_Y_TPC << "  " << NUM_VOXEL_Z_TPC << G4endl;;

//	G4Solid* RO_TPC_Solid = new G4Tubs("ReadOut TPC Solenoid", RIN_TPC, ROUT_TPC, Z_TPC, 0, PHI_TPC);
	G4Box* RO_TPC_Solid = new G4Box("ReadOut TPC Solenoid", ROUT_TPC, ROUT_TPC, Z_TPC);
	G4LogicalVolume* RO_TPC_LV = new G4LogicalVolume(RO_TPC_Solid, dummyMat, "RO_TPC_LV");
	G4VPhysicalVolume* RO_TPC_PV = new G4PVPlacement(0,
							 G4ThreeVector(0, 0, Z_TPC_OFFSET),
							 "RO_TPC_PV",
							 RO_TPC_LV,
							 RO_expHall,
							 FALSE,
							 0);

	G4VisAttributes* RO_TPC_VisAtt = new G4VisAttributes(true, G4Colour(1., 1., 0.));
	RO_TPC_LV -> SetVisAttributes(RO_TPC_VisAtt);

	// Dividing into Voxels

	// Slice the box parallel to yz-plane
	G4Box* RO_TPC_X_DIV = new G4Box("RO_TPC_X_DIV",
					X_VOXEL_SIZE_TPC/2,
					ROUT_TPC,
					Z_TPC);

	G4LogicalVolume* RO_TPC_X_DIV_LV = new G4LogicalVolume(RO_TPC_X_DIV,
							       dummyMat,
							       "RO_TPC_X_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_TPC_X_DIV_PV = new G4PVReplica("RO_TPC_X_DIV_PV",
							     RO_TPC_X_DIV_LV,
							     RO_TPC_PV,
							     kXAxis,
							     NUM_VOXEL_X_TPC,
							     X_VOXEL_SIZE_TPC);

	// Slice the voxel right above parallel to xz-plane
	G4Box* RO_TPC_Y_DIV = new G4Box("RO_TPC_Y_DIV",
					X_VOXEL_SIZE_TPC/2,
					Y_VOXEL_SIZE_TPC/2,
					Z_TPC);
	
	G4LogicalVolume* RO_TPC_Y_DIV_LV = new G4LogicalVolume(RO_TPC_Y_DIV,
							       dummyMat,
							       "RO_TPC_Y_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_TPC_Y_DIV_PV = new G4PVReplica("RO_TPC_Y_DIV_PV",
							    RO_TPC_Y_DIV_LV,
							    RO_TPC_X_DIV_PV,
							    kYAxis,
							    NUM_VOXEL_Y_TPC,
							    Y_VOXEL_SIZE_TPC);

	// Slice the voxel right above parallel to xy-plane
	G4Box* RO_TPC_Z_DIV = new G4Box("RO_TPC_Z_DIV",
					X_VOXEL_SIZE_TPC/2,
					Y_VOXEL_SIZE_TPC/2,
					Z_VOXEL_SIZE_TPC/2);

	G4LogicalVolume* RO_TPC_Z_DIV_LV = new G4LogicalVolume(RO_TPC_Z_DIV,
							       dummyMat,
							       "RO_TPC_Z_DIV_LV",
							       0, 0, 0);

	RO_TPC_Z_DIV_PV = new G4PVReplica("RO_TPC_Z_DIV_PV",
					  RO_TPC_Z_DIV_LV,
					  RO_TPC_Y_DIV_PV,
					  kZAxis,
					  NUM_VOXEL_Z_TPC,
					  Z_VOXEL_SIZE_TPC);

	TPCDummySD *dummySD = new TPCDummySD;
	RO_TPC_Z_DIV_LV -> SetSensitiveDetector(dummySD);

	return RO_expHall;
}
