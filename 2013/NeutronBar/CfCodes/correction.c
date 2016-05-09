/////////////////////////////////////////////////////////////////////
//This file find zero base time of gamma and apply pedestal to ADC.//
//The result is new tree file.                                     //
//At first subtract t0 of 5cm from t0 of 100cm. This is zero base  //
//adjustment. Extract not knowing factors.                         //
/////////////////////////////////////////////////////////////////////

#include <TTree.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1.h>
#include <Riostream.h>
#include <TMath.h>
#include <TF1.h>

void correction()
{
	//variable to read in (data_to_tree.root)
	Double_t lped;
	Double_t rped;
	Double_t acctl;
	Double_t acctr;
	Double_t accal; // KYO
	Double_t accar; // KYO
	Double_t Tl;
	Double_t Tr;
	Double_t Al;
	Double_t Ar;
	// variable to write out (corrected_tree.root)
	Double_t TDCl;
	Double_t TDCr;
	Double_t ADCl;
	Double_t ADCr;
	Double_t accTDCl;
	Double_t accTDCr;

//ptfactor = point to time factor (change TDC channel to time(ns) by multiplying this value)
	//const Double_t ptfactor = 0.050;
	const Double_t ptfactor = 0.0407; //from Kisoo

//number of data
	//w/o cut
	//const Double_t NOdataF = 104768;
	//const Double_t NOpedF = 10000;
	//const Double_t NOaccF = 2000;
	//w cut
	const Double_t NOdataF = 43493;
	const Double_t NOpedF = 10000;
	const Double_t NOaccF = 717;

//This values are slope and constant for exponential. We use exponential for Time Walk Correction. a is slope, b is constant.
/*
	//expo
	const Double_t al = -0.00109299;
	const Double_t ar = -0.000865513;
	const Double_t bl = 2.78141;
	const Double_t br = 2.69015;
*/
/*
	//pol1
	const Double_t al = -0.014366;
	const Double_t ar = -0.010128;
	const Double_t bl = 15.911062;
	const Double_t br = 14.549197;
*/
	//pol1
	const Double_t al = 0.0020; //from Cobalt
	const Double_t ar = -0.0007;
	const Double_t bl = 10.9742;
	const Double_t br = 9.5995;

//	const Double_t gaptime = 3.33; //[ns] (when L=1m, c=3*10^8m/s, t=L/c)
	const Double_t gaptime = 4.67; //[ns] (when L=1.4m, c=3*10^8m/s, t=L/c)
//	const Double_t gaptime = 4.59; //[ns] (when L=1.375m, c=3*10^8m/s, t=L/c)

//define input file and output file
	TFile* fin = new TFile("data_to_tree.root");
	TFile* fout = new TFile("corrected_tree.root", "RECREATE");

//define trees which bring data : fin

	//birng pedestal tree
	TTree* pedestal = (TTree*) fin->Get("pedestal");
	pedestal->SetBranchAddress("lped", &lped);
	pedestal->SetBranchAddress("rped", &rped);

	//bring accidental tree
	TTree* accidental = (TTree*) fin->Get("accidental");
	accidental->SetBranchAddress("accTl", &acctl);
	accidental->SetBranchAddress("accTr", &acctr);
	accidental->SetBranchAddress("accAl", &accal); //KYO
	accidental->SetBranchAddress("accAr", &accar); //KYO

	//bring data tree
	TTree* data = (TTree*) fin->Get("data");
	data->SetBranchAddress("Tl", &Tl);
	data->SetBranchAddress("Tr", &Tr);
	data->SetBranchAddress("Al", &Al);
	data->SetBranchAddress("Ar", &Ar);

	//make corrected data. except accidental correction : fout
	TTree* californium = new TTree("californium", "californium data");
	californium->Branch("TDCl", &TDCl, "TDCl/D");
	californium->Branch("TDCr", &TDCr, "TDCr/D");
	californium->Branch("ADCl", &ADCl, "ADCl/D");
	californium->Branch("ADCr", &ADCr, "ADCr/D");

	//make corrected accidental
	TTree* acccalifornium = new TTree("acccalifornium", "accidental californium data");
	acccalifornium->Branch("accTDCl", &accTDCl, "accTDCl/D");
	acccalifornium->Branch("accTDCr", &accTDCr, "accTDCr/D");

//define canvases and histograms

	//define plots for data
	TCanvas* c1 = new TCanvas("c1", "dataTl", 200, 0, 600, 600);
	TH1F* datalhist = new TH1F("datalhist", "left", 200, -20, 180);
	TCanvas* c2 = new TCanvas("c2", "dataTr", 210, 10, 600, 600);
	TH1F* datarhist = new TH1F("datarhist", "right", 200, -20, 180);

	//define plots for pedestal
	TCanvas* c3 = new TCanvas("c3", "pedl", 220, 20, 600, 600);
//	TH1F* pedlhist = new TH1F("pedlhist", "left", 200, 0, 200);
	TH1F* pedlhist = new TH1F("pedlhist", "left", 200, 60, 260);
	TCanvas* c4 = new TCanvas("c4", "pedr", 230, 30, 600, 600);
//	TH1F* pedrhist = new TH1F("pedrhist", "right", 200, 0, 200);
	TH1F* pedrhist = new TH1F("pedrhist", "right", 200, 60, 260);

	//define plots for corrected acccidental
	TCanvas* c5 = new TCanvas("c5", "acctl", 240, 40, 600, 600);
	TH1F* acclhist = new TH1F("acclhist", "left", 200, -50, 150);
	TCanvas* c6 = new TCanvas("c6", "acctr", 250, 50, 600, 600);
	TH1F* accrhist = new TH1F("accrhist", "right", 200, -50, 150);

	//define plots for gamma time correction
	TCanvas* c7 = new TCanvas("c7", "shift ch0", 260, 60, 600, 600);
	TH1F* shiftlhist = new TH1F("shiftlhist", "left", 200, -20, 180);
	TCanvas* c8 = new TCanvas("c8", "shift ch2", 270, 70, 600, 600);
	TH1F* shiftrhist = new TH1F("shiftrhist", "right", 200, -20, 180);

//main process

	//convert TDC to time
	for(Int_t i = 0; i < NOdataF; i++)
	{
		data->GetEntry(i);
/*
		//expo
		datalhist->Fill(Tl*ptfactor-TMath::Exp(al*Al)-bl);
		datarhist->Fill(Tr*ptfactor-TMath::Exp(ar*Ar)-br);
*/
		//pol1
		datalhist->Fill(Tl*ptfactor-al*Al-bl);
		datarhist->Fill(Tr*ptfactor-ar*Ar-br);
	}

	c1->cd();
	c1->SetLogy();
	datalhist->GetXaxis()->SetTitle("time(ns)");
	datalhist->GetYaxis()->SetTitle("count");
	datalhist->Draw();
//	datalhist->Fit("gaus", "", "", -3, 9);
	datalhist->Fit("gaus", "", "", -3, 8);
	Double_t datalt0mean = datalhist->GetFunction("gaus")->GetParameter(1);
	c1->SaveAs("CFD_datalt0fit.png");

	c2->cd();
	c2->SetLogy();
	datarhist->GetXaxis()->SetTitle("time(ns)");
	datarhist->GetYaxis()->SetTitle("count");
	datarhist->Draw();
//	datarhist->Fit("gaus", "", "", -5, 8);
	datarhist->Fit("gaus", "", "", -2, 9);
	Double_t datart0mean = datarhist->GetFunction("gaus")->GetParameter(1);
	c2->SaveAs("CFD_datart0fit.png");

	cout << "-----------------------------------" << endl;
	cout << "datalt0mean="<< datalt0mean << ", datart0mean= " << datart0mean << endl;
	cout << "-----------------------------------" << endl;

	//calculate pedestal
	for(Int_t j = 0; j < NOpedF; j++)
	{
		pedestal->GetEntry(j);
		pedlhist->Fill(lped);
		pedrhist->Fill(rped);
	}

	c3->cd();
//	c3->SetLogy();
	pedlhist->Draw();
//	pedlhist->Fit("gaus", "", "", 145, 165);
	pedlhist->Fit("gaus", "", "", 150, 160);
//	pedlhist->Fit("gaus", "", "", 115, 200); //Ben
	Double_t pedlmean = pedlhist->GetFunction("gaus")->GetParameter(1);
	c3->SaveAs("CFD_pedl.png");

	c4->cd();
//	c4->SetLogy();
	pedrhist->Draw();
	pedrhist->Fit("gaus", "", "", 105, 125);
//	pedrhist->Fit("gaus", "", "", 75, 125);
//	pedrhist->Fit("gaus", "", "", 75, 175); //Ben
	Double_t pedrmean = pedrhist->GetFunction("gaus")->GetParameter(1);
	c4->SaveAs("CFD_pedr.png");

	cout << "-----------------------------------" << endl;
	cout << "pedlmean=" << pedlmean << ", pedrmean=" << pedrmean << endl;
	cout << "-----------------------------------" << endl;

	//correct accidental and write
	for(Int_t i = 0; i < NOaccF; i++)
	{
		accidental->GetEntry(i);
/*
		//expo
		accTDCl = acctl*ptfactor-TMath::Exp(al*Al)-bl-datalt0mean+gaptime;
		accTDCr = acctr*ptfactor-TMath::Exp(ar*Ar)-br-datart0mean+gaptime;
*/
		//pol1
//		accTDCl = acctl*ptfactor-al*Al-bl-datalt0mean+gaptime;
//		accTDCr = acctr*ptfactor-ar*Ar-br-datart0mean+gaptime;
		accTDCl = acctl*ptfactor-al*accal-bl-datalt0mean+gaptime; // KYO
		accTDCr = acctr*ptfactor-ar*accar-br-datart0mean+gaptime; // KYO

		acclhist->Fill(accTDCl);
		accrhist->Fill(accTDCr);

		acccalifornium->Fill();
	}

	c5->cd();
	c5->SetLogy();
	acclhist->Draw();
	c5->SaveAs("CFD_accl.png");

	c6->cd();
	c6->SetLogy();
	accrhist->Draw();
	c6->SaveAs("CFD_accr.png");

	//correct data and write
	for(Int_t l = 0; l < NOdataF; l++)
	{
		data->GetEntry(l);
/*
		//expo
		TDCl = Tl*ptfactor-TMath::Exp(al*Al)-bl-datalt0mean+gaptime;
		TDCr = Tr*ptfactor-TMath::Exp(ar*Ar)-br-datart0mean+gaptime;
*/
		//pol1
		TDCl = Tl*ptfactor-al*Al-bl-datalt0mean+gaptime;
		TDCr = Tr*ptfactor-ar*Ar-br-datart0mean+gaptime;

		ADCl = Al-pedlmean;
		ADCr = Ar-pedrmean;

		shiftlhist->Fill(TDCl);
		shiftrhist->Fill(TDCr);

		californium->Fill();
	}

	c7->cd();
	c7->SetLogy();
	shiftlhist->Draw();
//	shiftlhist->Fit("gaus", "", "", -3, 9);
//	shiftlhist->Fit("gaus", "", "", -2, 11);
	shiftlhist->Fit("gaus", "", "", -1, 10);
//	shiftlhist->Fit("gaus", "", "", 0, 10);
	Double_t shiftlmean = shiftlhist->GetFunction("gaus")->GetParameter(1);

	c8->cd();
	c8->SetLogy();
	shiftrhist->Draw();
//	shiftrhist->Fit("gaus", "", "", -2, 11);
	shiftrhist->Fit("gaus", "", "", -1, 10);
//	shiftrhist->Fit("gaus", "", "", 0, 10);
	Double_t shiftrmean = shiftrhist->GetFunction("gaus")->GetParameter(1);

	// check if gamma peak is at the right position
	cout << "-----------------------------------" << endl;
	cout << "shiftlmean=" << shiftlmean << ", shiftrmean=" << shiftrmean << endl;
	cout << "-----------------------------------" << endl;


	fout->Write();
}
