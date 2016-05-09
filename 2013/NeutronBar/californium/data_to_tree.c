///////////////////////////////////////////////////////////////////////
//This file convert datafile to treefile.                            //
//In this file pedestal, close distance between trigger and detector,//
//large destance between trigger and detector are used.              //
///////////////////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <fstream>
#include <iostream>

void data_to_tree()
{
	TFile* f = new TFile("data_to_tree.root", "RECREATE");

	ifstream in;
	ofstream out;

	//bring data files and give name to use in this code
	//data file name is in order dataType_ch0highvoltage_ch2highvoltage_#ofevent_file#.dat
	//ped: pedestal. acc: accidental.
	// only CFD is used in this experiment.
	const Char_t* peddatafile = "./Californium_data/pedestal_2090v_2160v_10k_4.dat";
	const Char_t* accdatafile = "./Californium_data/accidental_californium_2090v_2160v_2k.dat";
	const Char_t* datafile = "./Californium_data/californium_2090v_2160v_100k_137.5cm.dat";

	//define parameters to store data.
	Double_t pedtime = 0;
	Double_t pedTl = 0;
	Double_t pedTr = 0;
	Double_t rped = 0;  // = pedAl
	Double_t lped = 0; // = pedAr
	Double_t acctime = 0;
	Double_t accTl = 0;
	Double_t accTr = 0;
	Double_t accAl = 0;
	Double_t accAr = 0;
	Double_t time = 0;
	Double_t Tl = 0;
	Double_t Tr = 0;
	Double_t Al = 0;
	Double_t Ar = 0;

	TTree* pedestal = new TTree("pedestal", "ADCpedestal");
	pedestal->Branch("lped", &lped, "lped/D");
	pedestal->Branch("rped", &rped, "rped/D");

	TTree* accidental = new TTree("accidental", "accidental data");
	accidental->Branch("accTl", &accTl, "accTl/D");
	accidental->Branch("accTr", &accTr, "accTr/D");
	accidental->Branch("accAl", &accAl, "accAl/D");
	accidental->Branch("accAr", &accAr, "accAr/D"); // KYO : You also need accADC branches to perform TWC 

	TTree* data = new TTree("data", "added data");
	data->Branch("Tl", &Tl, "Tl/D");
	data->Branch("Tr", &Tr, "Tr/D");
	data->Branch("Al", &Al, "Al/D");
	data->Branch("Ar", &Ar, "Ar/D");

	// KYO : Give some cut to the data and acc (not for ped) 
	// if (0 < TCD < 2500)
	// If you are considering the efficiency, remove this cut and store the raw data to tree

	in.open(peddatafile);
	if(in.is_open())
	{	
		while(1)
		{
			in >> pedtime >> pedTl >> pedTr >> lped >> rped;
			if(!in.good()) break;
//			if(0 < pedTl && pedTl < 2500 && 0 < pedTr && pedTr < 2500) { pedestal->Fill(); }
			pedestal->Fill();
		}
	}
	in.close();

	in.open(accdatafile);
	if(in.is_open())
	{
		while(1)
		{
			in >> acctime >> accTl >> accTr >> accAl >> accAr;
			if(!in.good()) break;
			if(0 < accTl && accTl < 2500 && 0 < accTr && accTr < 2500) { accidental->Fill(); }
		}
	}
	in.close();

	in.open(datafile);
	if(in.is_open())
	{
		while(1)
		{
			in >> time >> Tl >> Tr >> Al >> Ar;
			if(!in.good()) break;
			if(0 < Tl && Tl < 2500 && 0 < Tr && Tr < 2500) { data->Fill(); }
		}
	}
	in.close();

	f->Write();
}
