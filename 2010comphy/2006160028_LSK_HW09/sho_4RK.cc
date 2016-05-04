
#define A      1.0   
#define tmax  40.0   // second : maximum time to calculate
#define tmin   0.0   // second : minimum time to calculate
#define Y0     0.2   // initial value of Y
#define V0     0.0   // initial value of V
#define step  4000  // number of steps 

const static Int_t Nspace = step;
const static Float_t dt   = (tmax-tmin)/step;

Double_t Y[Nspace];
Double_t V[Nspace];
Double_t t[Nspace];
Double_t E[Nspace];

void rk4(Int_t i)
{
  Float_t t2 = t[i] + 0.5*dt;
  Float_t Y1 = Y[i] + 0.5*V[i]*dt; 
  Float_t V1 = V[i] - 0.5*A*Y[i]*dt;
  Float_t Y2 = Y[i] + 0.5*V1*dt;
  Float_t V2 = V[i] - 0.5*A*Y1*dt;
  Y[i+1] = Y[i] + V2*dt;
  V[i+1] = V[i] - A*Y2*dt;
}

void sho_4RK()
{ 
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();

  Y[0] = Y0;
  V[0] = V0;
  t[0] = tmin;
  for (Int_t i=0; i<Nspace-1; i++)
  {
    t[i+1] = t[i] + dt;
    rk4(i);
    E[i] = 0.5*V[i]*V[i] + 0.5*A*Y[i]*Y[i];
  }

  TCanvas* c1 = new TCanvas("c1","",10,10,1500,500); 
  c1 -> Divide(3,1);

  c1->cd(1);
  g1 = new TGraph(Nspace,t,Y);
  g2 = new TGraph(Nspace-1,t,E);
  g1->SetMarkerSize(0.5);
  g1->SetMarkerStyle(20);
  g2->SetMarkerSize(0.5);
  g2->SetMarkerStyle(20);
  g1->Draw("AP");

  c1->cd(2);
  TH2F * h2 = new TH2F("h2","Energy",2,0,40,2,0,0.03);
  h2->Draw();
  g2->Draw("P");
  
  c1->cd(3);
  c1->RangeAxis(0.0, 0.019, 40.0, 0.021);
 TH2F * h3 = new TH2F("h3","axis enlarged",2,0,40,2,0,0.03);
  h3->Draw();
  TGraph *g3 = new TGraph(Nspace-1,t,E);
//  g3->SetMinimum(0.019);
//  g3->SetMaximum(0.021);
//  g3-> SetRange(0.0, 0.019, 40.0, 0.021);
  g3->SetMarkerSize(0.5);
  g3->SetMarkerStyle(20);
  g3->Draw("P");
  
} 
