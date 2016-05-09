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
				G4double val1,
				G4double val2,
				G4double val3,
				G4double val4,
				G4double val5,
				G4double val6,
				G4double val7,
				G4double val8,
				G4double val9,
				G4int val10)
	:G4VReadOutGeometry(aString),
	X_EXPHALL(val1),
	Y_EXPHALL(val2), 
	Z_EXPHALL(val3),
	detS(val4),
	detC(val5),
	distS(val6),
	coverage(val7),
	angle1(val8),
	angle2(val9),
	pad(val10)
{
}

SiCsIROGeometry::~SiCsIROGeometry()
{
}

G4VPhysicalVolume* SiCsIROGeometry::Build()
{

	const G4double detX = 30.0*cm; //KYO :temporary
	const G4double detY = 30.0*cm; //KYO
	const G4double detZ = 25.0*cm; //KYO
	const G4int num_XVoxels_SiCsI = 30;
	const G4int num_YVoxels_SiCsI = 30;
	const G4int num_ZVoxels_SiCsI = 25;

	// just for filling the volume of the ROGeometry
	G4Material* dummyMat = new G4Material("dummyMat", 1., 1*g/mole, 1*g/cm3);
    
	// world volume
	G4Box* RO_expHallSolid = new G4Box("RO_EXP_HALL", X_EXPHALL, Y_EXPHALL, Z_EXPHALL);
	G4LogicalVolume* RO_expHallLV = new G4LogicalVolume(RO_expHallSolid, dummyMat, "RO_EXP_HALL_SiCsI_LV");
	G4PVPlacement* RO_expHall = new G4PVPlacement(0, G4ThreeVector(), "RO_EXP_HALL_SiCsI_PV", RO_expHallLV, 0, false, 0);

	G4VisAttributes* RO_expHallVisAtt = new G4VisAttributes(false, G4Colour(1., 1., 1.));
	RO_expHallLV -> SetVisAttributes(RO_expHallVisAtt);

	// SiCsI ReadOut // placement is also temporary
	G4Box *RODetSolid = new G4Box("RODetSolid", detX/2, detY/2, detZ/2);
	G4LogicalVolume* RODetLV = new G4LogicalVolume(RODetSolid, dummyMat, "RPDetLV");
	G4VPhysicalVolume* RODetPV = new G4PVPlacement(0, G4ThreeVector(0,0,33*cm), "RODetPV", RODetLV, RO_expHall, false, 0);
    
	// make voxel
	G4Box *RODetXVoxelSolid = new G4Box("RODetXVoxelSolid",
					detX/num_XVoxels_SiCsI/2,
					detY/2,
					detZ/2);
    G4LogicalVolume* RODetXVoxelLV = new G4LogicalVolume(RODetXVoxelSolid, dummyMat, "ROdetXVoxelLV");
    G4VPhysicalVolume* RODetXVoxelPV = new G4PVReplica("RODetXVoxelPV",
                                                       RODetXVoxelLV,
                                                       RODetPV,
                                                       kXAxis,
                                                       num_XVoxels_SiCsI,
                                                       detX/num_XVoxels_SiCsI);
    
    G4Box* RODetYVoxelSolid = new G4Box("RODetYVoxelSolid",
                                        detX/num_XVoxels_SiCsI/2,
                                        detY/num_YVoxels_SiCsI/2,
                                        detZ/2);
    G4LogicalVolume* RODetYVoxelLV = new G4LogicalVolume(RODetYVoxelSolid, dummyMat, "RODetYVoxelLV");
    G4VPhysicalVolume* RODetYVoxelPV = new G4PVReplica("RODetYVoxelPV",
                                                       RODetYVoxelLV,
                                                       RODetXVoxelPV,
                                                       kYAxis,
                                                       num_YVoxels_SiCsI,
                                                       detY/num_YVoxels_SiCsI);
    
    G4Box* RODetZVoxelSolid = new G4Box("RODetZVoxelSolid",
                                        detX/num_XVoxels_SiCsI/2,
                                        detY/num_YVoxels_SiCsI/2,
                                        detZ/num_ZVoxels_SiCsI/2);
    G4LogicalVolume* RODetZVoxelLV = new G4LogicalVolume(RODetZVoxelSolid, dummyMat, "RODetZVoxelLV");
    new G4PVReplica("RODetZVoxelPV",
                    RODetZVoxelLV,
                    RODetYVoxelPV,
                    kZAxis,
                    num_ZVoxels_SiCsI,
                    detZ/num_ZVoxels_SiCsI);
 
    SiCsIDummySD *dummySD = new SiCsIDummySD;
    RODetZVoxelLV -> SetSensitiveDetector(dummySD);

    return RO_expHall;
}

