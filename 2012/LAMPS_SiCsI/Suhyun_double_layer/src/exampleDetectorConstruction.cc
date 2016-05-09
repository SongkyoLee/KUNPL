
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

#include "exampleDetectorROGeometry.hh"

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
    labX = 100*cm;
    labY = 100*cm;
    labZ = 200*cm;
    
    detS  = 300e-04;      // length of a silicon pad
    detC  = 10;           // length of a scintillator
    
    distS = 23;           // distance from target to front surface of 1st layer 
    target = -30;         // z-component of the target's position vector
    coverage = 5*degree;  // polar angle coverage of each layer
    angle1 = 21.5*degree; // angle of 1st layer
    angle2 = 16.5*degree; // angle of 2nd layer
    
    pad = 8;              // # of pads (a layer)
}

G4VPhysicalVolume* exampleDetectorConstruction::Construct()
{
    G4Box *labSolid = new G4Box("labSolid", labX/2, labY/2, labZ/2);
    G4LogicalVolume *labLV = new G4LogicalVolume(labSolid, Helium, "labLV");
    G4VPhysicalVolume *labPV = new G4PVPlacement(0, G4ThreeVector(), "labPV", labLV, 0, false, 0);
    TString a;
    
    G4Box *detSolidS1 = new G4Box("detSolidS1", distS*(1/TMath::Cos(coverage/2))*TMath::Sin(angle1-(coverage/2))*TMath::Tan((0.5*360/pad)*degree)*cm, distS*TMath::Tan(coverage/2)*cm, detS/2);
    G4LogicalVolume *detLVS1 = new G4LogicalVolume(detSolidS1, Silicon, "detLVS1");
    for(i=0; i<pad; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/pad)*i*degree, -angle1, 0*degree), G4ThreeVector(0*cm, 0*cm, (distS-(detS/2))*cm).rotateX(-angle1).rotateZ(-(360/pad)*i*degree)+G4ThreeVector(0*cm, 0*cm, target*cm), Form("detPVS1%d", i), detLVS1, labPV, false, i);
    }
    
    G4Box *detSolidS2 = new G4Box("detSolidS2",  (distS+detC)*(1/TMath::Cos(coverage/2))*TMath::Sin(angle2-(coverage/2))*TMath::Tan((0.5*360/pad)*degree)*cm, (distS+detC)*TMath::Tan(coverage/2)*cm, detS/2);
    G4LogicalVolume *detLVS2 = new G4LogicalVolume(detSolidS2, Silicon, "detLVS2");
    for(i=0; i<pad; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/pad)*i*degree, -angle2, 0*degree), G4ThreeVector(0*cm, 0*cm, (distS+detC-(detS/2))*cm).rotateX(-angle2).rotateZ(-(360/pad)*i*degree)+G4ThreeVector(0*cm, 0*cm, target*cm), Form("detPVS2%d", i), detLVS2, labPV, false, i);
    }
    
    G4Trap *detSolidC1 = new G4Trap("detSolidC1", (detC/2)*cm, 0*degree, 0*degree,
        distS*TMath::Tan(coverage/2)*cm,
        distS*(1/TMath::Cos(coverage/2))*TMath::Sin(angle1-(coverage/2))*TMath::Tan((0.5*360/pad)*degree)*cm,
        distS*(1/TMath::Cos(coverage/2))*TMath::Sin(angle1-(coverage/2))*TMath::Tan((0.5*360/pad)*degree)*cm, 0*degree,
        (distS+detC)*TMath::Tan(coverage/2)*cm,
        (distS+detC)*(1/TMath::Cos(coverage/2))*TMath::Sin(angle1-coverage/2)*TMath::Tan((0.5*360/pad)*degree)*cm,
        (distS+detC)*(1/TMath::Cos(coverage/2))*TMath::Sin(angle1-coverage/2)*TMath::Tan((0.5*360/pad)*degree)*cm, 0*degree);
    G4LogicalVolume *detLVC1 = new G4LogicalVolume(detSolidC1, CsI, "detLVC1");
    for(i=0; i<pad; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/pad)*i*degree, -angle1, 0*degree),
        G4ThreeVector(0*cm, 0*cm,
        (distS+(detC/2))*cm).rotateX(-angle1).rotateZ(-(360/pad)*i*degree)+G4ThreeVector(0*cm, 0*cm, target*cm), Form("detPVC1%d", i), detLVC1, labPV, false, i);
    }
    
    G4Trap *detSolidC2 = new G4Trap("detSolidC2", (detC/2)*cm, 0*degree, 0*degree,            
        (distS+detC)*TMath::Tan(coverage/2)*cm,
        (distS+detC)*(1/TMath::Cos(coverage/2))*TMath::Sin(angle2-(coverage/2))*TMath::Tan((0.5*360/pad)*degree)*cm,
        (distS+detC)*(1/TMath::Cos(coverage/2))*TMath::Sin(angle2-(coverage/2))*TMath::Tan((0.5*360/pad)*degree)*cm, 0*degree,
        (distS+2*detC)*TMath::Tan(coverage/2)*cm,
        (distS+2*detC)*(1/TMath::Cos(coverage/2))*TMath::Sin(angle2-coverage/2)*TMath::Tan((0.5*360/pad)*degree)*cm,
        (distS+2*detC)*(1/TMath::Cos(coverage/2))*TMath::Sin(angle2-coverage/2)*TMath::Tan((0.5*360/pad)*degree)*cm, 0*degree);
    G4LogicalVolume *detLVC2 = new G4LogicalVolume(detSolidC2, CsI, "detLVC2");
    for(i=0; i<pad; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/pad)*i*degree, -angle2, 0*degree),
        G4ThreeVector(0*cm, 0*cm, 
        (distS+(3*detC/2))*cm).rotateX(-angle2).rotateZ(-(360/pad)*i*degree)+G4ThreeVector(0*cm, 0*cm, target*cm), Form("detPVC2%d", i), detLVC2, labPV, false, i);
    }
    
 //    G4Tubs *tpcSolid = new G4Tubs("tpcSolid", 5*cm, 15*cm, 120*cm/2, 0 , 2*pi);
 //    G4LogicalVolume *tpcLV = new G4LogicalVolume(tpcSolid, Vacuum, "tpcLV");
 //    new G4PVPlacement(0, G4ThreeVector(0, 0, 0), "tpcPV", tpcLV, labPV, false, 0);
    
    G4VisAttributes* detVisAttribL = new G4VisAttributes(false, G4Colour(1., 1., 1.));
    labLV -> SetVisAttributes(detVisAttribL);
    
    G4VisAttributes* detVisAttribS1 = new G4VisAttributes(G4Colour(0., 1., 0.));
    detLVS1 -> SetVisAttributes(detVisAttribS1);
    
    G4VisAttributes* detVisAttribS2 = new G4VisAttributes(G4Colour(0., 1., 0.));
    detLVS2 -> SetVisAttributes(detVisAttribS2);
    
    G4VisAttributes* detVisAttribC1 = new G4VisAttributes(G4Colour(0., 0., 1.));
    detLVC1 -> SetVisAttributes(detVisAttribC1);
    
    G4VisAttributes* detVisAttribC2 = new G4VisAttributes(G4Colour(0., 0., 1.));
    detLVC2 -> SetVisAttributes(detVisAttribC2);
   
 //   G4VisAttributes* detVisAttribtpc = new G4VisAttributes(G4Colour(1., 0., 0.));
 //   tpcLV -> SetVisAttributes(detVisAttribtpc);
    
    // Readout Geometry
    exampleDetectorROGeometry *detROGeometry = new exampleDetectorROGeometry("detROGeometry", labX, labY, labZ, 30*cm, 30*cm, 50*cm, G4ThreeVector(0, 0, 5*cm));
    
    detROGeometry -> BuildROGeometry();
    
    // Sensitive Detector
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    
    DetSD* detCSF =new DetSD("/detCF","1"); //CsI1
    detCSF -> SetROgeometry(detROGeometry);
    sdManager -> AddNewDetector(detCSF);
    detLVC1 -> SetSensitiveDetector(detCSF);
    
    DetSD* detSSF =new DetSD("/detSF","2"); //Si1
    detSSF -> SetROgeometry(detROGeometry);
    sdManager -> AddNewDetector(detSSF);
    detLVS1 -> SetSensitiveDetector(detSSF);
    
    DetSD* detCSB =new DetSD("/detCB","3"); //CsI2
    detCSB -> SetROgeometry(detROGeometry);
    sdManager -> AddNewDetector(detCSB);
    detLVC2 -> SetSensitiveDetector(detCSB);
    
    DetSD* detSSB =new DetSD("/detSB","3"); //Si2
    detSSB -> SetROgeometry(detROGeometry);
    sdManager -> AddNewDetector(detSSB);
    detLVS2 -> SetSensitiveDetector(detSSB);
    
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
    CsI->GetIonisation()->SetMeanExcitationEnergy(553.1*eV);
    
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

