#include "TFile.h"
#include "TTree.h"
#include <fstream>

Double_t linfunc(Double_t* x, Double_t* par)
{
  return par[0] + par[1]*x[0]; // linear fit : x = a+ bz
}

void method02()
{
////-------------------- read rootfile --------------------

  TFile* f = new TFile("rawData.root", "READ");
  TTree* t1 = (TTree*)f -> Get("SimulationData");

  Int_t entryNum = t1->GetEntries();
  std::cout<< " total entryNum = " << entryNum <<std::endl;

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

  TCanvas* c1 = new TCanvas("c1", "linear fit for DC0");
  TH2D* h1 = new TH2D("h1", "for DC0", 1000, 1200, 1700, 1000, -30, 20);
  TCanvas* c2 = new TCanvas("c2", "linear fit for DC3&4");
  TH2D* h2 = new TH2D("h2", "for DC3&4", 1000, 3200, 5400, 1000, 0, 4000);
  
  TF1* fit1 = new TF1("fit1", linfunc, 0.0, 7.0, 2); // xmin, xmax, NumOfPar)
  fit1->SetLineWidth(1);
  fit1->SetLineColor(2);
  fit1->SetParameters(1,1);

////-------------------- get data -------------------

  Double_t minTof = 1000; //default value
 
  for (Int_t i=0; i<entryNum; i++)
  {
    t1->GetEntry(i);

    if (isDC == 1) //for totalLength(mm): position info. from DC
    {
      if (detID == 0) {		h1->Fill(z, x); } 
      else if (detID == 3){	h2->Fill(z, x); }
      else if (detID == 4){	h2->Fill(z, x); }
    }

    if (isToF == 1) //for tof(ns): time of flight from ToF wall
    {
      if(x == 1 && minTof>hitTime) { minTof = hitTime; }
    } 
  }

  c1->cd();
  h1->GetXaxis()->SetTitle("z axis (mm)");
  h1->GetYaxis()->SetTitle("x axis (mm)"); 
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1);
  h1->Draw();
  h1->Fit(fit1, "C"); // don't calculate chisquare
  Double_t a1 = fit1->GetParameter(1); // p1=slope
  Double_t b1 = fit1->GetParameter(0); //p0=intercept : x=a1*z+b1

  c2->cd();
  h2->GetXaxis()->SetTitle("z axis (mm)");
  h2->GetYaxis()->SetTitle("x axis (mm)");
  h2->SetMarkerStyle(20);
  h2->SetMarkerSize(1);
  h2->Draw();
  h2->Fit(fit1, "C");
  Double_t a2 = fit1->GetParameter(1); //p1=slope
  //std::cout << "a2 = " << a2 << std::endl;
  Double_t b2 = fit1->GetParameter(0); //p0=intercept : x=a2*z+b2
  //std::cout << "b2 = " << b2 << std::endl;

////-------------------- analysis --------------------

  Double_t z1 = (2.243-b1*1e-3)/(a1+1); //mm -> m
  Double_t x1 = 2.243-z1;
  Double_t z2 = (3.657-b2*1e-3)/(a2+1);
  Double_t x2 = 3.657-z2;
  Double_t z3 = (8.183-b2*1e-3)/(a2+1);
  Double_t x3 = 8.183-z3;

  Double_t a11 = (-1/a1);  //slope
  Double_t b11 = (x1+(z1/a1)); //intercept
  Double_t a22 = (-1/a2);
  Double_t b22 = (x2+(z2/a2));

  Double_t z0 = (b22-b11)/(a11-a22); //center of the circle
  Double_t x0 = a11*z0+b11;
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

  std::cout << "					" <<std::endl;
  std::cout << " z1 = " << z1 << ",  x1 = " << x1 << std::endl;
  std::cout << " z2 = " << z2 << ",  x2 = " << x2 << std::endl;
  std::cout << " z3 = " << z3 << ",  x3 = " << x3 << std::endl;
  std::cout << "					" <<std::endl;
  //std::cout << " theta = " << theta << " (rad)" << std::endl;
  std::cout << " radius = " << radius << " (m)" << std::endl;
  //std::cout << " arc = " << arc << " (m)" << std::endl;
  std::cout << "					" <<std::endl;
  std::cout << " length1 = " << length1 << " (m)" << std::endl;
  std::cout << " length3 = " << length3 << " (m)" << std::endl;
  std::cout << "					" <<std::endl;
  std::cout << " travel length = " << totalLength << " (m)" << std::endl;
  std::cout << " time of flight = " << minTof << " (ns)" << std::endl;
  //std::cout << " velocity  = " << v << " (cm/s)" << std::endl;
  std::cout << "					" <<std::endl;
  std::cout << " momentum p = " << p << " (MeV/c)" << std::endl;
  std::cout << " mass m  = " << mass << " (MeV/c^2)" << std::endl;
  std::cout << "					" <<std::endl;

}
