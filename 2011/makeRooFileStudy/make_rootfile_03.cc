#include "TFile.h"
#include "TTree.h"
#include <fstream>

void make_rootfile_03() // categorize by event number!!
{
 std::ifstream Fin("iqmd4.dat",std::ios::in); // in : read the file

 Int_t temp, numTrack, pID;
 Double_t mass, px, py, pz;
 Int_t event = 0;

 TFile *f = new TFile("rootfile.root", "RECREATE"); //make rootfile
 TTree *tr = new TTree("Tree", ""); //tree
 tr->Branch("event", &event, "event/I"); //branch (I : Integer literal) 
 tr->Branch("pID", &pID, "pID/I");
 tr->Branch("mass", &mass, "mass/D"); // D : double literal
 tr->Branch("px", &px, "px/D");
 tr->Branch("py", &py, "py/D");
 tr->Branch("pz", &pz, "pz/D");

 Fin >> numTrack >> pID >> mass >> px >> py >> pz ;

 while(Fin)
 { 
	temp = numTrack; // for categorizing
	
	 for(Int_t i=0; i<temp; i++)
 	{
		tr->Fill();
 		Fin >> numTrack >> pID >> mass >> px >> py >> pz ;
//		cout << "numTrack: " << i << endl;
 	}
//	cout << "event: " << event << endl;
	event++;
 }
 f->Write();
}
