#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 0.0 //set
#define XMAX 100.0 //set

void draw_hist_tof()
{
 TFile* f = new TFile("tof.root", "READ");
 TTree* t1 = (TTree*)f->Get("T"); //from T to t1 
 Int_t entryNum = t1->GetEntries(); //total entry number
 std::cout<< "entryNum : "<< entryNum <<std::endl;

 Double_t time;
 t1->SetBranchAddress("time",&time);//read the "time" from T to &time;
 
 Double_t length;
 t1->SetBranchAddress("length",&length); 

// TCanvas *c1 = new TCanvas("c1", "histogram");
// TH1F *hx = new TH1F("hx", "count vs time", 100, XMIN, XMAX);

 Double_t meanLength;
 Double_t minTime;
 for (Int_t i=0; i<entryNum; i++)
 {
  t1->GetEntry(i); // get data from t1 to here
  std::cout<< "time : " << time << std::endl;
  std::cout <<"length : " << length << std::endl;
  minTime = 100;
  if ( time < minTime ) minTime = time; //minimun value of time
//  hx->Fill(time);

  meanLength += length; //sum (not normalized)
 }
// hx->Draw();

// std::cout << " meanlength sum :" << meanLength << std::endl;

 meanLength = meanLength/entryNum; //mean value of length

 std::cout << " meanlength :" << meanLength << std::endl;
 std::cout << " mintime :" << minTime << std::endl;


 // ========== Calculate kinetic energy (CGS units) ========== 

 Double_t v = (meanLength*100)/(minTime*(1e-09)); // m/ns -> cm/s
 Double_t c = 2.99792458*(1e+10); // cm/s
 Double_t gamma = 1/TMath::Sqrt(1-(v)*(v)/((c)*(c)));
 Double_t restE = 0.939565*1000; //GeV -> MeV
 Double_t totE = gamma*restE; //MeV
 Double_t kinE = totE-restE; //MeV

 std::cout<< "============================================"<<std::endl
          << "time of flight : "<< minTime <<" ns"<<std::endl
          << "                                            "<<std::endl
          << "travel length :"<< meanLength <<" m"<<std::endl
          << "velocity of particle : " <<v<<" cm/s"<<std::endl
          << "total energy : " <<totE<<" MeV"<<std::endl
          << "rest energy : " <<restE<<" MeV"<<std::endl
          << "rel. kinetic energy : " <<kinE<<" MeV"<<std::endl
          << "============================================"<<std::endl;
} 

