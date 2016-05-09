#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

void make_root_dE_E_SiCsI_IQMD_04()
{
	TFile *openFile = new TFile("rawData_IQMD_04.root", "READ");

	Int_t eventID, trackID, pID, parentID, sEventID, sTrackID, isSiCsI, detNum, copyNum;
	Double_t hitTime, energyInit, energyDeposit;

	TTree *GeneratorTree04 = (TTree *) openFile -> Get("GeneratorData");

	TTree *SimulationTree04 = (TTree *) openFile -> Get("SimulationData"); //meaningless?
		SimulationTree04 -> SetBranchAddress("eventID", &sEventID);
		SimulationTree04 -> SetBranchAddress("trackID", &sTrackID);
		SimulationTree04 -> SetBranchAddress("parentID", &parentID);
		SimulationTree04 -> SetBranchAddress("isSiCsI", &isSiCsI);
		SimulationTree04 -> SetBranchAddress("hitTime", &hitTime);
		SimulationTree04 -> SetBranchAddress("energyDeposit", &energyDeposit);
		SimulationTree04 -> SetBranchAddress("detNum", &detNum);
		SimulationTree04 -> SetBranchAddress("copyNum", &copyNum);


	TFile *writeFile = new TFile("dE_E_SiCsI_IQMD_04.root", "RECREATE");

	Int_t isSecondary;
	//Double_t pT, rapidity;

	const Int_t numEvents = 1000;
	const Int_t numSplits = 5;

	TTree *tempTree[numSplits];
	for (Int_t i = 0; i < numSplits; i++) {
		tempTree[i] = SimulationTree04 -> CopyTree(Form("eventID>=%d&&eventID<%d", 3000+i*numEvents/numSplits, 3000+(i+1)*numEvents/numSplits));
		cout << i << "th split ok!" << endl;
	}

	TTree *dE_E = new TTree("dE_E", "dE of Si vs. E of CsI");
		dE_E -> Branch("pID", &pID, "pID/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I"); //KYO
		dE_E -> Branch("eventID", &eventID, "eventID/I");
		dE_E -> Branch("energyInit", &energyInit, "energyInit/D");
		dE_E -> Branch("copyNum", &copyNum, "copyNum/I");

	for (Int_t i = 3000; i < 3000+numEvents; i++) {
		TTree *tempTree1 = GeneratorTree04 -> CopyTree(Form("eventID==%d", i));
			tempTree1 -> SetBranchAddress("eventID", &eventID);
			tempTree1 -> SetBranchAddress("trackID", &trackID);
			tempTree1 -> SetBranchAddress("pID", &pID);
			tempTree1 -> SetBranchAddress("energyInit", &energyInit);

		TTree *tempTree2 = SimulationTree04 -> CopyTree(Form("eventID==%d&&isSiCsI==1", i));

		Int_t temp1Entries = tempTree1 -> GetEntries(); //num of track per event 
		//cout << "temp1Entries : " << temp1Entries << endl;

		for (Int_t j = 0; j < temp1Entries; j++) {
			tempTree1 -> GetEntry(j);
			//cout << "track num j = " << j << endl;

			TTree *tempTree3 = tempTree2 -> CopyTree(Form("trackID==%d", j));

			Int_t temp3Entries = tempTree3 -> GetEntries(); //num of hit per track
			//cout << "temp3Entries : " << temp3Entries << endl;

			if (temp3Entries == 0) {
				delete tempTree3;
				continue;
			} else if ((pID==211||pID==-211)&&hitTime>5.0&&parentID==0&&isSiCsI==1){ // hitTime cut (temporary... dont need isSiCsi==1??)
				delete tempTree3;
				continue;
			} else {
			
				dE_E -> Fill();
				delete tempTree3;
			}
		}

		cout << "eventID: " << eventID << " is Done!!!!" << endl;

		delete tempTree2;
		delete tempTree1;
	}
	openFile -> Close();
	delete openFile;

	for (Int_t i = 0; i < numSplits; i++)
		delete tempTree[i];

	writeFile -> Write();
	writeFile -> Close();
	delete writeFile;

	return;
}
