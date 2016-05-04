 #include "TFile.h"
 #include "TTree.h"
 #include <fstream> 

 void make_root_Bragg()
{
 std::ifstream Fin("data.txt",std::ios::in); //read <data.txt> file

 Double_t layer, energy, time;
 Double_t temp[3];

 TFile *f = new TFile("bragg.root", "RECREATE"); //make <bragg.root>
 TTree *tr = new TTree("T", "exampleN03");
 tr->Branch("layer",&layer,"layer/D");
 tr->Branch("energy",&energy,"energy/D");
 tr->Branch("time",&time,"time/D");

 for(Int_t i=0; i<65; i++)
 {
  Fin >> temp[0] >> temp[1] >> temp[2] ;
  layer = temp[0];
  energy = temp[1];
  time = temp[2];

  std::cout<<layer<<" "<<energy<<" "<<time<<std::endl;
  tr->Fill();
 }
 f -> Write();
}
