#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TF1.h"
#include "TH1.h"
#include "TStyle.h"
#include "TMath.h"
#include "TROOT.h"
#include "Riostream.h"
#include <fstream>
#include <iomanip>

//#define eventNum 10000

void draw_hitTime_02()
{
	TFile* file = new TFile("rawData.root","READ");
	TTree* tree = (TTree*)file -> Get("SimulationData");

	Int_t eventID, trackID, pID, parentID, isTPC, isSiCsI;
	Double_t energyDeposit, hitTime, x, y, z;

	tree -> SetBranchAddress("eventID", &eventID);
	tree -> SetBranchAddress("trackID", &trackID);
	tree -> SetBranchAddress("pID", &pID);
	tree -> SetBranchAddress ("parentID", &parentID);
	tree -> SetBranchAddress("energyDeposit", &energyDeposit);
	tree -> SetBranchAddress("hitTime", &hitTime);
	tree -> SetBranchAddress("x", &x);
	tree -> SetBranchAddress("y", &y);
	tree -> SetBranchAddress("z", &z);
	tree -> SetBranchAddress("isTPC", &isTPC);
	tree -> SetBranchAddress("isSiCsI", &isSiCsI);

//	TCanvas* c1 = new TCanvas ("c1","track",800,800);
//	TH1D* h1 = new TH1D("h1", "hitTime", 200, 0, 20);

	TTree* tempTree = tree -> CopyTree("eventID==37");
	Int_t entries = tempTree -> GetEntries();

		for (Int_t j =0; j<entries; j++)
		{
			tempTree -> GetEntry(j);

			if(parentID==0&&pID==211&&isSiCsI==1)
			{
				h1 -> Fill(hitTime);
				std::ofstream outFile("hitTime.out", std::ios::app);
				outFile << std::setw(10) << eventID
					<< std::setw(10) << hitTime
					<< std::setw(10) << isTPC
					<< std::setw(10) << isSiCsI << std::endl;
			}
		}
	//std::cout << i << "th event is done! " << std::endl;
	//delete t_per_event;

//	c1->cd();
//	c1
//	h1->GetXaxis()->SetTitle("hitTime (ns)");
//	h1->GetYaxis()->SetTitle("counts");
//	h1->GetYaxis()->SetTitleOffset(1.5);
//	h1->SetStats(0);
//	h1->SetMarkerStyle(20);
//	h1->SetMarkerSize(0.3);
//	h1->Draw();
//	h1->SaveAs("track.png");
//	c1->SaveAs("211_hitTime_02.png");

}

