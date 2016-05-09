#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TGraphErrors.h>
#include <TF1.h>
#include <TMath.h>
#include <TStyle.h>
#include <TLegend.h>
#include <iostream>

void timedifference_for_draft()
{
	//NoF: Number of Files
	const int NoF = 2;
	const char* filename[NoF] = {"VTD_data_to_tree_t4.root",
										"CFD_data_to_tree_t4.root"};
	const char* treename[9] = {"10cm", "20cm", "30cm", "40cm", "50cm",
										"60cm", "70cm", "80cm", "90cm"};

	Double_t VTD_x[9] = {0.};
	Double_t VTD_y_before[9] = {0.};
	Double_t VTD_y_after[9] = {0.};
//	Double_t y_after[9] = {0.};
	Double_t VTD_xE[9] = {0.};
	Double_t VTD_yE[9] = {0.};

	Double_t CFD_x[9] = {0.};
	Double_t CFD_y_before[9] = {0.};
	Double_t CFD_y_after[9] = {0.};
	Double_t CFD_xE[9] = {0.};
	Double_t CFD_yE[9] = {0.};

	Int_t MaxBin[NoF][9] = {{0}};
	Double_t center[NoF][9] = {{0.}};
	Double_t sigma[NoF][9] = {{0.}};
	Double_t entry[NoF][9] = {{0.}};
	Double_t binentry[NoF][9] = {{0.}};

	//b: before, a: after, c: convers
	Double_t slope_b[NoF] = {0.};
	Double_t slopeE_b[NoF] = {0.};
	Double_t slope_a[NoF] = {0.};
	Double_t slopeE_a[NoF] = {0.};

	Double_t slope_b_c[NoF] = {0.};
	Double_t slopeE_b_c[NoF] = {0.};
	Double_t slope_a_c[NoF] = {0.};
	Double_t slopeE_a_c[NoF] = {0.};

	Double_t intercept_b[NoF] = {0.};
	Double_t interceptE_b[NoF] = {0.};
	Double_t intercept_a[NoF] = {0.};
	Double_t interceptE_a[NoF] = {0.};

	Double_t intercept_b_c[NoF] = {0.};
	Double_t interceptE_b_c[NoF] = {0.};
	Double_t intercept_a_c[NoF] = {0.};
	Double_t interceptE_a_c[NoF] = {0.};

	Double_t resolution_before[NoF] = {0.};
	Double_t resolution_after[NoF] = {0.};

	TFile* fin[NoF];

	TTree* tree[NoF][9];

	TCanvas* cdiff[2];
	TCanvas* cposition_before[NoF];
	TCanvas* cposition_after[NoF];
//	cposition_before->Divide(2,1);
//	TCanvas* cposition_after = new TCanvas("cposition_after", "", 120, 20, 600, 600);

	TH1F* hdiff[NoF][9];

	TLegend* logoleg_before[NoF];
	TLegend* discleg_before[NoF];
	TLegend* logoleg_after[NoF];
	TLegend* discleg_after[NoF];
/*
	TLegend* logoleg_after = new TLegend(0.2, 0.8, 0.3, 0.9);
	logoleg_after->SetFillStyle(0);
	logoleg_after->SetFillColor(0);
	logoleg_after->SetBorderSize(0);
	logoleg_after->SetTextSize(0.07);
	logoleg_after->SetMargin(0);
*/
	for(Int_t i = 0; i < NoF; i++)
	{
		fin[i] = new TFile(filename[i], "READ");
		cdiff[i] = new TCanvas(Form("cdiff_%d", i), "", 100, 0, 900, 900);
		cdiff[i]->Divide(3, 3);
		cposition_before[i] = new TCanvas(Form("cposition_before_%d", i), "", 110, 10, 600, 600);
		cposition_after[i] = new TCanvas(Form("cpsosition_after_%d", i), "", 110, 10, 600, 600);

		logoleg_before[i] = new TLegend(0.25, 0.75, 0.35, 0.85);
		logoleg_before[i]->SetFillStyle(0);
		logoleg_before[i]->SetFillColor(0);
		logoleg_before[i]->SetBorderSize(0);
		logoleg_before[i]->SetTextSize(0.07);
		logoleg_before[i]->SetMargin(0);

		discleg_before[i] = new TLegend(0.7, 0.25, 0.8, 0.35);
		discleg_before[i]->SetFillStyle(0);
		discleg_before[i]->SetFillColor(0);
		discleg_before[i]->SetBorderSize(0);
		discleg_before[i]->SetTextSize(0.07);
		discleg_before[i]->SetMargin(0);

		logoleg_after[i] = new TLegend(0.25, 0.75, 0.35, 0.85);
		logoleg_after[i]->SetFillStyle(0);
		logoleg_after[i]->SetFillColor(0);
		logoleg_after[i]->SetBorderSize(0);
		logoleg_after[i]->SetTextSize(0.07);
		logoleg_after[i]->SetMargin(0);

		discleg_after[i] = new TLegend(0.7, 0.25, 0.8, 0.35);
		discleg_after[i]->SetFillStyle(0);
		discleg_after[i]->SetFillColor(0);
		discleg_after[i]->SetBorderSize(0);
		discleg_after[i]->SetTextSize(0.07);
		discleg_after[i]->SetMargin(0);

		for(Int_t j = 0; j < 9; j++)
		{
			cdiff[i]->cd(j+1);
			hdiff[i][j] = new TH1F(Form("hdff_%d_%d", i, j), "", 60, -15, 15);
			tree[i][j] = (TTree*) fin[i]->Get(treename[j]);
			tree[i][j]->Project(Form("hdff_%d_%d", i, j), "Tl-Tr", "Tl<80&&Tr<80");
			hdiff[i][j]->Draw();

			MaxBin[i][j] = hdiff[i][j]->GetMaximumBin();
			center[i][j] = hdiff[i][j]->GetBinCenter(MaxBin[i][j]);
			hdiff[i][j]->Fit("gaus", "", "", center[i][j]-2, center[i][j]+2);
			if(i == 0)
			{
				VTD_x[j] = (j+1.)*10.;
				VTD_y_before[j] = hdiff[i][j]->GetFunction("gaus")->GetParameter(1);
				VTD_y_after[j] = VTD_y_before[j]+6.;
//		y_after[i] = y_before[i]+6;
				sigma[i][j] = hdiff[i][j]->GetFunction("gaus")->GetParameter(2);
			}
			else
			{
				CFD_x[j] = (j+1.)*10.;
				CFD_y_before[j] = hdiff[i][j]->GetFunction("gaus")->GetParameter(1);
				CFD_y_after[j] = CFD_y_before[j]+6.;
				sigma[i][j] = hdiff[i][j]->GetFunction("gaus")->GetParameter(2);
			}

			for(Int_t k = 0; k < 8; k++)
			{
				binentry[i][j] = hdiff[i][j]->GetBinContent(MaxBin[i][j]-4+k);
				entry[i][j] = entry[i][j]+binentry[i][j];
			}

			if(i == 0)
			{
				VTD_yE[j] = TMath::Sqrt(sigma[i][j]*sigma[i][j]/entry[i][j]);
			}
			else
			{
				CFD_yE[j] = TMath::Sqrt(sigma[i][j]*sigma[i][j]/entry[i][j]);
			}
		}

		cposition_before[i]->cd();

		cposition_before[i]->SetMargin(0.12, 0.05, 0.13, 0.05);
/*
		cposition_before[i]->SetLeftMargin(0.12);
		cposition_before[i]->SetBottomMargin(0.13);
*/
		if(i == 0)
		{
			TGraphErrors* VTD_vel_before = new TGraphErrors(9, VTD_x, VTD_y_before, VTD_xE, VTD_yE);
			VTD_vel_before->SetTitle("");
			VTD_vel_before->GetXaxis()->SetTitle("x (cm)");
			VTD_vel_before->GetYaxis()->SetTitle("#Deltat (ns)");
			VTD_vel_before->GetXaxis()->SetTitleSize(0.07);
			VTD_vel_before->GetYaxis()->SetTitleSize(0.07);
			VTD_vel_before->GetXaxis()->SetTitleOffset(0.85);
			VTD_vel_before->GetYaxis()->SetTitleOffset(0.75);
			VTD_vel_before->GetXaxis()->CenterTitle();
			VTD_vel_before->GetYaxis()->CenterTitle();
			VTD_vel_before->GetXaxis()->SetLabelSize(0.06);
			VTD_vel_before->GetYaxis()->SetLabelSize(0.06);
			VTD_vel_before->SetMarkerStyle(20);
			VTD_vel_before->SetMarkerSize(2);
			VTD_vel_before->Draw("AP");
			VTD_vel_before->Fit("pol1");

			logoleg_before[i]->AddEntry(VTD_vel_before, "(a)", "1");
			logoleg_before[i]->Draw();

			discleg_before[i]->AddEntry(VTD_vel_before, "VTD", "1");
			discleg_before[i]->Draw();

			slope_b[i] = VTD_vel_before->GetFunction("pol1")->GetParameter(1);
			slopeE_b[i] = VTD_vel_before->GetFunction("pol1")->GetParError(1);
			intercept_b[i] = VTD_vel_before->GetFunction("pol1")->GetParameter(0);
			interceptE_b[i] = VTD_vel_before->GetFunction("pol1")->GetParError(0);
		}
		else
		{
			TGraphErrors* CFD_vel_before = new TGraphErrors(9, CFD_x, CFD_y_before, CFD_xE, CFD_yE);
			CFD_vel_before->SetTitle("");
			CFD_vel_before->GetXaxis()->SetTitle("x (cm)");
			CFD_vel_before->GetYaxis()->SetTitle("#Deltat (ns)");
			CFD_vel_before->GetXaxis()->SetTitleSize(0.07);
			CFD_vel_before->GetYaxis()->SetTitleSize(0.07);
			CFD_vel_before->GetXaxis()->SetTitleOffset(0.85);
			CFD_vel_before->GetYaxis()->SetTitleOffset(0.75);
			CFD_vel_before->GetXaxis()->CenterTitle();
			CFD_vel_before->GetYaxis()->CenterTitle();
			CFD_vel_before->GetXaxis()->SetLabelSize(0.06);
			CFD_vel_before->GetYaxis()->SetLabelSize(0.06);
			CFD_vel_before->SetMarkerStyle(20);
			CFD_vel_before->SetMarkerSize(2);
			CFD_vel_before->Draw("AP");
			CFD_vel_before->Fit("pol1");

			logoleg_before[i]->AddEntry(CFD_vel_before, "(b)", "1");
			logoleg_before[i]->Draw();

			discleg_before[i]->AddEntry(CFD_vel_before, "CFD", "1");
			discleg_before[i]->Draw();

			slope_b[i] = CFD_vel_before->GetFunction("pol1")->GetParameter(1);
			slopeE_b[i] = CFD_vel_before->GetFunction("pol1")->GetParError(1);
			intercept_b[i] = CFD_vel_before->GetFunction("pol1")->GetParameter(0);
			interceptE_b[i] = CFD_vel_before->GetFunction("pol1")->GetParError(0);
		}

		cposition_after[i]->cd();

		cposition_after[i]->SetMargin(0.12, 0.05, 0.13, 0.05);
/*
		cposition_after[i]->SetLeftMargin(0.12);
		cposition_after[i]->SetBottomMargin(0.13);
*/
		if(i == 0)
		{
			TGraphErrors* VTD_vel_after = new TGraphErrors(9, VTD_x, VTD_y_after, VTD_xE, VTD_yE);
			VTD_vel_after->SetTitle("");
			VTD_vel_after->GetXaxis()->SetTitle("x (cm)");
			VTD_vel_after->GetYaxis()->SetTitle("#Deltat (ns)");
			VTD_vel_after->GetXaxis()->SetTitleSize(0.07);
			VTD_vel_after->GetYaxis()->SetTitleSize(0.07);
			VTD_vel_after->GetXaxis()->SetTitleOffset(0.85);
			VTD_vel_after->GetYaxis()->SetTitleOffset(0.75);
			VTD_vel_after->GetXaxis()->CenterTitle();
			VTD_vel_after->GetYaxis()->CenterTitle();
			VTD_vel_after->GetXaxis()->SetLabelSize(0.06);
			VTD_vel_after->GetYaxis()->SetLabelSize(0.06);
			VTD_vel_after->SetMarkerStyle(20);
			VTD_vel_after->SetMarkerSize(2);
			VTD_vel_after->Draw("AP");
			VTD_vel_after->Fit("pol1");

			logoleg_after[i]->AddEntry(VTD_vel_after, "(a)", "1");
			logoleg_after[i]->Draw();

			discleg_after[i]->AddEntry(VTD_vel_after, "VTD", "1");
			discleg_after[i]->Draw();

			slope_a[i] = VTD_vel_after->GetFunction("pol1")->GetParameter(1);
			slopeE_a[i] = VTD_vel_after->GetFunction("pol1")->GetParError(1);
			intercept_a[i] = VTD_vel_after->GetFunction("pol1")->GetParameter(0);
			interceptE_a[i] = VTD_vel_after->GetFunction("pol1")->GetParError(0);
		}
		else
		{
			TGraphErrors* CFD_vel_after = new TGraphErrors(9, CFD_x, CFD_y_after, CFD_xE, CFD_yE);
			CFD_vel_after->SetTitle("");
			CFD_vel_after->GetXaxis()->SetTitle("x (cm)");
			CFD_vel_after->GetYaxis()->SetTitle("#Deltat (ns)");
			CFD_vel_after->GetXaxis()->SetTitleSize(0.07);
			CFD_vel_after->GetYaxis()->SetTitleSize(0.07);
			CFD_vel_after->GetXaxis()->SetTitleOffset(0.85);
			CFD_vel_after->GetYaxis()->SetTitleOffset(0.75);
			CFD_vel_after->GetXaxis()->CenterTitle();
			CFD_vel_after->GetYaxis()->CenterTitle();
			CFD_vel_after->GetXaxis()->SetLabelSize(0.06);
			CFD_vel_after->GetYaxis()->SetLabelSize(0.06);
			CFD_vel_after->SetMarkerStyle(20);
			CFD_vel_after->SetMarkerSize(2);
			CFD_vel_after->Draw("AP");
			CFD_vel_after->Fit("pol1");

			logoleg_after[i]->AddEntry(CFD_vel_after, "(b)", "1");
			logoleg_after[i]->Draw();

			discleg_after[i]->AddEntry(CFD_vel_after, "CFD", "1");
			discleg_after[i]->Draw();

			slope_a[i] = CFD_vel_after->GetFunction("pol1")->GetParameter(1);
			slopeE_a[i] = CFD_vel_after->GetFunction("pol1")->GetParError(1);
			intercept_a[i] = CFD_vel_after->GetFunction("pol1")->GetParameter(0);
			interceptE_a[i] = CFD_vel_after->GetFunction("pol1")->GetParError(0);
		}
//	TGraphErrors* vel_after = new TGraphErrors(9, x, y_after, xE, yE);

		slope_b_c[i] = 1/slope_b[i];
		slopeE_b_c[i] = slopeE_b[i]/(slope_b[i]*slope_b[i]);
		intercept_b_c[i] = -intercept_b[i]/slope_b[i];
		interceptE_b_c[i] = TMath::Sqrt(TMath::Power(slopeE_b[i]*intercept_b[i]/(slope_b[i]*slope_b[i]), 2)+TMath::Power(interceptE_b[i]/slope_b[i],2));

		if(i == 0)
		{
			resolution_before[i] = TMath::Sqrt(TMath::Power(sigma[i][4]*slope_b_c[i], 2)+TMath::Power(VTD_y_before[4]*slopeE_b_c[i], 2)+TMath::Power(interceptE_b_c[i], 2));
		}
		else
		{
			resolution_before[i] = TMath::Sqrt(TMath::Power(sigma[i][4]*slope_b_c[i], 2)+TMath::Power(CFD_y_before[4]*slopeE_b_c[i], 2)+TMath::Power(interceptE_b_c[i], 2));
		}
/*
		cout << "before: " << slope_b_c[i] << " + " << slopeE_b_c[i] << endl;
		cout << "before: " << intercept_b_c[i] << " + " << interceptE_b_c[i] << endl;
		cout << "resolution before: " << resolution_before[i] << endl;
*/

		cposition_before[i]->SaveAs(Form("fig2_before_%d.pdf", i));
//	cposition_before->SaveAs("VTD_vel_before.png");

		slope_a_c[i] = 1/slope_a[i];
		slopeE_a_c[i] = slopeE_a[i]/(slope_a[i]*slope_a[i]);
		intercept_a_c[i] = -intercept_a[i]/slope_a[i];
		interceptE_a_c[i] = TMath::Sqrt(TMath::Power(slopeE_a[i]*intercept_a[i]/(slope_a[i]*slope_a[i]), 2)+TMath::Power(interceptE_a[i]/slope_a[i],2));

		if(i == 0)
		{
			resolution_after[i] = TMath::Sqrt(TMath::Power(sigma[i][4]*slope_a_c[i], 2)+TMath::Power(VTD_y_after[4]*slopeE_a_c[i], 2)+TMath::Power(interceptE_a_c[i], 2));
		}
		else
		{
			resolution_after[i] = TMath::Sqrt(TMath::Power(sigma[i][4]*slope_a_c[i], 2)+TMath::Power(CFD_y_after[4]*slopeE_a_c[i], 2)+TMath::Power(interceptE_a_c[i], 2));
		}
		cout << "after: " << slope_a_c[i] << " + " << slopeE_a_c[i] << endl;
		cout << "after: " << intercept_a_c[i] << " + " << interceptE_a_c[i] << endl;
		cout << "resolution after: " << resolution_after[i] << endl;

		cposition_after[i]->SaveAs(Form("fig2_after_%d.pdf", i));
	}
//	cposition_before->SaveAs("VTD_vel_before.png");
/*
	cposition_after->cd();
	cposition_after->SetLeftMargin(0.15);
	cposition_after->SetBottomMargin(0.15);
	vel_after->SetTitle("");
	vel_after->GetXaxis()->SetTitle("x (cm)");
	vel_after->GetYaxis()->SetTitle("#Deltat (ns)");
	vel_after->GetXaxis()->SetTitleSize(0.07);
	vel_after->GetYaxis()->SetTitleSize(0.07);
	vel_after->GetXaxis()->SetTitleOffset(0.7);

	cposition_after->cd();
	cposition_after->SetLeftMargin(0.15);
	cposition_after->SetBottomMargin(0.15);
	vel_after->SetTitle("");
	vel_after->GetXaxis()->SetTitle("x (cm)");
	vel_after->GetYaxis()->SetTitle("#Deltat (ns)");
	vel_after->GetXaxis()->SetTitleSize(0.07);
	vel_after->GetYaxis()->SetTitleSize(0.07);
	vel_after->GetXaxis()->SetTitleOffset(0.7);
	vel_after->GetYaxis()->SetTitleOffset(0.7);
	vel_after->GetXaxis()->CenterTitle();
	vel_after->GetYaxis()->CenterTitle();
	vel_after->SetMarkerStyle(20);
	vel_after->SetMarkerSize(2);
	vel_after->Draw("AP");
	vel_after->Fit("pol1");

	logoleg_after->AddEntry(vel_after, "(a)", "1");
	logoleg_after->Draw();

	slope_a = vel_after->GetFunction("pol1")->GetParameter(1);
	slopeE_a = vel_after->GetFunction("pol1")->GetParError(1);
	intercept_a = vel_after->GetFunction("pol1")->GetParameter(0);
	interceptE_a = vel_after->GetFunction("pol1")->GetParError(0);

	slope_a_c = 1/slope_a;
	slopeE_a_c = slopeE_a/(slope_a*slope_a);
	intercept_a_c = -intercept_a/slope_a;
	interceptE_a_c = TMath::Sqrt(TMath::Power(slopeE_a*intercept_a/(slope_a*slope_a), 2)+TMath::Power(interceptE_a/slope_a,2));
*/
//	resolution_after = TMath::Sqrt(TMath::Power(sigma[4]*slope_a_c, 2)+TMath::Power(y_after[4]*slopeE_a_c, 2)+TMath::Power(interceptE_a_c, 2));

//	cposition_after->SaveAs("VTD_vel_after.png");
//	cposition_after->SaveAs("VTD_vel_after.pdf");

//	cout << "after: " << slope_a_c << " + " << slopeE_a_c << endl;
//	cout << "after: " << intercept_a_c << " + " << interceptE_a_c << endl;

//	cout << "resolution after: " << resolution_after << endl;
}
