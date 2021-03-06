// ====================================================================
//   LAMPSDetectorConstruction.cc
// ====================================================================
#include "LAMPSDetectorConstruction.hh"
#include "LAMPSDetectorMessenger.hh"

#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Isotope.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Trap.hh"
#include "G4Polyhedra.hh"
#include "G4LogicalVolume.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"

#include "G4Colour.hh"
#include "TString.h"
#include "TMath.h"

// For magnetic field
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
//#include "LAMPSField.hh"
#include "Fields.hh"

// For Sensitive Detector
#include "TPCSD.hh"
#include "DCSD.hh"
#include "ToFSD.hh"
#include "LANDSD.hh"
#include "SiCsISD.hh"

#include <sstream>
using std::stringstream;

// For ReadOut Geometry - Genie
#include "TPCROGeometry.hh" 
#include "DCROGeometry.hh" 
#include "SiCsIROGeometry.hh" //KYO



//////////////////////////////////////////////////
LAMPSDetectorConstruction::LAMPSDetectorConstruction()
//////////////////////////////////////////////////
{
	DetMessenger = new LAMPSDetectorMessenger(this);
	fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
}

///////////////////////////////////////////////////
LAMPSDetectorConstruction::~LAMPSDetectorConstruction()
///////////////////////////////////////////////////
{
	delete DetMessenger;
}

/////////////////////////////////////////////////////////
G4VPhysicalVolume* LAMPSDetectorConstruction::Construct()
/////////////////////////////////////////////////////////
{
  // ==============================================================
  // elements
  // ==============================================================
  G4double A, Z;
  G4int N;
  G4String name, symbol;
  const double inch = 2.54*cm;
  char name1[30],name2[30];
  
  G4Colour aqua(0.247, 0.8, 1.0);
  G4Colour magenda(1.0, 0.0, 1.0);
  G4Colour yellow(1.0, 1.0, 0.0);
  G4Colour red(1.0, 0.0, 0.0);

  // Half of thickness for Scintillator
  const G4double scintiThickness  =0.5 * 5.0 * mm;   
  const G4double scintiThicknessIn = 0.5*3.0*mm;
  const G4double scintiThicknessFwd = 0.5*10.0*mm;

  A= 1.00794 *g/mole;
  G4Element* elH= new G4Element(name="Hydrogen", symbol="H", Z=1., A);

  A= 12.011 *g/mole;
  G4Element* elC= new G4Element(name="Carbon", symbol="C", Z=6., A);

  A= 14.00674 *g/mole;
  G4Element* elN= new G4Element(name="Nitrogen", symbol="N", Z=7., A);

  A= 15.9994 *g/mole;
  G4Element* elO= new G4Element(name="Oxygen", symbol="O", Z=8., A);

  A= 39.948 *g/mole;
  G4Element* elAr= new G4Element(name="Argon", symbol="Ar", Z=18., A);

  A= 28.0855 *g/mole;
  G4Element* elSi= new G4Element(name="Silicon", symbol="Si", Z=14., A);

  A= 126.90447 *g/mole;
  G4Element* elI= new G4Element(name="Iodine", symbol="I", Z=53., A);

  A= 132.90543 *g/mole;
  G4Element* elCs= new G4Element(name="Cesium", symbol="Cs", Z=55., A);

  A= 22.989768 *g/mole;
  G4Element* elNa= new G4Element(name="Sodium", symbol="Na", Z=11., A);

  A= 26.9815386 *g/mole;
  G4Element* elAl = new G4Element(name="Aluminum", symbol="Al", Z=13., A);

  A= 55.85 *g/mole; // Genie
  G4Element* elFe = new G4Element(name="Iron", symbol="Fe", Z=26., A);

  A= 4.002602 *g/mole; // Genie
  G4Element* elHe = new G4Element(name="Helium", symbol="He", Z=2., A);

  A= 199.9666 *g/mole; // Genie
  G4Element* elAu = new G4Element(name="Gold", symbol="Au", Z=79., A);

  A= 10.012937 *g/mole; // Genie
  G4Isotope *B10 = new G4Isotope(name="B10", Z=5., N=5, A);
  G4Element *elB10 = new G4Element(name="Boron", symbol="B", 1);
  elB10 -> AddIsotope(B10, 1);

  A= 20.1797 *g/mole; // Genie
  G4Element* elNe = new G4Element(name="Neon", symbol="Ne", Z=10., A);

  A = 208.9804 *g/mole; // KYO
  G4Element* elBi = new G4Element(name="Bismuth", symbol="Bi", Z=83., A); 

  A = 72.59 *g/mole; //KYO
  G4Element* elGe = new G4Element(name="Germanium", symbol="Ge", Z=32., A);

  A = 138.91*g/mole; //KYO
  G4Element* elLa = new G4Element(name="Lanthanum", symbol="La", Z=57., A);

  A = 79.904*g/mole; //KYO
  G4Element* elBr = new G4Element(name="Bromine", symbol="Br", Z=35., A);


  // ==============================================================
  // materials
  // ==============================================================
  G4double density, massfraction;
  G4int natoms, nel;
  G4int ncomponents;
  ///////////////////////shhwang

  // lh2
  density = 0.071*g/cm3;
  A = 1.01*g/mole;
  G4Material* lH2 = new G4Material(name="LH2", Z=1., A, density);

  //NaI/// 
  //  G4Element* elNa = new G4Element(name="Sodium", symbol="Na", Z=11., 22.989768*g/mole);//shhwang
  //  G4Element* elI = new G4Element(name="Iodine", symbol="I", Z=53., 126.90447*g/mole);//shhwang
  density = 3.67*g/cm3;
  G4Material* NaI = new G4Material(name="NaI", density, ncomponents=2, kStateSolid, 273.15*kelvin, 1.0*atmosphere);
  NaI->AddElement(elNa, natoms=1);
  NaI->AddElement(elI, natoms=1);
  ///////////////////////shhwang

  // temperature of experimental hall is controlled at 20 degree.
  const G4double expTemp= STP_Temperature+20.*kelvin;

  // vacuum
  density= universe_mean_density;
  G4Material* Vacuum= new G4Material(name="Vacuum", density, nel=2);
  Vacuum-> AddElement(elN, .7);
  Vacuum-> AddElement(elO, .3);

  // air
  density= 1.2929e-03 *g/cm3;  // at 20 degree
  G4Material* Air= new G4Material(name="Air", density, nel=3,
                                  kStateGas, expTemp);
  G4double ttt= 75.47+23.20+1.28;
  Air-> AddElement(elN,  massfraction= 75.47/ttt);
  Air-> AddElement(elO,  massfraction= 23.20/ttt);
  Air-> AddElement(elAr, massfraction=  1.28/ttt);

  // Ar gas
  A= 39.948 *g/mole;
  const G4double denAr= 1.782e-03 *g/cm3 * STP_Temperature/expTemp;
  G4Material* Ar= new G4Material(name="ArgonGas", Z=18, A, denAr,
                                 kStateGas, expTemp);


  // ethane (C2H6)
  const G4double denEthane= 1.356e-3 *g/cm3 * STP_Temperature/expTemp;
  G4Material* Ethane= new G4Material(name="Ethane", denEthane, nel=2,
                                     kStateGas, expTemp); 
  Ethane-> AddElement(elC, natoms=2);
  Ethane-> AddElement(elH, natoms=6);

  // methane (CH4)
  const G4double denMethane= 0.717e-3 *g/cm3 * STP_Temperature/expTemp;
  G4Material* Methane= new G4Material(name="Methane", denMethane, nel=2,
                                     kStateGas, expTemp);
  Methane-> AddElement(elC, natoms=1);
  Methane-> AddElement(elH, natoms=4);

  // Ar(50%) + ethane(50%) mixture
  density=  (denAr+denEthane)/2.;
  G4Material* ArEthane= new G4Material(name="ArEthane", density, nel=2,
                                       kStateGas, expTemp);
  ArEthane-> AddMaterial(Ar, massfraction= denAr/2./density);
  ArEthane-> AddMaterial(Ethane, massfraction= denEthane/2./density);


  // P10 gas Ar(90%) + methane(10%) mixture
  density=  0.9*denAr+0.1*denMethane;
  G4Material* P10= new G4Material(name="P10", density, nel=2,
                                       kStateGas, expTemp);
  P10-> AddMaterial(Ar, massfraction= 0.9*denAr/density);
  P10-> AddMaterial(Methane, massfraction= 0.1*denMethane/density);

  // G10 epoxy glass

  density = 1.700*g/cm3;
  G4Material* G10 = new G4Material(name="NemaG10", density, ncomponents=4);
  G10->AddElement(elSi, natoms=1);
  G10->AddElement(elO , natoms=2);
  G10->AddElement(elC , natoms=3);
  G10->AddElement(elH , natoms=3);

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // scintillator (Polystyene(C6H5CH=CH2))
  // implement here
  density = 1.032 *g/cm3;
  G4Material* Scinti = new G4Material(name="Scinti", density, nel=2);
  Scinti->AddElement(elC,natoms=8);
  Scinti->AddElement(elH,natoms=8);

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // CH2 Polyethelene
  // 
  density = 0.95 *g/cm3;
  G4Material* CH2 = new G4Material(name="CH2", density, nel=2);
  CH2->AddElement(elC,natoms=1);
  CH2->AddElement(elH,natoms=2);

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  // quartz (SiO2, crystalline)
  density= 2.64 *g/cm3;
  G4Material* Quartz= new G4Material(name="Quartz", density, nel= 2);
  Quartz-> AddElement(elSi, natoms=1);
  Quartz-> AddElement(elO,  natoms=2);

  // Aluminum - Genie
  density = 2.69 *g/cm3;
  G4Material* Aluminum = new G4Material(name="Aluminum_Solid", density, nel=1);
  Aluminum -> AddElement(elAl, natoms=1);

  // PET - Genie
  density = 1.4 *g/cm3;
  G4Material* PET = new G4Material(name="PET", density, nel=3);
  PET -> AddElement(elC,natoms=10);
  PET -> AddElement(elH,natoms=8);
  PET -> AddElement(elO,natoms=4);

  // Ar 50% + Methane 50% - Genie
  density = (denMethane + denAr) / 2;
  G4Material* ArMethane = new G4Material(name="ArMethane", density, nel=2, kStateGas, expTemp);
  ArMethane -> AddMaterial(Ar, massfraction=0.5*denAr/density);
  ArMethane -> AddMaterial(Methane, massfraction=0.5*denMethane/density);

  // Iron - Genie
  density = 7.874 *g/cm3;
  G4Material* Iron = new G4Material(name="Iron", density, nel=1);
  Iron -> AddElement(elFe, natoms=1);

  // Universal Vacuum - Genie
  G4double UV_atomicNumber = 1.;
  G4double UV_massOfMole = 1.008*g/mole;
  G4double UV_density = 1.e-25*g/cm3;
  G4double UV_temperature = 2.73*kelvin;
  G4double UV_pressure = 3.e-18*pascal;
  G4Material* Universal_Vacuum = new G4Material("interGalactic", UV_atomicNumber, UV_massOfMole, UV_density, kStateGas, UV_temperature, UV_pressure);

  // Helium Gas - Genie
  density = 0.0001786 *g/cm3 * STP_Temperature/expTemp;
  G4Material* HeGas = new G4Material(name="HeGas", density, nel=1, kStateGas, expTemp);
  HeGas -> AddElement(elHe, natoms=1);

	// Neon Gas - Genie
	density = 0.0009002 *g/cm3 * STP_Temperature/expTemp;
	G4Material *NeGas = new G4Material(name="NeGas", density, nel=1, kStateGas, expTemp);
	NeGas -> AddElement(elNe, natoms=1);

  // Scintillator BC400 - Genie
  density = 1.05 *g/cm3;
  G4Material* Scint = new G4Material(name="Scintillator", density, nel=2);
  Scint -> AddElement(elH, 11);
  Scint -> AddElement(elC, 10);

  // Gold - Genie
  density = 19.30 *g/cm3;
  G4Material* Gold = new G4Material("Gold", density, nel=1);
  Gold -> AddElement(elAu, massfraction=1.0);

  // Carbon - Genie
  density = 2.267 *g/cm3;
  G4Material* Carbon = new G4Material(name="CarbonPlate", density, nel=1);
  Carbon -> AddElement(elC, massfraction=1.0);

  // Boron10 - Genie
  density = 2.34 *g/cm3;
  G4Material* Boron10 = new G4Material(name="BoronSolid", density, nel=1);
  Boron10 -> AddElement(elB10, massfraction=1.0);

  // Silicon - KYO
  G4Material* Silicon = new G4Material("Silicon", 2.33*g/cm3, 1, kStateSolid, expTemp);
  Silicon -> AddElement(elSi, 1);

  // CsI - KYO
  G4Material* CsI = new G4Material("CsI", 4.51*g/cm3, 2, kStateSolid, expTemp);
  CsI -> AddElement(elCs, 1);
  CsI -> AddElement(elI, 1);
  CsI -> GetIonisation() -> SetMeanExcitationEnergy(553.1*eV);

  // BGO (Bi4Ge3O12) - KYO 
  density = 7.13 *g/cm3;
  G4Material* BGO = new G4Material(name="BGO", density, nel=3);
  BGO -> AddElement(elBi, 4);
  BGO -> AddElement(elGe, 3);
  BGO -> AddElement(elO, 12);

  //Lanthanum Bromide (LaBr3) - KYO
  density = 5.29*g/cm3;
  G4Material* LaBr3 = new G4Material(name="LaBr3", density, nel=2);
  LaBr3 -> AddElement(elLa, 1);
  LaBr3 -> AddElement(elBr, 3);


  //==============================================================
  // define detector sensitivity 
  //==============================================================

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String SDname;

  // ==============================================================
  // geometry
  // ==============================================================

  // ==============================================================
  // Experimental Hall (world)
  // ==============================================================

/*
  const G4double R_EXPHALL = 8.*m;
  const G4double DZ_EXPHALL = 8.*m;

  G4Tubs* expHallSolid=
    new G4Tubs("EXP_HALL", 0., R_EXPHALL, DZ_EXPHALL, 0., 360.*deg);
*/

  const G4double X_EXPHALL = 5.0*m;
  const G4double Y_EXPHALL = 2.0*m;
  const G4double Z_EXPHALL = 20.0*m;

  G4Box* expHallSolid = new G4Box("EXP_HALL", X_EXPHALL, Y_EXPHALL, Z_EXPHALL);

  G4LogicalVolume* expHallLV=
    new G4LogicalVolume(expHallSolid, Air, "EXP_HALL_LV");

  // visualization attributes
  G4VisAttributes* expHallVisAtt=
    new G4VisAttributes(false, G4Colour(1., 1., 1.));
  expHallLV-> SetVisAttributes(expHallVisAtt);
  
  G4PVPlacement* expHall= new G4PVPlacement(0, G4ThreeVector(), "EXP_HALL_PV",
                                            expHallLV, 0, false, 0);

  expHallLV -> SetUserLimits(new G4UserLimits(DBL_MAX, 27.*m, DBL_MAX, 0, 0));

/*
  //================
  // Target - Genie
  //================

  const G4double widthTarget = 50.*mm;
  const G4double heightTarget = 50.*mm;
  const G4double thicknessTarget = 20.*um;

  G4Box *TARGET_V = new G4Box("TARGET_V", widthTarget/2, heightTarget/2, thicknessTarget/2);
  G4LogicalVolume *TARGET_LV = new G4LogicalVolume(TARGET_V, Carbon, "TARGET_LV");
  new G4PVPlacement(0, G4ThreeVector(), "TARGET_PV", TARGET_LV, expHall, false, 0);
*/

  // ==============================================================
  //  Time projection chamber - Genie
  // ==============================================================  

  const G4double DZ_TPC_OFFSET	= 300.*mm;
  const G4double DZ_TPC		= 600.*mm;

  // ==============================================================  
  // Inside of TPC Solenoid - Genie
  // ==============================================================

  // Voxel size is not half
  const G4double X_VOXEL_SIZE_TPC = 5.*mm;
  const G4double Y_VOXEL_SIZE_TPC = 5.*mm;
  const G4double Z_VOXEL_SIZE_TPC = 5.*mm;

  const G4double ROUT_TPC_IN	= 500.*mm;
  const G4double RIN_TPC_IN	= 150.*mm;
  const G4double DPHI_TPC_IN	= 360.*deg;

  G4VSolid* TPC_Solid_IN = new G4Tubs("TPC Solenoid Inside", RIN_TPC_IN, ROUT_TPC_IN, DZ_TPC, 0., DPHI_TPC_IN);
  G4LogicalVolume* TPC_LV_IN = new G4LogicalVolume(TPC_Solid_IN, NeGas, "TPC_LV_IN");
  G4PVPlacement* TPC_PV_IN = new G4PVPlacement(0, G4ThreeVector(0, 0, DZ_TPC_OFFSET), "TPC_PV_IN", TPC_LV_IN, expHall, FALSE, 0);
  G4VisAttributes* TPC_VisAtt_IN= new G4VisAttributes(true, G4Colour(1.,1.,0.));
  TPC_LV_IN -> SetVisAttributes(TPC_VisAtt_IN);

  // ==============================================================  
  // Inner Frame of TPC Solenoid - Genie
  // ==============================================================

  const G4double ROUT_TPC_IF	= 150.2*mm;
  const G4double RIN_TPC_IF	= 150.*mm;
  const G4double DPHI_TPC_IF	= 360.*deg;

  G4VSolid* TPC_Solid_IF = new G4Tubs("TPC Solenoid Inner Frame", RIN_TPC_IF, ROUT_TPC_IF, DZ_TPC, 0., DPHI_TPC_IF);
  G4LogicalVolume* TPC_LV_IF = new G4LogicalVolume(TPC_Solid_IF, PET, "TPC_LV_IF");
  new G4PVPlacement(0, G4ThreeVector(), "TPC_PV_IF", TPC_LV_IF, TPC_PV_IN, FALSE, 0);
  G4VisAttributes* TPC_VisAtt_IF = new G4VisAttributes(true, G4Colour(1.,0.,0.));
  TPC_LV_IF -> SetVisAttributes(TPC_VisAtt_IF);

  // ==============================================================  
  // Outer Frame of TPC Solenoid - Genie
  // ==============================================================

  const G4double ROUT_TPC_OF	= 500.*mm;
  const G4double RIN_TPC_OF	= 495.*mm;
  const G4double DPHI_TPC_OF	= 360.*deg;

  G4VSolid* TPC_Solid_OF = new G4Tubs("TPC Solenoid Outer Frame", RIN_TPC_OF, ROUT_TPC_OF, DZ_TPC, 0., DPHI_TPC_OF);
  G4LogicalVolume* TPC_LV_OF = new G4LogicalVolume(TPC_Solid_OF, Aluminum, "TPC_LV_OF");
  new G4PVPlacement(0, G4ThreeVector(), "TPC_PV_OF", TPC_LV_OF, TPC_PV_IN, FALSE, 0);
  G4VisAttributes* TPC_VisAtt_OF = new G4VisAttributes(true, G4Colour(1.,0.,0.));
  TPC_LV_OF -> SetVisAttributes(TPC_VisAtt_OF);

  // ==============================================================  
  // Pad Chambers - Genie
  // ==============================================================

  const G4int NUM_PAD = 8;

  // ==============================================================  
  // Frame of Pad Chambers - Genie
  // ==============================================================

  const G4double HALF_PAD_FRAME_THICKNESS	= 50.*mm;
  const G4double HALF_PAD_FRAME_SHORT_SIDE	= 57.40*mm;
  const G4double HALF_PAD_FRAME_LONG_SIDE	= 213.33*mm;
  const G4double HALF_PAD_FRAME_RADIAL_LENGTH	= 188.21*mm;
  const G4double PAD_FRAME_RADIAL_POSITION	= 326.79*mm;
  const G4double PAD_FRAME_Z_POSITION_UP	= DZ_TPC + DZ_TPC_OFFSET + HALF_PAD_FRAME_THICKNESS;
  const G4double PAD_FRAME_Z_POSITION_DOWN	= -DZ_TPC + DZ_TPC_OFFSET - HALF_PAD_FRAME_THICKNESS;

  G4Trd *PAD_FRAME = new G4Trd("Pad Frame",
  			       HALF_PAD_FRAME_THICKNESS,
			       HALF_PAD_FRAME_THICKNESS,
			       HALF_PAD_FRAME_SHORT_SIDE,
			       HALF_PAD_FRAME_LONG_SIDE,
			       HALF_PAD_FRAME_RADIAL_LENGTH);
  G4LogicalVolume *PAD_FRAME_UP_LV[NUM_PAD];
  G4LogicalVolume *PAD_FRAME_DOWN_LV[NUM_PAD];

  G4PVPlacement *PAD_FRAME_UP_PV[NUM_PAD];
  G4PVPlacement *PAD_FRAME_DOWN_PV[NUM_PAD];

  G4VisAttributes* PAD_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0.6, 0.6, 0.6));

  for (G4int i = 0; i != NUM_PAD; i++)
  {
  	G4RotationMatrix* PAD_FRAME_ROTATE = new G4RotationMatrix();
	PAD_FRAME_ROTATE -> rotateY(-90.*deg);
	PAD_FRAME_ROTATE -> rotateX(i*45.*deg);

	// upstream
	stringstream PAD_FRAME_UP_LV_NAME;
	PAD_FRAME_UP_LV_NAME << "PAD_FRAME_UP_LV_" << i;
	PAD_FRAME_UP_LV[i] = new G4LogicalVolume(PAD_FRAME, PET, PAD_FRAME_UP_LV_NAME.str().c_str());

	stringstream PAD_FRAME_UP_NAME;
	PAD_FRAME_UP_NAME << "PAD_FRAME_UP_PV_" << i;


	PAD_FRAME_UP_PV[i] = new G4PVPlacement(PAD_FRAME_ROTATE,
			  G4ThreeVector(PAD_FRAME_RADIAL_POSITION, 0, PAD_FRAME_Z_POSITION_UP).rotateZ(i*45.*deg),
			  PAD_FRAME_UP_NAME.str().c_str(),
			  PAD_FRAME_UP_LV[i],
			  expHall,
			  FALSE,
			  0);

	PAD_FRAME_UP_NAME.str("");

	PAD_FRAME_UP_LV[i] -> SetVisAttributes(PAD_FRAME_VisAtt);

	// downstream
	stringstream PAD_FRAME_DOWN_NAME;
	PAD_FRAME_DOWN_NAME << "PAD_FRAME_DOWN_PV_" << i;

	stringstream PAD_FRAME_DOWN_LV_NAME;
	PAD_FRAME_DOWN_LV_NAME << "PAD_FRAME_DOWN_LV_" << i;
	PAD_FRAME_DOWN_LV[i] = new G4LogicalVolume(PAD_FRAME, PET, PAD_FRAME_DOWN_LV_NAME.str().c_str());

	PAD_FRAME_DOWN_PV[i] = new G4PVPlacement(PAD_FRAME_ROTATE,
			  G4ThreeVector(PAD_FRAME_RADIAL_POSITION, 0, PAD_FRAME_Z_POSITION_DOWN).rotateZ(i*45.*deg),
			  PAD_FRAME_DOWN_NAME.str().c_str(),
			  PAD_FRAME_DOWN_LV[i],
			  expHall,
			  FALSE,
			  0);

	PAD_FRAME_DOWN_NAME.str("");

	PAD_FRAME_DOWN_LV[i] -> SetVisAttributes(PAD_FRAME_VisAtt);
  }

  //================================  
  // Inside of Pad Chambers - Genie
  //================================

  const G4double HALF_PAD_INSIDE_THICKNESS	= 49.8*mm;
  const G4double HALF_PAD_INSIDE_SHORT_SIDE	= 57.4*mm;
  const G4double HALF_PAD_INSIDE_LONG_SIDE	= 213.24*mm;
  const G4double HALF_PAD_INSIDE_RADIAL_LENGTH	= 187.81*mm;

  G4Trd *PAD_INSIDE = new G4Trd("Pad Inside",
  			       HALF_PAD_INSIDE_THICKNESS,
			       HALF_PAD_INSIDE_THICKNESS,
			       HALF_PAD_INSIDE_SHORT_SIDE,
			       HALF_PAD_INSIDE_LONG_SIDE,
			       HALF_PAD_INSIDE_RADIAL_LENGTH);

  G4LogicalVolume *PAD_INSIDE_UP_LV[NUM_PAD];
  G4LogicalVolume *PAD_INSIDE_DOWN_LV[NUM_PAD];

  G4VisAttributes* PAD_INSIDE_VisAtt = new G4VisAttributes(true, G4Colour(0.5, 0, 1.));

  for (G4int i = 0; i != NUM_PAD; i++)
  {
	// upstream
	stringstream PAD_INSIDE_UP_LV_NAME;
	PAD_INSIDE_UP_LV_NAME << "PAD_INSIDE_UP_LV_" << i;
	PAD_INSIDE_UP_LV[i] = new G4LogicalVolume(PAD_INSIDE, NeGas, PAD_INSIDE_UP_LV_NAME.str().c_str());

	stringstream PAD_INSIDE_UP_NAME;
	PAD_INSIDE_UP_NAME << "PAD_INSIDE_UP_PV_" << i;

	new G4PVPlacement(0,
			  G4ThreeVector(),
			  PAD_INSIDE_UP_NAME.str().c_str(),
			  PAD_INSIDE_UP_LV[i],
			  PAD_FRAME_UP_PV[i],
			  FALSE,
			  i);

	PAD_INSIDE_UP_NAME.str("");

	PAD_INSIDE_UP_LV[i] -> SetVisAttributes(PAD_INSIDE_VisAtt);

	// downstream
	stringstream PAD_INSIDE_DOWN_LV_NAME;
	PAD_INSIDE_DOWN_LV_NAME << "PAD_INSIDE_DOWN_LV_" << i;
	PAD_INSIDE_DOWN_LV[i] = new G4LogicalVolume(PAD_INSIDE, NeGas, PAD_INSIDE_DOWN_LV_NAME.str().c_str());

	stringstream PAD_INSIDE_DOWN_NAME;
	PAD_INSIDE_DOWN_NAME << "PAD_INSIDE_DOWN_PV_" << i;

	new G4PVPlacement(0,
			  G4ThreeVector(),
			  PAD_INSIDE_DOWN_NAME.str().c_str(),
			  PAD_INSIDE_DOWN_LV[i],
			  PAD_FRAME_DOWN_PV[i],
			  FALSE,
			  10+i);

	PAD_INSIDE_DOWN_NAME.str("");

	PAD_INSIDE_DOWN_LV[i] -> SetVisAttributes(PAD_INSIDE_VisAtt);
  }


  //===========================================
  // TPC ReadOut Geometry - Genie
  //===========================================

  TPCROGeometry* TPC_RO_GEOMETRY = new TPCROGeometry("TPC_RO_GEOMETRY",
// For cylindrical world volume
//						      R_EXPHALL,
//						      DZ_EXPHALL,
// For cubic world volume
						      X_EXPHALL,
						      Y_EXPHALL,
						      Z_EXPHALL,
						      DZ_TPC_OFFSET,
						      ROUT_TPC_IN,
						      RIN_TPC_IN,
						      DZ_TPC,
						      DPHI_TPC_IN,
						      X_VOXEL_SIZE_TPC,
						      Y_VOXEL_SIZE_TPC,
						      Z_VOXEL_SIZE_TPC);

  TPC_RO_GEOMETRY -> BuildROGeometry(); 


  //=============================================================
  // Si-CsI detector  - KYO (from Suhyun)
  //=============================================================

    const G4double DZ_SiF  = 100e-03*mm;	// First silicon pad
    const G4double DZ_SiS  = 400e-03*mm;	// Second
    const G4double DZ_SiT  = 400e-03*mm;	// Third
    const G4double DZ_CsI  = 150*mm;		//These DZ are along the rotated z axes.
    
    const G4double DZ_OFFSET_surface = 206*mm;	// from target to front surface of 1st CsI
    //const G4double DZ_OFFSET_layer =  3*mm; // displacement bw two layers 
					// (back surface of 1st CsI to front surface of 2nd CsI)

    // for the coverage from 14*degree to 24*degree
    const G4double COVERAGE = 10*degree;  // polar angle coverage of each layer
    const G4double ANGLE1 = 19.0*degree; // polar angle of 1st layer center
    //const G4double ANGLE2 = 16.5*degree; // polar angle of 2nd layer center
 
    const G4int PADNUM = 8;              // # of pads (for each layer)

    // Voxel size (not half) - temporary
    const G4double X_VOXEL_SIZE_SiCsI = 10;
    const G4double Y_VOXEL_SIZE_SiCsI = 10;
    const G4double Z_VOXEL_SIZE_SiCsI = 10;

  //===================================================
  // Silicon detector SiF of 1st layer - KYO
  //===================================================
    
    G4Box *SiF1_Solid = new G4Box("SiF1_Solid", 
				DZ_OFFSET_surface*(1/TMath::Cos(COVERAGE/2))*TMath::Sin(ANGLE1-(COVERAGE/2))
					*TMath::Tan((0.5*360/PADNUM)*degree)*mm,
	 			DZ_OFFSET_surface*TMath::Tan(COVERAGE/2)*mm,
				DZ_SiF/2);

    G4LogicalVolume *SiF1_LV = new G4LogicalVolume(SiF1_Solid, Silicon, "SiF1_LV");

    for(G4int i=0; i<PADNUM; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/PADNUM)*i*degree, -ANGLE1, 0*degree),
			 G4ThreeVector(0*mm, 0*mm,(DZ_OFFSET_surface-DZ_SiT-DZ_SiS-(DZ_SiF/2))*mm)
				.rotateX(-ANGLE1).rotateZ(-(360/PADNUM)*i*degree),
			 Form("SiF1_PV_%d", i),
			 SiF1_LV,
			 expHall,
			 false,
			 i);
    }
   
   G4VisAttributes* SiF_VisAtt = new G4VisAttributes(G4Colour(0., 1., 0.));
   SiF1_LV -> SetVisAttributes(SiF_VisAtt);
 
  //===================================================
  // Silicon detector SiS of 1st layer - KYO
  //===================================================
    
    G4Box *SiS1_Solid = new G4Box("SiS1_Solid", 
				DZ_OFFSET_surface*(1/TMath::Cos(COVERAGE/2))*TMath::Sin(ANGLE1-(COVERAGE/2))
					*TMath::Tan((0.5*360/PADNUM)*degree)*mm,
	 			DZ_OFFSET_surface*TMath::Tan(COVERAGE/2)*mm,
				DZ_SiS/2);

    G4LogicalVolume *SiS1_LV = new G4LogicalVolume(SiS1_Solid, Silicon, "SiS1_LV");

    for(G4int i=0; i<PADNUM; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/PADNUM)*i*degree, -ANGLE1, 0*degree),
			 G4ThreeVector(0*mm, 0*mm,(DZ_OFFSET_surface-DZ_SiT-(DZ_SiS/2))*mm)
				.rotateX(-ANGLE1).rotateZ(-(360/PADNUM)*i*degree),
			 Form("SiS1_PV_%d", i),
			 SiS1_LV,
			 expHall,
			 false,
			 i);
    }
   
   G4VisAttributes* SiS_VisAtt = new G4VisAttributes(G4Colour(0., 1., 1.));
   SiS1_LV -> SetVisAttributes(SiS_VisAtt);
    
  //===================================================
  // Silicon detector SiT of 1st layer - KYO
  //===================================================
    
    G4Box *SiT1_Solid = new G4Box("SiT1_Solid", 
				DZ_OFFSET_surface*(1/TMath::Cos(COVERAGE/2))
				*TMath::Sin(ANGLE1-(COVERAGE/2))
				*TMath::Tan((0.5*360/PADNUM)*degree)*mm,
	 			DZ_OFFSET_surface*TMath::Tan(COVERAGE/2)*mm,
				DZ_SiT/2);

    G4LogicalVolume *SiT1_LV = new G4LogicalVolume(SiT1_Solid, Silicon, "SiT1_LV");

    for(G4int i=0; i<PADNUM; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/PADNUM)*i*degree, -ANGLE1, 0*degree),
			 G4ThreeVector(0*mm, 0*mm,
				(DZ_OFFSET_surface-(DZ_SiT/2))*mm)
				.rotateX(-ANGLE1).rotateZ(-(360/PADNUM)*i*degree),
			 Form("SiT1_PV_%d", i),
			 SiT1_LV,
			 expHall,
			 false,
			 i);
    }

   G4VisAttributes* SiT_VisAtt = new G4VisAttributes(G4Colour(0., 1., 1.));
   SiT1_LV -> SetVisAttributes(SiT_VisAtt);
    
  //===================================================
  // CsI scintillator of 1st layer - KYO
  //===================================================
    
    G4Trap *CsI1_solid = new G4Trap("CsI1_solid",
				(DZ_CsI/2)*mm, 0*degree, 0*degree,
        			DZ_OFFSET_surface*TMath::Tan(COVERAGE/2)*mm,
        			DZ_OFFSET_surface*(1/TMath::Cos(COVERAGE/2))
					*TMath::Sin(ANGLE1-(COVERAGE/2))
					*TMath::Tan((0.5*360/PADNUM)*degree)*mm,
        			DZ_OFFSET_surface*(1/TMath::Cos(COVERAGE/2))
					*TMath::Sin(ANGLE1-(COVERAGE/2))
					*TMath::Tan((0.5*360/PADNUM)*degree)*mm,
				0*degree,
        			(DZ_OFFSET_surface+DZ_CsI)*TMath::Tan(COVERAGE/2)*mm,
        			(DZ_OFFSET_surface+DZ_CsI)*(1/TMath::Cos(COVERAGE/2))
					*TMath::Sin(ANGLE1-COVERAGE/2)
					*TMath::Tan((0.5*360/PADNUM)*degree)*mm,
        			(DZ_OFFSET_surface+DZ_CsI)*(1/TMath::Cos(COVERAGE/2))
					*TMath::Sin(ANGLE1-COVERAGE/2)
					*TMath::Tan((0.5*360/PADNUM)*degree)*mm,
				 0*degree);

    G4LogicalVolume *CsI1_LV = new G4LogicalVolume(CsI1_solid, CsI, "CsI1_LV");

    for(G4int i=0; i<PADNUM; i++)
    { 
        new G4PVPlacement(new G4RotationMatrix(-(360/PADNUM)*i*degree, -ANGLE1, 0*degree),
       			G4ThreeVector(0*mm, 0*mm, (DZ_OFFSET_surface+(DZ_CsI/2))*mm)
				.rotateX(-ANGLE1).rotateZ(-(360/PADNUM)*i*degree),
			Form("CsI1_PV_%d", i), 
			CsI1_LV, 
			expHall, 
			false, 
			i);
    }
   
   G4VisAttributes* CsI_VisAtt = new G4VisAttributes(G4Colour(0., 0., 1.));
   CsI1_LV -> SetVisAttributes(CsI_VisAtt);

    
  // ===========================================
  // Si & CsI ROGeometry - KYO
  //============================================

	SiCsIROGeometry* SICSI_RO_GEOMETRY = new SiCsIROGeometry("SICSI_RO_GEOMETRY",
								X_EXPHALL,
								Y_EXPHALL,
								Z_EXPHALL,
								DZ_SiF,
								DZ_SiS,
								DZ_SiT,
								DZ_OFFSET_surface,
								X_VOXEL_SIZE_SiCsI,
								Y_VOXEL_SIZE_SiCsI,
								Z_VOXEL_SIZE_SiCsI,
								COVERAGE,
								ANGLE1,
								PADNUM);
	
	SICSI_RO_GEOMETRY -> BuildROGeometry();


  //====================
  // Collimator - Genie
  //====================

  const G4double WIDTH_COL = 2800.*mm;
  const G4double HEIGHT_COL = 2800.*mm;
  const G4double THICKNESS_COL = 200.*mm;

  const G4double WIDTH_COL_WINDOW = 800.*mm;
  const G4double HEIGHT_COL_WINDOW = 500.*mm;
  const G4double THICKNESS_COL_WINDOW = THICKNESS_COL;

  const G4double d_FROM_CENTER_COL = 1400.*mm;
  const G4ThreeVector COL_POS = G4ThreeVector(0, 0, d_FROM_CENTER_COL);

  G4Box *COL_IRON_PLATE = new G4Box("COL_IRON_PLATE", WIDTH_COL/2, HEIGHT_COL/2, THICKNESS_COL/2);
  G4Box *COL_WINDOW = new G4Box("COL_WINDOW", WIDTH_COL_WINDOW/2, HEIGHT_COL_WINDOW/2, THICKNESS_COL_WINDOW/2);

  G4SubtractionSolid *COL_V = new G4SubtractionSolid("COL_V", COL_IRON_PLATE, COL_WINDOW);
  G4LogicalVolume *COL_LV = new G4LogicalVolume(COL_V, Iron, "COL_LV");
  new G4PVPlacement(0, 
  		    COL_POS,
		    "COL_PV",
		    COL_LV,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* COL_VisAtt = new G4VisAttributes(true, G4Colour(0.5, 0.5, 0.5));
  COL_LV -> SetVisAttributes(COL_VisAtt);

  //---------------------------------
  // Drfit Chamber Shared Properties
  //---------------------------------

  // Voxel size is not half
  const G4double X_VOXEL_SIZE_DC = 0.2*mm;
  const G4double Y_VOXEL_SIZE_DC = 0.2*mm;
  const G4double Z_VOXEL_SIZE_DC = 0.2*mm;

  //-----------------------------------
  // Drift Chamber Before Dipole Frame
  //-----------------------------------

  const G4double d_FROM_CENTER_DCBD = 1450.*mm;
  const G4ThreeVector DCBD_POS = G4ThreeVector(0, 0, d_FROM_CENTER_DCBD);

  const G4double WIDTH_DCBD_FRAME = 800.*mm;
  const G4double HEIGHT_DCBD_FRAME = 500.*mm;
  const G4double THICKNESS_DCBD_FRAME = 100*mm;

  G4Box* DCBD_FRAME_BOX = new G4Box("DCBD_BOX", WIDTH_DCBD_FRAME/2, HEIGHT_DCBD_FRAME/2, THICKNESS_DCBD_FRAME/2);
  G4LogicalVolume* DCBD_FRAME_LV = new G4LogicalVolume(DCBD_FRAME_BOX, PET, "DCBD_FRAME_LV");
  G4PVPlacement* DCBD_FRAME_PV = new G4PVPlacement(0,
  		    DCBD_POS,
		    "DCBD_FRAME_PV",
		    DCBD_FRAME_LV,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* DCBD_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.7, 1.));
  DCBD_FRAME_LV -> SetVisAttributes(DCBD_FRAME_VisAtt);

  //------------------------------------
  // Drift Chamber Before Dipole Inside
  //------------------------------------

  const G4double FRAME_THICKNESS_DCBD = 0.1*mm;

  const G4double WIDTH_DCBD_IN = WIDTH_DCBD_FRAME - 2*FRAME_THICKNESS_DCBD;
  const G4double HEIGHT_DCBD_IN = HEIGHT_DCBD_FRAME - 2*FRAME_THICKNESS_DCBD;
  const G4double THICKNESS_DCBD_IN = THICKNESS_DCBD_FRAME - 2*FRAME_THICKNESS_DCBD;

  G4Box* DCBD_IN_BOX = new G4Box("DCBD_BOX", WIDTH_DCBD_IN/2, HEIGHT_DCBD_IN/2, THICKNESS_DCBD_IN/2);
  G4LogicalVolume* DCBD_IN_LV = new G4LogicalVolume(DCBD_IN_BOX, ArEthane, "DCBD_IN_LV");
  new G4PVPlacement(0,
  		    G4ThreeVector(),
		    "DCBD_IN_PV",
		    DCBD_IN_LV,
		    DCBD_FRAME_PV,
		    FALSE,
		    0);

  G4VisAttributes* DCBD_IN_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.5, 1.));
  DCBD_IN_LV -> SetVisAttributes(DCBD_IN_VisAtt);

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  const G4double NEW_CENTER = 295.*cm;
//  const G4double NEW_CENTER = 320.*cm;

  const G4double secondAngle = -12.8*deg;
  const G4double thirdAngle = -15.9*deg;
  const G4double fourthAngle = -19.0*deg;
  const G4double defaultAngle = 0;

  //=======================
  // Dipole Arm #1 - Genie
  //=======================

  const G4double GAP1_DPA1 = 50.*mm;
  const G4double GAP2_DPA1 = 100.*mm;
  const G4double ANGLE_DPA1 = defaultAngle + 90.*deg;

  G4RotationMatrix* ROTATE_DPA1 = new G4RotationMatrix();
  ROTATE_DPA1 -> rotateY(-ANGLE_DPA1);

  //------------------------------
  // Drift Chamber Upstream Frame
  //------------------------------

  const G4double d_FROM_NEW_CENTER_DCU1 = 1250.*mm;
  const G4ThreeVector DCU1_POS = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(0, 0, d_FROM_NEW_CENTER_DCU1).rotateY(ANGLE_DPA1);

  const G4double WIDTH_DCU1_FRAME = 750*mm;
  const G4double HEIGHT_DCU1_FRAME = 600*mm;
  const G4double THICKNESS_DCU1_FRAME = 100*mm;

  G4Box* DCU1_FRAME_BOX = new G4Box("DCU1_BOX", WIDTH_DCU1_FRAME/2, HEIGHT_DCU1_FRAME/2, THICKNESS_DCU1_FRAME/2);
  G4LogicalVolume* DCU1_FRAME_LV = new G4LogicalVolume(DCU1_FRAME_BOX, PET, "DCU1_FRAME_LV");
  G4PVPlacement* DCU1_FRAME_PV = new G4PVPlacement(ROTATE_DPA1,
  		    DCU1_POS,
		    "DCU1_FRAME_PV",
		    DCU1_FRAME_LV,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* DCU1_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.7, 1.));
  DCU1_FRAME_LV -> SetVisAttributes(DCU1_FRAME_VisAtt);

  //-------------------------------
  // Drift Chamber Upstream Inside
  //-------------------------------

  const G4double FRAME_THICKNESS_DCU1 = 0.1*mm;

  const G4double WIDTH_DCU1_IN = WIDTH_DCU1_FRAME - 2*FRAME_THICKNESS_DCU1;
  const G4double HEIGHT_DCU1_IN = HEIGHT_DCU1_FRAME - 2*FRAME_THICKNESS_DCU1;
  const G4double THICKNESS_DCU1_IN = THICKNESS_DCU1_FRAME - 2*FRAME_THICKNESS_DCU1;

  G4Box* DCU1_IN_BOX = new G4Box("DCU1_BOX", WIDTH_DCU1_IN/2, HEIGHT_DCU1_IN/2, THICKNESS_DCU1_IN/2);
  G4LogicalVolume* DCU1_IN_LV = new G4LogicalVolume(DCU1_IN_BOX, ArEthane, "DCU1_IN_LV");
  new G4PVPlacement(0,
  		    G4ThreeVector(),
		    "DCU1_IN_PV",
		    DCU1_IN_LV,
		    DCU1_FRAME_PV,
		    FALSE,
		    0);
  
  G4VisAttributes* DCU1_IN_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.5, 1.));
  DCU1_IN_LV -> SetVisAttributes(DCU1_IN_VisAtt);

  //---------------------
  // Helium Bag #1 Frame
  //---------------------

  const G4double HB1_FRAME_SHORT_SIDE_X_DPA1 = 880.*mm;
  const G4double HB1_FRAME_SHORT_SIDE_Y_DPA1 = 570.*mm;
  const G4double HB1_FRAME_LONG_SIDE_X_DPA1 = 2980.*mm;
  const G4double HB1_FRAME_LONG_SIDE_Y_DPA1 = 1196.2*mm;
  const G4double HB1_FRAME_Z_DPA1 = 2550.*mm;

  const G4double d_FROM_NEW_CENTER_HB1_DPA1 = d_FROM_NEW_CENTER_DCU1 + THICKNESS_DCU1_FRAME/2 + GAP1_DPA1 + HB1_FRAME_Z_DPA1/2;
  const G4ThreeVector HB1_FRAME_POS_DPA1 = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(0, 0, d_FROM_NEW_CENTER_HB1_DPA1).rotateY(ANGLE_DPA1); 

  G4Trd *HB1_FRAME_V_DPA1 = new G4Trd("Helium Bag Frame DPA1",
  				      HB1_FRAME_SHORT_SIDE_X_DPA1/2,
  			              HB1_FRAME_LONG_SIDE_X_DPA1/2,
  			              HB1_FRAME_SHORT_SIDE_Y_DPA1/2,
  			              HB1_FRAME_LONG_SIDE_Y_DPA1/2,
			              HB1_FRAME_Z_DPA1/2);
  G4LogicalVolume *HB1_FRAME_LV_DPA1 = new G4LogicalVolume(HB1_FRAME_V_DPA1, PET, "HB1_FRAME_LV_DPA1");
  G4PVPlacement* HB1_FRAME_PV_DPA1 = new G4PVPlacement(ROTATE_DPA1,
 		    HB1_FRAME_POS_DPA1,
		    "HB1_FRAME_PV_DPA1",
		    HB1_FRAME_LV_DPA1,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* HB1_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0, 1., 0));
  HB1_FRAME_LV_DPA1 -> SetVisAttributes(HB1_FRAME_VisAtt);

  //----------------------
  // Helium Bag #1 Inside
  //----------------------

  const G4double FRAME_THICKNESS_HB1_DPA1 = 0.2*mm;

  const G4double HB1_INSIDE_SHORT_SIDE_X_DPA1 = HB1_FRAME_SHORT_SIDE_X_DPA1 - 2*FRAME_THICKNESS_HB1_DPA1;
  const G4double HB1_INSIDE_LONG_SIDE_X_DPA1 = HB1_FRAME_LONG_SIDE_X_DPA1 - 2*FRAME_THICKNESS_HB1_DPA1;
  const G4double HB1_INSIDE_SHORT_SIDE_Y_DPA1 = HB1_FRAME_SHORT_SIDE_Y_DPA1 - 2*FRAME_THICKNESS_HB1_DPA1;
  const G4double HB1_INSIDE_LONG_SIDE_Y_DPA1 = HB1_FRAME_LONG_SIDE_Y_DPA1 - 2*FRAME_THICKNESS_HB1_DPA1;
  const G4double HB1_INSIDE_Z_DPA1 = HB1_FRAME_Z_DPA1 - 2*FRAME_THICKNESS_HB1_DPA1;

  G4Trd *HB1_INSIDE_V_DPA1 = new G4Trd("Helium Bag INSIDE DPA1",
  			               HB1_INSIDE_SHORT_SIDE_X_DPA1/2,
  			               HB1_INSIDE_LONG_SIDE_X_DPA1/2,
  				       HB1_INSIDE_SHORT_SIDE_Y_DPA1/2,
  				       HB1_INSIDE_LONG_SIDE_Y_DPA1/2,
				       HB1_INSIDE_Z_DPA1/2);
  G4LogicalVolume *HB1_INSIDE_LV_DPA1 = new G4LogicalVolume(HB1_INSIDE_V_DPA1, HeGas, "HB1_INSIDE_LV_DPA1");
  new G4PVPlacement(0,
 		    G4ThreeVector(),
		    "HB1_INSIDE_PV_DPA1",
		    HB1_INSIDE_LV_DPA1,
		    HB1_FRAME_PV_DPA1,
		    FALSE,
		    0);

  G4VisAttributes* HB1_INSIDE_VisAtt = new G4VisAttributes(true, G4Colour(0, 0.7, 0));
  HB1_INSIDE_LV_DPA1 -> SetVisAttributes(HB1_INSIDE_VisAtt);
  
  //----------------------
  // Helium Bag #1 Window
  //----------------------

  G4VisAttributes* HB1_WINDOW_VisAtt = new G4VisAttributes(true, G4Colour(0, 0, 1.));
  HB1_WINDOW_VisAtt -> SetForceSolid(true);

  //-------------------------------
  // Helium Bag #1 Window Upstream
  //-------------------------------

  const G4ThreeVector HB1_WINDOW_UP_DPA1_POS = G4ThreeVector(0, 0, -HB1_FRAME_Z_DPA1/2 + FRAME_THICKNESS_HB1_DPA1/2);

  G4Box *HB1_WINDOW_UP_V_DPA1 = new G4Box("Helium Bag Window Upstream",
  					  HB1_INSIDE_SHORT_SIDE_X_DPA1/2,
  					  HB1_INSIDE_SHORT_SIDE_Y_DPA1/2,
					  FRAME_THICKNESS_HB1_DPA1/2);
  G4LogicalVolume *HB1_WINDOW_UP_LV_DPA1 = new G4LogicalVolume(HB1_WINDOW_UP_V_DPA1, PET, "HB1_WINDOW_UP_LV_DPA1");
  new G4PVPlacement(0,
  		    HB1_WINDOW_UP_DPA1_POS,
		    "HB1_WINDOW_UP_PV_DPA1",
		    HB1_WINDOW_UP_LV_DPA1,
		    HB1_FRAME_PV_DPA1,
		    FALSE,
		    0);

  HB1_WINDOW_UP_LV_DPA1 -> SetVisAttributes(HB1_WINDOW_VisAtt);

  //---------------------------------
  // Helium Bag #1 Window Downstream
  //---------------------------------

  const G4ThreeVector HB1_WINDOW_DOWN_DPA1_POS = G4ThreeVector(0, 0, HB1_FRAME_Z_DPA1/2 - FRAME_THICKNESS_HB1_DPA1/2);

  G4Box *HB1_WINDOW_DOWN_V_DPA1 = new G4Box("Helium Bag Window Downstream",
  					  HB1_INSIDE_LONG_SIDE_X_DPA1/2,
  					  HB1_INSIDE_LONG_SIDE_Y_DPA1/2,
					  FRAME_THICKNESS_HB1_DPA1/2);
  G4LogicalVolume *HB1_WINDOW_DOWN_LV_DPA1 = new G4LogicalVolume(HB1_WINDOW_DOWN_V_DPA1, PET, "HB1_WINDOW_DOWN_LV_DPA1");
  new G4PVPlacement(0,
  		    HB1_WINDOW_DOWN_DPA1_POS,
		    "HB1_WINDOW_DOWN_PV_DPA1",
		    HB1_WINDOW_DOWN_LV_DPA1,
		    HB1_FRAME_PV_DPA1,
		    FALSE,
		    0);

  HB1_WINDOW_DOWN_LV_DPA1 -> SetVisAttributes(HB1_WINDOW_VisAtt);

  //-------------------------------
  // Drift Chamber Downstream Frame
  //-------------------------------

  const G4double WIDTH_DCD1_FRAME = 3100*mm;
  const G4double HEIGHT_DCD1_FRAME = 1300*mm;
  const G4double THICKNESS_DCD1_FRAME = 100*mm;

  const G4double d_FROM_NEW_CENTER_DCD1 = d_FROM_NEW_CENTER_DCU1 + THICKNESS_DCU1_FRAME/2 + GAP1_DPA1 + GAP2_DPA1 + HB1_FRAME_Z_DPA1 + THICKNESS_DCD1_FRAME/2;
  const G4ThreeVector DCD1_POS = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(0, 0, d_FROM_NEW_CENTER_DCD1).rotateY(ANGLE_DPA1);

  G4Box* DCD1_FRAME_BOX = new G4Box("DCD1_BOX", WIDTH_DCD1_FRAME/2, HEIGHT_DCD1_FRAME/2, THICKNESS_DCD1_FRAME/2);
  G4LogicalVolume* DCD1_FRAME_LV = new G4LogicalVolume(DCD1_FRAME_BOX, PET, "DCD1_FRAME_LV");
  G4PVPlacement* DCD1_FRAME_PV = new G4PVPlacement(ROTATE_DPA1,
  		    DCD1_POS,
		    "DCD1_FRAME_PV",
		    DCD1_FRAME_LV,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* DCD1_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.7, 1.));
  DCD1_FRAME_LV -> SetVisAttributes(DCD1_FRAME_VisAtt);

  //--------------------------------
  // Drift Chamber Downstream Inside
  //--------------------------------

  const G4double FRAME_THICKNESS_DCD1 = 0.1*mm;

  const G4double WIDTH_DCD1_IN = WIDTH_DCD1_FRAME - 2*FRAME_THICKNESS_DCD1;
  const G4double HEIGHT_DCD1_IN = HEIGHT_DCD1_FRAME - 2*FRAME_THICKNESS_DCD1;
  const G4double THICKNESS_DCD1_IN = THICKNESS_DCD1_FRAME - 2*FRAME_THICKNESS_DCD1;

  G4Box* DCD1_IN_BOX = new G4Box("DCD1_BOX", WIDTH_DCD1_IN/2, HEIGHT_DCD1_IN/2, THICKNESS_DCD1_IN/2);
  G4LogicalVolume* DCD1_IN_LV = new G4LogicalVolume(DCD1_IN_BOX, ArEthane, "DCD1_IN_LV");
  new G4PVPlacement(0,
  		    G4ThreeVector(),
		    "DCD1_IN_PV",
		    DCD1_IN_LV,
		    DCD1_FRAME_PV,
		    FALSE,
		    0);

  G4VisAttributes* DCD1_IN_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.5, 1.));
  DCD1_IN_LV -> SetVisAttributes(DCD1_IN_VisAtt);

  //-----------------------
  // ToF Wall DPA1 - Genie
  //-----------------------

  const G4int NUM_TOF_BARS_DPA1 = 31;
  const G4double WIDTH_TOF_DPA1 = 100.*mm;
  const G4double HEIGHT_TOF_DPA1 = 1300.*mm;
  const G4double THICKNESS_TOF_DPA1 = 100.*mm;

  G4Box* TOF_WALL_DPA1_V = new G4Box("ToF Wall DPA1", WIDTH_TOF_DPA1/2, HEIGHT_TOF_DPA1/2, THICKNESS_TOF_DPA1/2);
  G4LogicalVolume* TOF_WALL_DPA1_LV = new G4LogicalVolume(TOF_WALL_DPA1_V, Scint, "TOF_WALL_DPA1_LV");
  for (G4int i = 0; i != NUM_TOF_BARS_DPA1; i++)
  {
	const G4double TOF_BAR_X_POS_DPA1 = THICKNESS_TOF_DPA1*(NUM_TOF_BARS_DPA1/2 - i);
	const G4double TOF_BAR_Z_POS_DPA1 = d_FROM_NEW_CENTER_DCD1 + THICKNESS_DCD1_FRAME/2 + GAP2_DPA1 + THICKNESS_TOF_DPA1/2;
	const G4ThreeVector TOF_BAR_POS_DPA1 = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(TOF_BAR_X_POS_DPA1, 0., TOF_BAR_Z_POS_DPA1).rotateY(ANGLE_DPA1);
  	new G4PVPlacement(ROTATE_DPA1,
			  TOF_BAR_POS_DPA1,
			  "TOF_WALL_DPA1_PV",
			  TOF_WALL_DPA1_LV,
			  expHall,
			  FALSE,
			  i);
  }

  G4VisAttributes* TOF_WALL_DPA1_VisAtt = new G4VisAttributes(true, G4Colour(1., 0.5, 0.));
  TOF_WALL_DPA1_LV -> SetVisAttributes(TOF_WALL_DPA1_VisAtt);

  //=======================
  // Dipole Arm #2 - Genie
  //=======================

  const G4double GAP1_DPA2 = 50.*mm;
  const G4double GAP2_DPA2 = 100.*mm;
  const G4double ANGLE_DPA2 = defaultAngle + 45.*deg;

  G4RotationMatrix* ROTATE_DPA2 = new G4RotationMatrix();
  ROTATE_DPA2 -> rotateY(-ANGLE_DPA2);

  //------------------------------
  // Drift Chamber Upstream Frame
  //------------------------------

  const G4double WIDTH_DCU2_FRAME = 800*mm;
  const G4double HEIGHT_DCU2_FRAME = 600*mm;
  const G4double THICKNESS_DCU2_FRAME = 100*mm;

  const G4double d_FROM_NEW_CENTER_DCU2 = 750.*mm;
  const G4ThreeVector DCU2_POS = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(0, 0, d_FROM_NEW_CENTER_DCU2).rotateY(ANGLE_DPA2);

  G4Box* DCU2_FRAME_BOX = new G4Box("DCU2_BOX", WIDTH_DCU2_FRAME/2, HEIGHT_DCU2_FRAME/2, THICKNESS_DCU2_FRAME/2);
  G4LogicalVolume* DCU2_FRAME_LV = new G4LogicalVolume(DCU2_FRAME_BOX, PET, "DCU2_FRAME_LV");
  G4PVPlacement* DCU2_FRAME_PV = new G4PVPlacement(ROTATE_DPA2,
  		    DCU2_POS,
		    "DCU2_FRAME_PV",
		    DCU2_FRAME_LV,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* DCU2_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.7, 1.));
  DCU2_FRAME_LV -> SetVisAttributes(DCU2_FRAME_VisAtt);

  //-------------------------------
  // Drift Chamber Upstream Inside
  //-------------------------------

  const G4double FRAME_THICKNESS_DCU2 = 0.1*mm;

  const G4double WIDTH_DCU2_IN = WIDTH_DCU2_FRAME - 2*FRAME_THICKNESS_DCU2;
  const G4double HEIGHT_DCU2_IN = HEIGHT_DCU2_FRAME - 2*FRAME_THICKNESS_DCU2;
  const G4double THICKNESS_DCU2_IN = THICKNESS_DCU2_FRAME - 2*FRAME_THICKNESS_DCU2;

  G4Box* DCU2_IN_BOX = new G4Box("DCU2_BOX", WIDTH_DCU2_IN/2, HEIGHT_DCU2_IN/2, THICKNESS_DCU2_IN/2);
  G4LogicalVolume* DCU2_IN_LV = new G4LogicalVolume(DCU2_IN_BOX, ArEthane, "DCU2_IN_LV");
  new G4PVPlacement(0,
  		    G4ThreeVector(),
		    "DCU2_IN_PV",
		    DCU2_IN_LV,
		    DCU2_FRAME_PV,
		    FALSE,
		    0);

  G4VisAttributes* DCU2_IN_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.5, 1.));
  DCU2_IN_LV -> SetVisAttributes(DCU2_IN_VisAtt);

  //------------------
  // Helium Bag Frame
  //------------------

  const G4double HB_FRAME_SHORT_SIDE_X_DPA2 = 880.*mm;
  const G4double HB_FRAME_SHORT_SIDE_Y_DPA2 = 570.*mm;
  const G4double HB_FRAME_LONG_SIDE_X_DPA2 = 2990.*mm;
  const G4double HB_FRAME_LONG_SIDE_Y_DPA2 = 1196.2*mm;
  const G4double HB_FRAME_Z_DPA2 = 2550.*mm;

  const G4double d_FROM_NEW_CENTER_HB_DPA2 = d_FROM_NEW_CENTER_DCU2 + THICKNESS_DCU2_FRAME/2 + GAP1_DPA2 + HB_FRAME_Z_DPA2/2;
  const G4ThreeVector HB_FRAME_POS_DPA2 = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(0, 0, d_FROM_NEW_CENTER_HB_DPA2).rotateY(ANGLE_DPA2);

  G4Trd *HB_FRAME_V_DPA2 = new G4Trd("Helium Bag Frame DPA2",
  			       HB_FRAME_SHORT_SIDE_X_DPA2/2,
  			       HB_FRAME_LONG_SIDE_X_DPA2/2,
  			       HB_FRAME_SHORT_SIDE_Y_DPA2/2,
  			       HB_FRAME_LONG_SIDE_Y_DPA2/2,
			       HB_FRAME_Z_DPA2/2);
  G4LogicalVolume *HB_FRAME_LV_DPA2 = new G4LogicalVolume(HB_FRAME_V_DPA2, PET, "HB_FRAME_LV_DPA2");
  G4PVPlacement* HB_FRAME_PV_DPA2 = new G4PVPlacement(ROTATE_DPA2,
 		    HB_FRAME_POS_DPA2,
		    "HB_FRAME_PV_DPA2",
		    HB_FRAME_LV_DPA2,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* HB_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0, 1., 0));
  HB_FRAME_LV_DPA2 -> SetVisAttributes(HB_FRAME_VisAtt);

  //-------------------
  // Helium Bag Inside
  //-------------------

  const G4double FRAME_THICKNESS_HB_DPA2 = 0.2*mm;

  const G4double HB_INSIDE_SHORT_SIDE_X_DPA2 = HB_FRAME_SHORT_SIDE_X_DPA2 - 2*FRAME_THICKNESS_HB_DPA2;
  const G4double HB_INSIDE_LONG_SIDE_X_DPA2 = HB_FRAME_LONG_SIDE_X_DPA2 - 2*FRAME_THICKNESS_HB_DPA2;
  const G4double HB_INSIDE_SHORT_SIDE_Y_DPA2 = HB_FRAME_SHORT_SIDE_Y_DPA2 - 2*FRAME_THICKNESS_HB_DPA2;
  const G4double HB_INSIDE_LONG_SIDE_Y_DPA2 = HB_FRAME_LONG_SIDE_Y_DPA2 - 2*FRAME_THICKNESS_HB_DPA2;
  const G4double HB_INSIDE_Z_DPA2 = HB_FRAME_Z_DPA2 - 2*FRAME_THICKNESS_HB_DPA2;

  G4Trd *HB_INSIDE_V_DPA2 = new G4Trd("Helium Bag INSIDE DPA2",
  			       HB_INSIDE_SHORT_SIDE_X_DPA2/2,
  			       HB_INSIDE_LONG_SIDE_X_DPA2/2,
  			       HB_INSIDE_SHORT_SIDE_Y_DPA2/2,
  			       HB_INSIDE_LONG_SIDE_Y_DPA2/2,
			       HB_INSIDE_Z_DPA2/2);
  G4LogicalVolume *HB_INSIDE_LV_DPA2 = new G4LogicalVolume(HB_INSIDE_V_DPA2, HeGas, "HB_INSIDE_LV_DPA2");
  new G4PVPlacement(0,
 		    G4ThreeVector(),
		    "HB_INSIDE_PV_DPA2",
		    HB_INSIDE_LV_DPA2,
		    HB_FRAME_PV_DPA2,
		    FALSE,
		    0);

  G4VisAttributes* HB_INSIDE_VisAtt = new G4VisAttributes(true, G4Colour(0, 0.7, 0));
  HB_INSIDE_LV_DPA2 -> SetVisAttributes(HB_INSIDE_VisAtt);

  //-------------------
  // Helium Bag Window
  //-------------------

  G4VisAttributes* HB_WINDOW_VisAtt = new G4VisAttributes(true, G4Colour(0, 0, 1.));
  HB_WINDOW_VisAtt -> SetForceSolid(true);

  //----------------------------
  // Helium Bag Window Upstream
  //----------------------------

  const G4ThreeVector HB_WINDOW_UP_DPA2_POS = G4ThreeVector(0, 0, -HB_FRAME_Z_DPA2/2 + FRAME_THICKNESS_HB_DPA2/2);

  G4Box *HB_WINDOW_UP_V_DPA2 = new G4Box("Helium Bag Window Upstream",
  					  HB_INSIDE_SHORT_SIDE_X_DPA2/2,
  					  HB_INSIDE_SHORT_SIDE_Y_DPA2/2,
					  FRAME_THICKNESS_HB_DPA2/2);
  G4LogicalVolume *HB_WINDOW_UP_LV_DPA2 = new G4LogicalVolume(HB_WINDOW_UP_V_DPA2, PET, "HB_WINDOW_UP_LV_DPA2");
  new G4PVPlacement(0,
  		    HB_WINDOW_UP_DPA2_POS,
		    "HB_WINDOW_UP_PV_DPA2",
		    HB_WINDOW_UP_LV_DPA2,
		    HB_FRAME_PV_DPA2,
		    FALSE,
		    0);

  HB_WINDOW_UP_LV_DPA2 -> SetVisAttributes(HB_WINDOW_VisAtt);

  //------------------------------
  // Helium Bag Window Downstream
  //------------------------------

  const G4ThreeVector HB_WINDOW_DOWN_DPA2_POS = G4ThreeVector(0, 0, HB_FRAME_Z_DPA2/2 - FRAME_THICKNESS_HB_DPA2/2);

  G4Box *HB_WINDOW_DOWN_V_DPA2 = new G4Box("Helium Bag Window Downstream",
  					  HB_INSIDE_LONG_SIDE_X_DPA2/2,
  					  HB_INSIDE_LONG_SIDE_Y_DPA2/2,
					  FRAME_THICKNESS_HB_DPA2/2);
  G4LogicalVolume *HB_WINDOW_DOWN_LV_DPA2 = new G4LogicalVolume(HB_WINDOW_DOWN_V_DPA2, PET, "HB_WINDOW_DOWN_LV_DPA2");
  new G4PVPlacement(0,
  		    HB_WINDOW_DOWN_DPA2_POS,
		    "HB_WINDOW_DOWN_PV_DPA2",
		    HB_WINDOW_DOWN_LV_DPA2,
		    HB_FRAME_PV_DPA2,
		    FALSE,
		    0);

  HB_WINDOW_DOWN_LV_DPA2 -> SetVisAttributes(HB_WINDOW_VisAtt);

  //--------------------------------
  // Drift Chamber Downstream Frame
  //--------------------------------

  const G4double WIDTH_DCD2_FRAME = 3100*mm;
  const G4double HEIGHT_DCD2_FRAME = 1300*mm;
  const G4double THICKNESS_DCD2_FRAME = 100*mm;

  const G4double d_FROM_NEW_CENTER_DCD2 = d_FROM_NEW_CENTER_DCU2 + THICKNESS_DCU2_FRAME/2 + GAP1_DPA2 + HB_FRAME_Z_DPA2 + GAP2_DPA2 + THICKNESS_DCD2_FRAME/2;
  const G4ThreeVector DCD2_POS = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(0, 0, d_FROM_NEW_CENTER_DCD2).rotateY(ANGLE_DPA2);

  G4Box* DCD2_FRAME_BOX = new G4Box("DCD2_BOX", WIDTH_DCD2_FRAME/2, HEIGHT_DCD2_FRAME/2, THICKNESS_DCD2_FRAME/2);
  G4LogicalVolume* DCD2_FRAME_LV = new G4LogicalVolume(DCD2_FRAME_BOX, PET, "DCD2_FRAME_LV");
  G4PVPlacement *DCD2_FRAME_PV = new G4PVPlacement(ROTATE_DPA2,
  		    DCD2_POS,
		    "DCD2_FRAME_PV",
		    DCD2_FRAME_LV,
		    expHall,
		    FALSE,
		    0);

  G4VisAttributes* DCD2_FRAME_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.7, 1.));
  DCD2_FRAME_LV -> SetVisAttributes(DCD2_FRAME_VisAtt);

  //---------------------------------
  // Drift Chamber Downstream Inside
  //---------------------------------

  const G4double FRAME_THICKNESS_DCD2 = 0.1*mm;

  const G4double WIDTH_DCD2_IN = WIDTH_DCD2_FRAME - 2*FRAME_THICKNESS_DCD2;
  const G4double HEIGHT_DCD2_IN = HEIGHT_DCD2_FRAME - 2*FRAME_THICKNESS_DCD2;
  const G4double THICKNESS_DCD2_IN = THICKNESS_DCD2_FRAME - 2*FRAME_THICKNESS_DCD2;

  G4Box* DCD2_IN_BOX = new G4Box("DCD2_BOX", WIDTH_DCD2_IN/2, HEIGHT_DCD2_IN/2, THICKNESS_DCD2_IN/2);
  G4LogicalVolume* DCD2_IN_LV = new G4LogicalVolume(DCD2_IN_BOX, ArEthane, "DCD2_IN_LV");
  new G4PVPlacement(0,
  		    G4ThreeVector(),
		    "DCD2_IN_PV",
		    DCD2_IN_LV,
		    DCD2_FRAME_PV,
		    FALSE,
		    0);

  G4VisAttributes* DCD2_IN_VisAtt = new G4VisAttributes(true, G4Colour(0.4, 0.5, 1.));
  DCD2_IN_LV -> SetVisAttributes(DCD2_IN_VisAtt);

  //-----------------------
  // ToF Wall DPA2 - Genie
  //-----------------------

  const G4int NUM_TOF_BARS_DPA2 = 31;
  const G4double WIDTH_TOF_DPA2 = 100.*mm;
  const G4double HEIGHT_TOF_DPA2 = 1300.*mm;
  const G4double THICKNESS_TOF_DPA2 = 100.*mm;

  G4Box* TOF_WALL_DPA2_V = new G4Box("ToF Wall DPA2", WIDTH_TOF_DPA2/2, HEIGHT_TOF_DPA2/2, THICKNESS_TOF_DPA2/2);
  G4LogicalVolume* TOF_WALL_DPA2_LV = new G4LogicalVolume(TOF_WALL_DPA2_V, Scint, "TOF_WALL_DPA2_LV");
  for (G4int i = 0; i != NUM_TOF_BARS_DPA2; i++)
  {
	const G4double TOF_BAR_X_POS_DPA2 = THICKNESS_TOF_DPA2*(NUM_TOF_BARS_DPA2/2 - i);
	const G4double TOF_BAR_Z_POS_DPA2 = d_FROM_NEW_CENTER_DCD2 + THICKNESS_DCD2_FRAME/2 + GAP2_DPA2 + THICKNESS_TOF_DPA2/2;
	const G4ThreeVector TOF_BAR_POS_DPA2 = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(TOF_BAR_X_POS_DPA2, 0., TOF_BAR_Z_POS_DPA2).rotateY(ANGLE_DPA2);
  	new G4PVPlacement(ROTATE_DPA2,
			  TOF_BAR_POS_DPA2,
			  "TOF_WALL_DPA2_PV",
			  TOF_WALL_DPA2_LV,
			  expHall,
			  FALSE,
			  i);
  }

  G4VisAttributes* TOF_WALL_DPA2_VisAtt = new G4VisAttributes(true, G4Colour(1., 0.5, 0.));
  TOF_WALL_DPA2_LV -> SetVisAttributes(TOF_WALL_DPA2_VisAtt);

  //===========================================
  // Drift Chamber ReadOut Geometry - Genie
  //===========================================

  DCROGeometry* DC_RO_GEOMETRY = new DCROGeometry("DC_RO_GEOMETRY",
// For cylindrical world volume
//						      R_EXPHALL,
//						      DZ_EXPHALL,
// For cubic world volume
						      X_EXPHALL,
						      Y_EXPHALL,
						      Z_EXPHALL,
						      X_VOXEL_SIZE_DC,
						      Y_VOXEL_SIZE_DC,
						      Z_VOXEL_SIZE_DC,
						      WIDTH_DCBD_FRAME,
						      HEIGHT_DCBD_FRAME,
						      THICKNESS_DCBD_FRAME,
						      DCBD_POS,
						      ANGLE_DPA1,
						      WIDTH_DCU1_FRAME,
						      HEIGHT_DCU1_FRAME,
						      THICKNESS_DCU1_FRAME,
						      DCU1_POS,
						      WIDTH_DCD1_FRAME,
						      HEIGHT_DCD1_FRAME,
						      THICKNESS_DCD1_FRAME,
						      DCD1_POS,
						      ANGLE_DPA2,
						      WIDTH_DCU2_FRAME,
						      HEIGHT_DCU2_FRAME,
						      THICKNESS_DCU2_FRAME,
						      DCU2_POS,
						      WIDTH_DCD2_FRAME,
						      HEIGHT_DCD2_FRAME,
						      THICKNESS_DCD2_FRAME,
						      DCD2_POS
						      );

  DC_RO_GEOMETRY -> BuildROGeometry(); 

  //================================
  // LAND(neutron detector) - Genie
  //================================

  const bool LAND_1_USE = 1;
  const bool LAND_2_USE = 0;

  const G4double width_LAND = 2000.*mm;
  const G4double height_LAND = 2000.*mm;

  const G4double thickness_VC = 10.*mm;

  const G4double thickness_HB_LAND = 500.*mm;

  const G4double xSize_VERTICAL_SA = 100.*mm;
  const G4double ySize_HORIZONTAL_SA = 100.*mm;
  const G4double zSize_BOTH_SA = 100.*mm;

  const G4ThreeVector LAND1_Start_Pos = G4ThreeVector(0, 0, 15000.*mm - thickness_VC - thickness_HB_LAND);
  const G4ThreeVector LAND2_Start_Pos = G4ThreeVector(0, 0, 10000.*mm);

  const G4int numVerticalLayer = 5;
  const G4int numHorizontalLayer = 5;
  const G4int numBarInLayer = 20;

  const G4int numVerticalArray = numVerticalLayer * numBarInLayer;
  const G4int numHorizontalArray = numHorizontalLayer * numBarInLayer;

  G4VisAttributes* VC_VisAtt = new G4VisAttributes(true, G4Colour(0., 0., 1.));
  G4VisAttributes* HB_LAND_VisAtt = new G4VisAttributes(true, G4Colour(0., 1., 0.));
  G4VisAttributes* SA_VisAtt = new G4VisAttributes(true, G4Colour(0., 0., 1.));


  //----------------
  // LAND 1 - Genie
  //----------------

  //------------------------
  // Veto Counter 1 - Genie
  //------------------------

  const G4ThreeVector VC1_pos = LAND1_Start_Pos + G4ThreeVector(0, 0, thickness_VC/2);

  G4Box *VC1_V = new G4Box("VC1_SOLID", width_LAND/2, height_LAND/2, thickness_VC/2);
  G4LogicalVolume *VC1_LV = new G4LogicalVolume(VC1_V, Scint, "VC1_LV");
  new G4PVPlacement(0, VC1_pos, "VC1_PV", VC1_LV, expHall, false, 1099);

  VC1_LV -> SetVisAttributes(VC_VisAtt);

  //----------------------
  // Helium Bag 1 - Genie
  //----------------------

  const G4ThreeVector HB1_LAND_pos = LAND1_Start_Pos + G4ThreeVector(0, 0, thickness_VC) + G4ThreeVector(0, 0, thickness_HB_LAND/2);

  G4Box *HB1_LAND_V = new G4Box("HB1_LAND_SOLID", width_LAND/2, height_LAND/2, thickness_HB_LAND/2);
  G4LogicalVolume *HB1_LAND_LV = new G4LogicalVolume(HB1_LAND_V, HeGas, "HB1_LAND_LV");
  new G4PVPlacement(0, HB1_LAND_pos, "HB1_LAND_PV", HB1_LAND_LV, expHall, false, 0);

  HB1_LAND_LV -> SetVisAttributes(HB_LAND_VisAtt);

  //------------------------------
  // Scintillator Array 1 - Genie
  //------------------------------

  G4Box *SA_VERTICAL_V = new G4Box("SA_VERTICAL_V", xSize_VERTICAL_SA/2, height_LAND/2, zSize_BOTH_SA/2);
  G4Box *SA_HORIZONTAL_V = new G4Box("SA_HORIZONTAL_V", width_LAND/2, ySize_HORIZONTAL_SA/2, zSize_BOTH_SA/2);

  G4LogicalVolume *SA1_VERTICAL_LV = new G4LogicalVolume(SA_VERTICAL_V, Scint, "SA1_VERTICAL_LV");
  G4LogicalVolume *SA1_HORIZONTAL_LV = new G4LogicalVolume(SA_HORIZONTAL_V, Scint, "SA1_HORIZONTAL_LV");

  SA1_HORIZONTAL_LV -> SetVisAttributes(SA_VisAtt);
  SA1_VERTICAL_LV -> SetVisAttributes(SA_VisAtt);

  for (G4int i = 0; i != numVerticalLayer; i++) {
	for (G4int j = 0; j != numBarInLayer; j++) {
		G4int HorizontalBarNo = 1000 + 200*i + j; // XYZZ - X: LAND Number, Y: Layer Number, ZZ: Bar Number(along the axis)
		const G4ThreeVector SA1_HORIZONTAL_pos = LAND1_Start_Pos + G4ThreeVector(0, 0, thickness_VC) + G4ThreeVector(0, 0, thickness_HB_LAND)
						+ G4ThreeVector(0, (-numBarInLayer + 2*j + 1)*ySize_HORIZONTAL_SA/2, (4*i + 1)*zSize_BOTH_SA/2);

		new G4PVPlacement(0, SA1_HORIZONTAL_pos, "SA1_HORIZONTAL_PV", SA1_HORIZONTAL_LV, expHall, false, HorizontalBarNo);

		G4int VerticalBarNo = 1100 + 200*i + j; // XYZZ - X: LAND Number, Y: Layer Number, ZZ: Bar Number(along the axis)
		const G4ThreeVector SA1_VERTICAL_pos = LAND1_Start_Pos + G4ThreeVector(0, 0, thickness_VC) + G4ThreeVector(0, 0, thickness_HB_LAND)
						+ G4ThreeVector((-numBarInLayer + 2*j + 1)*xSize_VERTICAL_SA/2, 0, (4*i + 3)*zSize_BOTH_SA/2);

		new G4PVPlacement(0, SA1_VERTICAL_pos, "SA1_VERTICAL_PV", SA1_VERTICAL_LV, expHall, false, VerticalBarNo);
	}
  }

  if (LAND_2_USE == 1)
  {

  //----------------
  // LAND 2 - Genie
  //----------------

//  const G4double ROT_LAND2_ANGLE = 12.*deg;
//  const G4double ROT_LAND2_ANGLE = 8.76*deg;
  const G4double ROT_LAND2_ANGLE = 9.*deg;
  G4RotationMatrix *ROT_LAND2 = new G4RotationMatrix();
  ROT_LAND2 -> rotateY(ROT_LAND2_ANGLE);

  //------------------------
  // Veto Counter 2 - Genie
  //------------------------

  const G4ThreeVector VC2_pos = (LAND2_Start_Pos + G4ThreeVector(0, 0, thickness_VC/2)).rotateY(-ROT_LAND2_ANGLE);

  G4Box *VC2_V = new G4Box("VC2_SOLID", width_LAND/2, height_LAND/2, thickness_VC/2);
  G4LogicalVolume *VC2_LV = new G4LogicalVolume(VC2_V, Scint, "VC2_LV");
  new G4PVPlacement(ROT_LAND2, VC2_pos, "VC2_PV", VC2_LV, expHall, false, 2099);

  G4VisAttributes* VC2_VisAtt = new G4VisAttributes(true, G4Colour(0., 0., 1.));
  VC2_LV -> SetVisAttributes(VC2_VisAtt);

  //----------------------
  // Helium Bag 2 - Genie
  //----------------------

  const G4ThreeVector HB2_LAND_pos = (LAND2_Start_Pos + G4ThreeVector(0, 0, thickness_VC) + G4ThreeVector(0, 0, thickness_HB_LAND/2)).rotateY(-ROT_LAND2_ANGLE);

  G4Box *HB2_LAND_V = new G4Box("HB2_LAND_SOLID", width_LAND/2, height_LAND/2, thickness_HB_LAND/2);
  G4LogicalVolume *HB2_LAND_LV = new G4LogicalVolume(HB2_LAND_V, HeGas, "HB2_LAND_LV");
  new G4PVPlacement(ROT_LAND2, HB2_LAND_pos, "HB2_LAND_PV", HB2_LAND_LV, expHall, false, 0);

  G4VisAttributes* HB2_LAND_VisAtt = new G4VisAttributes(true, G4Colour(0., 1., 0.));
  HB2_LAND_LV -> SetVisAttributes(HB2_LAND_VisAtt);

  //------------------------------
  // Scintillator Array 2 - Genie
  //------------------------------

  G4LogicalVolume *SA2_VERTICAL_LV = new G4LogicalVolume(SA_VERTICAL_V, Scint, "SA2_VERTICAL_LV");
  G4LogicalVolume *SA2_HORIZONTAL_LV = new G4LogicalVolume(SA_HORIZONTAL_V, Scint, "SA2_HORIZONTAL_LV");

  SA2_HORIZONTAL_LV -> SetVisAttributes(SA_VisAtt);
  SA2_VERTICAL_LV -> SetVisAttributes(SA_VisAtt);

  for (G4int i = 0; i != numVerticalLayer; i++) {
	for (G4int j = 0; j != numBarInLayer; j++) {
		G4int HorizontalBarNo = 2000 + 200*i + j; // XYZZ - X: LAND Number, Y: Layer Number, ZZ: Bar Number(along the axis)
		const G4ThreeVector SA2_HORIZONTAL_pos = (LAND2_Start_Pos + G4ThreeVector(0, 0, thickness_VC) + G4ThreeVector(0, 0, thickness_HB_LAND)
						+ G4ThreeVector(0, (-numBarInLayer + 2*j + 1)*ySize_HORIZONTAL_SA/2, (4*i + 1)*zSize_BOTH_SA/2)).rotateY(-ROT_LAND2_ANGLE);

		new G4PVPlacement(ROT_LAND2, SA2_HORIZONTAL_pos, "SA2_HORIZONTAL_PV", SA2_HORIZONTAL_LV, expHall, false, HorizontalBarNo);

		G4int VerticalBarNo = 2100 + 200*i + j; // XYZZ - X: LAND Number, Y: Layer Number, ZZ: Bar Number(along the axis)
		const G4ThreeVector SA2_VERTICAL_pos = (LAND2_Start_Pos + G4ThreeVector(0, 0, thickness_VC) + G4ThreeVector(0, 0, thickness_HB_LAND)
						+ G4ThreeVector((-numBarInLayer + 2*j + 1)*xSize_VERTICAL_SA/2, 0, (4*i + 3)*zSize_BOTH_SA/2)).rotateY(-ROT_LAND2_ANGLE);

		new G4PVPlacement(ROT_LAND2, SA2_VERTICAL_pos, "SA2_VERTICAL_PV", SA2_VERTICAL_LV, expHall, false, VerticalBarNo);
	}
  }

  //==============================================================
  // LAND 2 Sensitive Detector - Genie
  //==============================================================

  LANDSD* LAND_VC2_SD = new LANDSD(SDname="/ND/VC2", "VC2");
  SDman -> AddNewDetector(LAND_VC2_SD);
  VC2_LV -> SetSensitiveDetector(LAND_VC2_SD);

  LANDSD* LAND_SA2_SD = new LANDSD(SDname="/ND/LAND2", "SA2");
  SDman -> AddNewDetector(LAND_SA2_SD);
  SA2_HORIZONTAL_LV -> SetSensitiveDetector(LAND_SA2_SD);
  SA2_VERTICAL_LV -> SetSensitiveDetector(LAND_SA2_SD);

  } // LAND 2 USE

  // ==============================================================
  //  Solenoid Magnet
  // ==============================================================

  const G4double RIN_SOL=   0.9*m;
  const G4double ROUT_SOL=  1.4*m;
  const G4double DZ_SOL=    1.0*m;
  const G4double DPHI_SOL=  360.*deg;

  G4VSolid* SolSolid = new G4Tubs("Solenoid Magnet", RIN_SOL, ROUT_SOL, DZ_SOL, 0., DPHI_SOL);
  G4LogicalVolume* SolLV = new G4LogicalVolume(SolSolid, Iron, "SolenoidLogical");
  new G4PVPlacement(0, G4ThreeVector(0, 0, DZ_TPC_OFFSET), "SOL_PV", SolLV, expHall, FALSE, 0);
  G4VisAttributes* SolVisAtt= new G4VisAttributes(true, G4Colour(1.,0.,1.));
  SolLV-> SetVisAttributes(SolVisAtt);

  // ==============================================================
  // mangentic field
  // ==============================================================
  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  
  // implement here

/*
  LAMPSField* myfield = new LAMPSField("parameter/solenoid.dat");
  G4FieldManager* fieldMgr =
  G4TransportationManager::GetTransportationManager()->GetFieldManager();
  fieldMgr->SetDetectorField(myfield);
  fieldMgr->CreateChordFinder(myfield);
*/

  //================
  // Dipole - Genie
  //================

  const G4double ROT_DP_ANGLE = -defaultAngle + 45.*deg;
  G4RotationMatrix *ROT_DP = new G4RotationMatrix();
  ROT_DP -> rotateY(ROT_DP_ANGLE);

  const G4double d_FROM_NEW_CENTER_DP = -350.*mm;

  //---------------------------
  // Dipole Vacuum - Genie
  //---------------------------

  const G4double DP_VACUUM_1_X_DIM = 1150.*mm;
  const G4double DP_VACUUM_1_Y_DIM = 800.*mm;
  const G4double DP_VACUUM_1_Z_DIM = 1800.*mm;

  G4Box* DP_VACUUM_V1 = new G4Box("DP_VACUUM_V1", DP_VACUUM_1_X_DIM/2, DP_VACUUM_1_Y_DIM/2, DP_VACUUM_1_Z_DIM/2);

  const G4double DP_VACUUM_2_X_DIM = 800.*mm;
  const G4double DP_VACUUM_2_Y_DIM = 800.*mm;
  const G4double DP_VACUUM_2_Z_DIM = 1410.*mm;

  G4RotationMatrix* ROT_DP_VACUUM_V2 = new G4RotationMatrix();
  ROT_DP_VACUUM_V2 -> rotateY(-ROT_DP_ANGLE - defaultAngle);

  const G4ThreeVector Trans_V2 = G4ThreeVector(0, 0, -d_FROM_NEW_CENTER_DP) + G4ThreeVector(0, 0, -DP_VACUUM_2_Z_DIM/2).rotateY(ROT_DP_ANGLE + defaultAngle);

  G4Box* DP_VACUUM_V2 = new G4Box("DP_VACUUM_V2", DP_VACUUM_2_X_DIM/2, DP_VACUUM_2_Y_DIM/2, DP_VACUUM_2_Z_DIM/2);

  const G4ThreeVector DP_VACUUM_POS = G4ThreeVector(0, 0, NEW_CENTER) + G4ThreeVector(0, 0, d_FROM_NEW_CENTER_DP).rotateY(-ROT_DP_ANGLE);

  G4UnionSolid* DP_VACUUM_V = new G4UnionSolid("DP_VACUUM_V", DP_VACUUM_V1, DP_VACUUM_V2, ROT_DP_VACUUM_V2, Trans_V2);
  G4LogicalVolume* DP_VACUUM_LV = new G4LogicalVolume(DP_VACUUM_V, Universal_Vacuum, "DP_VACUUM_LV", 0, 0, 0);
  G4PVPlacement* DP_VACUUM_PV = new G4PVPlacement(ROT_DP,
  						  DP_VACUUM_POS,
						  "DP_VACUUM_PV",
						  DP_VACUUM_LV,
						  expHall,
						  false,
						  0);

  G4VisAttributes* DP_VACUUM_Att = new G4VisAttributes(true, G4Colour(1., 1., 0));
  DP_VACUUM_LV -> SetVisAttributes(DP_VACUUM_Att);

  //--------------------------------------------
  // Dipole and Solenoid Magnetic Field - Genie
  //--------------------------------------------

  const G4double DP_X_DIM = 1000.*mm;
  const G4double DP_Y_DIM = 600.*mm;
  const G4double DP_Z_DIM = 1700.*mm;
  const G4double DP_STRENGTH = -1.*tesla;

  MagField(DP_X_DIM, DP_Y_DIM, DP_Z_DIM, NEW_CENTER, -d_FROM_NEW_CENTER_DP, ROT_DP_ANGLE, DP_STRENGTH);
  mField = DP_STRENGTH;

  G4Box* MField_box = new G4Box("MField_box", DP_X_DIM/2, DP_Y_DIM/2, DP_Z_DIM/2);
  G4LogicalVolume* MField_log = new G4LogicalVolume(MField_box, Universal_Vacuum, "MField_log", 0, 0, 0);
  G4PVPlacement* MField_phys = new G4PVPlacement(0,
 						 G4ThreeVector(),
						 "MField_phys",
						 MField_log,
						 DP_VACUUM_PV,
						 false,
						 0);

  G4VisAttributes* MField_Att = new G4VisAttributes(true, red);
  MField_log-> SetVisAttributes(MField_Att);

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  

  //==============================================================
  // TPC - Genie
  //==============================================================

  TPCSD* TPC_SD = new TPCSD(SDname="/TPC");
  TPC_SD -> SetROgeometry(TPC_RO_GEOMETRY);
  SDman -> AddNewDetector(TPC_SD);
  TPC_LV_IN -> SetSensitiveDetector(TPC_SD);

  //==============================================================
  // Drift Chamber - Genie
  //==============================================================
 
  DCSD* DC_SD_BD = new DCSD(SDname="/DC/BD", "BD");
  DC_SD_BD -> SetROgeometry(DC_RO_GEOMETRY);
  SDman -> AddNewDetector(DC_SD_BD);
  DCBD_IN_LV -> SetSensitiveDetector(DC_SD_BD);

  DCSD* DC_SD_DPA1 = new DCSD(SDname="/DC/DPA1", "DPA1");
  DC_SD_DPA1 -> SetROgeometry(DC_RO_GEOMETRY);
  SDman -> AddNewDetector(DC_SD_DPA1);
  DCU1_IN_LV -> SetSensitiveDetector(DC_SD_DPA1);
  DCD1_IN_LV -> SetSensitiveDetector(DC_SD_DPA1);

  DCSD* DC_SD_DPA2 = new DCSD(SDname="/DC/DPA2", "DPA2");
  DC_SD_DPA2 -> SetROgeometry(DC_RO_GEOMETRY);
  SDman -> AddNewDetector(DC_SD_DPA2);
  DCU2_IN_LV -> SetSensitiveDetector(DC_SD_DPA2);
  DCD2_IN_LV -> SetSensitiveDetector(DC_SD_DPA2);
  
  // ===========================================
  // Si & CsI Sensitive detector - KYO
  // ===========================================

	SiCsISD* SiF1_SD = new SiCsISD(SDname="/SiCsI/SiF1_SD", "SiF1");
	SiF1_SD -> SetROgeometry(SICSI_RO_GEOMETRY);
	SDman -> AddNewDetector(SiF1_SD);
	SiF1_LV -> SetSensitiveDetector(SiF1_SD);

	SiCsISD* SiS1_SD = new SiCsISD(SDname="/SiCsI/SiS1_SD", "SiS1");
	SiS1_SD -> SetROgeometry(SICSI_RO_GEOMETRY);
	SDman -> AddNewDetector(SiS1_SD);
	SiS1_LV -> SetSensitiveDetector(SiS1_SD);

	SiCsISD* SiT1_SD = new SiCsISD(SDname="/SiCsI/SiT1_SD", "SiT1");
	SiT1_SD -> SetROgeometry(SICSI_RO_GEOMETRY);
	SDman -> AddNewDetector(SiT1_SD);
	SiT1_LV -> SetSensitiveDetector(SiT1_SD);

	SiCsISD* CsI1_SD = new SiCsISD(SDname="/SiCsI/CsI1_SD", "CsI1");
	CsI1_SD -> SetROgeometry(SICSI_RO_GEOMETRY);
	SDman -> AddNewDetector(CsI1_SD);
	CsI1_LV -> SetSensitiveDetector(CsI1_SD);

  //==============================================================
  // ToF Wall - Genie
  //==============================================================

  ToFSD* ToF_SD_DPA1 = new ToFSD(SDname="/ToF/DPA1", "DPA1");
  SDman -> AddNewDetector(ToF_SD_DPA1);
  TOF_WALL_DPA1_LV  -> SetSensitiveDetector(ToF_SD_DPA1);

  ToFSD* ToF_SD_DPA2 = new ToFSD(SDname="/ToF/DPA2", "DPA2");
  SDman -> AddNewDetector(ToF_SD_DPA2);
  TOF_WALL_DPA2_LV  -> SetSensitiveDetector(ToF_SD_DPA2);

  //==============================================================
  // LAND 1 - Genie
  //==============================================================

  LANDSD* LAND_VC1_SD = new LANDSD(SDname="/ND/VC1", "VC1");
  SDman -> AddNewDetector(LAND_VC1_SD);
  VC1_LV -> SetSensitiveDetector(LAND_VC1_SD);

  LANDSD* LAND_SA1_SD = new LANDSD(SDname="/ND/LAND1", "SA1");
  SDman -> AddNewDetector(LAND_SA1_SD);
  SA1_HORIZONTAL_LV -> SetSensitiveDetector(LAND_SA1_SD);
  SA1_VERTICAL_LV -> SetSensitiveDetector(LAND_SA1_SD);

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  

  // ==============================================================
  // finally return the world volume
  // ==============================================================

  return expHall;

}

void LAMPSDetectorConstruction::MagField(G4double DP_X_DIM, G4double DP_Y_DIM, G4double DP_Z_DIM, G4double NEW_CENTER, G4double d_FROM_NEW_CENTER_DP, G4double ROT_DP_ANGLE, G4double DP_STRENGTH)
{
	DP_VALUES[0] = DP_X_DIM;
	DP_VALUES[1] = DP_Y_DIM;
	DP_VALUES[2] = DP_Z_DIM;
	DP_VALUES[3] = NEW_CENTER;
	DP_VALUES[4] = d_FROM_NEW_CENTER_DP,
	DP_VALUES[5] = ROT_DP_ANGLE;

	myDPfield = new Fields(DP_X_DIM, DP_Y_DIM, DP_Z_DIM, NEW_CENTER, d_FROM_NEW_CENTER_DP, ROT_DP_ANGLE, DP_STRENGTH);
//	G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	fieldMgr->SetDetectorField(myDPfield);
	fieldMgr->CreateChordFinder(myDPfield);

	mField = DP_STRENGTH;
}

void LAMPSDetectorConstruction::SetMagField(G4double DP_STRENGTH)
{
	delete myDPfield;

	myDPfield = new Fields(DP_VALUES[0], DP_VALUES[1], DP_VALUES[2], DP_VALUES[3], DP_VALUES[4], DP_VALUES[5], DP_STRENGTH);
//	G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	fieldMgr->SetDetectorField(myDPfield);
	fieldMgr->CreateChordFinder(myDPfield);

	mField = DP_STRENGTH;
}

G4double LAMPSDetectorConstruction::GetDPField()
{
	return mField;
}
