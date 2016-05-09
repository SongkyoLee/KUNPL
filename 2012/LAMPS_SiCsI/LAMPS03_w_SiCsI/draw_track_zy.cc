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

void draw_track_zy()
{
	TFile* file = new TFile("rawData.root","READ");
	TTree* tree = (TTree*)file -> Get("SimulationData");

	Int_t eventID, trackID, pID, isTPC, isSiCsI;
	Double_t energyDeposit, hitTime, x, y, z;

	tree -> SetBranchAddress("eventID", &eventID);
	tree -> SetBranchAddress("trackID", &trackID);
	tree -> SetBranchAddress("pID", &pID);
	tree -> SetBranchAddress("energyDeposit", &energyDeposit);
	tree -> SetBranchAddress("hitTime", &hitTime);
	tree -> SetBranchAddress("x", &x);
	tree -> SetBranchAddress("y", &y);
	tree -> SetBranchAddress("z", &z);
	tree -> SetBranchAddress("isTPC", &isTPC);
	tree -> SetBranchAddress("isSiCsI", &isSiCsI);

	TCanvas* c1 = new TCanvas ("c1","track",800,800);
	TH2D* h1 = new TH2D("h1", "track", 10000, -100, 900, 10000, -500, 500);

	Int_t entries = tree -> GetEntries();
	for (Int_t i =0; i<entries; i++)
	{
		tree->GetEntry(i);
		if(pID==211) //temporary
		{
		h1 -> Fill(z,y);
		}
	}

	c1->cd();
	h1->GetXaxis()->SetTitle("z (mm)");
	h1->GetYaxis()->SetTitle("y (mm)");
	h1->GetYaxis()->SetTitleOffset(1.5);
	h1->SetStats(0);
	h1->SetMarkerStyle(20);
	h1->SetMarkerSize(0.3);
	h1->Draw();
//	c1->SaveAs("track_zy.png");
}

