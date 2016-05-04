#include "TFile.h"
#include "TTree.h"
#include <fstream>

void draw_hist_Bragg()
{
 TFile* f = new TFile("bragg.root", "READ");
 TTree* t1 = (TTree*)f->Get("T"); 
 Int_t entryNum = t1->GetEntries();
 std::cout<< "entryNum : "<< entryNum <<std::endl;

 Double_t layer;
 Double_t energy;
 t1->SetBranchAddress("layer",&layer);
 t1->SetBranchAddress("energy",&energy);

 TCanvas *c1 = new TCanvas("c1", "histogram1");
 TH2F *hxy = new TH2F("hxy", "Energy vs Layer", 100, 0., 70., 100, 0., 20.);

 for (Int_t i=0; i<entryNum; i++)
 {
  t1->GetEntry(i);
  hxy->Fill(layer,energy);
  hxy->SetMarkerStyle(20);
  hxy->SetMarkerSize(.5);
  hxy->Draw();
 }
} 
