////////////////////////////////////////////////////
//This file make final version of neutron energy. //
////////////////////////////////////////////////////

#include <stdio.h>
#include <TMultiGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <fstream>
#include <TAxis.h>
#include <TLegend.h>
#include <TF1.h>

void fNenergy_samebin_v2()
{
	ifstream in;

// define some variables
	//const Double_t tResol_CFD = 0.926; // from Cobalt EXP (Ben)
	const Double_t tResol_CFD = 0.758; // from Cobalt EXP (Yeonju)
	const Double_t NM = 939.6; //[MeV/c^2] neutron mass
	Double_t energy = 0;
	Int_t count = 0;
	Double_t ItoD_CFD = 0;

//the neutron time range is 20-54 ns 
// Therefore, num of bin = (54-20)/bintWidth
	//const Int_t Narr = 68; //bidwidth=0.5 
	const Int_t Narr = 34; //binwidth=1.0

	const Double_t distance = 1.4035; //[m] avg of 1.375 and 1.432
	const Double_t speedOfLight = 0.299792458 ; //[m/ns]

	Double_t t_CFD[Narr] = {0}; //bin center : time
	Double_t tL_CFD[Narr] = {0}; //lower boundary of bin
	Double_t tU_CFD[Narr] = {0}; // upper boundary of bin
	Double_t v_CFD[Narr] = {0}; //bin center : Velocity
	Double_t vL_CFD[Narr] = {0}; // lower
	Double_t vU_CFD[Narr] = {0}; // upper
	Double_t gamma_CFD[Narr] = {0}; // Gamma-factor
	Double_t gammaL_CFD[Narr] = {0}; //lower
	Double_t gammaU_CFD[Narr] = {0}; //upper
	Double_t E_CFD[Narr] = {0}; // Kinteic Energy
	Double_t EL_CFD[Narr] = {0}; //lower 
	Double_t EU_CFD[Narr] = {0}; //upper
	Double_t y_pre_CFD[Narr] = {0}; // y axis : counts
	Double_t y_CFD[Narr] = {0}; // y axis : counts (normalized)
	Double_t yE_CFD[Narr] = {0}; // y axis error
	Double_t xE_CFD[Narr] = {0}; // x axis error

	Int_t binOption =0;
//	Double_t binWidth = 0.5;
	Double_t binWidth = 1.;

// loop for calculating KE of functional value (including upper and lower boundary)
	// cf)  Nenergy.txt is that of real data value
	for(Int_t i = 0; i < Narr; i++)
	{
		ItoD_CFD = (double) i;
		t_CFD[i] = 20+binWidth/2.+ItoD_CFD*binWidth; // neutron time distribution starts from t=20ns
		tU_CFD[i] = 20.+ItoD_CFD*binWidth;
		tL_CFD[i] = 20.+binWidth+ItoD_CFD*binWidth;
		v_CFD[i] = distance/t_CFD[i]; 
		vU_CFD[i] = distance/tU_CFD[i];
		vL_CFD[i] = distance/tL_CFD[i];
		gamma_CFD[i] = TMath::Sqrt(1/(1-(v_CFD[i]/speedOfLight)*(v_CFD[i]/speedOfLight)));
		gammaU_CFD[i] = TMath::Sqrt(1/(1-(vU_CFD[i]/speedOfLight)*(vU_CFD[i]/speedOfLight)));
		gammaL_CFD[i] = TMath::Sqrt(1/(1-(vL_CFD[i]/speedOfLight)*(vL_CFD[i]/speedOfLight)));
		//cout << i <<"th gamma factor = "<< gamma_CFD[i] << endl; // to check significant figure : x.xxxxx
		E_CFD[i] = NM*(gamma_CFD[i]-1); //defined for the center
		EU_CFD[i] = NM*(gammaU_CFD[i]-1);
		EL_CFD[i] = NM*(gammaL_CFD[i]-1);
		if (i==0 || i ==Narr-1) {
			cout << i <<"th"<< endl;
			cout << "tU=" << tU_CFD[i]<<endl;
			cout << "tL=" << tL_CFD[i]<<endl;
			cout << "EU =" << EU_CFD[i] << endl;
			cout << "EL =" << EL_CFD[i] << endl;
		}
	}

// Read the ASCII file and put data into the bin (for Counts vs Energy)
	in.open("Nenergy_pol1.txt");
	if(in.is_open())
	{
		while(1)
		{
			in >> energy >> count;
			if(!in.good()) break;

			for(Int_t i=0; i<Narr; i++){
				if (energy >= EL_CFD[i] && energy < EU_CFD[i]) {
					y_pre_CFD[i] += count; // accumulate "count"s when "energy"s are in this bin
					y_CFD[i] += count/(EU_CFD[i]-EL_CFD[i]); //normalize by the bin width
				}else continue;
			}
		}
	}
	in.close();


// ----- Error propagation -----

	// X_Error propagation (STEP1-5)
	// STEP1. for L
	// for the transverse distance(L) sigma, delL : 1.432m-1.375m=0.057m
	// for the longitudinal DepthOfInteraction sigma, DOI : 5cm=0.05m
	const Double_t sigL = TMath::Sqrt( TMath::Power(0.057/TMath::Sqrt(12),2)+TMath::Power(0.05/TMath::Sqrt(12),2) );
	// STEP2. for t
	// we use "tResol_CFD", the gamma TOF resolution from Cobalt EXP
	const Double_t sigT = tResol_CFD;

	Double_t sigV[Narr]={0};
	Double_t sigGamma[Narr]={0};
	Double_t y_CFDCounts = 0;
	Double_t y_pre_CFDCounts = 0;

	for(Int_t i = 0; i < Narr; i++)
	{
		// STEP3. for v=L/t
		// sigV= v*Sqrt((sigL/L)^2+(sigT/T)^2)
		sigV[i] = v_CFD[i]*TMath::Sqrt(TMath::Power((sigL/distance),2)+TMath::Power((sigT/t_CFD[i]),2)); 
		// STEP4. for gamma	
		// sigGamma/sigV = (gamma^3)*(v/c^2) : from derivative of gamma definition
		sigGamma[i] = sigV[i]*TMath::Power(gamma_CFD[i],3)*(v_CFD[i]/TMath::Power(speedOfLight,2));
		// STEP5. for KE = (gamma-1)mc^2
		// xE_CFD = sigGamma*mc^2
		xE_CFD[i]= sigGamma[i]*NM;

		// ----- Y_Error propagation -----
		// just sumw2 : Sqrt(N)
		// more precisely : N = Ndata - Nacc - Nbkg. (not estimated here. temporary..)
		//yE_CFD[i]=TMath::Sqrt(y_pre_CFD[i]);
		yE_CFD[i]=TMath::Sqrt(y_CFD[i]);

		//xE_CFD[i] = NM*tResol_CFD*TMath::Power(gamma_CFD[i]*v_CFD[i], 3)/0.09; //Kisoo
		//yE_CFD[i] = TMath::Sqrt(y_CFD[i]+tResol_CFD*tResol_CFD); //Kisoo

		cout<<"i="<<i<<", Energy_x=" << E_CFD[i] <<", counts_y="<<y_CFD[i]<<", y_pre="<<y_pre_CFD[i]<<endl;
		cout<< "    , xErr="<<xE_CFD[i]<<", yErr="<< yE_CFD[i] <<endl; 
		y_CFDCounts += y_CFD[i];
		y_pre_CFDCounts += y_pre_CFD[i];
	}

	cout << " "<<endl;
	cout << "total y_CFDCounts=" << y_CFDCounts << endl;
	cout << "total y_pre_CFDCounts=" << y_pre_CFDCounts << endl;
	cout << " "<<endl;


// -----  Draw the graph

	TCanvas* c = new TCanvas("c", "final energy distribution", 200, 0, 600, 600);

	//TMultiGraph* fNEnergy = new TMultiGraph("fNEnergy", "Energy spectrum");
	TLegend* legend = new TLegend(0.45, 0.68, 0.88, 0.87);
	legend->SetFillStyle(0);
	legend->SetFillColor(0);
	legend->SetBorderSize(0);
	legend->SetTextSize(0.047);

	//Draw Counts vs Energy graph for CFD data
	TGraphErrors* fNEnergy_CFD = new TGraphErrors(Narr, E_CFD, y_CFD, xE_CFD, yE_CFD);
	fNEnergy_CFD->SetMarkerColor(kBlue);
	fNEnergy_CFD->SetMarkerStyle(20);
	fNEnergy_CFD->SetMarkerSize(1);
	//fNEnergy->Add(fNEnergy_CFD);
	//legend->AddEntry(fNEnergy_CFD, "CFD data", "lp");

	//draw Watt Spectrum graph (as a reference)
	TF1 *fa1 = new TF1("fa1", "40000*exp(-0.88*x)*sinh(sqrt(2.0*x))", 0, 10);
	//fNEnergy->Add(fa1, "l");
	legend->AddEntry(fa1, "Watt spectrum", "l");
	legend->AddEntry(fNEnergy_CFD, "CFD data", "lp");
	//legend->AddEntry(fNEnergy_mean, "Systematic error", "f");

	c->cd();
	c->SetLogy();
	c->SetLeftMargin(0.15);
	c->SetBottomMargin(0.15);
	fa1->Draw();
	fa1->SetTitle("");
	fa1->SetRange(0, 11);
	fa1->GetXaxis()->SetTitle("E (MeV)");
	fa1->GetYaxis()->SetTitle("Counts (MeV^{-1})");
	fa1->GetXaxis()->SetTitleSize(0.07);
	fa1->GetYaxis()->SetTitleSize(0.07);
	fa1->GetXaxis()->SetTitleOffset(1.0);
	fa1->GetYaxis()->SetTitleOffset(1.0);
	fa1->GetXaxis()->SetLabelSize(0.055);
	fa1->GetYaxis()->SetLabelSize(0.055);
	fa1->GetXaxis()->CenterTitle();
	fa1->GetYaxis()->CenterTitle();
	fa1->SetMaximum(100000);
	fa1->SetMinimum(100);
	fa1->SetLineWidth(3);
//	fNEnergy_mean->SetFillColor(kYellow);
//	fNEnergy_mean->Draw("samePE3");
	fNEnergy_CFD->Draw("sameP");
	legend->Draw("same");
	fa1->Draw("same");
	
	legend->Draw();
	c->SaveAs("fNenergy_samebin_v2.png");
	c->SaveAs("fNenergy_samebin_v2.pdf");

}
