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

	TFile* f = new TFile("data_to_tree_t4.root", "RECREATE");

	ifstream in;
	ofstream out;

	//bring data files and give name to use in this code.
	//data file name is in order type_ch0threshold(left)_ch2threshold(right)_ch0highvoltage_ch2highvoltage_#ofevent
	const Char_t* file[9] = {"VTD_Co_10cm_t4.dat",
									"VTD_Co_20cm_t4.dat",
									"VTD_Co_30cm_t4.dat",
									"VTD_Co_40cm_t4.dat",
									"VTD_Co_50cm_t4.dat",
									"VTD_Co_60cm_t4.dat",
									"VTD_Co_70cm_t4.dat",
									"VTD_Co_80cm_t4.dat",
									"VTD_Co_90cm_t4.dat"};

	const Char_t* distance[9] = {"10cm", "20cm", "30cm", "40cm", "50cm", "60cm", "70cm", "80cm", "90cm"};

	TCanvas* c1 = new TCanvas("c1", "pedl", 200, 0, 600, 600);
	TH1F* pedlhist = new TH1F("pedlhist", "left", 200, 0, 200);
	TCanvas* c2 = new TCanvas("c2", "pedr", 210, 10, 610, 610);
	TH1F* pedrhist = new TH1F("pedrhist", "right", 200, 0, 200);

	in.open("VTD_pedestal.dat");

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
	pedlhist->Fit("gaus", "", "", 122, 126);
	Double_t pedlmean = pedlhist->GetFunction("gaus")->GetParameter(1);
	c1->SaveAs("VTDpedl.png");

	c2->cd();
	pedrhist->Draw();
	pedrhist->Fit("gaus", "", "", 92, 107);
	Double_t pedrmean = pedrhist->GetFunction("gaus")->GetParameter(1);
	c2->SaveAs("VTDpedr.png");

	//pr: position resolution
	TTree* pr[9];

	for(Int_t i = 0; i < 9; i++)
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
