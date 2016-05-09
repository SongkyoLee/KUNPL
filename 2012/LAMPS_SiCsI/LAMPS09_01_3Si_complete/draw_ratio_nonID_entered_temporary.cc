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

void draw_ratio_nonID_entered(Int_t selectXBins, Double_t selectMinX, Double_t selectMaxX)
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

	const Int_t n = selectMaxX/selectXBins;
	cout << " n = " << n << endl;

	Double_t ratio01[n], ratio02[n], ratio03[n], ratio04[n];
	Double_t x[n];

	//--------------- read root file_01_proton

	TFile* openNon01 = new TFile("dE_E_SiCsI_proton.root","READ");	
	TTree* entTree01 = (TTree *)openNon01 -> Get("dE_E");
	TTree* nonTree01 = entTree01 -> CopyTree( "(edep1!=0&&edep2!=0&&edep1<1.54&&edep2<120&&((edep2<50&&edep1<0.00065*(edep2-50)*(edep2-50)+0.5)||(edep2>=50&&edep1<0.00006*(edep2-120)*(edep2-120)+0.2))) || (edep3!=0&&edep4!=0&&edep3<1.54&&edep4<120&&((edep4<50&&edep3<0.00065*(edep4-50)*(edep4-50)+0.5)||(edep4>=50&&edep3<0.00006*(edep4-120)*(edep4-120)+0.2))) " );
	
	for (Int_t i=0; i<n; i++)
	{
	Double_t entEntries01 = entTree01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries01 = nonTree01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "proton total entered Entries = " << entEntries01 << endl;
	cout << "proton total non-identified  Entries = " << nonEntries01 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if ( entEntries01 ==0) {ratio01[i]==0;}
	else if {ratio01[i] = (nonEntries01/entEntries01)*100;}

	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  proton ratio = " << ratio01[i] << " (%)" << endl;
	cout << "                      " << endl;
	}

	TGraph *gr01 = new TGraph(n, x, ratio01);
	gr01->SetLineColor(15);
	//gr01->SetLineWidth(2);
	gr01->SetMarkerColor(15);
	gr01->SetMarkerStyle(20);
	gr01-> GetXaxis()->SetTitle("initial energy (MeV)");
	gr01-> GetYaxis()->SetTitle("non identified/enterered (%)");
	gr01-> GetYaxis()->SetTitle("non identified/entered (%)");
	gr01-> SetMaximum(85); // range of Y axis
	gr01->Draw("ALP");


	// --------------- read root file_02_deuteron

	TFile* openNon02 = new TFile("dE_E_SiCsI_deuteron.root","READ");	
	TTree* entTree02 = (TTree *)openNon02 -> Get("dE_E");
	TTree* nonTree02 = entTree02 -> CopyTree(" ( edep1!=0&&edep2!=0&&edep1<1.944&&edep2<150&&((edep2<55.0&&edep1<0.0009*(edep2-55)*(edep2-55)+0.8415)||(edep2>=55.0&&edep1<0.00006*(edep2-150)*(edep2-150)+0.3))) || (edep3!=0&&edep4!=0&&edep3<1.944&&edep4<150&&((edep4<55.0&&edep3<0.0009*(edep4-55)*(edep4-55)+0.8415)||(edep4>=55.0&&edep3<0.00006*(edep4-150)*(edep4-150)+0.3)))");

	for (Int_t i=0; i<n; i++)
	{
	Double_t entEntries02 = entTree02 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries02 = nonTree02 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "deuteron total entered Entries = " << entEntries02 << endl;
	cout << "deuteron total non-identified  Entries = " << nonEntries02 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if (entEntries02==0) {ratio02[i]==0;}
	else if { ratio02[i] = (nonEntries02/entEntries02)*100;}
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

	TFile* openNon03 = new TFile("dE_E_SiCsI_triton.root","READ");	
	TTree* entTree03 = (TTree *)openNon03 -> Get("dE_E");
	TTree* nonTree03 = entTree03 -> CopyTree(" (edep1!=0&&edep2!=0&&edep1<1.881&&edep2<170&&((edep2<55&&edep1<0.0011*(edep2-55)*(edep2-55)+1.1935)||(edep2>=55&&edep1<0.00006*(edep2-170)*(edep2-170)+0.4))) || (edep3!=0&&edep4!=0&&edep3<1.881&&edep4<170&&((edep4<55&&edep3<0.0011*(edep4-55)*(edep4-55)+1.1935)||(edep4>=55&&edep3<0.00006*(edep4-170)*(edep4-170)+0.4))) ");

	for (Int_t i=0; i<n; i++)
	{
	Double_t entEntries03 = entTree03 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries03 = nonTree03 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "trition total entered Entries = " << entEntries03 << endl;
	cout << "triton total non-identified  Entries = " << nonEntries03 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if (entEntries03 ==0) {ratio03[i]==0;}
	else if { ratio03[i] = (nonEntries03/entEntries03)*100; }
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  triton ratio = " << ratio03[i] << " (%)" << endl;
	cout << "                      " << endl;
	}

	TGraph *gr03 = new TGraph(n, x, ratio03);
	gr03->SetLineColor(9);
	//gr01->SetLineWidth(2);
	gr03->SetMarkerColor(9);
	gr03->SetMarkerStyle(20);
	gr03 -> Draw("LP");


	// --------------- read root file_04_Helium

	TFile* openNon04 = new TFile("dE_E_SiCsI_alpha.root","READ");	
	TTree* entTree04 = (TTree *)openNon04 -> Get("dE_E");
	TTree* nonTree04 = entTree04 -> CopyTree(" (edep1!=0&&edep2!=0&&edep1<5.591&&edep2<540&&((edep2<200&&edep1<0.00015*(edep2-200)*(edep2-200)+2.216)||(edep2>=200.0&&edep1<0.000011*(edep2-540)*(edep2-540)+0.95))) || (edep3!=0&&edep4!=0&&edep3<5.591&&edep4<540&&((edep4<200.0&&edep3<0.00015*(edep4-200)*(edep4-200)+2.216)||(edep4>=200.0&&edep3<0.000011*(edep4-540)*(edep4-540)+0.95)))");

	for (Int_t i=0; i<n; i++)
	{
	Double_t entEntries04 = entTree04 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries04 = nonTree04 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "Helium total entered Entries = " << entEntries04 << endl;
	cout << "Helium total non-identified  Entries = " << nonEntries04 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	ratio04[i] = (nonEntries04/entEntries04)*100;
	if (nonEntries04==0 || entEntries04 ==0) ratio04[i]==0;
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  Helium ratio = " << ratio04[i] << " (%)" << endl;
	cout << "                      " << endl;
	}

	TGraph *gr04 = new TGraph(n, x, ratio04);
	gr04->SetLineColor(8);
	//gr01->SetLineWidth(2);
	gr04->SetMarkerColor(8);
	gr04->SetMarkerStyle(20);
	gr04 -> Draw("LP");

	cvs -> Update();
	cvs -> SaveAs("ratio_nonID_entered.png");
	return;
}

