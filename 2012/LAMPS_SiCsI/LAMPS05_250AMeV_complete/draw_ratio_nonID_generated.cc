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

void draw_ratio_nonID_generated(Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX)
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

	TTree* Gen01 = GenTree.CopyTree("pID==2212"); //proton
	TTree* Gen02 = GenTree.CopyTree("pID==1000010020"); //deuteron
	TTree* Gen03 = GenTree.CopyTree("pID==1000010030"); //triton
	TTree* Gen04 = GenTree.CopyTree("pID==1000020040"); //Helium

	const Int_t n = selectMaxX/selectXBins;
	cout << " n = " << n << endl;

	Double_t ratio01[n], ratio02[n], ratio03[n], ratio04[n];
	Double_t x[n];

	//--------------- read root file_01_proton
	TFile* openFile01 = new TFile("nonID_SiCsI_01.root","READ");	
	TTree* tempTree01 = (TTree *)openFile01 -> Get("tempTree3");

	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries01 = Gen01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries01 = tempTree01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	//cout << "proton total generated Entries = " << genEntries01 << endl;
	//cout << "proton total non-identified  Entries = " << nonEntries01 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if ( genEntries01 ==0) {ratio01[i]==0;}
	else if {ratio01[i] = (nonEntries01/genEntries01)*100;}

	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  proton ratio = " << ratio01[i] << " (%)" << endl;
	//cout << "                      " << endl;
	}

	TGraph *gr01 = new TGraph(n, x, ratio01);
	gr01->SetLineColor(15);
	//gr01->SetLineWidth(2);
	gr01->SetMarkerColor(15);
	gr01->SetMarkerStyle(20);
	gr01-> GetXaxis()->SetTitle("initial energy (MeV)");
	gr01-> GetYaxis()->SetTitle("non identified/generated (%)");
	gr01-> GetYaxis()->SetTitle("non identified/generated (%)");
	gr01-> SetMaximum(85); // range of Y axis
	gr01->Draw("ALP");


	// --------------- read root file_02_deuteron
	TFile* openFile02 = new TFile("nonID_SiCsI_02.root","READ");	
	TTree* tempTree02 = (TTree *)openFile02 -> Get("tempTree3");

	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries02 = Gen02 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries02 = tempTree02 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "deuteron total generated Entries = " << genEntries02 << endl;
	cout << "deuteron total non-identified  Entries = " << nonEntries02 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if (genEntries02==0) {ratio02[i]==0;}
	else if { ratio02[i] = (nonEntries02/genEntries02)*100;}
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  deuteron ratio = " << ratio02[i] << " (%)" << endl;
	cout << "                      " << endl;
	}

	TGraph *gr02 = new TGraph(n, x, ratio02);
	gr02->SetLineColor(46);
	//gr01->SetLineWidth(2);
	gr02->SetMarkerColor(46);
	gr02->SetMarkerStyle(20);
	gr02 -> Draw("LP");


	// --------------- read root file_03_triton
	TFile* openFile03 = new TFile("nonID_SiCsI_03.root","READ");	
	TTree* tempTree03 = (TTree *)openFile03 -> Get("tempTree3");

	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries03 = Gen03 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries03 = tempTree03 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	//cout << "trition total generated Entries = " << genEntries03 << endl;
	//cout << "triton total non-identified  Entries = " << nonEntries03 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if (genEntries03 ==0) {ratio03[i]==0;}
	else if { ratio03[i] = (nonEntries03/genEntries03)*100; }
	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  triton ratio = " << ratio03[i] << " (%)" << endl;
	//cout << "                      " << endl;
	}

	TGraph *gr03 = new TGraph(n, x, ratio03);
	gr03->SetLineColor(9);
	//gr01->SetLineWidth(2);
	gr03->SetMarkerColor(9);
	gr03->SetMarkerStyle(20);
	gr03 -> Draw("LP");


	// --------------- read root file_04_Helium
	TFile* openFile04 = new TFile("nonID_SiCsI_04.root","READ");	
	TTree* tempTree04 = (TTree *)openFile04 -> Get("tempTree3");

	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries04 = Gen04 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries04 = tempTree04 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	//cout << "Helium total generated Entries = " << genEntries04 << endl;
	//cout << "Helium total non-identified  Entries = " << nonEntries04 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	ratio04[i] = (nonEntries04/genEntries04)*100;
	if (nonEntries04==0 || genEntries04 ==0) ratio04[i]==0;
	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	//cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  Helium ratio = " << ratio04[i] << " (%)" << endl;
	//cout << "                      " << endl;
	}

	TGraph *gr04 = new TGraph(n, x, ratio04);
	gr04->SetLineColor(8);
	//gr01->SetLineWidth(2);
	gr04->SetMarkerColor(8);
	gr04->SetMarkerStyle(20);
	gr04 -> Draw("LP");

	cvs -> Update();
	cvs -> SaveAs("ratio_nonID_generated.png");
	return;
}

