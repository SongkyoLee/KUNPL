/////////////////////////////////////////////////////////////////////////
//This file calculates the Time Walk Correction factor.                //
//1. divide charge sector and draw time for each sector to see mean.   //
//2. calculate variance from mean, and entries.                        //
//3. draw mean and variance of time in full charge sector.             //
//4. fit the gragh to get the Time Walk Correction factor.             //
/////////////////////////////////////////////////////////////////////////

#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TH1.h>
#include <TF1.h>
#include <TStyle.h>
#include <TMath.h>
#include <TLegend.h>

void TWC_for_draft()
{
//define variables
	//NoF: Number of File
	const Int_t NoF = 2;
	//want to divide charge from 80 to 160 for left, from 70 to 150 for right by 80 sectors
	const Int_t VTD_sector = 70;
	const Int_t CFD_sector = 80;

	Int_t start_time[NoF][2] = {{70, 50}, {80, 70}};

	Double_t Tl[NoF];
	Double_t Tr[NoF];
	Double_t Al[NoF];
	Double_t Ar[NoF];

/*
	Double_t slope[NoF][2] = {{0.}};
	Double_t intercept[NoF][2] = {{0.}};
*/
	const char* file_name[NoF] = {"VTD_data_to_tree_t4.root",
											"CFD_data_to_tree_t4.root"};

	const char* xtitle[2] = {"Q_{L} (Ch.)", "Q_{R} (Ch.)"};
	const char* ytitle[2] = {"t_{L} (ns)", "t_{R} (ns)"};

	const char* logoname[NoF][2] = {{"(a)", "(b)"}, {"(c)", "(d)"}};
	const char* discname[NoF] = {"VTD", "CFD"};

	Double_t VTD_mean[2][VTD_sector] = {{0.}};
	Double_t VTD_entry[2][VTD_sector] = {{0.}};
	Double_t VTD_variance[2][VTD_sector] = {{0.}};

	Double_t CFD_mean[2][CFD_sector] = {{0.}};
	Double_t CFD_entry[2][CFD_sector] = {{0.}};
	Double_t CFD_variance[2][CFD_sector] = {{0.}};

	Double_t VTD_xl[VTD_sector] = {0.};
	Double_t VTD_yl[VTD_sector] = {0.};
	Double_t VTD_xlE[VTD_sector] = {0.};
	Double_t VTD_ylE[VTD_sector] = {0.};

	Double_t VTD_xr[VTD_sector] = {0.};
	Double_t VTD_yr[VTD_sector] = {0.};
	Double_t VTD_xrE[VTD_sector] = {0.};
	Double_t VTD_yrE[VTD_sector] = {0.};

	Double_t CFD_xl[CFD_sector] = {0.};
	Double_t CFD_yl[CFD_sector] = {0.};
	Double_t CFD_xlE[CFD_sector] = {0.};
	Double_t CFD_ylE[CFD_sector] = {0.};

	Double_t CFD_xr[CFD_sector] = {0.};
	Double_t CFD_yr[CFD_sector] = {0.};
	Double_t CFD_xrE[CFD_sector] = {0.};
	Double_t CFD_yrE[CFD_sector] = {0.};

//define input and output
	TFile* fin[NoF];

	TTree* treein[NoF];

	TCanvas* c[NoF][2];
	TCanvas* cfit[NoF][2];
//	cfit->Divide(2, 2, 0.005, 0.005);

	TH1F* VTD_h[2][VTD_sector];
	TH1F* CFD_h[2][CFD_sector];

	TGraphErrors* ge[NoF][2];

	TLegend* logoleg[NoF][2];
	TLegend* discleg[NoF][2];

	for(Int_t i = 0; i < NoF; i ++)
	{
		fin[i] = new TFile(file_name[i]);

		treein[i] = (TTree*) fin[i]->Get("50cm");
		treein[i]->SetBranchAddress("Tl", &Tl[i]);
		treein[i]->SetBranchAddress("Tr", &Tr[i]);
		treein[i]->SetBranchAddress("Al", &Al[i]);
		treein[i]->SetBranchAddress("Ar", &Ar[i]);

		for(Int_t j = 0; j < 2; j++)
		{
			c[i][j] = new TCanvas(Form("c_%d_%d", i, j), "", 100, 0, 1800, 1800);

			c[i][j]->Divide(8, 9);
			cfit[i][j] = new TCanvas(Form("cfit_%d_%d", i, j), "", 100, 0, 600, 600);

			logoleg[i][j] = new TLegend(0.25, 0.75, 0.35, 0.85);
			logoleg[i][j]->SetFillStyle(0);
			logoleg[i][j]->SetFillColor(0);
			logoleg[i][j]->SetBorderSize(0);
			logoleg[i][j]->SetTextSize(0.07);
			logoleg[i][j]->SetMargin(0);

			discleg[i][j] = new TLegend(0.75, 0.2, 0.95, 0.3);
			discleg[i][j]->SetFillStyle(0);
			discleg[i][j]->SetFillColor(0);
			discleg[i][j]->SetBorderSize(0);
			discleg[i][j]->SetTextSize(0.075);
			discleg[i][j]->SetMargin(0);
//			discleg[i][j]->SetTextAngle(-90);
			//i == 0: VTD, i == 1: CFD
			if(i == 0)
			{
				for(Int_t k = 0; k < VTD_sector; k++)
				{
					//define histogram
					VTD_h[j][k] = new TH1F(Form("VTD_h_%d_%d", j, k), "", 30, 5, 20);

					//fill tree to histogram and draw
					//j == 0: left, j == 1: right
					if(j == 0)
					{
						treein[i]->Project(Form("VTD_h_%d_%d", j, k), "Tl", Form("Al>%d&&Al<=%d&&Tl<50", start_time[i][j]+k, start_time[i][j]+k+1));
					}
					else
					{
						treein[i]->Project(Form("VTD_h_%d_%d", j, k), "Tr", Form("Ar>%d&&Ar<=%d&&Tr<50", start_time[i][j]+k, start_time[i][j]+k+1));
					}
					c[i][j]->cd(k+1);

					VTD_h[j][k]->Draw();
					VTD_mean[j][k] = VTD_h[j][k]->GetMean();
					VTD_entry[j][k] = VTD_h[j][k]->GetEntries();

					for(Int_t l = 0; l < 4000; l++)
					{
						treein[i]->GetEntry(l);

						if(j == 0)
						{
							if(Al[i]>start_time[i][j]+k && Al[i]<=start_time[i][j]+k+1)
							{
								VTD_variance[j][k] = VTD_variance[j][k]+(Tl[i]-VTD_mean[j][k])*(Tl[i]-VTD_mean[j][k])/VTD_entry[j][k];
							}
						}
						else
						{
							if(Ar[i]>start_time[i][j]+k && Ar[i]<=start_time[i][j]+k+1)
							{
								VTD_variance[j][k] = VTD_variance[j][k]+(Tr[i]-VTD_mean[j][k])*(Tr[i]-VTD_mean[j][k])/VTD_entry[j][k];
							}
						}
					}

					if(j == 0)
					{
						VTD_xl[k] = (double)start_time[i][j]+(double)k+0.5;
						VTD_yl[k] = VTD_mean[j][k];
						VTD_ylE[k] = TMath::Sqrt(VTD_variance[j][k]/(VTD_entry[j][k]-1));
					}
					else
					{
						VTD_xr[k] = (double)start_time[i][j]+(double)k+0.5;
						VTD_yr[k] = VTD_mean[j][k];
						VTD_yrE[k] = TMath::Sqrt(VTD_variance[j][k]/(VTD_entry[j][k]-1));
					}
				}
				//end of k loop
				if(j == 0) ge[i][j] = new TGraphErrors(VTD_sector, VTD_xl, VTD_yl, VTD_xlE, VTD_ylE);
				else ge[i][j] = new TGraphErrors(VTD_sector, VTD_xr, VTD_yr, VTD_xrE, VTD_yrE);
			}
			else
			{
				for(Int_t k = 0; k < CFD_sector; k++)
				{
					CFD_h[j][k] = new TH1F(Form("CFD_h_%d_%d", j, k), "", 30, 5, 20);
					if(j == 0)
					{
						treein[i]->Project(Form("CFD_h_%d_%d", j, k), "Tl", Form("Al>%d&&Al<=%d&&Tl<50", start_time[i][j]+k, start_time[i][j]+k+1));
					}
					else
					{
						treein[i]->Project(Form("CFD_h_%d_%d", j, k), "Tr", Form("Ar>%d&&Ar<=%d&&Tr<50", start_time[i][j]+k, start_time[i][j]+k+1));
					}

					c[i][j]->cd(k+1);

					CFD_h[j][k]->Draw();
					CFD_mean[j][k] = CFD_h[j][k]->GetMean();
					CFD_entry[j][k] = CFD_h[j][k]->GetEntries();

					for(Int_t l = 0; l < 4000; l++)
					{
						treein[i]->GetEntry(l);

						if(j == 0)
						{
							if(Al[i]>start_time[i][j]+k && Al[i]<=start_time[i][j]+k+1)
							{
								CFD_variance[j][k] = CFD_variance[j][k]+(Tl[i]-CFD_mean[j][k])*(Tl[i]-CFD_mean[j][k])/CFD_entry[j][k];
							}
						}
						else
						{
							if(Ar[i]>start_time[i][j]+k && Ar[i]<=start_time[i][j]+k+1)
							{
								CFD_variance[j][k] = CFD_variance[j][k]+(Tr[i]-CFD_mean[j][k])*(Tr[i]-CFD_mean[j][k])/CFD_entry[j][k];
							}
						}
					}

					if(j == 0)
					{
						CFD_xl[k] = (double)start_time[i][j]+(double)k+0.5;
						CFD_yl[k] = CFD_mean[j][k];
						CFD_ylE[k] = TMath::Sqrt(CFD_variance[j][k]/(CFD_entry[j][k]-1));
					}
					else
					{
						CFD_xr[k] = (double)start_time[i][j]+(double)k+0.5;
						CFD_yr[k] = CFD_mean[j][k];
						CFD_yrE[k] = TMath::Sqrt(CFD_variance[j][k]/(CFD_entry[j][k]-1));
					}
				}
				//end of k loop
				if(j == 0) ge[i][j] = new TGraphErrors(CFD_sector, CFD_xl, CFD_yl, CFD_xlE, CFD_ylE);
				else ge[i][j] = new TGraphErrors(CFD_sector, CFD_xr, CFD_yr, CFD_xrE, CFD_yrE);
			}

			//draw histogram and get mean and entry from the histogram
			

				//calculate variance
				//put values for TgraphErrors

//			cfit->cd(i*2+j+1);

			cfit[i][j]->cd();
			cfit[i][j]->SetMargin(0.12, 0.05, 0.13, 0.05);
/*
			cfit[i][j]->SetLeftMargin(0.15);
			cfit[i][j]->SetBottomMargin(0.15);
*/
			ge[i][j]->SetTitle("");
			ge[i][j]->GetYaxis()->SetRangeUser(0, 25);
			ge[i][j]->GetXaxis()->SetTitle(xtitle[j]);
			ge[i][j]->GetYaxis()->SetTitle(ytitle[j]);
			ge[i][j]->GetXaxis()->SetTitleSize(0.06);
			ge[i][j]->GetYaxis()->SetTitleSize(0.06);
			ge[i][j]->GetXaxis()->SetTitleOffset(0.9);
			ge[i][j]->GetYaxis()->SetTitleOffset(0.85);
			ge[i][j]->GetXaxis()->CenterTitle();
			ge[i][j]->GetYaxis()->CenterTitle();
			ge[i][j]->GetXaxis()->SetLabelSize(0.055);
			ge[i][j]->GetYaxis()->SetLabelSize(0.055);
			ge[i][j]->Draw("AP");
			ge[i][j]->Fit("pol1");
/*
 		slope[j] = ge[j]->GetFunction("pol1")->GetParameter(1);
		intercept[j] = ge[j]->GetFunction("pol1")->GetParameter(0);
		TWCleg[j]->AddEntry(ge[j], Form("y = %.4fx+%.4f", slope[j], intercept[j]), "1");
		TWCleg[j]->Draw();
*/
			logoleg[i][j]->AddEntry(ge[i][j], logoname[i][j], "1");
			logoleg[i][j]->Draw();

			discleg[i][j]->AddEntry(ge[i][j], discname[i], "1");
			discleg[i][j]->Draw();

			cfit[i][j]->SaveAs(Form("fig_04_%d_%d.pdf", i, j));
		}
		//end of j loop
	}
	//end of i loop
//		cfit[j]->SaveAs(Form("TWC_VTD_%d.pdf", j));
}
