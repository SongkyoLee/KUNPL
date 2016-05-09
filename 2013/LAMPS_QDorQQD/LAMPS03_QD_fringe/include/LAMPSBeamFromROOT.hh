#ifndef LAMPSBEAMFROMROOT_h
#define LAMPSBEAMFROMROOT_h 1
#include <TROOT.h>
#include <TSystem.h>
#include <TTree.h>

#include "globals.hh"

class LAMPSPrimaryGeneratorAction;

class LAMPSBeamFromROOT
{
	public:
		LAMPSBeamFromROOT(LAMPSPrimaryGeneratorAction*, G4int, G4int, G4int);
		~LAMPSBeamFromROOT();

		void GetBeam(G4int&);
		void SelectEnergyAndModel(G4int&, G4int&);
		void SelectEvent(Int_t&);

	private:
		LAMPSPrimaryGeneratorAction* LAMPSPGA;

		TFile* openROOTFile;
		TDirectory* selectedEnergyAndModelDir;
		TTree* eventTree;
		
		Int_t energy;
		Int_t model;
		Int_t eventNum;

		Int_t numTracks;
		Int_t particleID;
		Double_t pX;
		Double_t pY;
		Double_t pZ;
};
#endif
