#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 880 //850
#define XMAX 980 //1050
#define Nbin 40 //20

Double_t linfunc(Double_t* x, Double_t* par)
{
  return par[0] + par[1]*x[0];
}

void draw_mass_Eloss_upper()
{
////-------------------- read rootfile --------------------

  TFile* f = new TFile("rawData.root", "READ");
  TTree* t1 = (TTree*)f -> Get("SimulationData");
 
  Int_t eventID;		t1->SetBranchAddress("eventID", &eventID);
  Double_t energyDeposit; 	t1->SetBranchAddress("energyDeposit", &energyDeposit);
  Double_t hitTime;		t1->SetBranchAddress("hitTime", &hitTime);
  Int_t isDC;			t1->SetBranchAddress("isDC", &isDC);
  Int_t detID;			t1->SetBranchAddress("detID", &detID);
  Double_t x;			t1->SetBranchAddress("x", &x);
  Double_t y;			t1->SetBranchAddress("y", &y);
  Double_t z;			t1->SetBranchAddress("z", &z);
  Int_t isToF;			t1->SetBranchAddress("isToF", &isToF);
  Int_t detNum;			t1->SetBranchAddress("detNum", &detNum);

  TCanvas *c1 = new TCanvas ("c1", "histogram");
  TH1F* h1 = new TH1F("h1", "mass ditribution", Nbin, XMIN, XMAX);
  TF1* g1 = new TF1("g1", "gaus", XMIN, XMAX);
 
//  TCanvas* cf2 = new TCanvas("cf2", "linear fit for DC3&4");
    TF1* fit1 = new TF1("fit1", linfunc, 0.0, 7.5, 2);
//  fit1->SetLineWidth(1);
//  fit1->SetLineColor(2);
//  fit1->SetParameters(1,1);

////-------------------- get data --------------------

  for (Int_t i=0; i<4; i++)
  {
    TH2D* hf2 = new TH2D("hf2", "for DC3&4", 1000, 0, 7500, 1000, 0, 5000);
    Int_t entryNum = t1->GetEntries(Form("eventID == %d", i)); // entryNum per event
    TTree* t1event = t1->CopyTree(Form("eventID == %d", i)); //make new tree for one event
   
    Double_t ex[2]={0,0}; Double_t ey[2]={0,0}; Double_t ez[2]={0,0};
    /*Double_t eDep1=0;*/ Double_t eDep2=0; Double_t eDep3=0;
    Double_t minTof = 100; //default value (to find mininum tof)
    
    for (Int_t k=0; k<entryNum; k++)
    { 
      t1event->GetEntry(k);

      if (isDC == 1) //for totalLength(mm) : position info. from DC
      {
//	if (detID == 0 && energyDeposit>eDep1)
//		{ eDep1=energyDeposit; x1=x*1e-3; y1=y*1e-3; z1=z*1e-3+0.8;}
	if (detID == 1 && energyDeposit>eDep2)
		{ eDep2=energyDeposit; ex[0]=x; ey[0]=y; ez[0]=z;}
	else if (detID == 2 && energyDeposit>eDep3)
		{ eDep3=energyDeposit; ex[1]=x; ey[1]=y; ez[1]=z;}
      }

      if (isToF == 1) //for  tof(ns) : time of flight from ToF wall
      {
	if(x == 0 && minTof>hitTime) { minTof = hitTime; }
      } 
    }

  for (Int_t q=0; q<2; q++) hf2->Fill(ez[q], ex[q]);

//  cf2->cd();
//  hf2->SetMarkerStyle(20);
//  hf2->SetMarkerSize(1);
//  hf2->Draw();
  hf2->Fit(fit1, "QNO");
  Double_t a2 = fit1->GetParameter(1); //slope
  Double_t b2 = fit1->GetParameter(0); //intercept
  delete hf2;

////-------------------- analysis--------------------

  std::cout <<"ez0, ex0 = " << ez[0]<< " , "<<ex[0]<<std::endl;
  std::cout <<"ez1, ex1 = " << ez[1]<< " , "<<ex[1]<<std::endl;
  std::cout<< "a2 = " << a2<< std::endl;
  std::cout<< "b2 = " <<b2<<std::endl;

  Double_t z1 = 2.243; //mm -> m
  Double_t x1 = 0;
  Double_t z2 = (3.657-b2*1e-3)/(a2+1);
  Double_t x2 = 3.657-z2;
  Double_t x3 = 4.20;
  Double_t z3 = (4.20-b2*1e-3)/a2;

  Double_t a22 = (-1/a2); //slope
  Double_t b22 = (x2+(z2/a2)); //intercept

  Double_t z0 = z1; //center of the circle
  Double_t x0 = a22*z0+b22;

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
  std::cout << " theta = " << theta << " (rad)" << std::endl;
  std::cout << " radius = " << radius << " (m)" << std::endl;
  std::cout << " arc = " << arc << " (m)" << std::endl;
  std::cout << "					" <<std::endl;
  std::cout << " length1 = " << length1 << " (m)" << std::endl;
  std::cout << " length3 = " << length3 << " (m)" << std::endl;
  std::cout << "					" <<std::endl;
  std::cout << " travel length = " << totalLength << " (m)" << std::endl;
  std::cout << " time of flight = " << minTof << " (ns)" << std::endl;
  std::cout << " velocity  = " << v << " (cm/s)" << std::endl;
  std::cout << "					" <<std::endl;
  std::cout << "p = " << p << " MeV/c,   m = " << mass << " MeV/c^2" << std::endl; 
  std::cout << "					" <<std::endl;
  h1->Fill(mass);
  }
  h1->Draw();
  h1->Fit(g1,"R");
  h1->GetXaxis()->SetTitle("mass (MeV/c^2)");
  h1->GetYaxis()->SetTitle("counts");
  c1->SaveAs("0103.png");
}

