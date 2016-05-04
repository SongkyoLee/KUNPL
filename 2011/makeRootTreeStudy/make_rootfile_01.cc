#include "TFile.h"
#include "TTree.h"
#include <fstream>

void make_rootfile_01() //with temp (meaningless..)
{
 std::ifstream Fin("iqmd4.dat",std::ios::in); // in : read the file

 Double_t numTrack, pID, mass, px, py, pz;
 Double_t temp[6];

 TFile *f = new TFile("rootfile01.root", "RECREATE"); //make rootfile
 TTree *tr = new TTree("Tree", ""); //tree
 tr->Branch("numTrack", &numTrack, "numTrack/D"); //branch (D : double value)
 tr->Branch("pID", &pID, "pID/D");
 tr->Branch("mass", &mass, "mass/D");
 tr->Branch("px", &px, "px/D");
 tr->Branch("py", &py, "py/D");
 tr->Branch("pz", &pz, "pz/D");

 for(Int_t i; i<278038; i++)
 {
	Fin >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4]>> temp[5] ;
	numTrack = temp[0];
	pID = temp[1];
 	mass = temp[2];
 	px = temp[3];
	py = temp[4];
 	pz = temp[5];

	tr -> Fill();
 }

 f->Write();

}
