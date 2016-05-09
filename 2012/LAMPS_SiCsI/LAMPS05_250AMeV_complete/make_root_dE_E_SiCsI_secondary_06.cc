#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

void make_root_dE_E_SiCsI_secondary_06()
{
	TFile *openFile = new TFile("rawData06.root", "READ");

	Int_t eventID, trackID, pID, parentID, sEventID, sTrackID, isSiCsI, detNum;
	Double_t hitTime, energyDeposit, edep1, edep2, edep3, edep4;

	TTree *GeneratorTree06 = (TTree *) openFile -> Get("GeneratorData");

	TTree *SimulationTree06 = (TTree *) openFile -> Get("SimulationData"); //meaningless?
		SimulationTree06 -> SetBranchAddress("eventID", &sEventID);
		SimulationTree06 -> SetBranchAddress("trackID", &sTrackID);
		SimulationTree06 -> SetBranchAddress("parentID", &parentID);
		SimulationTree06 -> SetBranchAddress("isSiCsI", &isSiCsI);
		SimulationTree06 -> SetBranchAddress("hitTime", &hitTime);
		SimulationTree06 -> SetBranchAddress("energyDeposit", &energyDeposit);
		SimulationTree06 -> SetBranchAddress("detNum", &detNum);


	TFile *writeFile = new TFile("dE_E_SiCsI_secondary_06.root", "RECREATE");

	Int_t isSecondary;
	//Double_t pT, rapidity;

	const Int_t numEvents = 1000;
	const Int_t numSplits = 10;

	TTree *tempTree[numSplits];
	for (Int_t i = 0; i < numSplits; i++) {
		tempTree[i] = SimulationTree06 -> CopyTree(Form("eventID>=%d&&eventID<%d", 5000+i*(numEvents)/numSplits, 5000+(i+1)*numEvents/numSplits));
		cout << i << "th split ok!" << endl;
	}

	TTree *dE_E = new TTree("dE_E", "dE of Si vs. E of CsI");
		dE_E -> Branch("pID", &pID, "pID/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I"); //KYO
		dE_E -> Branch("eventID", &eventID, "eventID/I");
		dE_E -> Branch("edep1", &edep1, "edep1/D");
		dE_E -> Branch("edep2", &edep2, "edep2/D");
		dE_E -> Branch("edep3", &edep3, "edep3/D");
		dE_E -> Branch("edep4", &edep4, "edep4/D");

	for (Int_t i = 5000; i < 5000+numEvents; i++) {
		TTree *tempTree1 = GeneratorTree06 -> CopyTree(Form("eventID==%d", i));
			tempTree1 -> SetBranchAddress("eventID", &eventID);
			tempTree1 -> SetBranchAddress("trackID", &trackID);
			tempTree1 -> SetBranchAddress("pID", &pID);

		TTree *tempTree2 = SimulationTree06 -> CopyTree(Form("eventID==%d&&isSiCsI==1", i));

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
			
				// KYO : edep calculation //
				edep1 = 0;
				edep2 = 0;
				edep3 = 0;
				edep4 = 0;

				for (Int_t k=0; k<temp3Entries; k++) {
					tempTree3 -> GetEntry(k);
					//cout<< "hit num k = " << k
				 	if (detNum==1)
					 { edep1 += energyDeposit; }
				 	else if (detNum==2)
					 { edep2 += energyDeposit; }
				 	else if (detNum==3)
					 { edep3 += energyDeposit; }
				 	else if (detNum==4)
					 { edep4 += energyDeposit; }
				}

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
