#include "TFile.h"
#include "TTree.h"
#include <fstream>

void make_rootfile_02() //without temp
{
 std::ifstream Fin("iqmd4.dat",std::ios::in); // in : read the file

 Int_t numTrack, pID;
 Double_t  mass, px, py, pz;

 TFile *f = new TFile("rootfile02.root", "RECREATE"); //make rootfile
 TTree *tr = new TTree("Tree", ""); //tree
 tr->Branch("numTrack", &numTrack, "numTrack/I"); //branch (I : Integer litera)
 tr->Branch("pID", &pID, "pID/I");
 tr->Branch("mass", &mass, "mass/D"); // D : double literal
 tr->Branch("px", &px, "px/D");
 tr->Branch("py", &py, "py/D");
 tr->Branch("pz", &pz, "pz/D");

 for(Int_t i; i<278038; i++)
 {
	Fin >> numTrack >> pID >> mass >> px >> py >> pz ;
	tr -> Fill();
 }

 f->Write();

}
