#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

//for alpha

void make_root_dE_E_SiCsI_alpha()
{
	TFile *openFile = new TFile("rawData_alpha.root", "READ");

	Int_t eventID, trackID, pID, parentID, sEventID, sTrackID, isSiCsI, detNum;
	Double_t hitTime, energyInit, energyDeposit;
	Double_t edep1, edep2, edep3, edep4, edep5, edep6, edep7, edep8;

	TTree *GeneratorTree01 = (TTree *) openFile -> Get("GeneratorData");

	TTree *SimulationTree01 = (TTree *) openFile -> Get("SimulationData"); //meaningless?
		SimulationTree01 -> SetBranchAddress("eventID", &sEventID);
		SimulationTree01 -> SetBranchAddress("trackID", &sTrackID);
		SimulationTree01 -> SetBranchAddress("parentID", &parentID);
		SimulationTree01 -> SetBranchAddress("isSiCsI", &isSiCsI);
		SimulationTree01 -> SetBranchAddress("hitTime", &hitTime);
		SimulationTree01 -> SetBranchAddress("energyDeposit", &energyDeposit);
		SimulationTree01 -> SetBranchAddress("detNum", &detNum);


	TFile *writeFile = new TFile("dE_E_SiCsI_alpha.root", "RECREATE");

	Int_t isSecondary;
	//Double_t pT, rapidity;

	const Int_t numEvents = 10000;
	const Int_t numSplits = 10;

	TTree *tempTree[numSplits];
	for (Int_t i = 0; i < numSplits; i++) {
		tempTree[i] = SimulationTree01 -> CopyTree(Form("eventID>=%d&&eventID<%d", i*numEvents/numSplits, (i+1)*numEvents/numSplits));
		cout << i << "th split ok!" << endl;
	}

	TTree *dE_E = new TTree("dE_E", "dE of Si vs. E of CsI");
		dE_E -> Branch("pID", &pID, "pID/I");
		dE_E -> Branch("trackID", &trackID, "trackID/I");
		dE_E -> Branch("eventID", &eventID, "eventID/I");
		dE_E -> Branch("energyInit", &energyInit, "energyInit/D"); //KYO
		dE_E -> Branch("edep1", &edep1, "edep1/D");
		dE_E -> Branch("edep2", &edep2, "edep2/D");
		dE_E -> Branch("edep3", &edep3, "edep3/D");
		dE_E -> Branch("edep4", &edep4, "edep4/D");
		dE_E -> Branch("edep5", &edep5, "edep5/D");
		dE_E -> Branch("edep6", &edep6, "edep6/D");
		dE_E -> Branch("edep7", &edep7, "edep7/D");
		dE_E -> Branch("edep8", &edep8, "edep8/D");


	for (Int_t i = 0; i < numEvents; i++) {
		TTree *tempTree1 = GeneratorTree01 -> CopyTree(Form("eventID==%d", i));
			tempTree1 -> SetBranchAddress("eventID", &eventID);
			tempTree1 -> SetBranchAddress("trackID", &trackID);
			tempTree1 -> SetBranchAddress("pID", &pID);
			tempTree1 -> SetBranchAddress("energyInit", &energyInit);

		TTree *tempTree2 = SimulationTree01 -> CopyTree(Form("eventID==%d&&isSiCsI==1", i));

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
				edep5 = 0;
				edep6 = 0;
				edep7 = 0;
				edep8 = 0;

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
				 	else if (detNum==5)
					 { edep5 += energyDeposit; }
				 	else if (detNum==6)
					 { edep6 += energyDeposit; }
				 	else if (detNum==7)
					 { edep7 += energyDeposit; }
				 	else if (detNum==8)
					 { edep8 += energyDeposit; }
				}

				dE_E -> Fill();

				delete tempTree3;
			}
		}

//		cout << "eventID: " << eventID << " is Done!!!!" << endl;
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
