#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 820
#define XMAX 1070
#define Nbin 20

void method01()
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

////-------------------- get data --------------------

  for (Int_t i=0; i<1000; i++)
  {
    Int_t entryNum = t1->GetEntries(Form("eventID == %d", i)); // entryNum per event
    //std::cout<< i <<"th entryNum = " << entryNum <<std::endl;
    
    Double_t sx1=0;	Double_t sy1=0;	Double_t sz1=0;	Double_t j1=0;  //sx1 == sum of x1
    Double_t sx2=0;	Double_t sy2=0;	Double_t sz2=0;	Double_t j2=0;
    Double_t sx3=0;	Double_t sy3=0;	Double_t sz3=0;	Double_t j3=0;
    Double_t minTof = 100; //default value (to find mininum tof)

    TTree* t1event = t1->CopyTree(Form("eventID == %d", i)); //make new tree for one event
    
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

  Double_t x1 = 1e-3*sx1/j1; Double_t y1 = 1e-3*sy1/j2; Double_t z1 = 1e-3*sz1/j1 +.8; 
  Double_t x22 =1e-3*sx2/j2; Double_t y22 =1e-3*sy2/j2; Double_t z22 =1e-3*sz2/j2;
  Double_t x3 = 1e-3*sx3/j3; Double_t y3 = 1e-3*sy3/j3; Double_t z3 = 1e-3*sz3/j3; //mm->m

  Double_t theta2 = TMath::ATan((x3-x22)/(z3-z22));
  Double_t length22 = .25/(cos(theta2-(TMath::Pi()/4)));
  Double_t length33 = .10/(cos(theta2-(TMath::Pi()/4)));

  Double_t x2 = x22 - length22*(sin(theta2));
  Double_t y2 = y22;
  Double_t z2 = z22 - length22*(cos(theta2));
 
  Double_t length1 = TMath::Sqrt( x1*x1 + y1*y1 + z1*z1 );
  Double_t length2 = TMath::Sqrt( (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1) );
  Double_t length3 = TMath::Sqrt( (x3-x2)*(x3-x2)+(y3-y2)*(y3-y2)+(z3-z2)*(z3-z2) );

  Double_t theta = TMath::ATan((x2-x1)/(z2-z1));
  Double_t radius = length2/(2*sin(theta));
  Double_t arc = radius*2*theta;

  Double_t p = 0.3*radius*1000; //GeV/c -> MeV/c

  Double_t totalLength = length1 + arc + length3 + length33;
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
  //std::cout << " momentum p = " << p << " (MeV/c)" << std::endl;
  //std::cout << " mass m  = " << mass << " (MeV/c^2)" << std::endl;
  //std::cout << "p = " << p << " MeV,   m = " << mass << " MeV" << std::endl; 
  //std::cout << "					" <<std::endl;
  h1->Fill(mass);
  }
  h1->Draw();
  h1->Fit(g1,"R");
  h1->GetXaxis()->SetTitle("mass (MeV/c^2)");
  h1->GetYaxis()->SetTitle("counts");
}

