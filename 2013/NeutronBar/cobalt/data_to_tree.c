////////////////////////////////////////////////////
//This file convert datafile to treefile.         //
//In this file many position datas are used.      //
//The distance is from left edge of detector.     //
//And pedestal subtraction is operated.           //
////////////////////////////////////////////////////

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>
#include <fstream>
#include <iostream>
#include <TH1.h>
#include <TF1.h>

void data_to_tree()
{
	Double_t pedtime;
	Double_t pedTr;
	Double_t pedTl;
	Double_t rped;
	Double_t lped;
	//ptfactor = point to time factor
	//const Double_t ptfactor = 0.050;
	const Double_t ptfactor = 0.0407;

	TFile* f = new TFile("data_to_tree.root", "RECREATE");

	ifstream in;
	ofstream out;

	//bring data files and give name to use in this code.
	//data file name is in order type_ch0highvoltage_ch2highvoltage_#ofevent_position_3.dat
	
	const Int_t nFile = 10; // including long file for TWC 
	const Char_t* file[nFile] = {"./Cobalt_data/Co_2090v_2160v_10k_10cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_20cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_30cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_40cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_50cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_60cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_70cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_80cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_10k_90cm_3.dat",
									"./Cobalt_data/Co_2090v_2160v_100k_50cm_3.dat"};

	const Char_t* distance[nFile] = {"10cm", "20cm", "30cm", "40cm", "50cm", "60cm", "70cm", "80cm", "90cm", "50cm100k"};

	TCanvas* c1 = new TCanvas("c1", "pedl", 200, 0, 600, 600);
	TH1F* pedlhist = new TH1F("pedlhist", "left", 200, 0, 200);
	TCanvas* c2 = new TCanvas("c2", "pedr", 210, 10, 610, 610);
	TH1F* pedrhist = new TH1F("pedrhist", "right", 200, 0, 200);

	//bring the pedestal file
	in.open("./Cobalt_data/pedestal_2090v_2160v_10k_4.dat");

	if(in.is_open())
	{
		while(1)
		{
			in >> pedtime >> pedTl >> pedTr >> lped >> rped;
			if(!in.good()) break;
			pedlhist->Fill(lped);
			pedrhist->Fill(rped);
		}
	}
	in.close();

	c1->cd();
	pedlhist->Draw();
	pedlhist->Fit("gaus", "", "", 150, 160);
	Double_t pedlmean = pedlhist->GetFunction("gaus")->GetParameter(1);
	c1->SaveAs("CFDpedl.png");

	c2->cd();
	pedrhist->Draw();
	pedrhist->Fit("gaus", "", "", 105, 125);
	Double_t pedrmean = pedrhist->GetFunction("gaus")->GetParameter(1);
	c2->SaveAs("CFDpedr.png");

	//pr: position resolution
	TTree* pr[nFile];

	for(Int_t i = 0; i < nFile; i++)
	{
		in.open(file[i]);

		Double_t time = 0;
		Double_t Tl = 0;
		Double_t Tr = 0;
		Double_t Al = 0;
		Double_t Ar = 0;

		pr[i] = new TTree(distance[i], "position resolution data");
		pr[i]->Branch("Tl", &Tl, "Tl/D");
		pr[i]->Branch("Tr", &Tr, "Tr/D");
		pr[i]->Branch("Al", &Al, "Al/D");
		pr[i]->Branch("Ar", &Ar, "Ar/D");

		//correction 
		// 1. TDCchannel * ptfactor
		// 2. ADC - pedestal mean
		if(in.is_open())
		{
			while(1)
			{
				in >> time >> Tl >> Tr >> Al >> Ar;
				if(!in.good()) break;
				Tl = Tl*ptfactor;
				Tr = Tr*ptfactor;
				Al = Al-pedlmean;
				Ar = Ar-pedrmean;
				pr[i]->Fill();
			}
		}
		in.close();
	}
	f->Write();
}
