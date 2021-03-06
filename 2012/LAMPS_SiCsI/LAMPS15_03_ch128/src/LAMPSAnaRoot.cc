//=================
// LAMPSAnaRoot.cc
//=================

#include "LAMPSAnaRoot.hh"
#include <iostream>
#include <sstream>

LAMPSAnaRoot::LAMPSAnaRoot()
{
	std::stringstream fileName;
	fileName << "rawData.root";
	rootFile = new TFile(fileName.str().c_str(), "RECREATE");
	rootDir = gDirectory;

  // IQMD Data Tree Making
	rootDir -> cd();

	generatorDataTree = new TTree("GeneratorData", "Primary Vertices are stored");
		generatorDataTree -> Branch("eventID", &eventID, "eventID/I");
		generatorDataTree -> Branch("trackID", &trackID, "trackID/I");
		generatorDataTree -> Branch("pID", &pID, "pID/I");
		generatorDataTree -> Branch("energyInit", &energyInit, "energyInit/D");
		generatorDataTree -> Branch("mass", &mass, "mass/D");
		generatorDataTree -> Branch("pX", &pX, "pX/D");
		generatorDataTree -> Branch("pY", &pY, "pY/D");
		generatorDataTree -> Branch("pZ", &pZ, "pZ/D");

	// Simulation Data Tree Making
	rootDir -> cd();

	simulationDataTree = new TTree("SimulationData", "Simulation Data is stored");
		simulationDataTree -> Branch("eventID", &eventID, "eventID/I");
		simulationDataTree -> Branch("trackID", &trackID, "trackID/I");
		simulationDataTree -> Branch("parentID", &parentID, "parentID/I");
		simulationDataTree -> Branch("pID", &pID, "pID/I");
		simulationDataTree -> Branch("energyDeposit", &energyDeposit, "energyDeposit/D");
		simulationDataTree -> Branch("hitTime", &hitTime, "hitTime/D");
		simulationDataTree -> Branch("isTPC", &isTPC, "isTPC/I");
		simulationDataTree -> Branch("vX", &vX, "vX/I");
		simulationDataTree -> Branch("vY", &vY, "vY/I");
		simulationDataTree -> Branch("vZ", &vZ, "vZ/I");
		simulationDataTree -> Branch("isDC", &isDC, "isDC/I");
		simulationDataTree -> Branch("x", &x, "x/D");
		simulationDataTree -> Branch("y", &y, "y/D");
		simulationDataTree -> Branch("z", &z, "z/D");
		simulationDataTree -> Branch("postx", &postx, "postx/D");
		simulationDataTree -> Branch("posty", &posty, "posty/D");
		simulationDataTree -> Branch("postz", &postz, "postz/D");
		simulationDataTree -> Branch("isToF", &isToF, "isToF/I");
		simulationDataTree -> Branch("copyNum", &copyNum, "copyNum/I");
		simulationDataTree -> Branch("detNum", &detNum, "detNum/I");
		simulationDataTree -> Branch("isLAND", &isLAND, "isLAND/I");
		simulationDataTree -> Branch("layerNum", &layerNum, "layerNum/I");
		simulationDataTree -> Branch("barNum", &barNum, "barNum/I");
		simulationDataTree -> Branch("isSiCsI", &isSiCsI, "isSiCsI/I");
		
}

LAMPSAnaRoot::~LAMPSAnaRoot()
{
	std::cout << "ROOT file is created!" << std::endl;

	rootFile -> Write();
//	rootFile -> Close();
//	delete rootFile;
}

void LAMPSAnaRoot::BeginOfEvent(Int_t eventNum)
{
	eventID = eventNum;
}

void LAMPSAnaRoot::FillPrimaryVertex(Int_t r_pNum, Int_t r_pID, Double_t r_energyInit, Double_t r_mass, Double_t r_pX, Double_t r_pY, Double_t r_pZ)
{
	trackID = r_pNum;
	pID = r_pID;
	energyInit = r_energyInit;
	mass = r_mass;
	pX = r_pX;
	pY = r_pY;
	pZ = r_pZ;

	generatorDataTree -> Fill();
}

// void LAMPSAnaRoot::FillTPC(Int_t r_pNum, Int_t r_parentID, Int_t r_pID, Int_t r_vX, Int_t r_vY, Int_t r_vZ, Double_t r_energyDeposit, Double_t r_hitTime)
void LAMPSAnaRoot::FillTPC(Int_t r_pNum, Int_t r_parentID, Int_t r_pID, Double_t preX, Double_t preY, Double_t preZ, Double_t postX, Double_t postY, Double_t postZ, Double_t r_energyDeposit, Double_t r_hitTime)
{
	if (r_energyDeposit == 0) return;

	trackID = r_pNum;
	parentID = r_parentID;
	pID = r_pID;
	energyDeposit = r_energyDeposit;
	hitTime = r_hitTime;
	isTPC = 1;
//	vX = r_vX;
//	vY = r_vY;
//	vZ = r_vZ;
	isDC = 0;
	detID = 0;
	x = preX;
	y = preY;
	z = preZ;
	postx = postX;
	posty = postY;
	postz = postZ;
	isToF = 0;
	detNum = 0;
	isLAND = 0;
	layerNum = 0;
	barNum = 0;
	isSiCsI = 0;

//	std::cout <<"isTPC = "<< isTPC <<"    , energy deposit = "<< energyDeposit << std::endl;

	simulationDataTree -> Fill();
}

void LAMPSAnaRoot::FillDC(Int_t r_pNum, G4String r_name, Int_t r_detID, Int_t r_parentID, Int_t r_pID, Double_t r_x, Double_t r_y, Double_t r_z, Double_t r_energyDeposit, Double_t r_hitTime)
{
	// Note: r_name is not used
	if (r_energyDeposit == 0) return;

	trackID = r_pNum;
	parentID = r_parentID;
	pID = r_pID;
	energyDeposit = r_energyDeposit;
	hitTime = r_hitTime;
	isTPC = 0;
	vX = 0;
	vY = 0;
	vZ = 0;
	isDC = 1;
	detID = r_detID;
	x = r_x;
	y = r_y;
	z = r_z;
	postx = 0;
	posty = 0;
	postz = 0;
	isToF = 0;
	detNum = 0;
	isLAND = 0;
	layerNum = 0;
	barNum = 0;
	isSiCsI = 0;

	simulationDataTree -> Fill();
}

void LAMPSAnaRoot::FillToF(Int_t r_pNum, Int_t r_detID, Int_t r_parentID, Int_t r_pID, Int_t r_detNum, Double_t r_energyDeposit, Double_t r_hitTime)
{
	if (r_energyDeposit == 0) return;

	trackID = r_pNum;
	parentID = r_parentID;
	pID = r_pID;
	energyDeposit = r_energyDeposit;
	hitTime = r_hitTime;
	isTPC = 0;
	vX = 0;
	vY = 0;
	vZ = 0;
	isDC = 0;
	detID = 0;
	x = r_detID;
	y = 0;
	z = 0;
	postx = 0;
	posty = 0;
	postz = 0;
	isToF = 1;
	detNum = r_detNum;
	isLAND = 0;
	layerNum = 0;
	barNum = 0;
	isSiCsI = 0;

	simulationDataTree -> Fill();
}

void LAMPSAnaRoot::FillLAND(Int_t r_pNum, Int_t r_parentID, Int_t r_pID, Int_t r_detNum, Double_t r_energyDeposit, Double_t r_hitTime)
{
	if (r_energyDeposit == 0) return;

	Int_t r_detID, r_layerNum, r_barNum;

	r_detID = (r_detNum - r_detNum%1000)/1000;
	r_layerNum = (r_detNum%1000 - r_detNum%100)/100;
	r_barNum = r_detNum%100;

	trackID = r_pNum;
	parentID = r_parentID;
	pID = r_pID;
	energyDeposit = r_energyDeposit;
	hitTime = r_hitTime;
	isTPC = 0;
	vX = 0;
	vY = 0;
	vZ = 0;
	isDC = 0;
	detID = r_detID;
	x = 0;
	y = 0;
	z = 0;
	postx = 0;
	posty = 0;
	postz = 0;
	isToF = 0;
	detNum = 0;
	isLAND = 1;
	layerNum = r_layerNum;
	barNum = r_barNum;
	isSiCsI = 0;

	simulationDataTree -> Fill();
}

void LAMPSAnaRoot::FillSiCsI(Int_t r_pNum, Int_t r_parentID, Int_t r_pID, Double_t r_x, Double_t r_y, Double_t r_z, Double_t r_energyDeposit, Double_t r_hitTime, Int_t r_copyNum, Int_t r_detNum) //KYO
{
	if (r_energyDeposit == 0) return;

	trackID = r_pNum;
	parentID = r_parentID;
	pID = r_pID;
	energyDeposit = r_energyDeposit;
	hitTime = r_hitTime;
	isTPC = 0;
	vX = 0;
	vY = 0;
	vZ = 0;
	isDC = 0;
	detID = 0;
	x = r_x;
	y = r_y;
	z = r_z;
	postx = 0;
	posty = 0;
	postz = 0;
	isToF = 0;
	copyNum = r_copyNum;
	detNum = r_detNum;
	isLAND = 0;
	layerNum = 0;
	barNum = 0;
	isSiCsI = 1; 

	simulationDataTree -> Fill();

//	std::cout <<"isSiCsI = "<< isSiCsI << "    , energy deposit = "<< energyDeposit<<std::endl;

}

