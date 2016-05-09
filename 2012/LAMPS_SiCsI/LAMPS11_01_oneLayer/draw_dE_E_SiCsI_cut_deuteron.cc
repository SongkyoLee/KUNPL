#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TF1.h>
#include <TMath.h>
#include <TPaletteAxis.h>
#include <TPaveStats.h>
#include <TFile.h>
#include <TTree.h>
#include <TDirectory.h>

#include <sstream>
#include <string>

using namespace std;

Double_t fitfunc(Double_t* x, Double_t* par)
{
	return par[0]*(x[0]-par[1])*(x[0]-par[1])+par[2];
}

void draw_dE_E_SiCsI_cut_deuteron(Int_t selectData, Int_t selectParticle, Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX, Int_t selectYBins, Double_t selectMinY, Double_t selectMaxY)
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
	gStyle -> SetTitleYOffset(0.6);
	gStyle -> SetTitleXSize(0.07);
	gStyle -> SetTitleYSize(0.07);
	gStyle -> SetPadLeftMargin(0.15);
	gStyle -> SetPadTopMargin(0.05);
	gStyle -> SetPadBottomMargin(0.15);

	// read root file (instead of Project)
	//TFile* openFile = new TFile("dE_E_SiCsI_secondary_01.root","READ");
	TChain dE_E_Tree("dE_E");
	//dE_E_Tree.Add("dE_E_SiCsI_proton.root");
	dE_E_Tree.Add("dE_E_SiCsI_deuteron.root");
	//dE_E_Tree.Add("dE_E_SiCsI_triton.root");
	//dE_E_Tree.Add("dE_E_SiCsI_alpha.root");

	TTree* tempTree = dE_E_Tree.CopyTree(Form("pID==%d",particleName[selectParticle]));

	Double_t deltaE, largeE;
	Double_t edep1, edep2, edep3, edep4, edep5, edep6, edep7, edep8;
	tempTree -> SetBranchAddress("edep1", &edep1);
	tempTree -> SetBranchAddress("edep2", &edep2);
	tempTree -> SetBranchAddress("edep3", &edep3);
	tempTree -> SetBranchAddress("edep4", &edep4);
	tempTree -> SetBranchAddress("edep5", &edep5);
	tempTree -> SetBranchAddress("edep6", &edep6);
	tempTree -> SetBranchAddress("edep7", &edep7);
	tempTree -> SetBranchAddress("edep8", &edep8);
		
		
	//draw histogram + graph
	TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);

	// graph parameter : a(x-p)^2+q
	Double_t leftPnt = 30.0;
	Double_t middlePnt = 80.0;
	Double_t rightPnt = 200.0;
	Double_t a1 = 0.0009;
	Double_t p1 = middlePnt;
	Double_t a2 = 0.00007;
	Double_t p2 = rightPnt;
	Double_t q2 = 0.9;
	Double_t q1 = a2*(p2-middlePnt)*(p2-middlePnt)+q2;
	Double_t upperLimit = a1*(p1-leftPnt)*(p1-leftPnt)+q1;
	cout << "q1 = " << q1 << endl; 
	cout << "upperLimit = " << upperLimit << endl; 

	TF1* gr1 = new TF1("fit1", fitfunc, leftPnt, middlePnt, 3);
	TF1* gr2 = new TF1("fit2", fitfunc, middlePnt, rightPnt, 3);
	gr1->SetParameters(a1,p1,q1);
	gr2->SetParameters(a2,p2,q2);

	cvs -> cd();

	TH2D *hist = new TH2D("hist", "dE vs E", selectXBins, selectMinX, selectMaxX, selectYBins, selectMinY, selectMaxY);

	Double_t tempEntries = tempTree -> GetEntries();
	cout << "total entries = "  << tempEntries << endl;

	for (Int_t i=0; i<tempEntries; i++)
	{
		deltaE=0;
		largeE=0;
		tempTree -> GetEntry(i);
		if(edep1!=0)
		{
			deltaE=edep1+edep2+edep3;
			largeE=edep4;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{hist->Fill(largeE,deltaE);}
		}

		else if(edep5!=0)
		{
			deltaE = edep5+edep6+edep7;
			largeE = edep8;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{hist->Fill(largeE,deltaE);}
		}
		//hist->Fill(largeE,deltaE);
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

	gr1->Draw("same");
	gr2->Draw("same");

	Double_t cutEntries = hist -> GetEntries();
	cout << "cut entries = " << cutEntries << endl;

	Double_t p_mis = cutEntries/tempEntries;
	cout << "P_mis = " << p_mis*100 <<" (%)" << endl;

//	cvs -> Update();

//	TPaletteAxis *palette = (TPaletteAxis *) hist -> FindObject("palette");
//		palette -> SetLabelSize(0.022);

//TPaveStats *stats = (TPaveStats *) hist -> FindObject("stats");
	//	stats -> SetX1NDC(0.68);
	//	stats -> SetX2NDC(0.87);
	//	stats -> SetY1NDC(0.74);
	//	stats -> SetY2NDC(0.93);

	cvs -> Update();

	cvs -> SaveAs(Form("dE_E_SiCsI_%d_%s_cut_deuteron.png", particleName[selectParticle], dataName[selectData]));
}

