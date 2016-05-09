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

void draw_pT_y(Int_t selectData, Int_t selectParticle, Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX, Int_t selectYBins, Double_t selectMinY, Double_t selectMaxY)
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

	TCanvas *cvs = new TCanvas("cvs", "canvas", 1000, 1000);
	cvs -> cd();

	TH2D *hist = new TH2D("hist", "p_{T}/m vs. y", selectXBins, selectMinX, selectMaxX, selectYBins, selectMinY, selectMaxY);
	TDirectory *histDir = gDirectory; //??KYO -study this

	TFile *openFile = new TFile("pT_y.root");
	TTree *pT_y = (TTree *) openFile -> Get("pT_y");

	histDir -> cd();
	pT_y -> Project("hist", "pT/mass:rapidity", Form("pID==%d", particleName[selectParticle]));

		hist -> GetXaxis() -> SetTitle("y");
		hist -> GetXaxis() -> SetTitleFont(132);
		hist -> GetXaxis() -> CenterTitle();
		hist -> GetYaxis() -> SetTitle("p_{T}/m");
		hist -> GetYaxis() -> SetTitleFont(132);
		hist -> GetYaxis() -> CenterTitle();
		hist -> Draw("colz");
	
	cvs -> Update();

	TPaletteAxis *palette = (TPaletteAxis *) hist -> FindObject("palette");
		palette -> SetLabelSize(0.022);
		palette -> Draw("same");

	TPaveStats *stats = (TPaveStats *) hist -> FindObject("stats");
		stats -> SetX1NDC(0.18);
		stats -> SetX2NDC(0.37);
		stats -> SetY1NDC(0.74);
		stats -> SetY2NDC(0.93);

	cvs -> Update();

// save histogram : KYO changed
//	stringstream saveFileName;
//	saveFileName << "pT_y-" << particleName[selectParticle] << "_" << dataName[selectData] << ".png";
//	cvs -> SaveAs(saveFileName.str().c_str());
	cvs -> SaveAs(Form("pT_y_%d_%s.png",
		particleName[selectParticle], dataName[selectData]));
}
