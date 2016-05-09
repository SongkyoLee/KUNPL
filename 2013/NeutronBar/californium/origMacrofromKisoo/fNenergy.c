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

void fNenergy()
{
	ifstream in;

	const Double_t tResol_VTD = 0.0153513;
	const Double_t tResol_CFD = 0.0180839;
	const Double_t NM = 939.6;
	Double_t energy = 0;
	Int_t count = 0;
//	Int_t sign = 0;
	Double_t ItoD_VTD = 0;
	Double_t ItoD_CFD = 0;

	Double_t v_VTD[44] = {0};
	Double_t vL_VTD[44] = {0};
	Double_t vU_VTD[44] = {0};
	Double_t gamma_VTD[44] = {0};
	Double_t gammaL_VTD[44] = {0};
	Double_t gammaU_VTD[44] = {0};
	Double_t E_VTD[44] = {0};
	Double_t EL_VTD[44] = {0};
	Double_t EU_VTD[44] = {0};
	Double_t v_CFD[52] = {0};
	Double_t vL_CFD[52] = {0};
	Double_t vU_CFD[52] = {0};
	Double_t gamma_CFD[52] = {0};
	Double_t gammaL_CFD[52] = {0};
	Double_t gammaU_CFD[52] = {0};
	Double_t E_CFD[52] = {0};
	Double_t EL_CFD[52] = {0};
	Double_t EU_CFD[52] = {0};
	Double_t y_pre_VTD[44] = {0};
	Double_t y_pre_CFD[52] = {0};
	Double_t y_VTD[44] = {0};
	Double_t y_CFD[52] = {0};
	Double_t yE_VTD[44] = {0};
	Double_t yE_CFD[52] = {0};
	Double_t xE_VTD[44] = {0};
	Double_t xE_CFD[52] = {0};
	Double_t mean[44] = {0};
	Double_t diff[44] = {0};
	Double_t band[44] = {0};
	Double_t statE[44] = {0};

	for(Int_t i = 0; i < 44; i++)
	{
		ItoD_VTD = (double) i;
		v_VTD[i] = 1/(20.25+ItoD_VTD/2.);
		vU_VTD[i] = 1/(20+ItoD_VTD/2.);
		vL_VTD[i] = 1/(20.5+ItoD_VTD/2.);
		gamma_VTD[i] = TMath::Sqrt(1/(1-(v_VTD[i]/0.3)*(v_VTD[i]/0.3)));
		gammaU_VTD[i] = TMath::Sqrt(1/(1-(vU_VTD[i]/0.3)*(vU_VTD[i]/0.3)));
		gammaL_VTD[i] = TMath::Sqrt(1/(1-(vL_VTD[i]/0.3)*(vL_VTD[i]/0.3)));
		E_VTD[i] = NM*(gamma_VTD[i]-1);
		EU_VTD[i] = NM*(gammaU_VTD[i]-1);
		EL_VTD[i] = NM*(gammaL_VTD[i]-1);
	}

	for(Int_t i = 0; i < 52; i++)
	{
		ItoD_CFD = (double) i;
		v_CFD[i] = 1/(18.25+ItoD_CFD/2.);
		vU_CFD[i] = 1/(18+ItoD_CFD/2.);
		vL_CFD[i] = 1/(18.5+ItoD_CFD/2.);
		gamma_CFD[i] = TMath::Sqrt(1/(1-(v_CFD[i]/0.3)*(v_CFD[i]/0.3)));
		gammaU_CFD[i] = TMath::Sqrt(1/(1-(vU_CFD[i]/0.3)*(vU_CFD[i]/0.3)));
		gammaL_CFD[i] = TMath::Sqrt(1/(1-(vL_CFD[i]/0.3)*(vL_CFD[i]/0.3)));
		E_CFD[i] = NM*(gamma_CFD[i]-1);
		EU_CFD[i] = NM*(gammaU_CFD[i]-1);
		EL_CFD[i] = NM*(gammaL_CFD[i]-1);
	}

	TCanvas* c = new TCanvas("c", "final energy distribution", 200, 0, 600, 600);

	in.open("Nenergy_VTD.txt");
	if(in.is_open())
	{
		while(1)
		{
			in >> energy >> count;

			if(!in.good()) break;

			if(energy >= EL_VTD[0] && energy < EU_VTD[0])
			{
				y_pre_VTD[0] += count;
				y_VTD[0] += count/(EU_VTD[0]-EL_VTD[0]);
			}

			else if(energy >= EL_VTD[1] && energy < EU_VTD[1])
			{
				y_pre_VTD[1] += count;
				y_VTD[1] += count/(EU_VTD[1]-EL_VTD[1]);
			}

			else if(energy >= EL_VTD[2] && energy < EU_VTD[2])
			{
				y_pre_VTD[2] += count;
				y_VTD[2] += count/(EU_VTD[2]-EL_VTD[2]);
			}

			else if(energy >= EL_VTD[3] && energy < EU_VTD[3])
			{
				y_pre_VTD[3] += count;
				y_VTD[3] += count/(EU_VTD[3]-EL_VTD[3]);
			}

			else if(energy >= EL_VTD[4] && energy < EU_VTD[4])
			{
				y_pre_VTD[4] += count;
				y_VTD[4] += count/(EU_VTD[4]-EL_VTD[4]);
			}

			else if(energy >= EL_VTD[5] && energy < EU_VTD[5])
			{
				y_pre_VTD[5] += count;
				y_VTD[5] += count/(EU_VTD[5]-EL_VTD[5]);
			}

			else if(energy >= EL_VTD[6] && energy < EU_VTD[6])
			{
				y_pre_VTD[6] += count;
				y_VTD[6] += count/(EU_VTD[6]-EL_VTD[6]);
			}

			else if(energy >= EL_VTD[7] && energy < EU_VTD[7])
			{
				y_pre_VTD[7] += count;
				y_VTD[7] += count/(EU_VTD[7]-EL_VTD[7]);
			}

			else if(energy >= EL_VTD[8] && energy < EU_VTD[8])
			{
				y_pre_VTD[8] += count;
				y_VTD[8] += count/(EU_VTD[8]-EL_VTD[8]);
			}

			else if(energy >= EL_VTD[9] && energy < EU_VTD[9])
			{
				y_pre_VTD[9] += count;
				y_VTD[9] += count/(EU_VTD[9]-EL_VTD[9]);
			}

			else if(energy >= EL_VTD[10] && energy < EU_VTD[10])
			{
				y_pre_VTD[10] += count;
				y_VTD[10] += count/(EU_VTD[10]-EL_VTD[10]);
			}

			else if(energy >= EL_VTD[11] && energy < EU_VTD[11])
			{
				y_pre_VTD[11] += count;
				y_VTD[11] += count/(EU_VTD[11]-EL_VTD[11]);
			}

			else if(energy >= EL_VTD[12] && energy < EU_VTD[12])
			{
				y_pre_VTD[12] += count;
				y_VTD[12] += count/(EU_VTD[12]-EL_VTD[12]);
			}

			else if(energy >= EL_VTD[13] && energy < EU_VTD[13])
			{
				y_pre_VTD[13] += count;
				y_VTD[13] += count/(EU_VTD[13]-EL_VTD[13]);
			}

			else if(energy >= EL_VTD[14] && energy < EU_VTD[14])
			{
				y_pre_VTD[14] += count;
				y_VTD[14] += count/(EU_VTD[14]-EL_VTD[14]);
			}

			else if(energy >= EL_VTD[15] && energy < EU_VTD[15])
			{
				y_pre_VTD[15] += count;
				y_VTD[15] += count/(EU_VTD[15]-EL_VTD[15]);
			}

			else if(energy >= EL_VTD[16] && energy < EU_VTD[16])
			{
				y_pre_VTD[16] += count;
				y_VTD[16] += count/(EU_VTD[16]-EL_VTD[16]);
			}

			else if(energy >= EL_VTD[17] && energy < EU_VTD[17])
			{
				y_pre_VTD[17] += count;
				y_VTD[17] += count/(EU_VTD[17]-EL_VTD[17]);
			}

			else if(energy >= EL_VTD[18] && energy < EU_VTD[18])
			{
				y_pre_VTD[18] += count;
				y_VTD[18] += count/(EU_VTD[18]-EL_VTD[18]);
			}

			else if(energy >= EL_VTD[19] && energy < EU_VTD[19])
			{
				y_pre_VTD[19] += count;
				y_VTD[19] += count/(EU_VTD[19]-EL_VTD[19]);
			}

			else if(energy >= EL_VTD[20] && energy < EU_VTD[20])
			{
				y_pre_VTD[20] += count;
				y_VTD[20] += count/(EU_VTD[20]-EL_VTD[20]);
			}

			else if(energy >= EL_VTD[21] && energy < EU_VTD[21])
			{
				y_pre_VTD[21] += count;
				y_VTD[21] += count/(EU_VTD[21]-EL_VTD[21]);
			}

			else if(energy >= EL_VTD[22] && energy < EU_VTD[22])
			{
				y_pre_VTD[22] += count;
				y_VTD[22] += count/(EU_VTD[22]-EL_VTD[22]);
			}

			else if(energy >= EL_VTD[23] && energy < EU_VTD[23])
			{
				y_pre_VTD[23] += count;
				y_VTD[23] += count/(EU_VTD[23]-EL_VTD[23]);
			}

			else if(energy >= EL_VTD[24] && energy < EU_VTD[24])
			{
				y_pre_VTD[24] += count;
				y_VTD[24] += count/(EU_VTD[24]-EL_VTD[24]);
			}

			else if(energy >= EL_VTD[25] && energy < EU_VTD[25])
			{
				y_pre_VTD[25] += count;
				y_VTD[25] += count/(EU_VTD[25]-EL_VTD[25]);
			}

			else if(energy >= EL_VTD[26] && energy < EU_VTD[26])
			{
				y_pre_VTD[26] += count;
				y_VTD[26] += count/(EU_VTD[26]-EL_VTD[26]);
			}

			else if(energy >= EL_VTD[27] && energy < EU_VTD[27])
			{
				y_pre_VTD[27] += count;
				y_VTD[27] += count/(EU_VTD[27]-EL_VTD[27]);
			}

			else if(energy >= EL_VTD[28] && energy < EU_VTD[28])
			{
				y_pre_VTD[28] += count;
				y_VTD[28] += count/(EU_VTD[28]-EL_VTD[28]);
			}

			else if(energy >= EL_VTD[29] && energy < EU_VTD[29])
			{
				y_pre_VTD[29] += count;
				y_VTD[29] += count/(EU_VTD[29]-EL_VTD[29]);
			}

			else if(energy >= EL_VTD[30] && energy < EU_VTD[30])
			{
				y_pre_VTD[30] += count;
				y_VTD[30] += count/(EU_VTD[30]-EL_VTD[30]);
			}

			else if(energy >= EL_VTD[31] && energy < EU_VTD[31])
			{
				y_pre_VTD[31] += count;
				y_VTD[31] += count/(EU_VTD[31]-EL_VTD[31]);
			}

			else if(energy >= EL_VTD[32] && energy < EU_VTD[32])
			{
				y_pre_VTD[32] += count;
				y_VTD[32] += count/(EU_VTD[32]-EL_VTD[32]);
			}

			else if(energy >= EL_VTD[33] && energy < EU_VTD[33])
			{
				y_pre_VTD[33] += count;
				y_VTD[33] += count/(EU_VTD[33]-EL_VTD[33]);
			}

			else if(energy >= EL_VTD[34] && energy < EU_VTD[34])
			{
				y_pre_VTD[34] += count;
				y_VTD[34] += count/(EU_VTD[34]-EL_VTD[34]);
			}

			else if(energy >= EL_VTD[35] && energy < EU_VTD[35])
			{
				y_pre_VTD[35] += count;
				y_VTD[35] += count/(EU_VTD[35]-EL_VTD[35]);
			}

			else if(energy >= EL_VTD[36] && energy < EU_VTD[36])
			{
				y_pre_VTD[36] += count;
				y_VTD[36] += count/(EU_VTD[36]-EL_VTD[36]);
			}

			else if(energy >= EL_VTD[37] && energy < EU_VTD[37])
			{
				y_pre_VTD[37] += count;
				y_VTD[37] += count/(EU_VTD[37]-EL_VTD[37]);
			}

			else if(energy >= EL_VTD[38] && energy < EU_VTD[38])
			{
				y_pre_VTD[38] += count;
				y_VTD[38] += count/(EU_VTD[38]-EL_VTD[38]);
			}

			else if(energy >= EL_VTD[39] && energy < EU_VTD[39])
			{
				y_pre_VTD[39] += count;
				y_VTD[39] += count/(EU_VTD[39]-EL_VTD[39]);
			}

			else if(energy >= EL_VTD[40] && energy < EU_VTD[40])
			{
				y_pre_VTD[40] += count;
				y_VTD[40] += count/(EU_VTD[40]-EL_VTD[40]);
			}

			else if(energy >= EL_VTD[41] && energy < EU_VTD[41])
			{
				y_pre_VTD[41] += count;
				y_VTD[41] += count/(EU_VTD[41]-EL_VTD[41]);
			}

			else if(energy >= EL_VTD[42] && energy < EU_VTD[42])
			{
				y_pre_VTD[42] += count;
				y_VTD[42] += count/(EU_VTD[42]-EL_VTD[42]);
			}

			else if(energy >= EL_VTD[43] && energy < EU_VTD[43])
			{
				y_pre_VTD[43] += count;
				y_VTD[43] += count/(EU_VTD[43]-EL_VTD[43]);
			}
		}
	}
	in.close();

	in.open("Nenergy_CFD.txt");
	if(in.is_open())
	{
		while(1)
		{
			in >> energy >> count;

			if(!in.good()) break;

			if(energy >= EL_CFD[0] && energy < EU_CFD[0])
			{
				y_pre_CFD[0] += count;
				y_CFD[0] += count/(EU_CFD[0]-EL_CFD[0]);
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
		}
	}
	in.close();

	for(Int_t i = 0; i < 44; i++)
	{
		//yE_VTD[i] = TMath::Sqrt(y_pre_VTD[i]);
		//yE_VTD[i] = TMath::Sqrt(1./y_VTD[i])*tResol_VTD;
		yE_VTD[i] = TMath::Sqrt(y_VTD[i]+tResol_VTD*tResol_VTD);
		//xE_VTD[i] = NM*tResol_VTD*TMath::Power(gamma_VTD[i]*v_VTD[i], 3)/0.09;
		//xE_VTD[i] = 2*E_VTD[i]*tResol_VTD/v_VTD[i];
	//	cout << y_VTD[i] << "    " << yE_VTD[i] << endl;
	}

	for(Int_t i = 0; i < 52; i++)
	{
		//yE_CFD[i] = TMath::Sqrt(y_pre_CFD[i]);
		yE_CFD[i] = TMath::Sqrt(y_CFD[i]+tResol_CFD*tResol_CFD);
		xE_CFD[i] = NM*tResol_CFD*TMath::Power(gamma_CFD[i]*v_CFD[i], 3)/0.09;
	}

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

//	TMultiGraph* fNEnergy = new TMultiGraph("fNEnergy", "Energy spectrum");
	TLegend* legend = new TLegend(0.45, 0.68, 0.88, 0.87);
	legend->SetFillStyle(0);
	legend->SetFillColor(0);
	legend->SetBorderSize(0);
	legend->SetTextSize(0.047);
/*
	TGraphErrors* fNEnergy_VTD = new TGraphErrors(44, E_VTD, y_VTD, xE_VTD, yE_VTD);
	fNEnergy_VTD->SetMarkerColor(kRed);
	fNEnergy_VTD->SetMarkerStyle(20);
	fNEnergy_VTD->SetMarkerSize(1);
//	fNEnergy->Add(fNEnergy_VTD);
	legend->AddEntry(fNEnergy_VTD, "VTD", "lp");

	TGraphErrors* fNEnergy_CFD = new TGraphErrors(52, E_CFD, y_CFD, xE_CFD, yE_CFD);
	fNEnergy_CFD->SetMarkerColor(kBlue);
	fNEnergy_CFD->SetMarkerStyle(20);
	fNEnergy_CFD->SetMarkerSize(1);
//	fNEnergy->Add(fNEnergy_CFD);
	legend->AddEntry(fNEnergy_CFD, "CFD", "lp");
*/

	TGraphErrors* fNEnergy_mean = new TGraphErrors(44, E_VTD, mean, xE_VTD, band);
	fNEnergy_mean->SetMarkerColor(kBlue);
	fNEnergy_mean->SetMarkerStyle(20);
	fNEnergy_mean->SetMarkerSize(1);

	for(Int_t i = 0; i < 44; i++)
	{
		cout << statE[i] << endl;
	}

	TGraphErrors* fNEnergy_noE = new TGraphErrors(44, E_VTD, mean, xE_VTD, statE);
	fNEnergy_noE->SetMarkerColor(kBlue);
	fNEnergy_noE->SetMarkerStyle(20);
	fNEnergy_noE->SetMarkerSize(1.5);
/*
	for(Int_t i = 0; i < 44; i++)
	{
		Double_t errorvalue = fNEnergy_noE->GetErrorY(i+1);
		cout << errorvalue << endl;
	}
*/	
	TF1 *fa1 = new TF1("fa1", "60000*exp(-0.88*x)*sinh(sqrt(2.0*x))", 0, 10);
//	fNEnergy->Add(fa1, "l");
	legend->AddEntry(fa1, "Watt spectrum", "l");
	legend->AddEntry(fNEnergy_noE, "Data", "lp");
	legend->AddEntry(fNEnergy_mean, "Systematic error", "f");

	c->cd();
	c->SetLogy();
	c->SetLeftMargin(0.15);
	c->SetBottomMargin(0.15);
	fa1->Draw();
	//fa1->SetMinimum(1);
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
	fNEnergy_mean->SetFillColor(kYellow);
	fNEnergy_mean->Draw("samePE3");
//	fNEnergy_VTD->Draw("sameP");
//	fNEnergy_CFD->Draw("sameP");
	legend->Draw("same");
	fa1->Draw("same");
	fNEnergy_noE->Draw("samePe");
/*
	fNEnergy->SetTitle("");
	fNEnergy->Draw("AP");
	fNEnergy->GetXaxis()->SetTitle("E (MeV)");
	fNEnergy->GetYaxis()->SetTitle("count/MeV");
	fNEnergy->GetXaxis()->SetTitleSize(0.055);
	fNEnergy->GetYaxis()->SetTitleSize(0.055);
	fNEnergy->GetYaxis()->SetTitleOffset(1.2);
	fNEnergy->GetXaxis()->SetLabelSize(0.055);
	fNEnergy->GetYaxis()->SetLabelSize(0.055);
	//fNEnergy->SetMinimum(80);
*/
	legend->Draw();
	c->SaveAs("mean_fNenergy.png");
	c->SaveAs("mean_fNenergy.pdf");
}
