#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 820
#define XMAX 1070
#define Nbin 20

Double_t linfunc(Double_t* x, Double_t* par)
{
  return par[0] + par[1]*x[0];
}

void t_draw_mass_04()
{
////-------------------- read rootfile --------------------

  TFile* f = new TFile("rawData.root", "READ");
  TTree* t1 = (TTree*)f -> Get("SimulationData");
 
  Int_t eventID;	t1->SetBranchAddress("eventID", &eventID);
  Double_t hitTime;	t1->SetBranchAddress("hitTime", &hitTime);
  Int_t isDC;		t1->SetBranchAddress("isDC", &isDC);
  Int_t detID;		t1->SetBranchAddress("detID", &detID);
  Double_t x;		t1->SetBranchAddress("x", &x);
  Double_t y;		t1->SetBranchAddress("y", &y);
  Double_t z;		t1->SetBranchAddress("z", &z);
  Int_t isToF;		t1->SetBranchAddress("isToF", &isToF);
  Int_t detNum;		t1->SetBranchAddress("detNum", &detNum);

  TCanvas *c1 = new TCanvas ("c1", "histogram");
  TH1F* h1 = new TH1F("h1", "mass ditribution", Nbin, XMIN, XMAX);
  TF1* g1 = new TF1("g1", "gaus", XMIN, XMAX);
  
  TCanvas* cf2 = new TCanvas("cf2","linear fit");
  TF1* fit1 = new TF1("fit1", linfunc, 0.0, 7.5, 2);
  fit1->SetLineWidth(1);
  fit1->SetLineColor(2);
  fit1->SetParameters(1,1);

////-------------------- get data --------------------

  for (Int_t i=0; i<5; i++)
  {
    TH2D* hf2 = new TH2D("hf2", "for DC3&4", 1000, 3.0, 7.5, 1000, 0, 5.0);

    Int_t entryNum = t1->GetEntries(Form("eventID == %d", i)); // entryNum per event
    TTree* t1event = t1->CopyTree(Form("eventID == %d", i)); //make new tree for one event
    
    Double_t sx1=0;	Double_t sy1=0;	Double_t sz1=0;	Double_t j1=0;  //sx1 == sum of x1
    Double_t sx2=0;	Double_t sy2=0;	Double_t sz2=0;	Double_t j2=0;
    Double_t sx3=0;	Double_t sy3=0;	Double_t sz3=0;	Double_t j3=0;
    Double_t minTof = 100; //default value (to find mininum tof)
    
    for (Int_t k=0; k<entryNum; k++)
    { 
      t1event->GetEntry(k);

      if (isDC == 1) //for totalLength(mm) : position info. from DC
      {
	if (detID == 0){	sx1+=x; sy1+=y; sz1+=z;	j1 ++;}
	else if (detID == 3){ sx2+=x; sy2+=y; sz2+=z;	j2 ++;}
	else if (detID == 4){ sx3+=x; sy3+=y; sz3+=z;	j3 ++;}
      }

      if (isToF == 1) //for  tof(ns) : time of flight from ToF wall
      {
	if(x == 1 && minTof>hitTime) { minTof = hitTime; }
      } 
    }

////-------------------- analysis--------------------

  Double_t ex[2] = {1e-3*sx2/j2, 1e-3*sx3/j3}; //mm -> m
  Double_t ez[2] = {1e-3*sz2/j2, 1e-3*sz3/j3};

  for (Int_t q=0; q<2; q++) hf2->Fill(ez[q], ex[q]);

  cf2->cd();
  hf2->SetMarkerStyle(20);
  hf2->SetMarkerSize(0.7);
  hf2->Fit(fit1, "C");
  hf2->Draw();
  Double_t a2 = fit1->GetParameter(1); //slope
  Double_t b2 = fit1->GetParameter(0); //intercept
  cf2->SaveAs(Form("t_04_fit_%d.png", i));
  delete hf2;
 
  Double_t z1 = 2.243;
  Double_t x1 = 0;
  Double_t z2 = (3.657-b2)/(a2+1);
  Double_t x2 = 3.657-z2;
  Double_t z3 = (8.183-b2)/(a2+1);
  Double_t x3 = 8.183-z3;
 
  Double_t length1 = TMath::Sqrt( x1*x1 + z1*z1 );
  Double_t length2 = TMath::Sqrt( (x2-x1)*(x2-x1)+(z2-z1)*(z2-z1) );
  Double_t length3 = TMath::Sqrt( (x3-x2)*(x3-x2)+(z3-z2)*(z3-z2) );

  Double_t theta = TMath::ATan((x2-x1)/(z2-z1));
  Double_t radius = length2/(2*sin(theta));
  Double_t arc = radius*2*theta;

  Double_t p = 0.3*radius*1000; //GeV/c -> MeV/c

  Double_t totalLength = length1 + arc + length3;
  Double_t v = (totalLength*100)/(minTof*1e-9) ; // m/ns -> cm/s
  Double_t c = 2.99792458*(1e+10); // cm/s      
  Double_t gamma = 1/TMath::Sqrt(1-((v*v)/(c*c)));

  Double_t mass = p*c/(gamma*v);

  //std::cout << "					" <<std::endl;
  //std::cout << " z1 = " << z1 << ",  x1 = " << x1 << std::endl;
  //std::cout << " z2 = " << z2 << ",  x2 = " << x2 << std::endl;
  //std::cout << " z3 = " << z3 << ",  x3 = " << x3 << std::endl;
  //std::cout << "					" <<std::endl;
  //std::cout << " theta = " << theta << " (rad)" << std::endl;
  //std::cout << " radius = " << radius << " (m)" << std::endl;
  //std::cout << " arc = " << arc << " (m)" << std::endl;
  //std::cout << "					" <<std::endl;
  //std::cout << " length1 = " << length1 << " (m)" << std::endl;
  //std::cout << " length3 = " << length3 << " (m)" << std::endl;
  //std::cout << "					" <<std::endl;
  //std::cout << " travel length = " << totalLength << " (m)" << std::endl;
  //std::cout << " time of flight = " << minTof << " (ns)" << std::endl;
  //std::cout << " velocity  = " << v << " (cm/s)" << std::endl;
  //std::cout << "					" <<std::endl;
  //std::cout << "p = " << p << " MeV/c,   m = " << mass << " MeV/c^2" << std::endl; 
  //std::cout << "					" <<std::endl;
  h1->Fill(mass);
  }
  c1->cd();
  h1->Draw();
  h1->Fit(g1,"R");
  h1->GetXaxis()->SetTitle("mass (MeV/c^2)");
  h1->GetYaxis()->SetTitle("counts");
  c1->SaveAs("t_04.png");
}

