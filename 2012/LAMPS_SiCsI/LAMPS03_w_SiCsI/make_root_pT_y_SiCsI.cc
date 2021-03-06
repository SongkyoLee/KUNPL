#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>

void make_root_pT_y_SiCsI()
{
	TFile *openFile = new TFile("rawData.root", "READ");

	Int_t eventID, trackID, pID, sEventID, sTrackID, isSiCsI;
	Double_t mass, pX, pY, pZ, hitTime;

	TTree *GeneratorTree = (TTree *) openFile -> Get("GeneratorData");

	TTree *SimulationTree = (TTree *) openFile -> Get("SimulationData"); //meaningless?
		SimulationTree -> SetBranchAddress("eventID", &sEventID);
		SimulationTree -> SetBranchAddress("trackID", &sTrackID);
		SimulationTree -> SetBranchAddress("isSiCsI", &isSiCsI);
		SimulationTree -> SetBranchAddress("hitTime", &hitTime);

	TFile *writeFile = new TFile("pT_y_SiCsI.root", "RECREATE");

	Int_t isSecondary;
	Double_t pT, rapidity;

	const Int_t numEvents = 10000;
	const Int_t numSplits = 10; //KYO

	TTree *tempTree[numSplits];
	for (Int_t i = 0; i < numSplits; i++) {
		tempTree[i] = SimulationTree -> CopyTree(Form("eventID>=%d&&eventID<%d", i*numEvents/numSplits, (i+1)*numEvents/numSplits));
		cout << i << "th split ok!" << endl;
	}

	TTree *pT_y = new TTree("pT_y", "Transverse momentum vs. Rapidity");
		pT_y -> Branch("pT", &pT, "pT/D");
		pT_y -> Branch("mass", &mass, "mass/D");
		pT_y -> Branch("pID", &pID, "pID/I");
		pT_y -> Branch("rapidity", &rapidity, "rapidity/D");
		pT_y -> Branch("trackID", &trackID, "trackID/I"); //KYO
		pT_y -> Branch("eventID", &eventID, "eventID/I"); //KYO

	for (Int_t i = 0; i < numEvents; i++) {
		TTree *tempTree1 = GeneratorTree -> CopyTree(Form("eventID==%d", i));
			tempTree1 -> SetBranchAddress("eventID", &eventID);
			tempTree1 -> SetBranchAddress("trackID", &trackID);
			tempTree1 -> SetBranchAddress("pID", &pID);
			tempTree1 -> SetBranchAddress("mass", &mass);
			tempTree1 -> SetBranchAddress("pX", &pX);
			tempTree1 -> SetBranchAddress("pY", &pY);
			tempTree1 -> SetBranchAddress("pZ", &pZ);

		TTree *tempTree2 = tempTree[i/(numEvents/numSplits)] -> CopyTree(Form("eventID==%d&&isSiCsI==1&&parentID==0&&(pID==2212||pID==1000010020||pID==1000010030||pID==1000020040||((pID==211||pID==-211)&&hitTime<5.0))", i)); //KYO for hitTime cut

		Int_t temp1Entries = tempTree1 -> GetEntries();
		//cout << "temp1Entries : " << temp1Entries << endl;

		for (Int_t j = 0; j < temp1Entries; j++) {
			tempTree1 -> GetEntry(j);

			TTree *tempTree3 = tempTree2 -> CopyTree(Form("trackID==%d", j));

			Int_t temp3Entries = tempTree3 -> GetEntries();
			//cout << "temp3Entries : " << temp3Entries << endl;

			if (temp3Entries == 0) {
				delete tempTree3;
				continue;
			} else {
				pT = TMath::Sqrt(pX*pX+pY*pY);
				Double_t E = TMath::Sqrt( mass*mass + pX*pX + pY*pY + pZ*pZ );
				rapidity = 0.5 * TMath::Log( (E+pZ)/(E-pZ) );
				//cout << "   pT : " << pT
				//     << "   ,mass : "<<mass
				//     << "   ,pID : " <<pID
				//     << "   ,rapidity : " <<rapidity
				//     << "   ,trackID = " << trackID 
 				 //    << "   ,sTrackID = " << sTrackID << endl;	
				pT_y -> Fill();

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
