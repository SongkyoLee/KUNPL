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

void draw_dE_E_SiCsI_all_3(Int_t selectData, Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX, Int_t selectYBins, Double_t selectMinY, Double_t selectMaxY)
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
	dE_E_Tree.Add("dE_E_SiCsI_proton.root");
	dE_E_Tree.Add("dE_E_SiCsI_deuteron.root");
	dE_E_Tree.Add("dE_E_SiCsI_triton.root");
//	dE_E_Tree.Add("dE_E_SiCsI_alpha.root");

	Double_t deltaE, largeE;
	Double_t edep1, edep2, edep3, edep4, edep5, edep6, edep7, edep8;

	dE_E_Tree.SetBranchAddress("edep1", &edep1);
	dE_E_Tree.SetBranchAddress("edep2", &edep2);
	dE_E_Tree.SetBranchAddress("edep3", &edep3);
	dE_E_Tree.SetBranchAddress("edep4", &edep4);
	dE_E_Tree.SetBranchAddress("edep5", &edep5);
	dE_E_Tree.SetBranchAddress("edep6", &edep6);
	dE_E_Tree.SetBranchAddress("edep7", &edep7);
	dE_E_Tree.SetBranchAddress("edep8", &edep8);
		
	//draw histogram
	TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);
	cvs -> cd();

	TH2D *hist = new TH2D("hist", "dE vs E", selectXBins, selectMinX, selectMaxX, selectYBins, selectMinY, selectMaxY);

	Int_t entries = dE_E -> GetEntries();

	for (Int_t i=0; i<entries; i++)
	{
		deltaE=0;
		largeE=0;

		dE_E -> GetEntry(i);
		if(edep1!=0)
		{	deltaE=edep1+edep2+edep3;
			largeE=edep4;
			//hist->Fill(edep2+edep3+edep4,edep1);
		}
		else if(edep5!=0)
		{
			deltaE=edep5+edep6+edep7;
			largeE=edep8;
		//	hist->Fill(edep6+edep7+edep8,edep5);
		}
		hist->Fill(largeE, deltaE);
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

	cvs -> SaveAs(Form("dE_E_SiCsI_%s_all_3.png", dataName[selectData]));
}

