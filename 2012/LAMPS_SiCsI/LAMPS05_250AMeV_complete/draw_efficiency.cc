#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <TF1.h>
#include <TGraph.h>
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

void draw_efficiency(Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX)
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
	//cvs -> SetLogy(); // log scale y axis

	// read root file_ rawData.root -> Generator
	TChain GenTree("GeneratorData");
	GenTree.Add("rawData01.root");
	GenTree.Add("rawData02.root");
	GenTree.Add("rawData03.root");
	GenTree.Add("rawData04.root");
	GenTree.Add("rawData05.root");
	GenTree.Add("rawData06.root");
	GenTree.Add("rawData07.root");
	GenTree.Add("rawData08.root");
	GenTree.Add("rawData09.root");
	GenTree.Add("rawData10.root");

	TTree* Gen01 = GenTree.CopyTree("pID==2212");
	TTree* Gen02 = GenTree.CopyTree("pID==1000010020");
	TTree* Gen03 = GenTree.CopyTree("pID==1000010030");
	TTree* Gen04 = GenTree.CopyTree("pID==1000020040");
	

	// read root file_01_proton
	TFile* openFile01 = new TFile("nonID_SiCsI_01.root","READ");	
	TTree* tempTree01 = (TTree *)openFile01 -> Get("tempTree3");

	//Int_t eventID, trackID;
	Double_t energyInit_Gen;
	Double_t energyInit_Simul;	

	//tempTree01 -> SetBranchAddress("eventID", &eventID);
	//tempTree01 -> SetBranchAddress("trackID", &trackID);
	Gen01 -> SetBranchAddress("energyInit", &energyInit_Gen);
	tempTree01 -> SetBranchAddress("energyInit", &energyInit_Simul);
	
//	TH1D *hist01 = new TH1D("hist01", "non-identified/generated vs initial energy", selectXBins, selectMinX, selectMaxX);

	const Int_t n = selectMaxX/selectXBins;
	cout << " n = " << n << endl;
	Double_t ratio01[n];
	Double_t x[n];

	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries01 = Gen01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries01 = tempTree01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	//cout << "proton total generated Entries = " << genEntries01 << endl;
	//cout << "proton total non-identified  Entries = " << nonEntries01 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	ratio01[i] = (nonEntries01/genEntries01)*100;
	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  proton ratio = " << ratio01[i] << " (%)" << endl;
	//cout << "                      " << endl;
	}

	TGraph *gr01 = new TGraph(n, x, ratio01);
	gr01->SetLineColor(4);
	//gr01->SetLineWidth(2);
	gr01->SetMarkerColor(4);
	gr01->SetMarkerStyle(21);
	gr01-> GetXaxis()->SetTitle("initial energy (MeV)");
	gr01-> GetYaxis()->SetTitle("non identified/generated (%)");
	gr01->Draw("AP");

/*
	hist01 -> GetXaxis() -> SetTitle("Initial Energy (MeV)");
	hist01 -> GetXaxis() -> SetTitleFont(132);
	hist01 -> GetXaxis() -> SetTitleSize(0.05);
	hist01 -> GetXaxis() -> CenterTitle();
	hist01 -> GetYaxis() -> SetTitle("non identified / generated (%)");
	hist01 -> GetYaxis() -> SetTitleFont(132);
	hist01 -> GetYaxis() -> SetTitleSize(0.05);
	hist01 -> GetYaxis() -> CenterTitle();
	hist01 -> SetStats(0); //stats
	hist01 -> SetLineColor(15);
//	hist01 -> Scale(1/eventNum); // normalization (10000 event)
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
	hist02 -> Scale(1/eventNum); // normalization
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
	hist03 -> Scale(1/eventNum); // normalization
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
	hist04 -> Scale(1/eventNum); // normalization
	hist04 -> Draw("same");






	cvs -> Update();
	cvs -> SaveAs("nonID_energyInit_05.png");
*/
	return;
}

