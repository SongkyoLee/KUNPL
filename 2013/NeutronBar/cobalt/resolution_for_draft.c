#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TF1.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLegend.h>

void resolution_for_draft()
{
	const int NoF = 2;
	const char* file_name[NoF] = {"VTD_TWCdata.root",
										"CFD_TWCdata.root"};
	const char* logoname[NoF] = {"(a)", "(b)"};

	//define variables
	Int_t MaxBin[NoF] = {0};
	Int_t center[NoF] = {0};
	Double_t mean[NoF] = {0};
	Double_t sigma[NoF] = {0};

	//get file
	TFile* fTWC[NoF];

	//get tree from file
	TTree* treeTWC[NoF];

	//define canvas, histogram, legend
	TCanvas* c1[NoF];
	gStyle->SetOptStat(0000);
//	c1->Divide(2, 1, 0.005, 0.01);

	TH1F* TWCresol[NoF];

	TLegend* resolleg[NoF];

	TLegend* logoleg[NoF];

	//project tree to histogram
	for(Int_t i = 0; i < NoF; i++)
	{
		fTWC[i] = new TFile(file_name[i], "READ");
		treeTWC[i] = (TTree*) fTWC[i]->Get("50cm");
		TWCresol[i] = new TH1F(Form("TWCresol_%d", i), "", 32, -8, 8);
		treeTWC[i]->Project(Form("TWCresol_%d", i), "(Tl+Tr)/2", "");
		c1[i] = new TCanvas(Form("c_%d", i), "", 100, 0, 600, 600);

		resolleg[i] = new TLegend(0.63, 0.73, 0.93, 0.83);
		resolleg[i]->SetFillStyle(0);
		resolleg[i]->SetFillColor(0);
		resolleg[i]->SetBorderSize(0);
		resolleg[i]->SetTextSize(0.05);
		resolleg[i]->SetTextAlign(32);
		resolleg[i]->SetMargin(0);

		logoleg[i] = new TLegend(0.25, 0.75, 0.35, 0.85);
		logoleg[i]->SetFillStyle(0);
		logoleg[i]->SetFillColor(0);
		logoleg[i]->SetBorderSize(0);
		logoleg[i]->SetTextSize(0.07);
		logoleg[i]->SetMargin(0);

		//draw
		c1[i]->cd();
		c1[i]->SetMargin(0.14, 0.05, 0.12, 0.05);
/*
		c1[i]->SetLeftMargin(0.15);
		c1[i]->SetBottomMargin(0.15);
*/
		TWCresol[i]->GetXaxis()->SetTitle("t_{avg} (ns)");
		TWCresol[i]->GetYaxis()->SetTitle("Counts");
		TWCresol[i]->GetXaxis()->SetTitleSize(0.06);
		TWCresol[i]->GetYaxis()->SetTitleSize(0.065);
		TWCresol[i]->GetXaxis()->SetTitleOffset(0.85);
		TWCresol[i]->GetYaxis()->SetTitleOffset(1.1);
		TWCresol[i]->GetXaxis()->CenterTitle();
		TWCresol[i]->GetYaxis()->CenterTitle();
		TWCresol[i]->GetXaxis()->SetLabelSize(0.055);
		TWCresol[i]->GetYaxis()->SetLabelSize(0.055);
		if(i == 0) TWCresol[i]->GetYaxis()->SetRangeUser(0, 1200);
		TWCresol[i]->Draw();

		//fit and get parameters
		MaxBin[i] = TWCresol[i]->GetMaximumBin();
		center[i] = TWCresol[i]->GetBinCenter(MaxBin[i]);
		if(i == 0) TWCresol[i]->Fit("gaus", "", "", center[i]-1.5, center[i]+2.0);
		else TWCresol[i]->Fit("gaus", "", "", center[i]-1.5, center[i]+1.5);
		mean[i] = TWCresol[i]->GetFunction("gaus")->GetParameter(1);
		sigma[i] = TWCresol[i]->GetFunction("gaus")->GetParameter(2);

		resolleg[i]->AddEntry(TWCresol[i], Form("<t_{avg}>: %.3f ns", mean[i]), "1");
		resolleg[i]->AddEntry(TWCresol[i], Form("#sigma: %.3f ns", sigma[i]), "1");
		resolleg[i]->Draw();

		logoleg[i]->AddEntry(TWCresol[i], logoname[i], "1");
		logoleg[i]->Draw();

		c1[i]->SaveAs(Form("fig_03_%d.pdf", i));
	}
}
