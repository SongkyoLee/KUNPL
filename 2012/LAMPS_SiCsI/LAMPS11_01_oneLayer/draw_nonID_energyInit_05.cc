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
#include <TColor.h>

#include <sstream>
#include <string>

using namespace std;

void draw_nonID_energyInit_05(Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX)
{

	const Double_t eventNum = 10000;

	// start drawing
	gStyle -> SetOptTitle(0);
	gStyle -> SetLabelSize(0.035, "X");
	gStyle -> SetLabelSize(0.035, "Y");
	gStyle -> SetTitleXOffset(0.8);
	gStyle -> SetTitleYOffset(0.9);
	gStyle -> SetTitleXSize(0.05);
	gStyle -> SetTitleYSize(0.05);
	
	TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);
	cvs -> cd();
	cvs -> SetLogy(); // log scale y axis

	Int_t eventID, trackID;
	Double_t edep1, edep2, edep3, edep4, energyInit;	

	// read root file 01 : proton
	TFile* openFile01 = new TFile("dE_E_SiCsI_proton.root","READ");	
	TTree* tempTree01 = (TTree *)openFile01 -> Get("dE_E");
	tempTree01 -> SetBranchAddress("eventID", &eventID);
	tempTree01 -> SetBranchAddress("trackID", &trackID);
	tempTree01 -> SetBranchAddress("edep1", &edep1);
	tempTree01 -> SetBranchAddress("edep2", &edep2);
	tempTree01 -> SetBranchAddress("edep3", &edep3);
	tempTree01 -> SetBranchAddress("edep4", &edep4);
	tempTree01 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist01 = new TH1D("hist01", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries01 = tempTree01 -> GetEntries();
	cout << "proton total Entries = " << entries01 << endl;

	for (Int_t i =0; i<entries01 ; i++)
	{
		tempTree01 -> GetEntry(i);
		if(edep1!=0&&edep2!=0&&edep1<1.54&&edep2<120&&((edep2<50&&edep1<0.00065*(edep2-50)*(edep2-50)+0.5)||(edep2>=50&&edep1<0.00006*(edep2-120)*(edep2-120)+0.2)))
		{hist01->Fill(energyInit);}
		else if(edep3!=0&&edep4!=0&&edep3<1.54&&edep4<120&&((edep4<50&&edep3<0.00065*(edep4-50)*(edep4-50)+0.5)||(edep4>=50&&edep3<0.00006*(edep4-120)*(edep4-120)+0.2)))
		{hist01->Fill(energyInit);}
	}

	hist01 -> GetXaxis() -> SetTitle("Initial Energy (MeV)");
	hist01 -> GetXaxis() -> SetTitleFont(132);
	hist01 -> GetXaxis() -> SetTitleSize(0.05);
	hist01 -> GetXaxis() -> CenterTitle();
	hist01 -> GetYaxis() -> SetTitle("Counts");
	hist01 -> GetYaxis() -> SetTitleFont(132);
	hist01 -> GetYaxis() -> SetTitleSize(0.05);
	hist01 -> GetYaxis() -> CenterTitle();
	hist01 -> SetStats(0); //stats
	hist01 -> SetLineColor(15);
	hist01 -> Scale(1/eventNum); // normalization (10000 event)
	hist01 -> Draw("");



	// read root file02 : deuteron
	TFile* openFile02 = new TFile("dE_E_SiCsI_deuteron.root","READ");	
	TTree* tempTree02 = (TTree *)openFile02 -> Get("dE_E");
	tempTree02 -> SetBranchAddress("eventID", &eventID);
	tempTree02 -> SetBranchAddress("trackID", &trackID);
	tempTree02 -> SetBranchAddress("edep1", &edep1);
	tempTree02 -> SetBranchAddress("edep2", &edep2);
	tempTree02 -> SetBranchAddress("edep3", &edep3);
	tempTree02 -> SetBranchAddress("edep4", &edep4);
	tempTree02 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist02 = new TH1D("hist02", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries02 = tempTree02 -> GetEntries();
	cout << "deuteron total Entries = " << entries02 << endl;

	for (Int_t i =0; i<entries02 ; i++)
	{
		tempTree02 -> GetEntry(i);
		if(edep1!=0&&edep2!=0&&edep1<1.944&&edep2<150&&((edep2<55.0&&edep1<0.0009*(edep2-55)*(edep2-55)+0.8415)||(edep2>=55.0&&edep1<0.00006*(edep2-150)*(edep2-150)+0.3)))
		{hist02->Fill(energyInit);}
		else if(edep3!=0&&edep4!=0&&edep3<1.944&&edep4<150&&((edep4<55.0&&edep3<0.0009*(edep4-55)*(edep4-55)+0.8415)||(edep4>=55.0&&edep3<0.00006*(edep4-150)*(edep4-150)+0.3)))
		{hist02->Fill(energyInit);}
	}

	hist02 -> SetLineColor(46);
	hist02 -> Scale(1/eventNum); // normalization
	hist02 -> Draw("same");


	// read root file 03 : triton
	TFile* openFile03 = new TFile("dE_E_SiCsI_triton.root","READ");	
	TTree* tempTree03 = (TTree *)openFile03 -> Get("dE_E");
	tempTree03 -> SetBranchAddress("eventID", &eventID);
	tempTree03 -> SetBranchAddress("trackID", &trackID);
	tempTree03 -> SetBranchAddress("edep1", &edep1);
	tempTree03 -> SetBranchAddress("edep2", &edep2);
	tempTree03 -> SetBranchAddress("edep3", &edep3);
	tempTree03 -> SetBranchAddress("edep4", &edep4);
	tempTree03 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist03 = new TH1D("hist03", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries03 = tempTree03 -> GetEntries();
	cout << "triton total Entries = " << entries03 << endl;

	for (Int_t i =0; i<entries03 ; i++)
	{
		tempTree03 -> GetEntry(i);
		if(edep1!=0&&edep2!=0&&edep1<1.881&&edep2<170&&((edep2<55&&edep1<0.0011*(edep2-55)*(edep2-55)+1.1935)||(edep2>=55&&edep1<0.00006*(edep2-170)*(edep2-170)+0.4)))
		{hist03->Fill(energyInit);}
		else if(edep3!=0&&edep4!=0&&edep3<1.881&&edep4<170&&((edep4<55&&edep3<0.0011*(edep4-55)*(edep4-55)+1.1935)||(edep4>=55&&edep3<0.00006*(edep4-170)*(edep4-170)+0.4)))
		{hist03->Fill(energyInit);}
	}

	hist03 -> SetLineColor(9);
	hist03 -> Scale(1/eventNum); // normalization
	hist03 -> Draw("same");


	// read root file 04 : Helium
	TFile* openFile04 = new TFile("dE_E_SiCsI_alpha.root","READ");	
	TTree* tempTree04 = (TTree *)openFile04 -> Get("dE_E");
	tempTree04 -> SetBranchAddress("eventID", &eventID);
	tempTree04 -> SetBranchAddress("trackID", &trackID);
	tempTree04 -> SetBranchAddress("edep1", &edep1);
	tempTree04 -> SetBranchAddress("edep2", &edep2);
	tempTree04 -> SetBranchAddress("edep3", &edep3);
	tempTree04 -> SetBranchAddress("edep4", &edep4);
	tempTree04 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist04 = new TH1D("hist04", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries04 = tempTree04 -> GetEntries();
	cout << "Helium total Entries = " << entries04 << endl;

	for (Int_t i =0; i<entries04 ; i++)
	{
		tempTree04 -> GetEntry(i);
		if(edep1!=0&&edep2!=0&&edep1<5.591&&edep2<540&&((edep2<200&&edep1<0.00015*(edep2-200)*(edep2-200)+2.216)||(edep2>=200&&edep1<0.000011*(edep2-540)*(edep2-540)+0.95)))
		{hist04->Fill(energyInit);}
		else if(edep3!=0&&edep4!=0&&edep3<5.591&&edep4<540&&((edep4<200&&edep3<0.00015*(edep4-200)*(edep4-200)+2.216)||(edep4>=200&&edep3<0.000011*(edep4-540)*(edep4-540)+0.95)))
		{hist04->Fill(energyInit);}
	}

	hist04 -> SetLineColor(8);
	hist04 -> Scale(1/eventNum); // normalization
	hist04 -> Draw("same");

	cvs -> Update();
	cvs -> SaveAs("nonID_energyInit.png");
	return;
}
