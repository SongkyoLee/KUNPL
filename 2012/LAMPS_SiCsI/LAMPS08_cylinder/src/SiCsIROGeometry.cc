//========================================
// SiCsIROGeometry.cc - KYO
//========================================

#include "SiCsIROGeometry.hh"
#include "SiCsIDummySD.hh" //KYO

#include "G4Box.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh" //KYO
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh" //KYO

SiCsIROGeometry::SiCsIROGeometry(G4String aString,
				G4double DIM_X_EXPHALL,
				G4double DIM_Y_EXPHALL,
				G4double DIM_Z_EXPHALL,
				G4double DIM_RIN_Si,
				G4double DIM_ROUT_Si,
				G4double DIM_RIN_CsI,
				G4double DIM_ROUT_CsI,
				G4double DIM_DPHI_SiCsI,
				G4double DIM_DZ_Si,
				G4double DIM_DZ_CsI,
				G4double DIM_DZ_Si_OFFSET,
				G4double DIM_X_VOXEL_SIZE_SiCsI,
				G4double DIM_Y_VOXEL_SIZE_SiCsI,
				G4double DIM_Z_VOXEL_SIZE_SiCsI):
	G4VReadOutGeometry(aString),
	X_EXPHALL(DIM_X_EXPHALL),
	Y_EXPHALL(DIM_Y_EXPHALL), 
	Z_EXPHALL(DIM_Z_EXPHALL),
	RIN_Si(DIM_RIN_Si),
	ROUT_Si(DIM_ROUT_Si),
	RIN_CsI(DIM_RIN_CsI),
	ROUT_CsI(DIM_ROUT_CsI),
	DPHI_SiCsI(DIM_DPHI_SiCsI),
	DZ_Si(DIM_DZ_Si),
	DZ_CsI(DIM_DZ_CsI),
	DZ_Si_OFFSET(DIM_DZ_Si_OFFSET),
	X_VOXEL_SIZE_SiCsI(DIM_X_VOXEL_SIZE_SiCsI),
	Y_VOXEL_SIZE_SiCsI(DIM_Y_VOXEL_SIZE_SiCsI),
	Z_VOXEL_SIZE_SiCsI(DIM_Z_VOXEL_SIZE_SiCsI)
{
}

SiCsIROGeometry::~SiCsIROGeometry()
{
}

G4VPhysicalVolume* SiCsIROGeometry::Build()
{

	// just for filling the volume of the ROGeometry
	G4Material* dummyMat = new G4Material("dummyMat", 1., 1*g/mole, 1*g/cm3);

	//=====================================
	// world volume of ROGeometry (cubic)
	//=====================================

	G4Box* RO_expHallSolid = new G4Box("RO_EXP_HALL", X_EXPHALL, Y_EXPHALL, Z_EXPHALL);
	G4LogicalVolume* RO_expHallLV = new G4LogicalVolume(RO_expHallSolid, dummyMat, "RO_EXP_HALL_SiCsI_LV");
	G4PVPlacement* RO_expHall = new G4PVPlacement(0, G4ThreeVector(), "RO_EXP_HALL_SiCsI_PV", RO_expHallLV, 0, false, 0);

	G4VisAttributes* RO_expHallVisAtt = new G4VisAttributes(false, G4Colour(1., 1., 1.));
	RO_expHallLV -> SetVisAttributes(RO_expHallVisAtt);

	//=====================================
	// SiCsI ROGeometry
	//=====================================

	const G4int NUM_VOXEL_X_SiCsI = (G4int)(2*ROUT_CsI/X_VOXEL_SIZE_SiCsI);
	const G4int NUM_VOXEL_Y_SiCsI = (G4int)(2*ROUT_CsI/Y_VOXEL_SIZE_SiCsI);
	const G4int NUM_VOXEL_Z_SiCsI = (G4int)(2*(DZ_Si+DZ_CsI)/Z_VOXEL_SIZE_SiCsI);


	G4Box *RO_SiCsI_Solid = new G4Box("RO_SiCsI_Solid", ROUT_CsI, ROUT_CsI, (DZ_Si+DZ_CsI)/2);
	G4LogicalVolume* RO_SiCsI_LV = new G4LogicalVolume(RO_SiCsI_Solid, dummyMat, "RO_SiCsI_LV");
	G4VPhysicalVolume* RO_SiCsI_PV = new G4PVPlacement(0, G4ThreeVector(0,0,DZ_Si_OFFSET+DZ_CsI/2), "RO_SiCsI_PV", RO_SiCsI_LV, RO_expHall, false, 0);
    

	//=====================================
	// Dividing into Voxels
	//=====================================

	
	G4Box *RO_SiCsI_X_DIV = new G4Box("RO_SiCsI_X_DIV",
					X_VOXEL_SIZE_SiCsI/2,
					ROUT_CsI,
					DZ_Si+DZ_CsI);
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
					DZ_Si+DZ_CsI);
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

