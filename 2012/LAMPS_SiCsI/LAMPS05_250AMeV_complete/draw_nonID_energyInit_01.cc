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

void draw_nonID_energyInit_01(Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX)
{
	// start drawing
	gStyle -> SetOptTitle(0);
	gStyle -> SetLabelSize(0.035, "X");
	gStyle -> SetLabelSize(0.035, "Y");
	gStyle -> SetTitleXOffset(0.8);
	gStyle -> SetTitleYOffset(0.8);
	gStyle -> SetTitleXSize(0.07);
	gStyle -> SetTitleYSize(0.07);
	
	TCanvas *cvs = new TCanvas("cvs", "canvas", 800, 600);
	cvs -> cd();

	// read root file_01_proton
	TFile* openFile01 = new TFile("nonID_SiCsI_01.root","READ");	
	TTree* tempTree01 = (TTree *)openFile01 -> Get("tempTree3");

	Int_t eventID, trackID;
	Double_t energyInit;	

	tempTree01 -> SetBranchAddress("eventID", &eventID);
	tempTree01 -> SetBranchAddress("trackID", &trackID);
	tempTree01 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist01 = new TH1D("hist01", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries01 = tempTree01 -> GetEntries();
	cout << "proton total Entries = " << entries01 << endl;

	for (Int_t i =0; i<entries01 ; i++)
	{
	tempTree01 -> GetEntry(i);
	hist01->Fill(energyInit);
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
	hist01 -> SetLineColor(1);
	hist01 -> Draw("");

	// read root file_02_deuteron
	TFile* openFile02 = new TFile("nonID_SiCsI_02.root","READ");	
	TTree* tempTree02 = (TTree *)openFile02 -> Get("tempTree3");

	tempTree02 -> SetBranchAddress("eventID", &eventID);
	tempTree02 -> SetBranchAddress("trackID", &trackID);
	tempTree02 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist02 = new TH1D("hist02", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries02 = tempTree02 -> GetEntries();
	cout << "deuteron total Entries = " << entries02 << endl;

	for (Int_t i =0; i<entries02 ; i++)
	{
	tempTree02 -> GetEntry(i);
	hist02->Fill(energyInit);
	}

	hist02 -> SetLineColor(46);
	hist02 -> Draw("same");

	// read root file_03_triton
	TFile* openFile03 = new TFile("nonID_SiCsI_03.root","READ");	
	TTree* tempTree03 = (TTree *)openFile03 -> Get("tempTree3");

	tempTree03 -> SetBranchAddress("eventID", &eventID);
	tempTree03 -> SetBranchAddress("trackID", &trackID);
	tempTree03 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist03 = new TH1D("hist03", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries03 = tempTree03 -> GetEntries();
	cout << "triton total Entries = " << entries03 << endl;

	for (Int_t i =0; i<entries03 ; i++)
	{
	tempTree03 -> GetEntry(i);
	hist03->Fill(energyInit);
	}

	hist03 -> SetLineColor(9);
	hist03 -> Draw("same");

	// read root file_04_Helium
	TFile* openFile04 = new TFile("nonID_SiCsI_04.root","READ");	
	TTree* tempTree04 = (TTree *)openFile04 -> Get("tempTree3");

	tempTree04 -> SetBranchAddress("eventID", &eventID);
	tempTree04 -> SetBranchAddress("trackID", &trackID);
	tempTree04 -> SetBranchAddress("energyInit", &energyInit);
	
	TH1D *hist04 = new TH1D("hist04", "counts vs initial energy", selectXBins, selectMinX, selectMaxX);

	Double_t entries04 = tempTree04 -> GetEntries();
	cout << "Helium total Entries = " << entries04 << endl;

	for (Int_t i =0; i<entries04 ; i++)
	{
	tempTree04 -> GetEntry(i);
	hist04->Fill(energyInit);
	}

	hist04 -> SetLineColor(8);
	hist04 -> Draw("same");

	cvs -> Update();
	cvs -> SaveAs("nonID_energyInit_01.png");
	return;
}

