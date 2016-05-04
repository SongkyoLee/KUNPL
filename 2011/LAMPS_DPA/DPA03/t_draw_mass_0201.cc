#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 850
#define XMAX 1050
#define Nbin 50

Double_t linfunc(Double_t* x, Double_t* par)
{
  return par[0] + par[1]*x[0]; // linear fit : x = a+ bz
}

void t_draw_mass_0201()
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

////-------------------- histogram --------------------

  //TCanvas* cf1 = new TCanvas("cf1", "linear fit for DC0");
  //TCanvas* cf2 = new TCanvas("cf2", "linear fit for DC3&4");
  
  TF1* fit1 = new TF1("fit1", linfunc, 0.0, 7.5, 2); // xmin, xmax, NumOfPar)
  //fit1->SetLineWidth(1);
  //fit1->SetLineColor(2);
  //fit1->SetParameters(1,1);

  TCanvas* c1 = new TCanvas("c1", "histogram");
  TH1F* h1 = new TH1F("h1", "mass distribution", Nbin, XMIN, XMAX);
  TF1* g1 = new TF1("g1", "gaus", XMIN, XMAX);

////-------------------- get data -------------------

  Double_t minTof = 1000; //default value
 
  for (Int_t i=0; i<10; i++)
  {

  TH2D* hf1 = new TH2D("hf1", "for DC0", 1000, 1200, 1700, 1000, -30, 20);
  TH2D* hf2 = new TH2D("hf2", "for DC3&4", 1000, 300, 7500, 1000, 0, 5000);

    Int_t entryNum = t1->GetEntries(Form("eventID==%d",i));
    TTree* t1event = t1->CopyTree(Form("eventID==%d",i));

    for(Int_t k=0; k<entryNum; k++)
    {
      t1event->GetEntry(k);

      if (isDC == 1) //for totalLength(mm): position info. from DC
      {
        //if (detID == 0) {		hf1->Fill(z, x); } 
        if (detID == 3){	hf2->Fill(z, x); }
        else if (detID == 4){	hf2->Fill(z, x); }
      }

      if (isToF == 1) //for tof(ns): time of flight from ToF wall
      {
        if(x == 1 && minTof>hitTime) { minTof = hitTime; }
      } 
    }

  //cf1->cd();
  //hf1->GetXaxis()->SetTitle("z axis (mm)");
  //hf1->GetYaxis()->SetTitle("x axis (mm)"); 
  //hf1->SetMarkerStyle(20);
  //hf1->SetMarkerSize(1);
  //hf1->Draw();
  //hf1->Fit(fit1, "QNO");
  //Double_t a1 = fit1->GetParameter(1); // p1=slope
  //Double_t b1 = fit1->GetParameter(0); //p0=intercept : x=a1*z+b1

  //cf2->cd();
  //hf2->GetXaxis()->SetTitle("z axis (mm)");
  //hf2->GetYaxis()->SetTitle("x axis (mm)");
  //hf2->SetMarkerStyle(20);
  //hf2->SetMarkerSize(1);
  //hf2->Draw();
  hf2->Fit(fit1, "QNO");
  Double_t a2 = fit1->GetParameter(1); //p1=slope
  Double_t b2 = fit1->GetParameter(0); //p0=intercept : x=a2*z+b2
  delete hf2;

////-------------------- analysis --------------------

  Double_t z1 = 2.243; //mm -> m
  Double_t x1 = 0;
  Double_t z2 = (3.657-b2*1e-3)/(a2+1);
  Double_t x2 = 3.657-z2;
  Double_t z3 = (8.183-b2*1e-3)/(a2+1);
  Double_t x3 = 8.183-z3;

  Double_t a22 = (-1/a2); //slope
  Double_t b22 = (x2+(z2/a2)); //intercept

  Double_t z0 = z1; //center of the circle
  Double_t x0 = a22*z0+b22;
  //std::cout << " z0 = " << z0 << std::endl;
  //std::cout << " x0 = " << x0 << std::endl;

  Double_t length1 = TMath::Sqrt(x1*x1 + z1*z1);
  Double_t length3 = TMath::Sqrt((x3-x2)*(x3-x2) + (z3-z2)*(z3-z2));

  Double_t theta = TMath::ATan((x2-x1)/(z2-z1));
  Double_t radius = TMath::Sqrt((z0-z1)*(z0-z1)+(x0-x1)*(x0-x1));
  Double_t arc = radius*2*theta;

  Double_t p = 0.3*radius*1000; //GeV/c -> MeV/c

  Double_t totalLength = length1 + arc + length3;
  Double_t v = (totalLength*100)/(minTof*1e-9); //m/ns -> cm/s
  Double_t c = 2.99792458*(1e+10); // cm/s      
  Double_t gamma = 1/TMath::Sqrt(1-((v*v)/(c*c)));

  Double_t mass = p*c/(gamma*v);

  h1->Fill(mass);
  
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
  //std::cout << " momentum p = " << p << " (MeV/c)" << std::endl;
  //std::cout << " mass m  = " << mass << " (MeV/c^2)" << std::endl;
  std::cout << "p = " << p << " MeV,   m = " << mass << " MeV" << std::endl; 
  //std::cout << "					" <<std::endl;
  }
  h1->Draw();
  h1->Fit(g1, "R");
  h1->GetXaxis()->SetTitle("mass (MeV/c^2)");
  h1->GetYaxis()->SetTitle("counts");
  
}
