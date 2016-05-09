
#include "exampleDetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4Box.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "DetSD.hh"
#include "TString.h"
#include "TMath.h"
#include "G4SDManager.hh"

#include "G4TransportationManager.hh"
#include "G4UniformMagField.hh"

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
	//Experimental Hall
	labX = 100*cm;
	labY = 100*cm;
	labZ = 200*cm;

	//Silicon layer
	detSiX = 9.0*cm;
	detSiY = 9.0*cm;
	detSiZ = 100e-06*m;

	detSiPlaceZ = 23*cm+detSiZ/2; 

	//CsI Scintillator    
	detCsIX = 9.0*cm;
	detCsIY = 9.0*cm;
	detCsIZ = 5.0*cm;

	detCsIPlaceZ = detSiPlaceZ+detSiZ/2+detCsIZ/2;

}

G4VPhysicalVolume* exampleDetectorConstruction::Construct()
{
    G4Box *labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2);
//    G4LogicalVolume *labLV = new G4LogicalVolume(labSolid, Helium, "labLV");
    G4LogicalVolume *labLV = new G4LogicalVolume(labSolid, Vacuum, "labLV");
    G4VPhysicalVolume *labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);
    TString a;
    
    G4Box *detSi = new G4Box("detSi", detSiX/2, detSiY/2, detSiZ/2);
    G4LogicalVolume *detSiLV = new G4LogicalVolume(detSi, Silicon, "detSiLV");
    G4VPhysicalVolume *detSiPV = new G4PVPlacement(0, G4ThreeVector(0,0,detSiPlaceZ), "detSiPV", detSiLV, labPV, false, 0);

    G4Box *detCsI = new G4Box("detCsI", detCsIX/2, detCsIY/2, detCsIZ/2);
    G4LogicalVolume *detCsILV = new G4LogicalVolume(detCsI, CsI, "detCsILV");
    G4VPhysicalVolume *detCsIPV = new G4PVPlacement(0, G4ThreeVector(0,0,detCsIPlaceZ), "detCsIPV", detCsILV, labPV, false, 0);
   
	 	// Visualization 
    G4VisAttributes* detVisAttriblabLV = new G4VisAttributes(false, G4Colour(1., 1., 1.));
    labLV -> SetVisAttributes(detVisAttriblabLV);
    
    G4VisAttributes* detVisAttribdetSiLV = new G4VisAttributes(G4Colour(0., 1., 0.));
    detSiLV -> SetVisAttributes(detVisAttribdetSiLV);
    
    G4VisAttributes* detVisAttribdetCsILV = new G4VisAttributes(G4Colour(0., 0., 1.));
    detCsILV -> SetVisAttributes(detVisAttribdetCsILV);
    
    // Sensitive Detector
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    
    DetSD* Si_SD =new DetSD("/Si_SD","1");
    sdManager -> AddNewDetector(Si_SD);
    detSiLV -> SetSensitiveDetector(Si_SD);
    
    DetSD* CsI_SD =new DetSD("/CsI_SD","2");
    sdManager -> AddNewDetector(CsI_SD);
    detCsILV -> SetSensitiveDetector(CsI_SD);
    
    return labPV;
}


void exampleDetectorConstruction::ConstructMaterials()
{
    //STP_Temperature = 0 degree Celcius
    const G4double labTemp = STP_Temperature + 20.*kelvin;
    
    //Elements - G4Element(name, symbol, Z-number, molecular mass)
    elHe = new G4Element("Helium", "He", 2, 4.002602*g/mole);
    elSi = new G4Element("silicon","Si", 14, 28.09*g/mole);
    elCs  = new G4Element ("Cesium", "Cs", 55, 132.905*g/mole);
    elI  = new G4Element ("Iodide", "I",  53, 126.9044*g/mole);
    
    //Materials - G4Material(name, density, # of element, state, temperature)
    Helium = new G4Material("Helium", 1.79e-04*g/cm3, 1, kStateGas, labTemp);
    Helium -> AddElement(elHe, 1);
    
    Silicon = new G4Material("Silicon", 2.33*g/cm3, 1, kStateSolid, labTemp);
    Silicon -> AddElement(elSi, 1);
    
    CsI = new G4Material("CsI", 4.51*g/cm3, 2, kStateSolid, labTemp);
    CsI->AddElement(elCs, 1);
    CsI->AddElement(elI, 1);
    CsI->GetIonisation()->SetMeanExcitationEnergy(553.1*eV); //threshold?
    
    Vacuum = new G4Material("Vacuum", 1., 1.01*g/mole, universe_mean_density, kStateGas, labTemp, 3.e-18*pascal);
}

void exampleDetectorConstruction::DestructMaterials()
{
    delete Helium;
    delete Silicon;
    delete CsI;
    
    delete elHe;
    delete elSi;
    delete elCs;
    delete elI;
}

