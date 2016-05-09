#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TPaletteAxis.h>
#include <TPaveStats.h>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <sstream>
#include <string>

using namespace std;

void draw_energyInit_IQMD(Int_t selectData, Int_t selectParticle, Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX)
{
	// data specification
  const Int_t numParticles = 6;
	const Int_t numData = 2;
	string dataName[numData] = {"250MeV_Soft", "250MeV_Hard"}; //KYO

  Int_t particleName[numParticles] = {2212, 1000010020, 1000010030, 1000020040, 211, -211};
	//proton, deuteron, tau, alpha, +pion, -pion

  //processing the arguments)
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

	// start drawing
	gStyle -> SetPalette(1);
	gStyle -> SetOptTitle(0);
	gStyle -> SetLabelSize(0.035, "X");
	gStyle -> SetLabelSize(0.035, "Y");
	gStyle -> SetTitleXOffset(0.8);
	gStyle -> SetTitleYOffset(0.9);
	gStyle -> SetTitleXSize(0.07);
	gStyle -> SetTitleYSize(0.07);
	gStyle -> SetPadLeftMargin(0.15);
	gStyle -> SetPadTopMargin(0.05);
	gStyle -> SetPadBottomMargin(0.15);

	// read root file (TChain instead of Project)
	TChain dE_E_Tree("dE_E");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_01.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_02.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_03.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_04.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_05.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_06.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_07.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_08.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_09.root");
	dE_E_Tree.Add("dE_E_SiCsI_IQMD_10.root");

  TTree* tempTree = dE_E_Tree.CopyTree(Form("pID==%d",particleName[selectParticle]));

	Double_t energyInit;
	tempTree -> SetBranchAddress("energyInit", &energyInit);
		
	//draw histogram
	TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);
	cvs -> cd();

	TH1D *hist = new TH1D("hist", "Initial Energy", selectXBins, selectMinX, selectMaxX);

	Int_t entries = tempTree -> GetEntries();

	for (Int_t i=0; i<entries; i++)
	{

   tempTree -> GetEntry(i);
	 hist->Fill(energyInit);
	}

		hist -> GetXaxis() -> SetTitle("Initial Energy (MeV)");
		hist -> GetXaxis() -> SetTitleFont(132);
		hist -> GetXaxis() -> SetTitleSize(0.05);
		hist -> GetXaxis() -> CenterTitle();
		hist -> GetYaxis() -> SetTitle("counts (MeV)");
		hist -> GetYaxis() -> SetTitleFont(132);
		hist -> GetYaxis() -> SetTitleSize(0.05);
		hist -> GetYaxis() -> CenterTitle();
//		hist -> SetStats(0); //stats
		hist -> Draw();

	cvs -> Update();

//	TPaletteAxis *palette = (TPaletteAxis *) hist -> FindObject("palette");
//		palette -> SetLabelSize(0.022);

	//TPaveStats *stats = (TPaveStats *) hist -> FindObject("stats");
	//	stats -> SetX1NDC(0.68);
	//	stats -> SetX2NDC(0.87);
	//	stats -> SetY1NDC(0.74);
	//	stats -> SetY2NDC(0.93);

	cvs -> Update();

	cvs -> SaveAs(Form("energyInit_%d_%s_IQMD_all_3.png",particleName[selectParticle], dataName[selectData]));
}

