#include <TROOT.h>
#include <TStyle.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TMath.h>
#include <TLegend.h>

//define fit functions bg: back ground, g: gamma, n: neutron
Double_t bg(Double_t* x, Double_t* par);
Double_t ggauss(Double_t* x, Double_t* par);
Double_t ngauss(Double_t* x, Double_t* par);
Double_t myfit(Double_t* x, Double_t* par);

void timedistribution_for_draft_exp()
{
//define variables
	//UL = upper limit, LL = lower limit. because histogram x axis unit(bin width) is 0.5, multiply 2
	// If time range is from -20 to 70,
	// Int_t i range is from -40 to 140 with 180 bins.
	const Int_t LL = -20*2;
	const Int_t UL = 70*2; //KYO : changed upper limit

	Int_t datacount[UL-LL] = {0};
	Int_t acccount[UL-LL] = {0};
	Int_t loop[UL-LL] = {0};
	Int_t sign[UL-LL] = {0};

	Double_t par[8];
//define file, tree...
	TFile* fin = new TFile("corrected_tree.root");

	TTree* californium = (TTree*) fin->Get("californium");
	TTree* accidental = (TTree*) fin->Get("acccalifornium");

	TCanvas* c_before = new TCanvas("c_before", "", 100, 0, 600, 1200);
	TCanvas* c_after = new TCanvas("c_after", "", 110, 10, 600, 600);
//	TH1F* hdata = new TH1F("hdata", "", 200, -20, 80);
//	TH1F* hacc = new TH1F("hacc", "", 200, -20, 80);
//	TH1F* hcorrect = new TH1F("hcorrect", "", 200, -20, 80);
	TH1F* hdata = new TH1F("hdata", "", 180, -20, 70);
	TH1F* hacc = new TH1F("hacc", "", 180, -20, 70);
	TH1F* hcorrect = new TH1F("hcorrect", "", 180, -20, 70);

	TF1* fitf = new TF1("fitf", myfit, -20, 80, 8);
	fitf->SetLineColor(kMagenta);
	TF1* bgf = new TF1("bgf", bg, 6, 25, 2);
	bgf->SetLineColor(3);
	bgf->SetLineStyle(9);
	TF1* ggaussf = new TF1("ggaussf", ggauss, -10, 15, 3);
	ggaussf->SetLineColor(4);
	ggaussf->SetLineStyle(2);
	TF1* ngaussf = new TF1("ngaussf", ngauss, 13, 46, 3);
	ngaussf->SetLineColor(kRed);
	ngaussf->SetLineStyle(2);

	TLegend* funcleg = new TLegend(0.6, 0.7, 0.9, 0.9);
	funcleg->SetFillStyle(0);
	funcleg->SetFillColor(0);
	funcleg->SetBorderSize(0);
	funcleg->SetTextSize(0.04);
	funcleg->SetMargin(0.47);
/*
	TLegend* logoleg = new TLegend(0.78, 0.25, 0.88, 0.35);
	logoleg->SetFillStyle(0);
	logoleg->SetFillColor(0);
	logoleg->SetBorderSize(0);
	logoleg->SetTextSize(0.07);
	logoleg->SetMargin(0);
*/
//	TLegend* gammaleg = new TLegend(0.25, 0.8, 0.35, 0.9);
	TLegend* gammaleg = new TLegend(0.30, 0.8, 0.40, 0.9);
	gammaleg->SetFillStyle(0);
	gammaleg->SetFillColor(0);
	gammaleg->SetBorderSize(0);
	gammaleg->SetTextSize(0.06);
	gammaleg->SetMargin(0);

//	TLegend* neutronleg = new TLegend(0.45, 0.7, 0.55, 0.8);
	TLegend* neutronleg = new TLegend(0.55, 0.6, 0.65, 0.7);
	neutronleg->SetFillStyle(0);
	neutronleg->SetFillColor(0);
	neutronleg->SetBorderSize(0);
	neutronleg->SetTextSize(0.06);
	neutronleg->SetMargin(0);

	californium->Project("hdata", "(TDCl+TDCr)/2", "TDCl<70&&TDCr<70"); //KYO
	accidental->Project("hacc", "(accTDCl+accTDCr)/2", "accTDCl<70&&accTDCr<70");

	c_before->Divide(1,2);
	c_before->cd(1);
	hdata->Draw();
	c_before->cd(2);
	hacc->Draw();

	// Accidental rate achieved to equalize data-taking time for data and accidental
	// (Thus, Total data taking time/ total accidental taking time)
	Double_t accRate = 8.35671;

	for(Int_t i = LL; i < UL; i++)
	{
		datacount[i-LL] = hdata->GetBinContent(i+41);
		acccount[i-LL] = hacc->GetBinContent(i+41);
		loop[i-LL] = datacount[i-LL]-TMath::Nint(accRate*acccount[i-LL]);

		if(loop[i-LL] >= 0) sign[i-LL] = 0;
		else
		{
			sign[i-LL] = 1;
	//		loop[i-LL] = TMath::Abs(loop[i-LL]);
			loop[i-LL] = 0;
		}
		hcorrect->Fill(i/2., loop[i-LL]);
	}

	c_after->cd();
	c_after->SetLogy();
	c_after->SetMargin(0.14, 0.05, 0.14, 0.05);
/*
	c_after->SetLeftMargin(0.15);
	c_after->SetBottomMargin(0.15);
*/
	gStyle->SetOptStat(0000);
	hcorrect->SetLineColor(1);
	hcorrect->GetXaxis()->SetTitle("t_{avg} (ns)");
	hcorrect->GetYaxis()->SetTitle("Counts");
	hcorrect->GetXaxis()->SetTitleSize(0.07);
	hcorrect->GetYaxis()->SetTitleSize(0.07);
	hcorrect->GetXaxis()->SetTitleOffset(0.85);
	hcorrect->GetYaxis()->SetTitleOffset(1.0);
	hcorrect->GetXaxis()->CenterTitle();
	hcorrect->GetYaxis()->CenterTitle();
	hcorrect->GetXaxis()->SetLabelSize(0.06);
	hcorrect->GetYaxis()->SetLabelSize(0.06);

	hcorrect->Draw();

//	fitf->SetParameters(6000., 3., 2., -500., -1., 800., 30., 3.);
//	fitf->SetParameters(8500., 4., 2., -400., -1., 1400., 40., 6.);
	fitf->SetParameters(8500., 4., 2., -700., 50., 1400., 40., 6.);
	hcorrect->Fit("fitf", "R");

	fitf->GetParameters(par);
	ggaussf->SetParameters(par);
	ggaussf->Draw("same");
	ngaussf->SetParameters(&par[5]);
	ngaussf->Draw("same");
	bgf->SetParameters(&par[3]);
	bgf->Draw("same");

	funcleg->AddEntry(hcorrect, "Data", "lpe");
	funcleg->AddEntry(bgf, "Background", "l");
	funcleg->AddEntry(ggaussf, "#gamma or n", "l");
//	funcleg->AddEntry(ngaussf, "Neutron", "l");
	funcleg->AddEntry(fitf, "Total", "l");
	funcleg->Draw();

//	logoleg->AddEntry(hcorrect, "(a)", "1");
//	logoleg->Draw();

	gammaleg->AddEntry(hcorrect, "#gamma", "1");
	gammaleg->Draw();

	neutronleg->AddEntry(hcorrect, "n", "1");
	neutronleg->Draw();

	c_after->SaveAs("CFD_totalfit_exp.pdf");
}

Double_t ggauss(Double_t *x, Double_t* par)
{
	if(x[0] >= -10 && x[0] < 20) return par[0]*TMath::Exp(-0.5*((x[0]-par[1])/par[2])*((x[0]-par[1])/par[2]));
	else return 0.;
}

Double_t bg(Double_t* x, Double_t* par)
{
	if(x[0] >= 9 && x[0] < 26) return par[0]*TMath::Exp(par[1]*x[0]);
	else return 0.;
}

Double_t ngauss(Double_t* x, Double_t* par)
{
	if(x[0] >= 15 && x[0] <= 60) return par[0]*TMath::Exp(-0.5*((x[0]-par[1])/par[2])*((x[0]-par[1])/par[2]));
	else return 0.;
}

Double_t myfit(Double_t* x, Double_t* par)
{
	if(x[0] >= -10 && x[0] < 9) return ggauss(x, par);
	else if(x[0] >= 9 && x[0] < 15) return ggauss(x, par)+bg(x, &par[3]);
	else if(x[0] >= 15 && x[0] < 20) return ggauss(x, par)+ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 20 && x[0] < 26) return ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 26 && x[0] <= 60) return ngauss(x, &par[5]);
	else return 0.;
/* KYO
	if(x[0] >= -10 && x[0] < 9) return ggauss(x, par);
	else if(x[0] >= 9 && x[0] < 16) return ggauss(x, par)+bg(x, &par[3]);
	else if(x[0] >= 16 && x[0] < 17) return ggauss(x, par)+ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 17 && x[0] < 26) return ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 26 && x[0] <= 60) return ngauss(x, &par[5]);
	else return 0.;
*/
/* Ben
	if(x[0] >= -10 && x[0] < 9) return ggauss(x, par);
	else if(x[0] >= 9 && x[0] < 15) return ggauss(x, par)+bg(x, &par[3]);
	else if(x[0] >= 15 && x[0] < 20) return ggauss(x, par)+ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 20 && x[0] < 26) return ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 26 && x[0] <= 60) return ngauss(x, &par[5]);
	else return 0.;
*/
/* Kisoo
	if(x[0] >= -10 && x[0] < 6) return ggauss(x, par);
	else if(x[0] >= 6 && x[0] < 13) return ggauss(x, par)+bg(x, &par[3]);
	else if(x[0] >= 13 && x[0] < 15) return ggauss(x, par)+ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 15 && x[0] < 25) return ngauss(x, &par[5])+bg(x, &par[3]);
	else if(x[0] >= 25 && x[0] <= 46) return ngauss(x, &par[5]);
	else return 0.;
*/
}
