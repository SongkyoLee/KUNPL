#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TF1.h>
#include <TMath.h>
#include <TPaletteAxis.h>
#include <TPaveStats.h>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <sstream>
#include <string>

using namespace std;

void make_root_nonID_SiCsI_03(Int_t selectData, Int_t selectParticle, Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX, Int_t selectYBins, Double_t selectMinY, Double_t selectMaxY)
{
	// data specification
	const Int_t numParticles = 6;
	const Int_t numData = 2;

	string dataName[numData] = {"250MeV_Soft", "250MeV_Hard"}; //KYO
	Int_t particleName[numParticles] = {2212, 1000010020, 1000010030, 1000020040, 211, -211};
// proton, deuteron, tau, alpha, +pion, -pion
	
	// processing the arguments
	if (selectData >= numData || selectData < 0)
	{
		cout << "You don't know the data, huh?" << endl;
		return;
	}

	if (selectParticle >= numParticles || selectParticle < 0)
	{
		cout << "Do you know what particle you chose?" << endl;
		return;
	}

	// read root file
	TChain dE_E_Tree("dE_E");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_01.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_02.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_03.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_04.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_05.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_06.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_07.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_08.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_09.root");
	dE_E_Tree.Add("dE_E_SiCsI_secondary_10.root");

	TChain GenTree("GeneratorData");
	GenTree.Add("rawData01.root");
	GenTree.Add("rawData02.root");
	GenTree.Add("rawData03.root");
	GenTree.Add("rawData04.root");
	GenTree.Add("rawData05.root");
	GenTree.Add("rawData06.root");
	GenTree.Add("rawData07.root");
	GenTree.Add("rawData08.root");
	GenTree.Add("rawData09.root");
	GenTree.Add("rawData10.root");

	Int_t eventID, trackID, tempEventID, tempTrackID;
	Double_t edep1, edep2, edep3, edep4, energyInit;

	TTree* tempTree0 = GenTree.CopyTree(Form("pID==%d",particleName[selectParticle]));
	tempTree0 -> SetBranchAddress("eventID", &eventID);
	tempTree0 -> SetBranchAddress("trackID", &trackID);
	tempTree0 -> SetBranchAddress("energyInit", &energyInit);
	
	TTree* tempTree1 = dE_E_Tree.CopyTree(Form("pID==%d",particleName[selectParticle]));
	tempTree1 -> SetBranchAddress("eventID", &tempEventID);
	tempTree1 -> SetBranchAddress("trackID", &tempTrackID);
	tempTree1 -> SetBranchAddress("edep1", &edep1);
	tempTree1 -> SetBranchAddress("edep2", &edep2);
	tempTree1 -> SetBranchAddress("edep3", &edep3);
	tempTree1 -> SetBranchAddress("edep4", &edep4);

	Double_t tempEntries1 = tempTree1 -> GetEntries();
	cout << "total entries = "  << tempEntries1 << endl;

	TTree * tempTree2 = new TTree("tempTree2", "");
	tempTree2 -> Branch("tempEventID", &tempEventID, "tempEventID/I");
	tempTree2 -> Branch("tempTrackID", &tempTrackID, "tempTrackID/I");
	tempTree2 -> Branch("edep1", &edep1, "edep1/D");
	tempTree2 -> Branch("edep2", &edep2, "edep2/D");
	tempTree2 -> Branch("edep3", &edep3, "edep3/D");
	tempTree2 -> Branch("edep4", &edep4, "edep4/D");

	for (Int_t i=0; i<tempEntries1; i++)
	{
	tempTree1 -> GetEntry(i);
	if(edep1!=0&&edep2!=0&&edep1<1.881&&edep2<170&&((edep2<55.0&&edep1<0.0011*(edep2-55)*(edep2-55)+1.1935)||(edep2>=55.0&&edep1<0.00006*(edep2-170)*(edep2-170)+0.4)))
	{tempTree2->Fill();}
	else if(edep3!=0&&edep4!=0&&edep3<1.881&&edep4<170&&((edep4<55.0&&edep3<0.0011*(edep4-55)*(edep4-55)+1.1935)||(edep4>=55.0&&edep3<0.00006*(edep4-170)*(edep4-170)+0.4)))
	{tempTree2->Fill();}
	}

	delete tempTree1;

	Double_t tempEntries2 = tempTree2 -> GetEntries();
	cout << "cut entries = " << tempEntries2 << endl;

	Double_t p_mis = tempEntries2/tempEntries1;
	cout << "P_mis = " << p_mis*100 <<" (%)" << endl;

	Double_t tempEntries0 = tempTree0 -> GetEntries();
	cout << "generator Entries = " << tempEntries0 << endl;

	//make root file and tempTree3
	TFile *writeFile = new TFile("nonID_SiCsI_03.root","RECREATE");

	TTree * tempTree3 = new TTree("tempTree3", "");
	tempTree3 -> Branch("eventID", &eventID, "eventID/I");
	tempTree3 -> Branch("trackID", &trackID, "trackID/I");
	tempTree3 -> Branch("edep1", &edep1, "edep1/D");
	tempTree3 -> Branch("edep2", &edep2, "edep2/D");
	tempTree3 -> Branch("edep3", &edep3, "edep3/D");
	tempTree3 -> Branch("edep4", &edep4, "edep4/D");
	tempTree3 -> Branch("energyInit", &energyInit, "energyInit/D");

	for (Int_t j=0 ; j<tempEntries2 ; j++)
	{
	tempTree2 -> GetEntry(j);
		for (Int_t k=0; k< tempEntries0; k++)
		{
		tempTree0 -> GetEntry(k);
		if(tempEventID==eventID&&tempTrackID==trackID)
		tempTree3 -> Fill(); 
		}
	} 

 	delete tempTree2;

	writeFile -> Write();
	writeFile -> Close();
	delete writeFile;
	//delete tempTree3;

	return;
}

