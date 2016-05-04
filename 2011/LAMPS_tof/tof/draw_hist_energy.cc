#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 144.5 //set
#define XMAX 151.5
#define Nbin 35 

void draw_hist_energy()
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
  TH1F *h1 = new TH1F("h1", "count vs kinetic energy", Nbin, XMIN, XMAX);

  TCanvas *c2 = new TCanvas("c2", "histogram");
  TH1F *h2 = new TH1F("h2", "count vs kinetic energy", Nbin, XMIN, XMAX);

  TF1 *g1 = new TF1("g1", "gaus", XMIN, XMAX); //gaussian fitting

 // ========== CGS units ========== 
  Double_t c = 2.99792458*(1e+10); // cm/s
  Double_t restE = 0.939565*1000; //GeV -> MeV

 // ============= without error ============== 
  c1->cd();

  for (Int_t i=0; i<entryNum; i++)
  {
    t1->GetEntry(i); // get data from t1 to here

    Double_t v = (length*100)/(time*(1e-09)); // m/ns -> cm/s
    Double_t gamma = 1/TMath::Sqrt(1-(v)*(v)/((c)*(c)));
    Double_t totE = gamma*restE; //MeV
    Double_t kinE = totE-restE; //MeV

    h1->Fill(kinE);
  }
  h1->Draw();
  h1->Fit(g1, "R");
  h1->GetXaxis()->SetTitle("energy (MeV)");
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

    Double_t v = (length*100)/(time*(1e-09)); // m/ns -> cm/s
    Double_t gamma = 1/TMath::Sqrt(1-(v)*(v)/((c)*(c)));
    Double_t totE = gamma*restE; //MeV
    Double_t kinE = totE-restE; //MeV

    h2->Fill(kinE);
  }
  h2->Draw();
  h2->Fit(g1, "R");
  h2->GetXaxis()->SetTitle("energy (MeV)");
  h2->GetYaxis()->SetTitle("counts");
}
