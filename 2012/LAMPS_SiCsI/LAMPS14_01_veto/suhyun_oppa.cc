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
#include <TMath.h>

using namespace std;

void suhyun_oppa(Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX)
{

	gStyle -> SetTitleYOffset(1.5);

	// read root file (TChain instead of Project)
  TFile* openFile = new TFile("rawData_IQMD.root","READ");
	TTree* GenTree = (TTree*)openFile -> Get("GeneratorData");

  Int_t pID;
	Double_t energyInit, pX, pY, pZ;
	GenTree -> SetBranchAddress("energyInit", &energyInit);
	GenTree -> SetBranchAddress("pID", &pID);
//	GenTree -> SetBranchAddress("pX", &pX);
//	GenTree -> SetBranchAddress("pY", &pY);
//	GenTree -> SetBranchAddress("pZ", &pZ);
		
	//draw histogram
	TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);
	cvs -> cd();

	TH1D *hist = new TH1D("hist", "", selectXBins, selectMinX, selectMaxX);
//  GenTree -> Project("hist", "energyInit", "0.249<(TMath::Sqrt(pX*pX+pY*pY)/pZ)&&0.445>(TMath::Sqrt(pX*pX+pY*pY)/pZ)&&pID!=2112&&pID!=111");
  GenTree -> Project("hist", "energyInit","pID==1000020040");

		hist -> GetXaxis() -> SetTitle("E_{tot} (MeV)");
//		hist -> GetXaxis() -> SetTitleFont(132);
//		hist -> GetXaxis() -> SetTitleSize(0.05);
//		hist -> GetXaxis() -> CenterTitle();
		hist -> GetYaxis() -> SetTitle("Entries");
//		hist -> GetYaxis() -> SetTitleFont(132);
//		hist -> GetYaxis() -> SetTitleSize(0.05);
//		hist -> GetYaxis() -> CenterTitle();
		hist -> SetStats(0); //stats
		hist -> Draw();

	cvs -> Update();
//	cvs -> SaveAs("02_14to24deg_charged.pdf");
	cvs -> SaveAs("gen_Helium.pdf");

 Int_t ent[200];
 for (Int_t i=0; i<selectXBins; i++)
		{
			ent[i] = hist->GetBinContent(i+1);
		 	cout << "ent_" << i+1 << " = " << ent[i] << endl;
//		 	cout << ent[i] << endl;

		}

}

