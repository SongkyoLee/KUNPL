#include "TFile.h"
#include "TTree.h"
#include "TH3D.h"
#include "TROOT.h"
#include "Riostream.h"

void divide_rawData()
{
	TFile* openFile = new TFile("rawData.root","READ");
	TTree* GeneratorData = (TTree*)openFile -> Get("GeneratorData");
	TTree* SimulationData = (TTree*)openFile -> Get("SimulationData");

	TFile *writeFile01 = new TFile("rawData01.root", "RECREATE");
	TTree *GeneratorData01 = GeneratorData -> CopyTree("eventID>=0&&eventID<1000");
	TTree *SimulationData01 = SimulationData -> CopyTree("eventID>=0&&eventID<1000");
	writeFile01 -> Write();
	writeFile01 -> Close();
	delete writeFile01;

	TFile *writeFile02 = new TFile("rawData02.root", "RECREATE");
	TTree *GeneratorData02 = GeneratorData -> CopyTree("eventID>=1000&&eventID<2000");
	TTree *SimulationData02 = SimulationData -> CopyTree("eventID>=1000&&eventID<2000");
	writeFile02 -> Write();
	writeFile02 -> Close();
	delete writeFile02;

	TFile *writeFile03= new TFile("rawData03.root", "RECREATE");
	TTree *GeneratorData03 = GeneratorData -> CopyTree("eventID>=2000&&eventID<3000");
	TTree *SimulationData03 = SimulationData -> CopyTree("eventID>=2000&&eventID<3000");
	writeFile03 -> Write();
	writeFile03 -> Close();
	delete writeFile03;

	TFile *writeFile04= new TFile("rawData04.root", "RECREATE");
	TTree *GeneratorData04 = GeneratorData -> CopyTree("eventID>=3000&&eventID<4000");
	TTree *SimulationData04 = SimulationData -> CopyTree("eventID>=3000&&eventID<4000");
	writeFile04 -> Write();
	writeFile04 -> Close();
	delete writeFile04;

	TFile *writeFile05= new TFile("rawData05.root", "RECREATE");
	TTree *GeneratorData05 = GeneratorData -> CopyTree("eventID>=4000&&eventID<5000");
	TTree *SimulationData05 = SimulationData -> CopyTree("eventID>=4000&&eventID<5000");
	writeFile05 -> Write();
	writeFile05 -> Close();
	delete writeFile05;

	TFile *writeFile06= new TFile("rawData06.root", "RECREATE");
	TTree *GeneratorData06 = GeneratorData -> CopyTree("eventID>=5000&&eventID<6000");
	TTree *SimulationData06 = SimulationData -> CopyTree("eventID>=5000&&eventID<6000");
	writeFile06 -> Write();
	writeFile06 -> Close();
	delete writeFile06;

	TFile *writeFile07= new TFile("rawData07.root", "RECREATE");
	TTree *GeneratorData07 = GeneratorData -> CopyTree("eventID>=6000&&eventID<7000");
	TTree *SimulationData07 = SimulationData -> CopyTree("eventID>=6000&&eventID<7000");
	writeFile07 -> Write();
	writeFile07 -> Close();
	delete writeFile07;

	TFile *writeFile08= new TFile("rawData08.root", "RECREATE");
	TTree *GeneratorData08 = GeneratorData -> CopyTree("eventID>=7000&&eventID<8000");
	TTree *SimulationData08 = SimulationData -> CopyTree("eventID>=7000&&eventID<8000");
	writeFile08 -> Write();
	writeFile08 -> Close();
	delete writeFile08;

	TFile *writeFile09= new TFile("rawData09.root", "RECREATE");
	TTree *GeneratorData09 = GeneratorData -> CopyTree("eventID>=8000&&eventID<9000");
	TTree *SimulationData09 = SimulationData -> CopyTree("eventID>=8000&&eventID<9000");
	writeFile09 -> Write();
	writeFile09 -> Close();
	delete writeFile09;

	TFile *writeFile10= new TFile("rawData10.root", "RECREATE");
	TTree *GeneratorData10 = GeneratorData -> CopyTree("eventID>=9000&&eventID<10000");
	TTree *SimulationData10 = SimulationData -> CopyTree("eventID>=9000&&eventID<10000");
	writeFile10 -> Write();
	writeFile10 -> Close();
	delete writeFile10;

	return;
}
