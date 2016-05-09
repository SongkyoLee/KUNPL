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

void fNenergy_samebin_v1()
{
	ifstream in;

//	const Double_t tResol_CFD = 0.0180839;
	//const Double_t tResol_CFD = 0.926; // from Cobalt EXP (Ben)
	const Double_t tResol_CFD = 0.758; // from Cobalt EXP (Yeonju)
	const Double_t NM = 939.6; //[MeV/c^2] neutron mass
	Double_t energy = 0;
	Int_t count = 0;
//	Int_t sign = 0;
	Double_t ItoD_CFD = 0;

	// KYO
	//(i=40; i<108; i++) was the neutron time range 
	// Therefore, 108-40 = 68 
	const Int_t Narr = 68; 
	const Double_t distance = 1.4035; //[m] avg of 1.375 and 1.432
//	const Double_t distance = 1.4; //[m]
	const Double_t speedOfLight = 0.299792458 ; //[m/ns]
//	const Double_t speedOfLight = 0.3 ; //[m/ns]

	Double_t v_CFD[Narr] = {0}; //bin center : Velocity
	Double_t vL_CFD[Narr] = {0}; // lower boundary of bin :Velocity
	Double_t vU_CFD[Narr] = {0}; // upper boundary of bin : Velocity
	Double_t gamma_CFD[Narr] = {0}; // bin center Gamma-factor
	Double_t gammaL_CFD[Narr] = {0}; //lower
	Double_t gammaU_CFD[Narr] = {0}; //upper
	Double_t E_CFD[Narr] = {0}; // Kinteic Energy
	Double_t EL_CFD[Narr] = {0}; //lower 
	Double_t EU_CFD[Narr] = {0}; //upper
	Double_t y_pre_CFD[Narr] = {0}; // y axis : counts
	Double_t y_CFD[Narr] = {0}; // y axis : counts (normalized)
	Double_t yE_CFD[Narr] = {0}; // y axis error
	Double_t xE_CFD[Narr] = {0}; // x axis error


	// loop for calculating KE of function value (upper and lower limit of bin)
	// cf)  Nenergy.txt is that of real data value
	for(Int_t i = 0; i < Narr; i++)
	{
		ItoD_CFD = (double) i;
//		v_CFD[i] = distance/(20.25+ItoD_CFD/2.); 
		vU_CFD[i] = distance/(20+ItoD_CFD/2.); // v = L/t, where neutron time dist. starts from i=40 => t=20ns
		vL_CFD[i] = distance/(20.5+ItoD_CFD/2.);
//		gamma_CFD[i] = TMath::Sqrt(1/(1-(v_CFD[i]/speedOfLight)*(v_CFD[i]/speedOfLight)));
		//cout << i <<"th gamma factor = "<< gamma_CFD[i] << endl; // to check significant figure : x.xxxxx
		gammaU_CFD[i] = TMath::Sqrt(1/(1-(vU_CFD[i]/speedOfLight)*(vU_CFD[i]/speedOfLight)));
		gammaL_CFD[i] = TMath::Sqrt(1/(1-(vL_CFD[i]/speedOfLight)*(vL_CFD[i]/speedOfLight)));
//		E_CFD[i] = NM*(gamma_CFD[i]-1); //defined for the center
		EU_CFD[i] = NM*(gammaU_CFD[i]-1);
		EL_CFD[i] = NM*(gammaL_CFD[i]-1);
	}

	TCanvas* c = new TCanvas("c", "final energy distribution", 200, 0, 600, 600);

	in.open("Nenergy_pol1.txt");
	if(in.is_open())
	{
		while(1)
		{
			in >> energy >> count;

			if(!in.good()) break;

			if(energy >= EL_CFD[0] && energy < EU_CFD[0])
			{
				y_pre_CFD[0] += count; // accumulate "count"s when "energy"s are in this bin
				y_CFD[0] += count/(EU_CFD[0]-EL_CFD[0]); //normalize by the bin width
			}

			else if(energy >= EL_CFD[1] && energy < EU_CFD[1])
		{
				y_pre_CFD[1] += count;
				y_CFD[1] += count/(EU_CFD[1]-EL_CFD[1]);
			}

			else if(energy >= EL_CFD[2] && energy < EU_CFD[2])
			{
				y_pre_CFD[2] += count;
				y_CFD[2] += count/(EU_CFD[2]-EL_CFD[2]);
			}

			else if(energy >= EL_CFD[3] && energy < EU_CFD[3])
			{
				y_pre_CFD[3] += count;
				y_CFD[3] += count/(EU_CFD[3]-EL_CFD[3]);
			}

			else if(energy >= EL_CFD[4] && energy < EU_CFD[4])
			{
				y_pre_CFD[4] += count;
				y_CFD[4] += count/(EU_CFD[4]-EL_CFD[4]);
			}

			else if(energy >= EL_CFD[5] && energy < EU_CFD[5])
			{
				y_pre_CFD[5] += count;
				y_CFD[5] += count/(EU_CFD[5]-EL_CFD[5]);
			}

			else if(energy >= EL_CFD[6] && energy < EU_CFD[6])
			{
				y_pre_CFD[6] += count;
				y_CFD[6] += count/(EU_CFD[6]-EL_CFD[6]);
			}

			else if(energy >= EL_CFD[7] && energy < EU_CFD[7])
			{
				y_pre_CFD[7] += count;
				y_CFD[7] += count/(EU_CFD[7]-EL_CFD[7]);
			}

			else if(energy >= EL_CFD[8] && energy < EU_CFD[8])
			{
				y_pre_CFD[8] += count;
				y_CFD[8] += count/(EU_CFD[8]-EL_CFD[8]);
			}

			else if(energy >= EL_CFD[9] && energy < EU_CFD[9])
			{
				y_pre_CFD[9] += count;
				y_CFD[9] += count/(EU_CFD[9]-EL_CFD[9]);
			}

			else if(energy >= EL_CFD[10] && energy < EU_CFD[10])
			{
				y_pre_CFD[10] += count;
				y_CFD[10] += count/(EU_CFD[10]-EL_CFD[10]);
			}

			else if(energy >= EL_CFD[11] && energy < EU_CFD[11])
			{
				y_pre_CFD[11] += count;
				y_CFD[11] += count/(EU_CFD[11]-EL_CFD[11]);
			}

			else if(energy >= EL_CFD[12] && energy < EU_CFD[12])
			{
				y_pre_CFD[12] += count;
				y_CFD[12] += count/(EU_CFD[12]-EL_CFD[12]);
			}

			else if(energy >= EL_CFD[13] && energy < EU_CFD[13])
			{
				y_pre_CFD[13] += count;
				y_CFD[13] += count/(EU_CFD[13]-EL_CFD[13]);
			}

			else if(energy >= EL_CFD[14] && energy < EU_CFD[14])
			{
				y_pre_CFD[14] += count;
				y_CFD[14] += count/(EU_CFD[14]-EL_CFD[14]);
			}

			else if(energy >= EL_CFD[15] && energy < EU_CFD[15])
			{
				y_pre_CFD[15] += count;
				y_CFD[15] += count/(EU_CFD[15]-EL_CFD[15]);
			}

			else if(energy >= EL_CFD[16] && energy < EU_CFD[16])
			{
				y_pre_CFD[16] += count;
				y_CFD[16] += count/(EU_CFD[16]-EL_CFD[16]);
			}

			else if(energy >= EL_CFD[17] && energy < EU_CFD[17])
			{
				y_pre_CFD[17] += count;
				y_CFD[17] += count/(EU_CFD[17]-EL_CFD[17]);
			}

			else if(energy >= EL_CFD[18] && energy < EU_CFD[18])
			{
				y_pre_CFD[18] += count;
				y_CFD[18] += count/(EU_CFD[18]-EL_CFD[18]);
			}

			else if(energy >= EL_CFD[19] && energy < EU_CFD[19])
			{
				y_pre_CFD[19] += count;
				y_CFD[19] += count/(EU_CFD[19]-EL_CFD[19]);
			}

			else if(energy >= EL_CFD[20] && energy < EU_CFD[20])
			{
				y_pre_CFD[20] += count;
				y_CFD[20] += count/(EU_CFD[20]-EL_CFD[20]);
			}

			else if(energy >= EL_CFD[21] && energy < EU_CFD[21])
			{
				y_pre_CFD[21] += count;
				y_CFD[21] += count/(EU_CFD[21]-EL_CFD[21]);
			}

			else if(energy >= EL_CFD[22] && energy < EU_CFD[22])
			{
				y_pre_CFD[22] += count;
				y_CFD[22] += count/(EU_CFD[22]-EL_CFD[22]);
			}

			else if(energy >= EL_CFD[23] && energy < EU_CFD[23])
			{
				y_pre_CFD[23] += count;
				y_CFD[23] += count/(EU_CFD[23]-EL_CFD[23]);
			}

			else if(energy >= EL_CFD[24] && energy < EU_CFD[24])
			{
				y_pre_CFD[24] += count;
				y_CFD[24] += count/(EU_CFD[24]-EL_CFD[24]);
			}

			else if(energy >= EL_CFD[25] && energy < EU_CFD[25])
			{
				y_pre_CFD[25] += count;
				y_CFD[25] += count/(EU_CFD[25]-EL_CFD[25]);
			}

			else if(energy >= EL_CFD[26] && energy < EU_CFD[26])
			{
				y_pre_CFD[26] += count;
				y_CFD[26] += count/(EU_CFD[26]-EL_CFD[26]);
			}

			else if(energy >= EL_CFD[27] && energy < EU_CFD[27])
			{
				y_pre_CFD[27] += count;
				y_CFD[27] += count/(EU_CFD[27]-EL_CFD[27]);
			}

			else if(energy >= EL_CFD[28] && energy < EU_CFD[28])
			{
				y_pre_CFD[28] += count;
				y_CFD[28] += count/(EU_CFD[28]-EL_CFD[28]);
			}

			else if(energy >= EL_CFD[29] && energy < EU_CFD[29])
			{
				y_pre_CFD[29] += count;
				y_CFD[29] += count/(EU_CFD[29]-EL_CFD[29]);
			}

			else if(energy >= EL_CFD[30] && energy < EU_CFD[30])
			{
				y_pre_CFD[30] += count;
				y_CFD[30] += count/(EU_CFD[30]-EL_CFD[30]);
			}

			else if(energy >= EL_CFD[31] && energy < EU_CFD[31])
			{
				y_pre_CFD[31] += count;
				y_CFD[31] += count/(EU_CFD[31]-EL_CFD[31]);
			}

			else if(energy >= EL_CFD[32] && energy < EU_CFD[32])
			{
				y_pre_CFD[32] += count;
				y_CFD[32] += count/(EU_CFD[32]-EL_CFD[32]);
			}

			else if(energy >= EL_CFD[33] && energy < EU_CFD[33])
			{
				y_pre_CFD[33] += count;
				y_CFD[33] += count/(EU_CFD[33]-EL_CFD[33]);
			}

			else if(energy >= EL_CFD[34] && energy < EU_CFD[34])
			{
				y_pre_CFD[34] += count;
				y_CFD[34] += count/(EU_CFD[34]-EL_CFD[34]);
			}

			else if(energy >= EL_CFD[35] && energy < EU_CFD[35])
			{
				y_pre_CFD[35] += count;
				y_CFD[35] += count/(EU_CFD[35]-EL_CFD[35]);
			}

			else if(energy >= EL_CFD[36] && energy < EU_CFD[36])
			{
				y_pre_CFD[36] += count;
				y_CFD[36] += count/(EU_CFD[36]-EL_CFD[36]);
			}

			else if(energy >= EL_CFD[37] && energy < EU_CFD[37])
			{
				y_pre_CFD[37] += count;
				y_CFD[37] += count/(EU_CFD[37]-EL_CFD[37]);
			}

			else if(energy >= EL_CFD[38] && energy < EU_CFD[38])
			{
				y_pre_CFD[38] += count;
				y_CFD[38] += count/(EU_CFD[38]-EL_CFD[38]);
			}

			else if(energy >= EL_CFD[39] && energy < EU_CFD[39])
			{
				y_pre_CFD[39] += count;
				y_CFD[39] += count/(EU_CFD[39]-EL_CFD[39]);
			}

			else if(energy >= EL_CFD[40] && energy < EU_CFD[40])
			{
				y_pre_CFD[40] += count;
				y_CFD[40] += count/(EU_CFD[40]-EL_CFD[40]);
			}

			else if(energy >= EL_CFD[41] && energy < EU_CFD[41])
			{
				y_pre_CFD[41] += count;
				y_CFD[41] += count/(EU_CFD[41]-EL_CFD[41]);
			}

			else if(energy >= EL_CFD[42] && energy < EU_CFD[42])
			{
				y_pre_CFD[42] += count;
				y_CFD[42] += count/(EU_CFD[42]-EL_CFD[42]);
			}
			else if(energy >= EL_CFD[43] && energy < EU_CFD[43])
			{
				y_pre_CFD[43] += count;
				y_CFD[43] += count/(EU_CFD[43]-EL_CFD[43]);
			}

			else if(energy >= EL_CFD[44] && energy < EU_CFD[44])
			{
				y_pre_CFD[44] += count;
				y_CFD[44] += count/(EU_CFD[44]-EL_CFD[44]);
			}

			else if(energy >= EL_CFD[45] && energy < EU_CFD[45])
			{
				y_pre_CFD[45] += count;
				y_CFD[45] += count/(EU_CFD[45]-EL_CFD[45]);
			}

			else if(energy >= EL_CFD[46] && energy < EU_CFD[46])
			{
				y_pre_CFD[46] += count;
				y_CFD[46] += count/(EU_CFD[46]-EL_CFD[46]);
			}

			else if(energy >= EL_CFD[47] && energy < EU_CFD[47])
			{
				y_pre_CFD[47] += count;
				y_CFD[47] += count/(EU_CFD[47]-EL_CFD[47]);
			}

			else if(energy >= EL_CFD[48] && energy < EU_CFD[48])
			{
				y_pre_CFD[48] += count;
				y_CFD[48] += count/(EU_CFD[48]-EL_CFD[48]);
			}

			else if(energy >= EL_CFD[49] && energy < EU_CFD[49])
			{
				y_pre_CFD[49] += count;
				y_CFD[49] += count/(EU_CFD[49]-EL_CFD[49]);
			}

			else if(energy >= EL_CFD[50] && energy < EU_CFD[50])
			{
				y_pre_CFD[50] += count;
				y_CFD[50] += count/(EU_CFD[50]-EL_CFD[50]);
			}

			else if(energy >= EL_CFD[51] && energy < EU_CFD[51])
			{
				y_pre_CFD[51] += count;
				y_CFD[51] += count/(EU_CFD[51]-EL_CFD[51]);
			}

			else if(energy >= EL_CFD[52] && energy < EU_CFD[52])
			{
				y_pre_CFD[52] += count;
				y_CFD[52] += count/(EU_CFD[52]-EL_CFD[52]);
			}

			else if(energy >= EL_CFD[53] && energy < EU_CFD[53])
			{
				y_pre_CFD[53] += count;
				y_CFD[53] += count/(EU_CFD[53]-EL_CFD[53]);
			}

			else if(energy >= EL_CFD[54] && energy < EU_CFD[54])
			{
				y_pre_CFD[54] += count;
				y_CFD[54] += count/(EU_CFD[54]-EL_CFD[54]);
			}

			else if(energy >= EL_CFD[55] && energy < EU_CFD[55])
			{
				y_pre_CFD[55] += count;
				y_CFD[55] += count/(EU_CFD[55]-EL_CFD[55]);
			}

			else if(energy >= EL_CFD[56] && energy < EU_CFD[56])
			{
				y_pre_CFD[56] += count;
				y_CFD[56] += count/(EU_CFD[56]-EL_CFD[56]);
			}

			else if(energy >= EL_CFD[57] && energy < EU_CFD[57])
			{
				y_pre_CFD[57] += count;
				y_CFD[57] += count/(EU_CFD[57]-EL_CFD[57]);
			}

			else if(energy >= EL_CFD[58] && energy < EU_CFD[58])
			{
				y_pre_CFD[58] += count;
				y_CFD[58] += count/(EU_CFD[58]-EL_CFD[58]);
			}

			else if(energy >= EL_CFD[59] && energy < EU_CFD[59])
			{
				y_pre_CFD[59] += count;
				y_CFD[59] += count/(EU_CFD[59]-EL_CFD[59]);
			}

			else if(energy >= EL_CFD[60] && energy < EU_CFD[60])
			{
				y_pre_CFD[60] += count;
				y_CFD[60] += count/(EU_CFD[60]-EL_CFD[60]);
			}

			else if(energy >= EL_CFD[61] && energy < EU_CFD[61])
			{
				y_pre_CFD[61] += count;
				y_CFD[61] += count/(EU_CFD[61]-EL_CFD[61]);
			}

			else if(energy >= EL_CFD[62] && energy < EU_CFD[62])
			{
				y_pre_CFD[62] += count;
				y_CFD[62] += count/(EU_CFD[62]-EL_CFD[62]);
			}

			else if(energy >= EL_CFD[63] && energy < EU_CFD[63])
			{
				y_pre_CFD[63] += count;
				y_CFD[63] += count/(EU_CFD[63]-EL_CFD[63]);
			}

			else if(energy >= EL_CFD[64] && energy < EU_CFD[64])
			{
				y_pre_CFD[64] += count;
				y_CFD[64] += count/(EU_CFD[64]-EL_CFD[64]);
			}

			else if(energy >= EL_CFD[65] && energy < EU_CFD[65])
			{
				y_pre_CFD[65] += count;
				y_CFD[65] += count/(EU_CFD[65]-EL_CFD[65]);
			}

			else if(energy >= EL_CFD[66] && energy < EU_CFD[66])
			{
				y_pre_CFD[66] += count;
				y_CFD[66] += count/(EU_CFD[66]-EL_CFD[66]);
			}

			else if(energy >= EL_CFD[67] && energy < EU_CFD[67])
			{
				y_pre_CFD[67] += count;
				y_CFD[67] += count/(EU_CFD[67]-EL_CFD[67]);
			}
		}
	}
	in.close();

	Double_t y_CFDCounts = 0;
	Double_t y_pre_CFDCounts = 0;

	// ----- X_Error propagation (STEP1-5) -----
	// STEP1. for L
		// for the transverse distance(L) sigma, delL : 1.432m-1.375m=0.057m
		// for the longitudinal DepthOfInteraction sigma, DOI : 5cm=0.05m
		const Double_t sigL = TMath::Sqrt( TMath::Power(0.057/TMath::Sqrt(12),2)+TMath::Power(0.05/TMath::Sqrt(12),2) );
	// STEP2. for t
		// we use "tResol_CFD", the gamma TOF resolution from Cobalt EXP
		const Double_t sigT = tResol_CFD;

	Double_t sigV[Narr]={0};
	Double_t sigGamma[Narr]={0};

	for(Int_t i = 0; i < Narr; i++)
	{
		// STEP3. for v=L/t
			// sigV= v * Sqrt((sigL/L)^2 + (sigT/T)^2)
			ItoD_CFD = (double) i;
			v_CFD[i] = distance/(20.25+ItoD_CFD/2.); 
			sigV[i] = v_CFD[i]*TMath::Sqrt(TMath::Power((sigL/distance),2)+TMath::Power((sigT/(20.25+ItoD_CFD/2.)),2)); 
		// STEP4. for gamma	
			// sigGamma / sigV = (gamma^3)*(v/c^2) : from derivative of gamma definition
			gamma_CFD[i] = TMath::Sqrt(1/(1-(v_CFD[i]/speedOfLight)*(v_CFD[i]/speedOfLight)));
			sigGamma[i] = sigV[i]*TMath::Power(gamma_CFD[i],3)*(v_CFD[i]/TMath::Power(speedOfLight,2));
		// STEP5. for KE = (gamma-1)mc^2
			// xE_CFD = sigGamma*mc^2 = sigGamma*NM
			E_CFD[i] = NM*(gamma_CFD[i]-1); //defined for the center
			xE_CFD[i]= sigGamma[i]*NM;

		// ----- Y_Error propagation -----
		// just sumw2 : Sqrt(N)
		// more precisely : N = Ndata - Nacc - Nbkg. (not estimated here. temporary..)
		//yE_CFD[i]=TMath::Sqrt(y_pre_CFD[i]);
		yE_CFD[i]=TMath::Sqrt(y_CFD[i]);
		//yE_CFD[i]=TMath::Sqrt(y_pre_CFD[i]);

		//yE_CFD[i] = TMath::Sqrt(y_pre_CFD[i]);
		//xE_CFD[i] = NM*tResol_CFD*TMath::Power(gamma_CFD[i]*v_CFD[i], 3)/0.09; //Kisoo
		//yE_CFD[i] = TMath::Sqrt(y_CFD[i]+tResol_CFD*tResol_CFD); //Kisoo

		cout<<"i="<<i<<", Energy_x" << E_CFD[i] <<", counts_y="<<y_CFD[i]<<", y_pre="<<y_pre_CFD[i]<<endl;
		cout<< "    , xErr="<<xE_CFD[i]<<", yErr="<< yE_CFD[i] <<endl; 
		y_CFDCounts += y_CFD[i];
		y_pre_CFDCounts += y_pre_CFD[i];
	}

	cout << " "<<endl;
	cout << "total y_CFDCounts=" << y_CFDCounts << endl;
	cout << "total y_pre_CFDCounts=" << y_pre_CFDCounts << endl;
	cout << " "<<endl;

/* Kisoo & Dr.Lee
	for(Int_t i = 0; i < 44; i++)
	{
		mean[i] = (y_VTD[i]+y_CFD[i+4])/2.;
		statE[i] = TMath::Sqrt(mean[i]);
		//statE[i] = TMath::Sqrt(y_VTD[i]*y_CFD[i]);
//cout << statE[i] << endl;
		if(EL_VTD[i] > 6)
		{
			diff[i] = TMath::Abs(y_VTD[i]-y_CFD[i+4]);
			band[i] = TMath::Sqrt(diff[i]*diff[i]+0.1*0.1*mean[i]*mean[i]);
		}
	}
*/

//	TMultiGraph* fNEnergy = new TMultiGraph("fNEnergy", "Energy spectrum");
	TLegend* legend = new TLegend(0.45, 0.68, 0.88, 0.87);
	legend->SetFillStyle(0);
	legend->SetFillColor(0);
	legend->SetBorderSize(0);
	legend->SetTextSize(0.047);

// Draw Counts vs Energy graph for CFD data
	TGraphErrors* fNEnergy_CFD = new TGraphErrors(Narr, E_CFD, y_CFD, xE_CFD, yE_CFD);
	fNEnergy_CFD->SetMarkerColor(kBlue);
	fNEnergy_CFD->SetMarkerStyle(20);
	fNEnergy_CFD->SetMarkerSize(1);
//	fNEnergy->Add(fNEnergy_CFD);
//	legend->AddEntry(fNEnergy_CFD, "CFD data", "lp");


// draw Watt Spectrum graph (as a reference)
//	TF1 *fa1 = new TF1("fa1", "40000*exp(-0.88*x)*sinh(sqrt(2.0*x))", 0, 10);
	TF1 *fa1 = new TF1("fa1", "40000*exp(-0.88*x)*sinh(sqrt(2.0*x))", 0, 10);
//	fNEnergy->Add(fa1, "l");
	legend->AddEntry(fa1, "Watt spectrum", "l");
	legend->AddEntry(fNEnergy_CFD, "CFD data", "lp");
//	legend->AddEntry(, "Systematic error", "f");
//	legend->AddEntry(fNEnergy_noE, "Data", "lp");
//	legend->AddEntry(fNEnergy_mean, "Systematic error", "f");

	c->cd();
	c->SetLogy();
	c->SetLeftMargin(0.15);
	c->SetBottomMargin(0.15);
	fa1->Draw();
	//fa1->SetMinimum(1);
	fa1->SetTitle("");
	fa1->SetRange(0, 11);
	//fa1->SetRange(0, 27);
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
//	fNEnergy_VTD->Draw("sameP");
	fNEnergy_CFD->Draw("sameP");
	legend->Draw("same");
	fa1->Draw("same");
	//fNEnergy_noE->Draw("samePe");
	
	legend->Draw();
	c->SaveAs("fNenergy_samebin_v1.png");
	c->SaveAs("fNenergy_samebin_v1.pdf");
}
