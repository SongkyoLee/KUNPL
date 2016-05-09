#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

//for proton

void calculate_Eloss()
{
	TFile *openFile = new TFile("rawData.root", "READ");

	Double_t energyDeposit;
	Double_t energyLoss =0;

	TTree *GeneratorData = (TTree *) openFile -> Get("GeneratorData");
	TTree *SimulationData = (TTree *) openFile -> Get("SimulationData"); //meaningless?
	SimulationData -> SetBranchAddress("energyDeposit", &energyDeposit);

	Int_t entries = SimulationData -> GetEntries(); //num of track per event 
	cout << "Entries : " << entries << endl;

	for (Int_t i=0; i<entries; i++)
	{
		SimulationData -> GetEntry(i);
		cout << "track num i = " << i << endl;

		energyLoss += energyDeposit;
		cout << "energyLoss = " << energyLoss << endl;

	}

	openFile -> Close();
	delete openFile;

	return;
}
