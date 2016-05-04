#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 144.5 //set
#define XMAX 151.5 //set

void draw_wo_uncertainty()
{
  TFile* f = new TFile("tof.root", "READ");
  TTree* t1 = (TTree*)f->Get("T"); //from T to t1 
  Int_t entryNum = t1->GetEntries(); //total entry number
  std::cout<< "entryNum : "<< entryNum <<std::endl;

  Double_t time;
  t1->SetBranchAddress("time",&time);//read the "time" from T to &time; 
  Double_t length;
  t1->SetBranchAddress("length",&length); 

  TCanvas *c1 = new TCanvas("c1", "histogram");
  TH1F *hx = new TH1F("hx", "count vs kinetic energy", 35, XMIN, XMAX);

 // ========== CGS units ========== 
  Double_t c = 2.99792458*(1e+10); // cm/s
  Double_t restE = 0.939565*1000; //GeV -> MeV

  for (Int_t i=0; i<entryNum; i++)
  {
    t1->GetEntry(i); // get data from t1 to here

    Double_t v = (length*100)/(time*(1e-09)); // m/ns -> cm/s
    Double_t gamma = 1/TMath::Sqrt(1-(v)*(v)/((c)*(c)));
    Double_t totE = gamma*restE; //MeV
    Double_t kinE = totE-restE; //MeV

//    std::cout << kinE << std::endl;
    hx->Fill(kinE);
  }
  hx->Draw();
}
