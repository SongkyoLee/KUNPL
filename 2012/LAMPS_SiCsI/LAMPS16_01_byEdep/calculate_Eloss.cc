#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

//for proton

void calculate_Eloss(Int_t NE=0, Int_t KE)
{
	TFile *openFile = new TFile(Form("rawData_%dMeV.root",KE), "READ");

	Int_t eventID, trackID, isToF;
	Double_t energyDeposit;
	const int numEvents=NE;
	Double_t energyLoss[numEvents]={0.};

	TTree *GeneratorData = (TTree *) openFile -> Get("GeneratorData");
	TTree *SimulationData = (TTree *) openFile -> Get("SimulationData"); //meaningless?
		SimulationData -> SetBranchAddress("eventID", &eventID);
		SimulationData -> SetBranchAddress("isToF", &isToF);

	ofstream outFile(Form("energyLoss_%dMeV.dat", KE), std::ios::app);

	for (Int_t i=0; i<numEvents ; i ++)
	{
		TTree* tempTree = SimulationData -> CopyTree(Form("eventID==%d&&isToF!=1", i));
		tempTree -> SetBranchAddress("energyDeposit", &energyDeposit);

		Int_t tempEntries = tempTree -> GetEntries(); //num of track per event 
//		cout << i << "th Entries : " << tempEntries << endl;

		for (Int_t j=0; j<tempEntries; j++)
		{
			tempTree -> GetEntry(j);
//			cout << "track num j = " << j << endl;

			energyLoss[i] += energyDeposit;
//			cout << "energyLoss = " << energyLoss[i] << endl;

		}
//	cout << "---------------------------------------------------" << endl;
	cout << "total energy loss of event " << i <<" is "<< energyLoss[i] << endl;
//	cout << "---------------------------------------------------" << endl;

	outFile << setw(5) << i <<  setw(10) << energyLoss[i] << endl;

	}
	openFile -> Close();
	delete openFile;

	return;
}
