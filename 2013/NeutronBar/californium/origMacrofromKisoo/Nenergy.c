////////////////////////////////////////////////////////////
//This file calculate neutron energy.                     //
//Bring Zero base corrected TDC and shift the gamma value //
//to flight time of 1m.                                   //
//Then neutron ttime can converted into neutron energy.   //
////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TMath.h>
#include <TGraphErrors.h>
#include <stdio.h>
#include <TStyle.h>
#include <TLegend.h>

Double_t bg(Double_t *x, Double_t *par);

Double_t ggauss(Double_t *x, Double_t *par);

Double_t ngauss(Double_t *x, Double_t *par);

Double_t myfit(Double_t *x, Double_t *par);

void Nenergy()
{
	//NM = neutron mass
	const Double_t NM = 939.6;
	const Double_t tResol = 0.00547159;
	//LL = lower limit, upper limit. because histogram x axis unit is 0.5, multiply 2
	const Double_t LL = -20*2;
	const Double_t UL = 80*2;

	Int_t looptl;
	Int_t looptr;
	Int_t loopmean;
	Int_t sign;
	Double_t ItoD = 0;
	Double_t vel = 0;
	Double_t gamma = 0;
	Double_t Energy = 0;
	Int_t fitnoise = 0;
	Int_t hcounts = 0;
	Int_t Ecounts = 0;

	//Double_t mean[8] = {0};
	Double_t x[8] = {3.3, 4.25, 4.75, 5.25, 5.75, 6.5, 7.5, 9};
	Double_t y[8] = {0};
	Double_t xE[8] = {0};
	Double_t yE[8] = {0};

	TFile* fin = new TFile("corrected_tree.root");
	FILE* fout;

	TTree* californium = (TTree*) fin->Get("californium");
	TTree* accidental = (TTree*) fin->Get("acccalifornium");

//define canvases and histograms

	//plots for TDC
	TCanvas* c1 = new TCanvas("c1", "TDCl", 200, 0, 600, 600);
	TH1F* TDCl = new TH1F("TDCl", "", 200, -20, 80);
	TCanvas* c2 = new TCanvas("c2", "TDCr", 210, 10, 600, 600);
	TH1F* TDCr = new TH1F("TDCr", "", 200, -20, 80);

	//plots for accidental
	TCanvas* c3 = new TCanvas("c3", "accidental TDCl", 220, 20, 600, 600);
	TH1F* accTDCl = new TH1F("accTDCl", "", 200, -20, 80);
	TCanvas* c4 = new TCanvas("c4", "accidental TDCr", 230, 30, 600, 600);
	TH1F* accTDCr = new TH1F("accTDCr", "", 200, -20, 80);

	//plots for TDC mean
	TCanvas* c5 = new TCanvas("c5", "TDCmean", 240, 40, 600, 600);
	TH1F* TDCmean = new TH1F("TDCmean", "", 200, -20, 80);
	TCanvas* c6 = new TCanvas("c6", "accTDCmean", 250, 50, 600, 600);
	TH1F* accTDCmean = new TH1F("accTDCmean", "", 200, -20, 80);

	//plots for corrected TDC
	TCanvas* c7 = new TCanvas("c7", "corrected TDCl", 260, 60, 600, 600);
	TH1F* correctedTDCl = new TH1F("correctedTDCl", "", 200, -20, 80);
	TCanvas* c8 = new TCanvas("c8", "corrected TDCr", 270, 70, 600, 600);
	TH1F* correctedTDCr = new TH1F("correctedTDCr", "", 200, -20, 80);
	TCanvas* c9 = new TCanvas("c9", "corrected TDCmean", 280, 80, 600, 600);
	TH1F* correctedTDCmean = new TH1F("correctedTDCmean", "CFD", 200, -20, 80);

	TCanvas* c10 = new TCanvas("c10", "fitTDCmean", 290, 90, 600, 600);
	TH1F* fitTDCmean = new TH1F("fitTDCmean", "CFD", 200, -20, 80);

	//plot for neutron energy
	TCanvas* c11 = new TCanvas("c11", "neutron energy", 290, 90, 600, 600);
	TH1F* Nenergy = new TH1F("NEnergy", "neutron energy", 150, 0, 15);
/*
	//plots for ADC in each energy region
	TCanvas* c11 = new TCanvas("c11", "ADC", 300, 100, 1200, 1800);
	TH1F* ADCr0 = new TH1F("ADCr0", "2.6~4 MeV", 175, 50, 750);
	TH1F* ADCr1 = new TH1F("ADCr1", "4~4.5 MeV", 175, 50, 750);
	TH1F* ADCr2 = new TH1F("ADCr2", "4.5~5 MeV", 175, 50, 750);
	TH1F* ADCr3 = new TH1F("ADCr3", "5~5.5 MeV", 175, 50, 750);
	TH1F* ADCr4 = new TH1F("ADCr4", "5.5~6 MeV", 175, 50, 750);
	TH1F* ADCr5 = new TH1F("ADCr5", "6~7 MeV", 175, 50, 750);
	TH1F* ADCr6 = new TH1F("ADCr6", "7~8 MeV", 175, 50, 750);
	TH1F* ADCr7 = new TH1F("ADCr7", "8~10 MeV", 175, 50, 750);

	TCanvas* c12 = new TCanvas("c12", "energy vs ADC", 310, 110, 600, 600);
*/
//project tree to histogram
	californium->Project("TDCl", "TDCl", "TDCl<80");
	californium->Project("TDCr", "TDCr", "TDCr<80");
	accidental->Project("accTDCl", "accTDCl", "accTDCl<80");
	accidental->Project("accTDCr", "accTDCr", "accTDCr<80");
	californium->Project("TDCmean", "(TDCl+TDCr)/2", "TDCl<80&&TDCr<80");
	accidental->Project("accTDCmean", "(accTDCl+accTDCr)/2", "accTDCl<80&&accTDCr<80");
/*
	californium->Project("ADCr0", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>2.6&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=4");
	californium->Project("ADCr1", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>4&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=4.5");
	californium->Project("ADCr2", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>4.5&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=5");
	californium->Project("ADCr3", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>5&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=5.5");
	californium->Project("ADCr4", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>5.5&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=6");
	californium->Project("ADCr5", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>6&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=7");
	californium->Project("ADCr6", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>7&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=8");
	californium->Project("ADCr7", "ADCl+ADCr", "TDCl<80&&TDCr<80&&(TDCl+TDCr)/2>17&&(TDCl+TDCr)/2<=44&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))>8&&2*939.6*TMath::Sqrt(0.36/(0.36-(TDCl+TDCr)*(TDCl+TDCr)))/((TDCl+TDCr)*(TDCl+TDCr))<=10");
*/
//draw histograms
	c1->cd();
	c1->SetLogy();
	TDCl->Draw();
//	c1->SaveAs("CFD_datal.png");

	c2->cd();
	c2->SetLogy();
	TDCr->Draw();
//	c2->SaveAs("CFD_datar.png");

	c3->cd();
	c3->SetLogy();
	accTDCl->Draw();
//	c3->SaveAs("CFD_accTDCl.png");

	c4->cd();
	c4->SetLogy();
	accTDCr->Draw();
//	c4->SaveAs("CFD_accTDCr.png");

	c5->cd();
//	c5->SetLogy();
	TDCmean->Draw();
	c5->SaveAs("CFD_TDCmean.png");

	c6->cd();
//	c6->SetLogy();
	accTDCmean->Draw();
	c6->SaveAs("CFD_accmean.png");

//subtract accidental from data
//	if(fout = fopen("Nenergy.txt", "w"))
//	{
		for(Int_t i = LL; i < UL; i++)
		{
			Int_t datatlcount = TDCl->GetBinContent(i+41);
			Int_t datatrcount = TDCr->GetBinContent(i+41);
			Int_t acctlcount = TDCl->GetBinContent(i+41);
			Int_t acctrcount = TDCr->GetBinContent(i+41);
//1.6875 is accidental rate. I achieved this value by equalize data taking time
			looptl = datatlcount-TMath::Nint(1.39726*acctlcount);
			looptr = datatrcount-TMath::Nint(1.39726*acctrcount);

			if(looptl < 0) looptl = TMath::Abs(looptl);
			if(looptr < 0) looptr = TMath::Abs(looptr);

			correctedTDCl->Fill(i/2., looptl);
			correctedTDCr->Fill(i/2., looptr);

			Int_t count = TDCmean->GetBinContent(i+41);
			Int_t acccount = accTDCmean->GetBinContent(i+41);
			loopmean = count-TMath::Nint(1.39726*acccount);

			if(loopmean >= 0) sign = 0;
			if(loopmean < 0)
			{
				sign = 1;
				loopmean = TMath::Abs(loopmean);
			}

			correctedTDCmean->Fill(i/2., loopmean);
			fitTDCmean->Fill(i/2., loopmean);
/*
			if(i > 35 && i < 88)
			{
				for(Int_t j = 0; j < loopmean; j++)
				{
					ItoD = (double) i;
					vel = 1/(ItoD/2.+0.25);
					gamma = TMath::Sqrt(1/(1-(vel/0.3)*(vel/0.3)));
					Energy = (gamma-1)*NM;
					Nenergy->Fill(Energy);
				}
				fprintf(fout, "%f %d \n", Energy, loopmean);
				//xE[i] = NM*tResol*TMath::Power(gamma*vel, 3)/0.09;
			}
*/

		}
//	}
//	fclose(fout);

//draw corrected data
	c7->cd();
	c7->SetLogy();
	correctedTDCl->Draw();
	c7->SaveAs("CFD_acccorrectedl.png");

	c8->cd();
	c8->SetLogy();
	correctedTDCr->Draw();
	c8->SaveAs("CFD_acccorrectedr.png");

	c9->cd();
//	c9->SetLogy();
	c9->SetBottomMargin(0.15);
	gStyle->SetOptStat(0000);
	correctedTDCmean->GetXaxis()->SetTitle("t_{avg} (ns)");
	correctedTDCmean->GetYaxis()->SetTitle("counts");
	correctedTDCmean->GetXaxis()->SetTitleSize(0.053);
	correctedTDCmean->GetYaxis()->SetTitleSize(0.053);
	correctedTDCmean->GetXaxis()->SetTitleOffset(1.0);
	correctedTDCmean->GetYaxis()->SetTitleOffset(1.0);
	correctedTDCmean->Draw();
	correctedTDCmean->Fit("gaus", "", "", 1, 5);
	Double_t g0para = correctedTDCmean->GetFunction("gaus")->GetParError(1);
//this value is resolution of gamma signal. this value is used to make energy error
	cout << g0para << endl;
	c9->SaveAs("CFD_acccorrectedmean.png");
/*
	TF1* myfit = new TF1("myfit", "gaus", 15, 50);

	c10->cd();
	c10->SetBottomMargin(0.15);
	gStyle->SetOptStat(0000);
	fitTDCmean->GetXaxis()->SetTitle("t_{avg} (ns)");
	fitTDCmean->GetYaxis()->SetTitle("counts");
	fitTDCmean->GetXaxis()->SetTitleSize(0.053);
	fitTDCmean->GetYaxis()->SetTitleSize(0.053);
	fitTDCmean->GetXaxis()->SetTitleOffset(1.0);
	fitTDCmean->GetYaxis()->SetTitleOffset(1.0);
	fitTDCmean->Draw();
	fitTDCmean->Fit("myfit", "R");
	Double_t nfitmean = fitTDCmean->GetFunction("myfit")->GetParameter(1);
	Double_t nfitsigma = fitTDCmean->GetFunction("myfit")->GetParameter(2);
	cout << nfitmean << "  " << nfitsigma << endl;
	c10->SaveAs("CFD_Nfit.png");
*/

	TF1* fitf = new TF1("fitf", myfit, -20, 80, 8);
	fitf->SetLineColor(kMagenta);
	TF1* bgf = new TF1("bgf", bg, 6, 20, 2);
	bgf->SetLineColor(kBlue);
	bgf->SetLineStyle(2);
	TF1* ggaussf = new TF1("ggaussf", ggauss, -10, 15, 3);
	ggaussf->SetLineColor(kRed);
	ggaussf->SetLineStyle(2);
	TF1* ngaussf = new TF1("ngaussf", ngauss, 13, 46, 3);
	ngaussf->SetLineColor(kRed);
	ngaussf->SetLineStyle(2);

	c10->cd();
	c10->SetLogy();
	c10->SetBottomMargin(0.15);
	gStyle->SetOptStat(0000);
	fitTDCmean->GetXaxis()->SetTitle("t_{avg} (ns)");
	fitTDCmean->GetYaxis()->SetTitle("Counts");
	fitTDCmean->GetXaxis()->SetTitleSize(0.053);
	fitTDCmean->GetYaxis()->SetTitleSize(0.053);
	fitTDCmean->GetXaxis()->SetTitleOffset(1.0);
	fitTDCmean->GetYaxis()->SetTitleOffset(1.0);
	fitTDCmean->Draw();

	fitf->SetParameters(6000., 3., 2., -500., -1., 800., 30., 3.);
	fitTDCmean->Fit("fitf", "R");
//	fitf->SetParameters(2, 3.);
//	fitf->SetParameters(5, 30.);

//	fitTDCmean->Fit("fitf", "V+", "");

	Double_t par[8];

	fitf->GetParameters(par);
	ggaussf->SetParameters(par);
	ggaussf->Draw("same");
	ngaussf->SetParameters(&par[5]);
	ngaussf->Draw("same");
	bgf->SetParameters(&par[3]);
	bgf->Draw("same");

	TLegend* legend = new TLegend(0.54, 0.65, 0.88, 0.85);
	legend->SetFillColor(0);
	legend->SetBorderSize(0);
//	legend->SetTextFont(72);
	legend->SetTextSize(0.04);
	legend->AddEntry(fitTDCmean, "Data", "lpe");
	legend->AddEntry(bgf, "Background", "l");
	legend->AddEntry(ggaussf, "gamma fit", "l");
	legend->AddEntry(ngaussf, "neutron fit", "l");
	legend->AddEntry(fitf, "total fit", "l");
	legend->Draw();

	c10->SaveAs("CFD_totalfit.png");

	if(fout = fopen("Nenergy.txt", "w"))
	{
		for(Int_t i = 36; i < 87; i++)
		{
			ItoD = (double) i;
			vel = 1./(ItoD/2.+0.25);
			gamma = TMath::Sqrt(1./(1.-(vel/0.3)*(vel/0.3)));
			Energy = (gamma-1)*NM;
			Nenergy->Fill(Energy);
			fitnoise = TMath::Nint(bgf->Eval(ItoD/2.+0.25));
			if(fitnoise < 0) fitnoise = 0;
			hcounts = TMath::Nint(fitTDCmean->GetBinContent(i+40));
			Ecounts = hcounts-fitnoise;
			fprintf(fout, "%f %d \n", Energy, Ecounts);
		}
	}
	fclose(fout);

	c11->cd();
	c11->SetLogy();
	Nenergy->GetXaxis()->SetTitle("E (MeV)");
	Nenergy->GetYaxis()->SetTitle("count");
	Nenergy->Draw();
	c11->SaveAs("CFD_neutronenergy_pre.png");
/*
	c11->SetBottomMargin(0.16);
	c11->Divide(2,4,0.01,0);
//	gStyle->SetOptStat(0000);
	c11->SetLogy();
	c11->cd(1);
	ADCr0->SetTitleSize(0.13, "Y");
	ADCr0->SetLabelSize(0.05, "X");
	ADCr0->SetLabelSize(0.08, "Y");
	ADCr0->GetYaxis()->SetTitleOffset(0.4);
	ADCr0->GetYaxis()->SetTitle("count");
	ADCr0->Draw();
	ADCr0->Fit("gaus", "", "", 170, 250);
	y[0] = ADCr0->GetFunction("gaus")->GetParameter(1);
	yE[0] = ADCr0->GetFunction("gaus")->GetParError(1);

	c11->cd(2);
	ADCr4->SetTitleSize(0.05, "X");
	ADCr4->SetLabelSize(0.05, "X");
	ADCr4->SetLabelSize(0.08, "Y");
	ADCr4->Draw();
	ADCr4->Fit("gaus", "", "", 240, 380);
	y[4] = ADCr4->GetFunction("gaus")->GetParameter(1);
	yE[4] = ADCr4->GetFunction("gaus")->GetParError(1);

	c11->cd(3);
	ADCr1->SetTitleSize(0.09, "X");
	ADCr1->SetLabelSize(0.07, "X");
	ADCr1->SetLabelSize(0.07, "Y");
	ADCr1->Draw();
	ADCr1->Fit("gaus", "", "", 180, 290);
	y[1] = ADCr1->GetFunction("gaus")->GetParameter(1);
	yE[1] = ADCr1->GetFunction("gaus")->GetParError(1);

	c11->cd(4);
	ADCr5->SetTitleSize(0.09, "X");
	ADCr5->SetLabelSize(0.07, "X");
	ADCr5->SetLabelSize(0.07, "Y");
	ADCr5->Draw();
	ADCr5->Fit("gaus", "", "", 260, 450);
	y[5] = ADCr5->GetFunction("gaus")->GetParameter(1);
	yE[5] = ADCr5->GetFunction("gaus")->GetParError(1);

	c11->cd(5);
	ADCr2->SetTitleSize(0.09, "X");
	ADCr2->SetLabelSize(0.07, "X");
	ADCr2->SetLabelSize(0.07, "Y");
	ADCr2->Draw();
	ADCr2->Fit("gaus", "", "", 200, 320);
	y[2] = ADCr2->GetFunction("gaus")->GetParameter(1);
	yE[2] = ADCr2->GetFunction("gaus")->GetParError(1);

	c11->cd(6);
	ADCr6->SetTitleSize(0.09, "X");
	ADCr6->SetLabelSize(0.07, "X");
	ADCr6->SetLabelSize(0.07, "Y");
	ADCr6->Draw();
	ADCr6->Fit("gaus", "", "", 290, 500);
	y[6] = ADCr6->GetFunction("gaus")->GetParameter(1);
	yE[6] = ADCr6->GetFunction("gaus")->GetParError(1);

	c11->cd(7);
	ADCr3->SetTitleSize(0.09, "X");
	ADCr3->SetLabelSize(0.07, "X");
	ADCr3->SetLabelSize(0.07, "Y");
	ADCr3->GetXaxis()->SetTitleOffset(0.7);
	ADCr3->GetXaxis()->SetTitle("ADC");
	ADCr3->Draw();
	ADCr3->Fit("gaus", "", "", 220, 350);
	y[3] = ADCr3->GetFunction("gaus")->GetParameter(1);
	yE[3] = ADCr3->GetFunction("gaus")->GetParError(1);

	c11->cd(8);
	ADCr7->SetTitleSize(0.09, "X");
	ADCr7->SetLabelSize(0.07, "X");
	ADCr7->GetXaxis()->SetTitleOffset(0.7);
	ADCr7->GetXaxis()->SetTitle("ADC");
	ADCr7->Draw();
	ADCr7->Fit("gaus", "", "", 290, 560);
	y[7] = ADCr7->GetFunction("gaus")->GetParameter(1);
	yE[7] = ADCr7->GetFunction("gaus")->GetParError(1);

	c11->SaveAs("CFD_ADC_for_energy.png");

	for(Int_t i = 0; i < 8; i++)
	{
		xE[i] = TMath::Sqrt(8*x[i]*x[i]*x[i]*0.09/NM)*tResol;
	}

	TGraphErrors* ADCenergy = new TGraphErrors(8, x, y, xE, yE);
	c12->cd();
	ADCenergy->SetTitle("CFD");
	ADCenergy->GetYaxis()->SetRangeUser(0, 500);
	ADCenergy->GetXaxis()->SetTitle("energy (MeV)");
	ADCenergy->GetYaxis()->SetTitle("ADC");
	//ADCenergy->SetMarkerStyle(3);
	ADCenergy->SetMarkerSize(3);
	ADCenergy->Draw("AP");
	c12->SaveAs("CFD_ADC_vs_energy.png");
*/
}

Double_t ggauss(Double_t *x, Double_t *par)
{
	if(x[0] >= -10 && x[0] < 15) return par[0]*TMath::Exp(-0.5*((x[0]-par[1])/par[2])*((x[0]-par[1])/par[2]));
	else return 0.;
}

Double_t bg(Double_t *x, Double_t *par)
{
	if(x[0] >= 6 && x[0] < 20) return par[0]*TMath::Exp(par[1]*x[0]);
	else return 0.;
}

Double_t ngauss(Double_t *x, Double_t *par)
{
	if(x[0] >= 13 && x[0] <= 46) return par[0]*TMath::Exp(-0.5*((x[0]-par[1])/par[2])*((x[0]-par[1])/par[2]));
	else return 0.;
}

Double_t myfit(Double_t *x, Double_t *par)
{
	if(x[0] >= -10 && x[0] < 6) return ggauss(x, par);
	else if(x[0] >= 6 && x[0] < 13) return ggauss(x, par)+bg(x, &par[3]);
	else if(x[0] >= 13 && x[0] < 15) return ggauss(x, par)+ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 15 && x[0] < 20) return ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 20 && x[0] <=46) return ngauss(x, &par[5]);
	else return 0.;
}
