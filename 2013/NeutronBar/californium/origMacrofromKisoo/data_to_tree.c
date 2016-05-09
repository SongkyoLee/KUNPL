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
	//data file name is in order distance_ch0threshold(left)_ch2threshold(right)_ch0highvoltage_ch2highvoltage_#ofevent_file#.
	//ped: pedestal. acc: accidental. datam3 and datam4 are same condition. They must be added.
	const Char_t* peddatafile = "VTD_pedestal.dat";
	const Char_t* accdatafile_1 = "accidental_1k_1.dat";
	const Char_t* accdatafile_2 = "accidental_1k_2.dat";
	const Char_t* datafile = "VTD_Cf.dat";

	//define parameters which store data.
	Double_t pedtime = 0;
	Double_t pedTl = 0;
	Double_t pedTr = 0;
	Double_t rped = 0;
	Double_t lped = 0;
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

	TTree* data = new TTree("data", "added data");
	data->Branch("Tl", &Tl, "Tl/D");
	data->Branch("Tr", &Tr, "Tr/D");
	data->Branch("Al", &Al, "Al/D");
	data->Branch("Ar", &Ar, "Ar/D");

	in.open(peddatafile);
	if(in.is_open())
	{
		while(1)
		{
			in >> pedtime >> pedTl >> pedTr >> lped >> rped;
			if(!in.good()) break;
			pedestal->Fill();
		}
	}
	in.close();

	in.open(accdatafile_1);
	if(in.is_open())
	{
		while(1)
		{
			in >> acctime >> accTl >> accTr >> accAl >> accAr;
			if(!in.good()) break;
			accidental->Fill();
		}
	}
	in.close();

	in.open(accdatafile_2);
	if(in.is_open())
	{
		while(1)
		{
			in >> acctime >> accTl >> accTr >> accAl >> accAr;
			if(!in.good()) break;
			accidental->Fill();
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
			data->Fill();
		}
	}
	in.close();

	f->Write();
}
