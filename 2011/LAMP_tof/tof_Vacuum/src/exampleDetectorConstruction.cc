#include "exampleDetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4Box.hh" //making shape
#include "G4PVPlacement.hh" //placing
#include "G4PVReplica.hh" //SK

#include "DetSD.hh"
#include "G4SDManager.hh"

#include "exampleDetectorROGeometry.hh"

exampleDetectorConstruction::exampleDetectorConstruction()
{
  ConstructMaterials();
  DefineDimensions();
}

exampleDetectorConstruction::~exampleDetectorConstruction()
{
  DestructMaterials();
}

void exampleDetectorConstruction::DefineDimensions()
{ 
  labX = 1.5*m; //SKChanged..
  labY = 1.5*m; 
  labZ = 9.0*m;

  detX = 0.1*m;
  detY = 1.1*m;
  detZ = 2.0*cm;

  layerNum = 11; //SK
}

G4VPhysicalVolume* exampleDetectorConstruction::Construct()
{
  G4Box* labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2); 
  G4LogicalVolume* labLV = new G4LogicalVolume(labSolid, Vacuum, "labLV");
  G4VPhysicalVolume* labPV = new G4PVPlacement (0, G4ThreeVector() , "labPV",
						 labLV, 0,  false, 0);

  G4Box* offsetSolid //SKChanged.. the offset for the origin of the mother vol.
	 = new G4Box("offsetSolid", (detX*layerNum)/2, detY/2, detZ/2);
  G4LogicalVolume* offLV = new G4LogicalVolume(offsetSolid, dummyMat, "offLV");
  new G4PVPlacement(0, G4ThreeVector(0, 0, 4*m), "offPV", offLV, labPV, false, 0);
 
  G4Box* detSolid = new G4Box("detSolid", detX/2, detY/2, detZ/2);
  G4LogicalVolume* detLV = new G4LogicalVolume(detSolid , Scint , "detLV");
  new G4PVReplica("detPV", detLV, offLV, kXAxis, layerNum, detX); //SKChanged..
  //new G4PVPlacement(0, G4ThreeVector(0, 0, 4*m), "detPV", detLV, labPV, false, 0);

  G4VisAttributes* detVisAttrib = new G4VisAttributes(G4Colour(0., 0., 1.));
  detLV -> SetVisAttributes(detVisAttrib);

  //ReadOutGeometry
  exampleDetectorROGeometry* detROGeometry
			=new exampleDetectorROGeometry("DetROGeometry",
 							labX, labY, labZ,
							(detX*layerNum), detY, detZ,//SK
							G4ThreeVector(0, 0, 4*m)); //SK
  detROGeometry -> BuildROGeometry();

  //Sensitive Detector
  G4SDManager* sdManager = G4SDManager::GetSDMpointer();

  DetSD* detSD = new DetSD("/det");
  detSD -> SetROgeometry(detROGeometry);
  sdManager -> AddNewDetector(detSD);
  detLV -> SetSensitiveDetector(detSD);

  return labPV;
}

void exampleDetectorConstruction::ConstructMaterials()
{
 // STP Temperature = 0 degree Celcius
  const	G4double labTemp = STP_Temperature + 20.*kelvin;

  //SKChanged.. instead of exampleDetectorROGeometry, define dummymat here
  dummyMat = new G4Material("dummyMat", 1., 1*g/mole, 1*g/cm3); //SK..

  // Elements − G4Emelent(name, symbol, Z−number, molecular mass) 
  elN = new G4Element("Nitrogen", "N", 7, 14.00674*g/mole);
  elO = new G4Element("Oxygen", "O", 8, 15.9994*g/mole);
  elAr = new G4Element("Argon", "Ar", 18, 39.948*g/mole);
  elC = new G4Element("Carbon", "C", 6, 12.011*g/mole);
  elH = new G4Element("Hydrogen", "H", 1, 1.00794*g/mole);

  // Materials − G4Material(name, density , # of element , state , temperature) 
  Air = new G4Material("Air", 1.2929e-03*g/cm3, 3, kStateGas, labTemp);
    Air -> AddElement(elN, 75.47/99.95);
    Air -> AddElement(elO, 23.20/99.95);
    Air -> AddElement(elAr, 1.28/99.95);

  Scint = new G4Material("Scintillator", 1.05*g/cm3, 2, kStateSolid, labTemp);
    Scint -> AddElement(elC, 10);
    Scint -> AddElement(elH, 11);

  Water = new G4Material("Water", 1*g/cm3, 2, kStateLiquid, labTemp);
    Water -> AddElement(elH, 2);
    Water -> AddElement(elO, 1);

  Vacuum = new G4Material("Galactic", 1., 1.01*g/mole,
			universe_mean_density,kStateGas,
			 2.73*kelvin, 1.e-19*pascal); //SKChanged..
}

void exampleDetectorConstruction::DestructMaterials()
{
  delete Scint;
  delete Air;
  delete Water;
  delete Vacuum; //SK
  delete dummyMat;//SK

  delete elH;
  delete elC;
  delete elAr;
  delete elO;
  delete elN;
}

