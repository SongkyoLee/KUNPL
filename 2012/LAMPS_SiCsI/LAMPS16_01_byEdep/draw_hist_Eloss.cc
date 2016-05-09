#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

//#define NBIN 200
//#define XMIN 0
//#define XMAX 1

//for proton

void draw_hist_Eloss(char* KE, Int_t xNBIN, Int_t xMIN, Int_t xMAX)
{
	ifstream Fin(Form("energyLoss_%s.dat", KE), std::ios::in);

	const Int_t temp = 1500; //default value for cut
	Int_t eventNum[temp];
	Double_t energyLoss[temp];
	for (Int_t i = 0; i < temp; i++)
	{ eventNum[i] = -1; energyLoss[i]=0.; } //Initialization
//	Int_t count = 0;

	/*
	while(Fin.is_open())
	{
		Fin >> eventNum[count] >> energyLoss[count] ;
		if(eventNum[count]!=1500) { count++; }
		else break;
	}
	*/
	TCanvas* c1 = new TCanvas("c1","histogram");
	TH1F* h1 = new TH1F("h1", "", xNBIN, xMIN, xMAX);
	h1 -> GetXaxis() -> SetTitle("Energy Loss (MeV)");
	h1 -> GetXaxis() -> CenterTitle();
	h1 -> GetYaxis() -> SetTitle("counts");
	h1 -> GetYaxis() -> CenterTitle();

	for(Int_t j=0; j< temp; j++)
	{
		Fin >> eventNum[j] >> energyLoss[j] ;
	//	cout << j <<"th :: " << eventNum[j] << " :: Eloss = " << energyLoss[j] << endl;
		if(eventNum[j]==-1) break;
//		else count++;
	}
		
	Fin.close();
	cout << "j = " << j << endl;

	for(Int_t i=0; i<j; i++)
	{
		cout << i <<"th Eloss = " << energyLoss[i] << endl;
	 	if(energyLoss[i]!=0) {	h1 -> Fill(energyLoss[i]); }
	}

	h1->Draw();
	c1 -> SaveAs(Form("energyLoss_%s.png", KE));
	//	return;
}
