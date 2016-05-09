#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

//#define xNBIN 200
//#define xMIN 0
//#define xMAX 16

//for proton
void draw_hist_Eloss_all(Int_t xNBIN, Int_t xMIN, Int_t xMAX)
{
	const Int_t numKE = 11;
	const Int_t temp = 1500; //default value for cut
	Int_t KE[numKE] = {19, 20, 23, 24, 25, 50, 100, 200, 300, 350, 400};
	Int_t COL[numKE] = {15, 8, 4, 2, 1, 13, 11, 8, 4, 2, 1};
	Int_t totalMaxY = 0;
	
	TCanvas* c1 = new TCanvas("c1","histogram");
	TH1F* hist[numKE];
	gStyle -> SetOptStat(0);
//	TH1F* hist = new TH1F("hist", "", xNBIN, xMIN, xMAX);

	for(Int_t k=0; k<numKE; k++)
	{	
		ifstream Fin(Form("energyLoss_%dMeV.dat", KE[k]), std::ios::in);
		hist[k] = new TH1F("hist", "", xNBIN, xMIN, xMAX);
		hist[k] -> GetXaxis() -> SetTitle("Energy Loss (MeV)");
		hist[k] -> GetXaxis() -> CenterTitle();
		hist[k] -> GetYaxis() -> SetTitle("counts");
		hist[k] -> GetYaxis() -> CenterTitle();
		hist[k] -> SetLineColor(COL[k]);

		Int_t eventNum[temp];
		Double_t energyLoss[temp];
		for (Int_t i=0; i<temp; i++){ eventNum[i] = -1; energyLoss[i]=0.; } //Initialization

		for(Int_t j=0; j< temp; j++)
		{
			Fin >> eventNum[j] >> energyLoss[j] ;
			if(eventNum[j]==-1) break;
		}
		
		Fin.close();
//		cout << "j = " << j << endl;

		for(Int_t i=0; i<j; i++)
		{
//			cout << i <<"th Eloss = " << energyLoss[i] << endl;
	 		if(energyLoss[i]!=0) {	hist[k] -> Fill(energyLoss[i]); }
		}

		Int_t maxY = hist[k] -> GetMaximum();
//		cout << "maxY = " << maxY << endl;
		if (maxY > totalMaxY) { totalMaxY=maxY; }
//		cout << "totalMaxY = " << totalMaxY << endl;

//		if(k==0)  hist[k]->Draw();
//		else hist[k]->Draw("same");
//		c1->Update();
	}

	for(k=0; k<numKE; k++)
	{
		if(k==0)
		{
			hist[k]->SetMaximum(totalMaxY+20); 
			hist[k]->Draw(); 
			c1->Update();
		}
		else 
		{
			hist[k] -> Draw("same");
			c1->Update();
		}
	}
	c1 -> SaveAs("energyLoss_all.png");
	//	return;
}
