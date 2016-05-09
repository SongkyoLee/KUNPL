#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TPaletteAxis.h>
#include <TPaveStats.h>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <sstream>
#include <string>

using namespace std;

void draw_dE_E_SiCsI_all(Int_t selectData, Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX, Int_t selectYBins, Double_t selectMinY, Double_t selectMaxY)
{
	// data specification
	const Int_t numData = 2;
	string dataName[numData] = {"250MeV_Soft", "250MeV_Hard"}; //KYO

	if (selectData >= numData || selectData < 0)
	{
		cout << "You don't know the data, huh?" << endl;
		return;
	}

	// start drawing
	gStyle -> SetPalette(1);
	gStyle -> SetOptTitle(0);
	gStyle -> SetLabelSize(0.035, "X");
	gStyle -> SetLabelSize(0.035, "Y");
	gStyle -> SetTitleXOffset(0.8);
	gStyle -> SetTitleYOffset(0.6);
	gStyle -> SetTitleXSize(0.07);
	gStyle -> SetTitleYSize(0.07);
	gStyle -> SetPadLeftMargin(0.15);
	gStyle -> SetPadTopMargin(0.05);
	gStyle -> SetPadBottomMargin(0.15);

	// read root file (TChain instead of Project)
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

	Double_t edep1, edep2, edep3, edep4;
	dE_E_Tree.SetBranchAddress("edep1", &edep1);
	dE_E_Tree.SetBranchAddress("edep2", &edep2);
	dE_E_Tree.SetBranchAddress("edep3", &edep3);
	dE_E_Tree.SetBranchAddress("edep4", &edep4);
		
	//draw histogram
	TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);
	cvs -> cd();

	TH2D *hist = new TH2D("hist", "dE vs E", selectXBins, selectMinX, selectMaxX, selectYBins, selectMinY, selectMaxY);

	Int_t entries = dE_E -> GetEntries();

	for (Int_t i=0; i<entries; i++)
	{
	dE_E -> GetEntry(i);
	if(edep1!=0&&edep2!=0)
	{hist->Fill(edep2,edep1);}
	else if(edep3!=0&&edep4!=0)
	{hist->Fill(edep4,edep3);}
	}
		hist -> GetXaxis() -> SetTitle("E (MeV)");
		hist -> GetXaxis() -> SetTitleFont(132);
		hist -> GetXaxis() -> SetTitleSize(0.05);
		hist -> GetXaxis() -> CenterTitle();
		hist -> GetYaxis() -> SetTitle("dE (MeV)");
		hist -> GetYaxis() -> SetTitleFont(132);
		hist -> GetYaxis() -> SetTitleSize(0.05);
		hist -> GetYaxis() -> CenterTitle();
		hist -> SetStats(0); //stats
		hist -> Draw("colz");

	cvs -> Update();

	TPaletteAxis *palette = (TPaletteAxis *) hist -> FindObject("palette");
		palette -> SetLabelSize(0.022);

	//TPaveStats *stats = (TPaveStats *) hist -> FindObject("stats");
	//	stats -> SetX1NDC(0.68);
	//	stats -> SetX2NDC(0.87);
	//	stats -> SetY1NDC(0.74);
	//	stats -> SetY2NDC(0.93);

	cvs -> Update();

	cvs -> SaveAs(Form("dE_E_SiCsI_%s_all.png", dataName[selectData]));
}

