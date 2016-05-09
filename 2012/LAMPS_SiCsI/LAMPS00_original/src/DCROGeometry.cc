//-----------------------------------------
// DCROGeometry,cc
//-----------------------------------------

#include "DCROGeometry.hh"
#include "DCDummySD.hh"
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
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"

DCROGeometry::DCROGeometry(G4String aString,
// For cylindrical world volume
//			     G4double R_DIM_EXPHALL,
//			     G4double DZ_DIM_EXPHALL,
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
	                     G4double ROT_ANGLE_DPA1_DIM,
	                     G4double WIDTH_DCU1_DIM,
	                     G4double HEIGHT_DCU1_DIM,
	                     G4double THICKNESS_DCU1_DIM,
	                     G4ThreeVector POS_DCU1_DIM,
	                     G4double WIDTH_DCD1_DIM,
	                     G4double HEIGHT_DCD1_DIM,
	                     G4double THICKNESS_DCD1_DIM,
	                     G4ThreeVector POS_DCD1_DIM,
	                     G4double ROT_ANGLE_DPA2_DIM,
	                     G4double WIDTH_DCU2_DIM,
	                     G4double HEIGHT_DCU2_DIM,
	                     G4double THICKNESS_DCU2_DIM,
	                     G4ThreeVector POS_DCU2_DIM,
	                     G4double WIDTH_DCD2_DIM,
	                     G4double HEIGHT_DCD2_DIM,
	                     G4double THICKNESS_DCD2_DIM,
	                     G4ThreeVector POS_DCD2_DIM):
	G4VReadOutGeometry(aString),
// For cylindrical world volume
//	R_EXPHALL(R_DIM_EXPHALL),
//	DZ_EXPHALL(DZ_DIM_EXPHALL),
// For cubic world volume
	X_EXPHALL(X_DIM_EXPHALL),
	Y_EXPHALL(Y_DIM_EXPHALL),
	Z_EXPHALL(Z_DIM_EXPHALL),
	X_VOXEL_SIZE_DC(X_VOXEL_SIZE_DIM_DC),
	Y_VOXEL_SIZE_DC(Y_VOXEL_SIZE_DIM_DC),
	Z_VOXEL_SIZE_DC(Z_VOXEL_SIZE_DIM_DC),
        WIDTH_DCBD(WIDTH_DCBD_DIM),
        HEIGHT_DCBD(HEIGHT_DCBD_DIM),
        THICKNESS_DCBD(THICKNESS_DCBD_DIM),
        POS_DCBD(POS_DCBD_DIM),
        ROT_ANGLE_DPA1(ROT_ANGLE_DPA1_DIM),
        WIDTH_DCU1(WIDTH_DCU1_DIM),
        HEIGHT_DCU1(HEIGHT_DCU1_DIM),
        THICKNESS_DCU1(THICKNESS_DCU1_DIM),
        POS_DCU1(POS_DCU1_DIM),
        WIDTH_DCD1(WIDTH_DCD1_DIM),
        HEIGHT_DCD1(HEIGHT_DCD1_DIM),
        THICKNESS_DCD1(THICKNESS_DCD1_DIM),
        POS_DCD1(POS_DCD1_DIM),
        ROT_ANGLE_DPA2(ROT_ANGLE_DPA2_DIM),
        WIDTH_DCU2(WIDTH_DCU2_DIM),
        HEIGHT_DCU2(HEIGHT_DCU2_DIM),
        THICKNESS_DCU2(THICKNESS_DCU2_DIM),
        POS_DCU2(POS_DCU2_DIM),
        WIDTH_DCD2(WIDTH_DCD2_DIM),
        HEIGHT_DCD2(HEIGHT_DCD2_DIM),
        THICKNESS_DCD2(THICKNESS_DCD2_DIM),
        POS_DCD2(POS_DCD2_DIM)
{
}

DCROGeometry::~DCROGeometry()
{
}

G4VPhysicalVolume* DCROGeometry::Build()
{
	// A dummy material is used to fill the volumes of the readout geometry.
	G4Material* dummyMat = new G4Material(name="dummyMat", 1., 1.*g/mole, 1.*g/cm3);

	//------------------------------------------
	// World Volume of ReadOut Geometry - Genie
	//------------------------------------------

	// For cylindrical world volume
//	G4Tubs* RO_expHallSolid = new G4Tubs("RO_EXP_HALL_DC", 0., R_EXPHALL, DZ_EXPHALL, 0., 360.*deg); 
	// For cubic world volume
	G4Box* RO_expHallSolid = new G4Box("RO_EXP_HALL", X_EXPHALL, Y_EXPHALL, Z_EXPHALL);
	G4LogicalVolume* RO_expHallLV = new G4LogicalVolume(RO_expHallSolid, dummyMat, "RO_EXP_HALL_DC_LV");
	G4PVPlacement* RO_expHall = new G4PVPlacement(0, G4ThreeVector(), "RO_EXP_HALL_DC_PV", RO_expHallLV, 0, false, 0);

	G4VisAttributes* RO_expHallVisAtt = new G4VisAttributes(false, G4Colour(1., 1., 1.));
	RO_expHallLV -> SetVisAttributes(RO_expHallVisAtt);

	DCDummySD *dummySD = new DCDummySD;

	//-------------------------------
	// DCBD ReadOut Geometry - Genie
	//-------------------------------

	const G4int NUM_VOXEL_X_DCBD = (G4int)(WIDTH_DCBD/X_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Y_DCBD = (G4int)(HEIGHT_DCBD/Y_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Z_DCBD = (G4int)(THICKNESS_DCBD/Z_VOXEL_SIZE_DC);

	G4Box* RO_DCBD_Solid = new G4Box("ReadOut DCBD Solenoid", WIDTH_DCBD/2, HEIGHT_DCBD/2, THICKNESS_DCBD/2);
	G4LogicalVolume* RO_DCBD_LV = new G4LogicalVolume(RO_DCBD_Solid, dummyMat, "RO_DCBD_LV");
	G4VPhysicalVolume* RO_DCBD_PV = new G4PVPlacement(0,
							 POS_DCBD,
							 "RO_DCBD_PV",
							 RO_DCBD_LV,
							 RO_expHall,
							 FALSE,
							 0);

	// Dividing into Voxels

	// Slice the box parallel to yz-plane
	G4Box* RO_DCBD_X_DIV = new G4Box("RO_DCBD_X_DIV",
					X_VOXEL_SIZE_DC/2,
					HEIGHT_DCBD/2,
					THICKNESS_DCBD/2);

	G4LogicalVolume* RO_DCBD_X_DIV_LV = new G4LogicalVolume(RO_DCBD_X_DIV,
							       dummyMat,
							       "RO_DCBD_X_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCBD_X_DIV_PV = new G4PVReplica("RO_DCBD_X_DIV_PV",
							     RO_DCBD_X_DIV_LV,
							     RO_DCBD_PV,
							     kXAxis,
							     NUM_VOXEL_X_DCBD,
							     X_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xz-plane
	G4Box* RO_DCBD_Y_DIV = new G4Box("RO_DCBD_Y_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					THICKNESS_DCBD/2);
	
	G4LogicalVolume* RO_DCBD_Y_DIV_LV = new G4LogicalVolume(RO_DCBD_Y_DIV,
							       dummyMat,
							       "RO_DCBD_Y_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCBD_Y_DIV_PV = new G4PVReplica("RO_DCBD_Y_DIV_PV",
							    RO_DCBD_Y_DIV_LV,
							    RO_DCBD_X_DIV_PV,
							    kYAxis,
							    NUM_VOXEL_Y_DCBD,
							    Y_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xy-plane
	G4Box* RO_DCBD_Z_DIV = new G4Box("RO_DCBD_Z_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					Z_VOXEL_SIZE_DC/2);

	G4LogicalVolume* RO_DCBD_Z_DIV_LV = new G4LogicalVolume(RO_DCBD_Z_DIV,
							        dummyMat,
							        "RO_DCBD_Z_DIV_LV",
							        0, 0, 0);

	G4VPhysicalVolume* RO_DCBD_Z_DIV_PV = new G4PVReplica("RO_DCBD_Z_DIV_PV",
					  RO_DCBD_Z_DIV_LV,
					  RO_DCBD_Y_DIV_PV,
					  kZAxis,
					  NUM_VOXEL_Z_DCBD,
					  Z_VOXEL_SIZE_DC);

	RO_DCBD_Z_DIV_LV -> SetSensitiveDetector(dummySD);

	//==============
	// Dipole Arm 1
	//==============
	
	G4RotationMatrix* ROTATE_DPA1 = new G4RotationMatrix();
	ROTATE_DPA1 -> rotateY(-ROT_ANGLE_DPA1);

	//-------------------------------
	// DCU1 ReadOut Geometry - Genie
	//-------------------------------

	const G4int NUM_VOXEL_X_DCU1 = (G4int)(WIDTH_DCU1/X_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Y_DCU1 = (G4int)(HEIGHT_DCU1/Y_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Z_DCU1 = (G4int)(THICKNESS_DCU1/Z_VOXEL_SIZE_DC);

	G4Box* RO_DCU1_Solid = new G4Box("ReadOut DCU1 Solenoid", WIDTH_DCU1/2, HEIGHT_DCU1/2, THICKNESS_DCU1/2);
	G4LogicalVolume* RO_DCU1_LV = new G4LogicalVolume(RO_DCU1_Solid, dummyMat, "RO_DCU1_LV");
	G4VPhysicalVolume* RO_DCU1_PV = new G4PVPlacement(ROTATE_DPA1,
							 POS_DCU1,
							 "RO_DCU1_PV",
							 RO_DCU1_LV,
							 RO_expHall,
							 FALSE,
							 0);

	G4VisAttributes* RO_DCU1_VisAtt = new G4VisAttributes(true, G4Colour(1., 1., 0.));
	RO_DCU1_LV -> SetVisAttributes(RO_DCU1_VisAtt);

	// Dividing into Voxels

	// Slice the box parallel to yz-plane
	G4Box* RO_DCU1_X_DIV = new G4Box("RO_DCU1_X_DIV",
					X_VOXEL_SIZE_DC/2,
					HEIGHT_DCU1/2,
					THICKNESS_DCU1/2);

	G4LogicalVolume* RO_DCU1_X_DIV_LV = new G4LogicalVolume(RO_DCU1_X_DIV,
							       dummyMat,
							       "RO_DCU1_X_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCU1_X_DIV_PV = new G4PVReplica("RO_DCU1_X_DIV_PV",
							     RO_DCU1_X_DIV_LV,
							     RO_DCU1_PV,
							     kXAxis,
							     NUM_VOXEL_X_DCU1,
							     X_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xz-plane
	G4Box* RO_DCU1_Y_DIV = new G4Box("RO_DCU1_Y_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					THICKNESS_DCU1/2);
	
	G4LogicalVolume* RO_DCU1_Y_DIV_LV = new G4LogicalVolume(RO_DCU1_Y_DIV,
							       dummyMat,
							       "RO_DCU1_Y_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCU1_Y_DIV_PV = new G4PVReplica("RO_DCU1_Y_DIV_PV",
							    RO_DCU1_Y_DIV_LV,
							    RO_DCU1_X_DIV_PV,
							    kYAxis,
							    NUM_VOXEL_Y_DCU1,
							    Y_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xy-plane
	G4Box* RO_DCU1_Z_DIV = new G4Box("RO_DCU1_Z_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					Z_VOXEL_SIZE_DC/2);

	G4LogicalVolume* RO_DCU1_Z_DIV_LV = new G4LogicalVolume(RO_DCU1_Z_DIV,
							       dummyMat,
							       "RO_DCU1_Z_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCU1_Z_DIV_PV = new G4PVReplica("RO_DCU1_Z_DIV_PV",
							      RO_DCU1_Z_DIV_LV,
							      RO_DCU1_Y_DIV_PV,
							      kZAxis,
							      NUM_VOXEL_Z_DCU1,
							      Z_VOXEL_SIZE_DC);

	RO_DCU1_Z_DIV_LV -> SetSensitiveDetector(dummySD);

	//-------------------------------
	// DCD1 ReadOut Geometry - Genie
	//-------------------------------

	const G4int NUM_VOXEL_X_DCD1 = (G4int)(WIDTH_DCD1/X_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Y_DCD1 = (G4int)(HEIGHT_DCD1/Y_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Z_DCD1 = (G4int)(THICKNESS_DCD1/Z_VOXEL_SIZE_DC);

	G4Box* RO_DCD1_Solid = new G4Box("ReadOut DCD1 Solenoid", WIDTH_DCD1/2, HEIGHT_DCD1/2, THICKNESS_DCD1/2);
	G4LogicalVolume* RO_DCD1_LV = new G4LogicalVolume(RO_DCD1_Solid, dummyMat, "RO_DCD1_LV");
	G4VPhysicalVolume* RO_DCD1_PV = new G4PVPlacement(ROTATE_DPA1,
							 POS_DCD1,
							 "RO_DCD1_PV",
							 RO_DCD1_LV,
							 RO_expHall,
							 FALSE,
							 0);

	G4VisAttributes* RO_DCD1_VisAtt = new G4VisAttributes(true, G4Colour(1., 1., 0.));
	RO_DCD1_LV -> SetVisAttributes(RO_DCD1_VisAtt);

	// Dividing into Voxels

	// Slice the box parallel to yz-plane
	G4Box* RO_DCD1_X_DIV = new G4Box("RO_DCD1_X_DIV",
					X_VOXEL_SIZE_DC/2,
					HEIGHT_DCD1/2,
					THICKNESS_DCD1/2);

	G4LogicalVolume* RO_DCD1_X_DIV_LV = new G4LogicalVolume(RO_DCD1_X_DIV,
							       dummyMat,
							       "RO_DCD1_X_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCD1_X_DIV_PV = new G4PVReplica("RO_DCD1_X_DIV_PV",
							     RO_DCD1_X_DIV_LV,
							     RO_DCD1_PV,
							     kXAxis,
							     NUM_VOXEL_X_DCD1,
							     X_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xz-plane
	G4Box* RO_DCD1_Y_DIV = new G4Box("RO_DCD1_Y_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					THICKNESS_DCD1/2);
	
	G4LogicalVolume* RO_DCD1_Y_DIV_LV = new G4LogicalVolume(RO_DCD1_Y_DIV,
							       dummyMat,
							       "RO_DCD1_Y_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCD1_Y_DIV_PV = new G4PVReplica("RO_DCD1_Y_DIV_PV",
							    RO_DCD1_Y_DIV_LV,
							    RO_DCD1_X_DIV_PV,
							    kYAxis,
							    NUM_VOXEL_Y_DCD1,
							    Y_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xy-plane
	G4Box* RO_DCD1_Z_DIV = new G4Box("RO_DCD1_Z_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					Z_VOXEL_SIZE_DC/2);

	G4LogicalVolume* RO_DCD1_Z_DIV_LV = new G4LogicalVolume(RO_DCD1_Z_DIV,
							       dummyMat,
							       "RO_DCD1_Z_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCD1_Z_DIV_PV = new G4PVReplica("RO_DCD1_Z_DIV_PV",
							      RO_DCD1_Z_DIV_LV,
							      RO_DCD1_Y_DIV_PV,
							      kZAxis,
							      NUM_VOXEL_Z_DCD1,
							      Z_VOXEL_SIZE_DC);

	RO_DCD1_Z_DIV_LV -> SetSensitiveDetector(dummySD);

	//==============
	// Dipole Arm 2
	//==============
	
	G4RotationMatrix* ROTATE_DPA2 = new G4RotationMatrix();
	ROTATE_DPA2 -> rotateY(-ROT_ANGLE_DPA2);

	//-------------------------------
	// DCU2 ReadOut Geometry - Genie
	//-------------------------------

	const G4int NUM_VOXEL_X_DCU2 = (G4int)(WIDTH_DCU2/X_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Y_DCU2 = (G4int)(HEIGHT_DCU2/Y_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Z_DCU2 = (G4int)(THICKNESS_DCU2/Z_VOXEL_SIZE_DC);

	G4Box* RO_DCU2_Solid = new G4Box("ReadOut DCU2 Solenoid", WIDTH_DCU2/2, HEIGHT_DCU2/2, THICKNESS_DCU2/2);
	G4LogicalVolume* RO_DCU2_LV = new G4LogicalVolume(RO_DCU2_Solid, dummyMat, "RO_DCU2_LV");
	G4VPhysicalVolume* RO_DCU2_PV = new G4PVPlacement(ROTATE_DPA2,
							 POS_DCU2,
							 "RO_DCU2_PV",
							 RO_DCU2_LV,
							 RO_expHall,
							 FALSE,
							 0);

	G4VisAttributes* RO_DCU2_VisAtt = new G4VisAttributes(true, G4Colour(1., 1., 0.));
	RO_DCU2_LV -> SetVisAttributes(RO_DCU2_VisAtt);

	// Dividing into Voxels

	// Slice the box parallel to yz-plane
	G4Box* RO_DCU2_X_DIV = new G4Box("RO_DCU2_X_DIV",
					X_VOXEL_SIZE_DC/2,
					HEIGHT_DCU2/2,
					THICKNESS_DCU2/2);

	G4LogicalVolume* RO_DCU2_X_DIV_LV = new G4LogicalVolume(RO_DCU2_X_DIV,
							       dummyMat,
							       "RO_DCU2_X_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCU2_X_DIV_PV = new G4PVReplica("RO_DCU2_X_DIV_PV",
							     RO_DCU2_X_DIV_LV,
							     RO_DCU2_PV,
							     kXAxis,
							     NUM_VOXEL_X_DCU2,
							     X_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xz-plane
	G4Box* RO_DCU2_Y_DIV = new G4Box("RO_DCU2_Y_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					THICKNESS_DCU2/2);
	
	G4LogicalVolume* RO_DCU2_Y_DIV_LV = new G4LogicalVolume(RO_DCU2_Y_DIV,
							       dummyMat,
							       "RO_DCU2_Y_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCU2_Y_DIV_PV = new G4PVReplica("RO_DCU2_Y_DIV_PV",
							    RO_DCU2_Y_DIV_LV,
							    RO_DCU2_X_DIV_PV,
							    kYAxis,
							    NUM_VOXEL_Y_DCU2,
							    Y_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xy-plane
	G4Box* RO_DCU2_Z_DIV = new G4Box("RO_DCU2_Z_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					Z_VOXEL_SIZE_DC/2);

	G4LogicalVolume* RO_DCU2_Z_DIV_LV = new G4LogicalVolume(RO_DCU2_Z_DIV,
							       dummyMat,
							       "RO_DCU2_Z_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCU2_Z_DIV_PV = new G4PVReplica("RO_DCU2_Z_DIV_PV",
							      RO_DCU2_Z_DIV_LV,
							      RO_DCU2_Y_DIV_PV,
							      kZAxis,
							      NUM_VOXEL_Z_DCU2,
							      Z_VOXEL_SIZE_DC);

	RO_DCU2_Z_DIV_LV -> SetSensitiveDetector(dummySD);

	//-------------------------------
	// DCD2 ReadOut Geometry - Genie
	//-------------------------------

	const G4int NUM_VOXEL_X_DCD2 = (G4int)(WIDTH_DCD2/X_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Y_DCD2 = (G4int)(HEIGHT_DCD2/Y_VOXEL_SIZE_DC);
	const G4int NUM_VOXEL_Z_DCD2 = (G4int)(THICKNESS_DCD2/Z_VOXEL_SIZE_DC);

	G4Box* RO_DCD2_Solid = new G4Box("ReadOut DCD2 Solenoid", WIDTH_DCD2/2, HEIGHT_DCD2/2, THICKNESS_DCD2/2);
	G4LogicalVolume* RO_DCD2_LV = new G4LogicalVolume(RO_DCD2_Solid, dummyMat, "RO_DCD2_LV");
	G4VPhysicalVolume* RO_DCD2_PV = new G4PVPlacement(ROTATE_DPA2,
							 POS_DCD2,
							 "RO_DCD2_PV",
							 RO_DCD2_LV,
							 RO_expHall,
							 FALSE,
							 0);

	G4VisAttributes* RO_DCD2_VisAtt = new G4VisAttributes(true, G4Colour(1., 1., 0.));
	RO_DCD2_LV -> SetVisAttributes(RO_DCD2_VisAtt);

	// Dividing into Voxels

	// Slice the box parallel to yz-plane
	G4Box* RO_DCD2_X_DIV = new G4Box("RO_DCD2_X_DIV",
					X_VOXEL_SIZE_DC/2,
					HEIGHT_DCD2/2,
					THICKNESS_DCD2/2);

	G4LogicalVolume* RO_DCD2_X_DIV_LV = new G4LogicalVolume(RO_DCD2_X_DIV,
							       dummyMat,
							       "RO_DCD2_X_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCD2_X_DIV_PV = new G4PVReplica("RO_DCD2_X_DIV_PV",
							     RO_DCD2_X_DIV_LV,
							     RO_DCD2_PV,
							     kXAxis,
							     NUM_VOXEL_X_DCD2,
							     X_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xz-plane
	G4Box* RO_DCD2_Y_DIV = new G4Box("RO_DCD2_Y_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					THICKNESS_DCD2/2);
	
	G4LogicalVolume* RO_DCD2_Y_DIV_LV = new G4LogicalVolume(RO_DCD2_Y_DIV,
							       dummyMat,
							       "RO_DCD2_Y_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCD2_Y_DIV_PV = new G4PVReplica("RO_DCD2_Y_DIV_PV",
							    RO_DCD2_Y_DIV_LV,
							    RO_DCD2_X_DIV_PV,
							    kYAxis,
							    NUM_VOXEL_Y_DCD2,
							    Y_VOXEL_SIZE_DC);

	// Slice the voxel right above parallel to xy-plane
	G4Box* RO_DCD2_Z_DIV = new G4Box("RO_DCD2_Z_DIV",
					X_VOXEL_SIZE_DC/2,
					Y_VOXEL_SIZE_DC/2,
					Z_VOXEL_SIZE_DC/2);

	G4LogicalVolume* RO_DCD2_Z_DIV_LV = new G4LogicalVolume(RO_DCD2_Z_DIV,
							       dummyMat,
							       "RO_DCD2_Z_DIV_LV",
							       0, 0, 0);

	G4VPhysicalVolume* RO_DCD2_Z_DIV_PV = new G4PVReplica("RO_DCD2_Z_DIV_PV",
							      RO_DCD2_Z_DIV_LV,
							      RO_DCD2_Y_DIV_PV,
							      kZAxis,
							      NUM_VOXEL_Z_DCD2,
						  	      Z_VOXEL_SIZE_DC);

	RO_DCD2_Z_DIV_LV -> SetSensitiveDetector(dummySD);

	return RO_expHall;
}
