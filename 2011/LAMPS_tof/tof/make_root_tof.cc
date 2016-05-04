 #include "TFile.h"
 #include "TTree.h"
 #include <fstream> 

 void make_root_tof()
{
 std::ifstream Fin("edep.out",std::ios::in); //read edep.out file

 Double_t length, time;

 TFile *f = new TFile("tof.root", "RECREATE"); //create tof.root file
 TTree *tr = new TTree("T", "example");
 tr->Branch("length",&length,"length/D"); //get &length from length
 tr->Branch("time",&time,"time/D");

 for(Int_t i=0; i<10000; i++) // total line of edep.out
 {
  Fin >> length >>  time ;
//  std::cout<<length<<" "<<time<<std::endl;
  tr->Fill();
 }
 f -> Write(); 
}
