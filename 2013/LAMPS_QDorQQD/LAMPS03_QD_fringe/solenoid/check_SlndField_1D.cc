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


void check_SlndField_1D()
{

	//open the solenoid data file (from OPERA)
	std::ifstream Fin("solenoid.dat",std::ios::in); // in : read the file

	const Int_t rNum = 101;
	const Int_t zNum = 201;

	// fix the rPos and see Bz,Br as a function of zPos
	const Int_t isR = 500;
//	const Int_t isR = 100;

	Double_t rPos[rNum][zNum];
	Double_t zPos[rNum][zNum];
	Double_t Br[rNum][zNum];
	Double_t Bz[rNum][zNum];

	// make the canvas and histogram
	TCanvas *c1 = new TCanvas("c1","",1600,700);
	TPad *pad1 = new TPad("pad1","",0.02,0.02,0.48,0.98);
	TPad *pad2 = new TPad("pad2","",0.52,0.02,0.98,0.98);
	TH2D *hist_Bz_z = new TH2D("hist_Bz_z", "Longitudinal B-Field;z (mm);B_{z} (T)",220, -800, 1400, 500, 0.3, 0.55);
//	TH2D *hist_Bz_z = new TH2D("hist_Bz_z", "Longitudinal B-Field;z (mm);B_{z} (T)",220, -800, 1400, 500, -0.55, -0.3);
	TH2D *hist_Br_z = new TH2D("hist_Br_z", "Radial B-Field;z (mm);B_{r} (T)",220, -800, 1400, 500, -0.1, 0.1);

	// read the data
	// ir = rPos/10
	// iz = (zPos+700)/10
	for (Int_t ir=0; ir<rNum; ir++) {
		for (Int_t iz=0; iz<zNum; iz++) {
			Fin >> rPos[ir][iz] >> zPos[ir][iz] >> Br[ir][iz] >> Bz[ir][iz];
			if (rPos[ir][iz]==isR) { 
				// Both Br & Bz should have opposite sign (Jackson 5.4)
				hist_Bz_z -> Fill(zPos[ir][iz],-1*Bz[ir][iz]);
				hist_Br_z -> Fill(zPos[ir][iz],-1*Br[ir][iz]);

			}
		}
	}
	
	// Draw the text pave
	TPaveText *text = new TPaveText(0.74,0.92,0.97,0.95, "NDC");
//	TPaveText *text = new TPaveText(1000,0.3,1300,0.35);
	text ->AddText(Form("R= %d mm",isR));
	text->SetFillColor(0);
//	text->SetFillStyle(4000);
	text->SetBorderSize(0);
//	text->SetMargin(0.2);
	text->SetTextSize(0.035);
	text->SetTextColor(kCyan+1);

	// draw the histogram
//	c1->Divide(2,1,0,0);
	pad1->Draw();
	pad2->Draw();

	gStyle->SetOptStat(0);
	//gStyle->SetPalette(1,0);

	pad1->cd();
	pad1->SetGridx();
	pad1->SetGridy();
	hist_Bz_z->SetTitleOffset(1.1, "X");
	hist_Bz_z->SetTitleOffset(1.2, "Y");
//	hist_Bz_z->SetTitleFont(132,"X");
//	hist_Bz_z->SetTitleFont(132,"Y");
	hist_Bz_z->SetTitleSize(0.04,"X");
	hist_Bz_z->SetTitleSize(0.04,"Y");
	hist_Bz_z->GetXaxis()->CenterTitle();
	hist_Bz_z->GetYaxis()->CenterTitle();
	hist_Bz_z->Draw("CONT3");
	text->Draw();

	pad2->cd();
	pad2->SetGridx();
	pad2->SetGridy();
	hist_Br_z->SetTitleOffset(1.1, "X");
	hist_Br_z->SetTitleOffset(1.2, "Y");
	hist_Br_z->SetTitleSize(0.04,"X");
	hist_Br_z->SetTitleSize(0.04,"Y");
	hist_Br_z->GetXaxis()->CenterTitle();
	hist_Br_z->GetYaxis()->CenterTitle();
	hist_Br_z->Draw("CONT3");
	text->Draw();

	// save as PDF
	c1->SaveAs(Form("Slnd_Bfield_1D_R%dmm.pdf",isR));
//	c1->SaveAs(Form("Bz_z_R%dmm.pdf",isR));
//	c2->SaveAs(Form("Br_z_R%dmm.pdf",isR));

	return;

}

