#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 52.0 //set
#define XMAX 53.5
#define Nbin 35 

void draw_time()
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
  TH1F *h1 = new TH1F("h1", "Helium gas (wo)", Nbin, XMIN, XMAX);

  TCanvas *c2 = new TCanvas("c2", "histogram");
  TH1F *h2 = new TH1F("h2", "Helium gas (w)", Nbin, XMIN, XMAX);

  TF1 *g1 = new TF1("g1", "gaus", XMIN, XMAX); //gaussian fitting

 // ============= without error ============== 
  c1->cd();

  for (Int_t i=0; i<entryNum; i++)
  {
    t1->GetEntry(i); // get data from t1 to here
    h1->Fill(time);
  }
  h1->Draw();
//  h1->Fit(g1, "R");
  h1->GetXaxis()->SetTitle("time of flight (ns)");
  h1->GetYaxis()->SetTitle("counts");

 // ============= with error ============== 

  gRandom->SetSeed();
  Float_t error;

  c2->cd(); //with error

  for (Int_t i=0; i<entryNum; i++)
  {
    t1->GetEntry(i); // get data from t1 to here

    error = gRandom -> Gaus(0, 0.1);
    time = time + error;
    h2->Fill(time);
  }
  h2->Draw();
  h2->Fit(g1, "R");
  h2->GetXaxis()->SetTitle("time of flight (ns)");
  h1->GetYaxis()->SetTitle("counts");
}
