#include <Riostream.h>
//#include <TROOT.h>
//#include <TFile.h>
//#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TStyle.h>
//#include <TH1D.h>
#include <TH2D.h>
#include <TDirectory.h>
//#include <TLegend.h>
#include <TPaveText.h>
//#include <TText.h>
//#include <TGraph.h>
#include <TMath.h>
 
#include <sstream>
#include <string>

 using namespace std;


void check_SlndField()
{

	//open the solenoid data file (from OPERA)
	std::ifstream Fin("solenoid.dat",std::ios::in); // in : read the file

	const Int_t rNum = 101;
	const Int_t zNum = 201;

	// fix the rPos and see Bz,Br as a function of zPos
	const Int_t isR = 500;

	Double_t rPos[rNum][zNum];
	Double_t zPos[rNum][zNum];
	Double_t Br[rNum][zNum];
	Double_t Bz[rNum][zNum];

	// make the canvas and histogram
	TCanvas *c1 = new TCanvas("c1","",900,700);
	TCanvas *c2 = new TCanvas("c2","",900,700);
	TH2D *hist_Bz_z = new TH2D("hist_Bz_z", "Longitudinal B-Field B_{z}(z);z (mm);B_{z} (T)",220, -800, 1400, 100, 0.3, 0.55);
	TH2D *hist_Br_z = new TH2D("hist_Br_z", "Radial B-Field B_{r}(z);z (mm);B_{r} (T)",220, -800, 1400, 100, -0.1, 0.1);

	// read the data
	// ir = rPos/10
	// iz = (zPos+700)/10
	for (Int_t ir=0; ir<rNum; ir++) {
		for (Int_t iz=0; iz<zNum; iz++) {
			Fin >> rPos[ir][iz] >> zPos[ir][iz] >> Br[ir][iz] >> Bz[ir][iz];
			if (rPos[ir][iz]==isR) { 
				hist_Bz_z -> Fill(zPos[ir][iz],Bz[ir][iz]);
				hist_Br_z -> Fill(zPos[ir][iz],Br[ir][iz]);
			}
		}
	}
	
	// draw the histogram
	gStyle->SetOptStat(0);
//	gStyle->SetOptTitle(0);
	gStyle->SetTitleFont(132);
	gPad->SetGridx(5);
	gPad->SetGridy(5);

	TPaveText *text = new TPaveText(0.75,0.92,0.99,0.99, "NDC");
	text ->AddText(Form("R= %d mm",isR));
	text->SetFillColor(0);
	text->SetFillStyle(4000);
	text->SetBorderSize(0);
	text->SetMargin(0.2);
	text->SetTextSize(0.05);
	text->SetTextColor(kCyan+1);

	c1->cd();
//	hist_Bz_z->SetTitleOffset(1.0, "X");
//	hist_Bz_z->SetTitleOffset(1.0, "Y");
//	hist_Bz_z->SetTitleFont(132,"X");
//	hist_Bz_z->SetTitleFont(132,"Y");
	hist_Bz_z->SetTitleSize(0.05,"X");
	hist_Bz_z->SetTitleSize(0.05,"Y");
	hist_Bz_z->GetXaxis()->CenterTitle();
	hist_Bz_z->GetYaxis()->CenterTitle();
	hist_Bz_z->Draw();
	text->Draw();

	c2->cd();
	hist_Bz_z->SetTitleSize(0.05,"X");
	hist_Bz_z->SetTitleSize(0.05,"Y");
	hist_Bz_z->GetXaxis()->CenterTitle();
	hist_Bz_z->GetYaxis()->CenterTitle();
	hist_Br_z -> Draw();
	text->Draw();

	// save as PDF
	c1->SaveAs(Form("Bz_z_R%dmm.pdf",isR));
	c2->SaveAs(Form("Br_z_R%dmm.pdf",isR));

	return;

}

