#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 0.0 //set
#define XMAX 35.0 //set

void draw_hist_tof()
{
 TFile* f = new TFile("tof.root", "READ");
 TTree* t1 = (TTree*)f->Get("T"); 
 Int_t entryNum = t1->GetEntries();
 std::cout<< "entryNum : "<< entryNum <<std::endl;

 Double_t time;
 t1->SetBranchAddress("time",&time);

 TCanvas *c1 = new TCanvas("c1", "histogram with gaussian");
 TH1F *hx = new TH1F("hx", "count vs time", 100, XMIN, XMAX);

 for (Int_t i=0; i<entryNum; i++)
 {
  t1->GetEntry(i);
  hx->Fill(time);
 }
 hx->Draw();

 TF1* g1 = new TF1("g1", "gaus", 2., 4.2); //(name, type, Xmin, Xmax)
 TF1* g2 = new TF1("g2", "gaus", 18., 20.);
 TF1* total = new TF1("total","gaus(0)+gaus(3)",XMIN,XMAX); // combine g1 and g2

 Double_t par[6];

 hx->Fit(g1,"R");
 hx->Fit(g2,"R+");

 g1->GetParameters(&par[0]); //0,1,2 and 1 is the mean value
 g2->GetParameters(&par[3]); //3,4,5 and 4 is the mean value
 total->SetParameters(par); 
 hx->Fit(total,"R+");

// ========= Calculate kinetic energy (CGS units) ========== 

 Double_t tof = (par[4]-par[1])*(1e-09); // ns -> s
 Double_t gapt = 200; // cm
 Double_t v = gapt/tof; // cm/s
 Double_t c = 2.99792458*(1e+10); // cm/s
 Double_t gamma = 1/TMath::Sqrt(1-(v)*(v)/((c)*(c)));
 Double_t restE = 0.939565*1000; //GeV -> MeV
 Double_t totE = gamma*restE; //MeV
 Double_t kinE = totE-restE; //MeV

 std::cout<< "============================================"<<std::endl
          << "mean value for 1st peak : "<<par[1]<<" ns"<<std::endl
          << "mean value for 2nd peak : "<<par[4]<<" ns"<<std::endl
          << "Therefore, the time of flight : "<<tof<<" s"<<std::endl
          << "                                            "<<std::endl
          << "GapThickness :"<<gapt<<" cm"<<std::endl
          << "velocity of neutron : " <<v<<" cm/s"<<std::endl
          << "total energy : " <<totE<<" MeV"<<std::endl
          << "rest energy : " <<restE<<" MeV"<<std::endl
          << "rel. kinetic energy : " <<kinE<<" MeV"<<std::endl
          << "============================================"<<std::endl;

} 

