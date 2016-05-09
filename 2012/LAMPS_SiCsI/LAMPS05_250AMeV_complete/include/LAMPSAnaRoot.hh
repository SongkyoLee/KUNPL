//=================
// LAMPSAnaRoot.hh
//=================

#ifndef LAMPSANAROOT_H
#define LAMPSANAROOT_H 1

#include "G4String.hh"

#include <TROOT.h>
#include <TSystem.h>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

class LAMPSAnaRoot
{
	private:
	/*
	Int_t eventNum;
	Int_T pNum;
	Int_t pID;
	Int_t vX, vY, vZ;
	Int_t detID, detNum;
	Double_t energyInit;
	Double_t pX, pY, pZ;
	Double_t mass;
	Double_t energyDeposit;
	Double_t hitTime;
	*/

	TFile *rootFile;
	TDirectory *rootDir;
	TTree *generatorDataTree;
	TTree *simulationDataTree;

	Int_t pID;
	Double_t energyInit, mass, pX, pY, pZ;

	Int_t eventID, trackID, parentID;
	Double_t energyDeposit;
	Double_t hitTime;
	Int_t isTPC;
	Int_t vX, vY, vZ;
	Int_t isDC;
	Int_t detID;
	Double_t x, y, z;
	Double_t postx, posty, postz;
	Int_t isToF;
	Int_t detNum;
	Int_t isLAND;
	Int_t layerNum, barNum;
	Int_t isSiCsI; // KYO

	public:
	LAMPSAnaRoot();
	~LAMPSAnaRoot();

	void BeginOfEvent(Int_t eventNum);
	void FillPrimaryVertex(Int_t pNum, Int_t pID, Double_t energyInit, Double_t mass, Double_t pX, Double_t pY, Double_t pZ);
//	void FillTPC(Int_t pNum, Int_t parentID, Int_t pID, Int_t vX, Int_t vY, Int_t vZ, Double_t energyDeposit, Double_t hitTime);
	void FillTPC(Int_t pNum, Int_t parentID, Int_t pID, Double_t preX, Double_t preY, Double_t preZ, Double_t postX, Double_t postY, Double_t postZ, Double_t energyDeposit, Double_t hitTime);
	void FillDC(Int_t pNum, G4String name, Int_t detID, Int_t parentID, Int_t pID, Double_t x, Double_t y, Double_t z, Double_t energyDeposit, Double_t hitTime);
	void FillToF(Int_t pNum, Int_t detID, Int_t parentID, Int_t pID, Int_t detNum, Double_t energyDeposit, Double_t hitTime);
	void FillLAND(Int_t pNum, Int_t parentID, Int_t pID, Int_t detNum, Double_t energyDeposit, Double_t hitTime);
	void FillSiCsI(Int_t pNum, Int_t parentID, Int_t pID, Double_t preX, Double_t preY, Double_t preZ, Double_t postX, Double_t postY, Double_t postZ, Double_t energyDeposit, Double_t hitTime, Int_t detNum); //KYO
};

#endif
