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

#define lineNum 4315

void draw_hitTime_03()
{
	std::ifstream inFile("hitTime.out", std::ios::in);

	Int_t eventID, isTPC, isSiCsI;
	Double_t hitTime;

	TCanvas* c1 = new TCanvas ("c1","track",800,800);
	TH1D* h1 = new TH1D("h1", "hit time", 160, 0, 16);

	for(Int_t i=0; i<lineNum; i++)
	{
		inFile >> eventID >> hitTime >> isTPC >> isSiCsI ;
		h1 -> Fill(hitTime);
	}

	c1->cd();
	h1->GetXaxis()->SetTitle("hit time (ns)");
	h1->GetYaxis()->SetTitle("counts");
	h1->GetYaxis()->SetTitleOffset(1.5);
//	h1->SetStats(0);
//	h1->SetMarkerStyle(20);
//	h1->SetMarkerSize(0.3);
	h1->Draw();
	c1->SaveAs("211_hitTime.png");

}

