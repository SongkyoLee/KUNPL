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

#define eventNum 10000

void draw_hitTime()
{
	TFile* file = new TFile("rawData.root","READ");
	TTree* tree = (TTree*)file -> Get("SimulationData");

	Int_t eventID, trackID, pID, parentID, isTPC, isSiCsI;
	Double_t energyDeposit, hitTime, x, y, z;

	tree -> SetBranchAddress("eventID", &eventID);
	tree -> SetBranchAddress("trackID", &trackID);
	tree -> SetBranchAddress("pID", &pID);
	tree -> SetBranchAddress("parentID", &parentID);
	tree -> SetBranchAddress("energyDeposit", &energyDeposit);
	tree -> SetBranchAddress("hitTime", &hitTime);
	tree -> SetBranchAddress("x", &x);
	tree -> SetBranchAddress("y", &y);
	tree -> SetBranchAddress("z", &z);
	tree -> SetBranchAddress("isTPC", &isTPC);
	tree -> SetBranchAddress("isSiCsI", &isSiCsI);

	TCanvas* c1 = new TCanvas ("c1","track",800,800);
	TH1D* h1 = new TH1D("h1", "hitTime", 200, 0, 20);


	for(Int_t i = 0; i < eventNum; i++)
	{

		Int_t entries = tree -> GetEntries(Form("eventID==%d",i));
		TTree* t_per_event = tree -> CopyTree(Form("eventID==%d",i));

		for (Int_t j =0; j<entries; j++)
		{
			t_per_event -> GetEntry(j);

			if(parentID==0&&isSiCsI==1&&pID==211)
			{
				h1 -> Fill(hitTime);
			}
		}
	std::cout << i << "th event is done! " << std::endl;
	delete t_per_event;
	}

	c1->cd();
//	c1
	h1->GetXaxis()->SetTitle("hitTime (ns)");
	h1->GetYaxis()->SetTitle("counts");
	h1->GetYaxis()->SetTitleOffset(1.5);
//	h1->SetStats(0);
//	h1->SetMarkerStyle(20);
//	h1->SetMarkerSize(0.3);
	h1->Draw();
	c1->SaveAs("211_hitTime_00.png");

}

