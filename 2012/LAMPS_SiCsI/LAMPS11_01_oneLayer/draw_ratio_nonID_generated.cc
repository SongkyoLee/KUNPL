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

	const Int_t n = selectMaxX/selectXBins;
	cout << " n = " << n << endl;

	Double_t ratio01[n], ratio02[n], ratio03[n], ratio04[n];
	Double_t x[n];

	Double_t deltaE, largeE;
	Double_t energyInit, edep1, edep2, edep3, edep4, edep5, edep6, edep7, edep8;

	//--------------- read root file_01_proton

	// graph parameter : a(x-p)^2+q
	Double_t leftPnt = 10.0;
	Double_t middlePnt = 50.0;
	Double_t rightPnt = 150.0;
	Double_t a1 = 0.00150;
	Double_t p1 = middlePnt;
	Double_t a2 = 0.00010;
	Double_t p2 = rightPnt;
	Double_t q2 = 0.6;
	Double_t q1 = a2*(p2-middlePnt)*(p2-middlePnt)+q2;
	Double_t upperLimit = a1*(p1-leftPnt)*(p1-leftPnt)+q1;

	TFile* openRaw01 =new TFile("rawData_proton.root","READ");
	TTree* genTree01 = (TTree *)openRaw01 -> Get("GeneratorData");

	TFile* openNon01 = new TFile("dE_E_SiCsI_proton.root","READ");	
	TTree* tempTree01 = (TTree *)openNon01 -> Get("dE_E");
	tempTree01 -> SetBranchAddress("energyInit", &energyInit);
	tempTree01 -> SetBranchAddress("edep1", &edep1);
	tempTree01 -> SetBranchAddress("edep2", &edep2);
	tempTree01 -> SetBranchAddress("edep3", &edep3);
	tempTree01 -> SetBranchAddress("edep4", &edep4);
	tempTree01 -> SetBranchAddress("edep5", &edep5);
	tempTree01 -> SetBranchAddress("edep6", &edep6);
	tempTree01 -> SetBranchAddress("edep7", &edep7);
	tempTree01 -> SetBranchAddress("edep8", &edep8);

//	TTree* nonTree01 = tempTree01 -> CopyTree(" (edep1!=0&&edep2!=0&&edep1<1.54&&edep2<120&&((edep2<50&&edep1<0.00065*(edep2-50)*(edep2-50)+0.5)||(edep2>=50&&edep1<0.00006*(edep2-120)*(edep2-120)+0.2))) || (edep3!=0&&edep4!=0&&edep3<1.54&&edep4<120&&((edep4<50&&edep3<0.00065*(edep4-50)*(edep4-50)+0.5)||(edep4>=50&&edep3<0.00006*(edep4-120)*(edep4-120)+0.2))) ");

	Double_t tempEntries01 = tempTree01 -> GetEntries();
	cout << "proton entered entries = " << tempEntries01 << endl;

	TTree* nonTree01 = new TTree("tempTree", "");
	//nonTree01 -> Branch("tempEventID", &tempEventID,"tempEventID/I");
	//nonTree01 -> Branch("tempTrackID", &tempEventID,"tempTrackID/I");
	//nonTree01 -> Branch("edep1", &edep1,"edep1/D");
	//nonTree01 -> Branch("edep2", &edep2,"edep2/D");
	//nonTree01 -> Branch("edep3", &edep3,"edep3/D");
	//nonTree01 -> Branch("edep4", &edep4,"edep4/D");
	//nonTree01 -> Branch("edep5", &edep5,"edep5/D");
	//nonTree01 -> Branch("edep6", &edep6,"edep6/D");
	//nonTree01 -> Branch("edep7", &edep7,"edep7/D");
	//nonTree01 -> Branch("edep8", &edep8,"edep8/D");
	nonTree01 -> Branch("deltaE", &deltaE, "deltaE/D");
	nonTree01 -> Branch("largeE", &largeE, "largeE/D");
	nonTree01 -> Branch("energyInit", &energyInit, "energyInit/D");

	for (Int_t i=0; i<tempEntries01; i++)
	{
		deltaE=0;
		largeE=0;
		tempTree01 -> GetEntry(i);
		if(edep1!=0)
		{
			deltaE=edep1+edep2+edep3;
			largeE=edep4;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{nonTree01->Fill();}
		}

		else if(edep5!=0)
		{
			deltaE = edep5+edep6+edep7;
			largeE = edep8;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{nonTree01->Fill();}
		}
	}
	
	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries01 = genTree01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries01 = nonTree01 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "proton total generated Entries = " << genEntries01 << endl;
	cout << "proton total non-identified  Entries = " << nonEntries01 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if ( genEntries01 ==0) {ratio01[i]==0;}
	else if {ratio01[i] = (nonEntries01/genEntries01)*100;}

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
	gr01-> GetYaxis()->SetTitle("non identified/generated (%)");
	gr01-> GetYaxis()->SetTitle("non identified/generated (%)");
	gr01-> SetMaximum(100); // range of Y axis
	gr01->Draw("ALP");


	//--------------- read root file_02_deuteron

	// graph parameter : a(x-p)^2+q
	leftPnt = 30.0;
	middlePnt = 80.0;
	rightPnt = 200.0;
	a1 = 0.0009;
	p1 = middlePnt;
	a2 = 0.00007;
	p2 = rightPnt;
	q2 = 0.9;
	q1 = a2*(p2-middlePnt)*(p2-middlePnt)+q2;
	upperLimit = a1*(p1-leftPnt)*(p1-leftPnt)+q1;

	TFile* openRaw02 =new TFile("rawData_deuteron.root","READ");
	TTree* genTree02 = (TTree *)openRaw02 -> Get("GeneratorData");

	TFile* openNon02 = new TFile("dE_E_SiCsI_deuteron.root","READ");	
	TTree* tempTree02 = (TTree *)openNon02 -> Get("dE_E");
	tempTree02 -> SetBranchAddress("energyInit", &energyInit);
	tempTree02 -> SetBranchAddress("edep1", &edep1);
	tempTree02 -> SetBranchAddress("edep2", &edep2);
	tempTree02 -> SetBranchAddress("edep3", &edep3);
	tempTree02 -> SetBranchAddress("edep4", &edep4);
	tempTree02 -> SetBranchAddress("edep5", &edep5);
	tempTree02 -> SetBranchAddress("edep6", &edep6);
	tempTree02 -> SetBranchAddress("edep7", &edep7);
	tempTree02 -> SetBranchAddress("edep8", &edep8);

	Double_t tempEntries02 = tempTree02 -> GetEntries();
	cout << "deuteron entered entries = " << tempEntries02 << endl;

	TTree* nonTree02 = new TTree("tempTree", "");
	nonTree02 -> Branch("deltaE", &deltaE, "deltaE/D");
	nonTree02 -> Branch("largeE", &largeE, "largeE/D");
	nonTree02 -> Branch("energyInit", &energyInit, "energyInit/D");

	for (Int_t i=0; i<tempEntries02; i++)
	{
		deltaE=0;
		largeE=0;
		tempTree02 -> GetEntry(i);
		if(edep1!=0)
		{
			deltaE=edep1+edep2+edep3;
			largeE=edep4;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{nonTree02->Fill();}
		}

		else if(edep5!=0)
		{
			deltaE = edep5+edep6+edep7;
			largeE = edep8;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{nonTree02->Fill();}
		}
	}
	
	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries02 = genTree02 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries02 = nonTree02 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "deuteron total generated Entries = " << genEntries02 << endl;
	cout << "deuteron total non-identified  Entries = " << nonEntries02 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if ( genEntries02 ==0) {ratio02[i]==0;}
	else if {ratio02[i] = (nonEntries02/genEntries02)*100;}

	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  deuteron ratio = " << ratio02[i] << " (%)" << endl;
	cout << "                      " << endl;
	}

	TGraph *gr02 = new TGraph(n, x, ratio02);
	gr02->SetLineColor(46);
	//gr02->SetLineWidth(2);
	gr02->SetMarkerColor(46);
	gr02->SetMarkerStyle(20);
	gr02->Draw("LP");


	//--------------- read root file_03_triton

	// graph parameter : a(x-p)^2+q
	leftPnt = 40.0;
	middlePnt = 100.0;
	rightPnt = 230.0;
	a1 = 0.0007;
	p1 = middlePnt;
	a2 = 0.00006;
	p2 = rightPnt;
	q2 = 1.3;
	q1 = a2*(p2-middlePnt)*(p2-middlePnt)+q2;
	upperLimit = a1*(p1-leftPnt)*(p1-leftPnt)+q1;

	TFile* openRaw03 =new TFile("rawData_triton.root","READ");
	TTree* genTree03 = (TTree *)openRaw03 -> Get("GeneratorData");

	TFile* openNon03 = new TFile("dE_E_SiCsI_triton.root","READ");	
	TTree* tempTree03 = (TTree *)openNon03 -> Get("dE_E");
	tempTree03 -> SetBranchAddress("energyInit", &energyInit);
	tempTree03 -> SetBranchAddress("edep1", &edep1);
	tempTree03 -> SetBranchAddress("edep2", &edep2);
	tempTree03 -> SetBranchAddress("edep3", &edep3);
	tempTree03 -> SetBranchAddress("edep4", &edep4);
	tempTree03 -> SetBranchAddress("edep5", &edep5);
	tempTree03 -> SetBranchAddress("edep6", &edep6);
	tempTree03 -> SetBranchAddress("edep7", &edep7);
	tempTree03 -> SetBranchAddress("edep8", &edep8);

	Double_t tempEntries03 = tempTree03 -> GetEntries();
	cout << "triton entered entries = " << tempEntries03 << endl;

	TTree* nonTree03 = new TTree("tempTree", "");
	nonTree03 -> Branch("deltaE", &deltaE, "deltaE/D");
	nonTree03 -> Branch("largeE", &largeE, "largeE/D");
	nonTree03 -> Branch("energyInit", &energyInit, "energyInit/D");

	for (Int_t i=0; i<tempEntries03; i++)
	{
		deltaE=0;
		largeE=0;
		tempTree03 -> GetEntry(i);
		if(edep1!=0)
		{
			deltaE=edep1+edep2+edep3;
			largeE=edep4;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{nonTree03->Fill();}
		}

		else if(edep5!=0)
		{
			deltaE = edep5+edep6+edep7;
			largeE = edep8;
			if (deltaE<upperLimit && largeE<rightPnt && ((largeE<middlePnt&& deltaE<a1*(largeE-p1)*(largeE-p1)+q1) || (largeE>=middlePnt&& deltaE<a2*(largeE-p2)*(largeE-p2)+q2)))
			{nonTree03->Fill();}
		}
	}
	
	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries03 = genTree03 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries03 = nonTree03 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "triton total generated Entries = " << genEntries03 << endl;
	cout << "triton total non-identified  Entries = " << nonEntries03 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	if ( genEntries03 ==0) {ratio03[i]==0;}
	else if {ratio03[i] = (nonEntries03/genEntries03)*100;}

	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV : (" <<x[i]<< ")" << endl;
	cout << i*selectXBins <<" to "<< (i+1)*selectXBins << " MeV :  triton ratio = " << ratio03[i] << " (%)" << endl;
	cout << "                      " << endl;
	}

	TGraph *gr03 = new TGraph(n, x, ratio03);
	gr03->SetLineColor(9);
	//gr03->SetLineWidth(2);
	gr03->SetMarkerColor(9);
	gr03->SetMarkerStyle(20);
	gr03->Draw("LP");

/*
	// --------------- read root file_04_Helium

	TFile* openRaw04 =new TFile("rawData_alpha.root","READ");
	TTree* genTree04 = (TTree *)openRaw04 -> Get("GeneratorData");

	TFile* openNon04 = new TFile("dE_E_SiCsI_alpha.root","READ");	
	TTree* tempTree04 = (TTree *)openNon04 -> Get("dE_E");
	TTree* nonTree04 = tempTree04 -> CopyTree(" (edep1!=0&&edep2!=0&&edep1<5.591&&edep2<540&&((edep2<200&&edep1<0.00015*(edep2-200)*(edep2-200)+2.216)||(edep2>=200.0&&edep1<0.000011*(edep2-540)*(edep2-540)+0.95))) || (edep3!=0&&edep4!=0&&edep3<5.591&&edep4<540&&((edep4<200.0&&edep3<0.00015*(edep4-200)*(edep4-200)+2.216)||(edep4>=200.0&&edep3<0.000011*(edep4-540)*(edep4-540)+0.95)))");

	for (Int_t i=0; i<n; i++)
	{
	Double_t genEntries04 = genTree04 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	Double_t nonEntries04 = nonTree04 -> GetEntries(Form("energyInit>%d&&energyInit<%d",i*selectXBins,(i+1)*selectXBins));
	cout << "Helium total generated Entries = " << genEntries04 << endl;
	cout << "Helium total non-identified  Entries = " << nonEntries04 << endl;
	x[i] = (i*selectXBins+(i+1)*selectXBins)/2;
	ratio04[i] = (nonEntries04/genEntries04)*100;
	if (nonEntries04==0 || genEntries04 ==0) ratio04[i]==0;
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
*/

	cvs -> Update();
	cvs -> SaveAs("ratio_nonID_generated.png");
	return;
}

