//========================================
// SiCsIROGeometry.cc - KYO
//========================================

#include "SiCsIROGeometry.hh"
#include "SiCsIDummySD.hh"

#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"

SiCsIROGeometry::SiCsIROGeometry(G4String aString,
				G4double DIM_X_EXPHALL,
				G4double DIM_Y_EXPHALL,
				G4double DIM_Z_EXPHALL,
				G4double DIM_DZ_SiF,
				G4double DIM_DZ_SiS,
				G4double DIM_DZ_SiT,
				G4double DIM_DZ_OFFSET_surface,
				G4double DIM_X_VOXEL_SIZE_SiCsI,
				G4double DIM_Y_VOXEL_SIZE_SiCsI,
				G4double DIM_Z_VOXEL_SIZE_SiCsI,
				G4double DIM_COVERAGE,
				G4double DIM_ANGLE1,
				G4int DIM_PADNUM)
	:G4VReadOutGeometry(aString),
	X_EXPHALL(DIM_X_EXPHALL),
	Y_EXPHALL(DIM_Y_EXPHALL), 
	Z_EXPHALL(DIM_Z_EXPHALL),
	DZ_SiF(DIM_DZ_SiF),
	DZ_SiS(DIM_DZ_SiS),
	DZ_SiT(DIM_DZ_SiT),
	DZ_OFFSET_surface(DIM_DZ_OFFSET_surface),
	X_VOXEL_SIZE_SiCsI(DIM_X_VOXEL_SIZE_SiCsI),
	Y_VOXEL_SIZE_SiCsI(DIM_Y_VOXEL_SIZE_SiCsI),
	Z_VOXEL_SIZE_SiCsI(DIM_Z_VOXEL_SIZE_SiCsI),
	COVERAGE(DIM_COVERAGE),
	ANGLE1(DIM_ANGLE1),
	PADNUM(DIM_PADNUM)
{
}

SiCsIROGeometry::~SiCsIROGeometry()
{
}

G4VPhysicalVolume* SiCsIROGeometry::Build()
{
	// just for filling the volume of the ROGeometry
	G4Material* dummyMat = new G4Material("dummyMat", 1., 1*g/mole, 1*g/cm3);
  
	//====================================================
	// world volume of ROGeometry
	//====================================================

	G4Box* RO_expHallSolid = new G4Box("RO_EXP_HALL", X_EXPHALL, Y_EXPHALL, Z_EXPHALL);
	G4LogicalVolume* RO_expHallLV = new G4LogicalVolume(RO_expHallSolid, dummyMat, "RO_EXP_HALL_SiCsI_LV");
	G4PVPlacement* RO_expHall = new G4PVPlacement(0, G4ThreeVector(), "RO_EXP_HALL_SiCsI_PV", RO_expHallLV, 0, false, 0);

	G4VisAttributes* RO_expHallVisAtt = new G4VisAttributes(false, G4Colour(1., 1., 1.));
	RO_expHallLV -> SetVisAttributes(RO_expHallVisAtt);

	//=============================================
	// SiCsI ReadOut
	//==============================================

	const G4double ROUT_SiCsI = 150*mm; // temporary : same with RIN_TPC
	const G4double DZ_SiCsI = 600*mm; //temporary (half length of TPC)
	const G4double DZ_OFFSET_SiCsI = 300*mm; // temporary
	const G4int NUM_VOXEL_X_SiCsI= (G4int)(2*ROUT_SiCsI/X_VOXEL_SIZE_SiCsI);
	const G4int NUM_VOXEL_Y_SiCsI= (G4int)(2*ROUT_SiCsI/Y_VOXEL_SIZE_SiCsI);
	const G4int NUM_VOXEL_Z_SiCsI= (G4int)(2*DZ_SiCsI/Z_VOXEL_SIZE_SiCsI);

	G4Box *RO_SiCsI_Solid = new G4Box("RO_SiCsI_Solid", ROUT_SiCsI, ROUT_SiCsI, DZ_SiCsI/2);
	G4LogicalVolume* RO_SiCsI_LV = new G4LogicalVolume(RO_SiCsI_Solid, dummyMat, "RO_SiCsI_LV");
	G4VPhysicalVolume* RO_SiCsI_PV = new G4PVPlacement(0, G4ThreeVector(0,0,DZ_OFFSET_SiCsI), "RO_SiCsI_PV", RO_SiCsI_LV, RO_expHall, false, 0);
    

	//=====================================
	// Dividing into Voxels
	//=====================================

	
	G4Box *RO_SiCsI_X_DIV = new G4Box("RO_SiCsI_X_DIV",
					X_VOXEL_SIZE_SiCsI/2,
					ROUT_SiCsI,
					DZ_SiCsI);
	G4LogicalVolume* RO_SiCsI_X_DIV_LV = new G4LogicalVolume(RO_SiCsI_X_DIV,
								 dummyMat,
								 "RO_SiCsI_X_DIV_LV",
								 0, 0, 0);
	G4VPhysicalVolume* RO_SiCsI_X_DIV_PV = new G4PVReplica("RO_SiCsI_X_DIV_PV",
                                                       RO_SiCsI_X_DIV_LV,
                                                       RO_SiCsI_PV,
                                                       kXAxis,
                                                       NUM_VOXEL_X_SiCsI,
                                                       X_VOXEL_SIZE_SiCsI);

	
	G4Box *RO_SiCsI_Y_DIV = new G4Box("RO_SiCsI_Y_DIV",
					X_VOXEL_SIZE_SiCsI/2,
					Y_VOXEL_SIZE_SiCsI/2,
					DZ_SiCsI);
	G4LogicalVolume* RO_SiCsI_Y_DIV_LV = new G4LogicalVolume(RO_SiCsI_Y_DIV,
								 dummyMat,
								 "RO_SiCsI_Y_DIV_LV",
								 0, 0, 0);
	G4VPhysicalVolume* RO_SiCsI_Y_DIV_PV = new G4PVReplica("RO_SiCsI_Y_DIV_PV",
                                                       RO_SiCsI_Y_DIV_LV,
                                                       RO_SiCsI_X_DIV_PV,
                                                       kYAxis,
                                                       NUM_VOXEL_Y_SiCsI,
                                                       Y_VOXEL_SIZE_SiCsI);
	
	G4Box *RO_SiCsI_Z_DIV = new G4Box("RO_SiCsI_Z_DIV",
					X_VOXEL_SIZE_SiCsI/2,
					Y_VOXEL_SIZE_SiCsI/2,
					Z_VOXEL_SIZE_SiCsI/2);
	G4LogicalVolume* RO_SiCsI_Z_DIV_LV = new G4LogicalVolume(RO_SiCsI_Z_DIV,
								 dummyMat,
								 "RO_SiCsI_Z_DIV_LV",
								 0, 0, 0);
	G4VPhysicalVolume* RO_SiCsI_Z_DIV_PV = new G4PVReplica("RO_SiCsI_Z_DIV_PV",
                                                       RO_SiCsI_Z_DIV_LV,
                                                       RO_SiCsI_Y_DIV_PV,
                                                       kZAxis,
                                                       NUM_VOXEL_Z_SiCsI,
                                                       Z_VOXEL_SIZE_SiCsI);
 
    SiCsIDummySD *dummySD = new SiCsIDummySD;
    RO_SiCsI_Z_DIV_LV -> SetSensitiveDetector(dummySD);

    return RO_expHall;
}

