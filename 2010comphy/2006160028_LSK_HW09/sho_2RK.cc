

// 2006160028 LSK

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

void rk2(Int_t i)
{
  Float_t t2 = t[i] + 0.5*dt;
  Float_t Yp = Y[i] + 0.5*V[i]*dt; 
  Float_t Vp = V[i] - 0.5*A*Y[i]*dt;
  V[i+1] = V[i] - A*Yp*dt;
  Y[i+1] = Y[i] + Vp*dt;
}

void sho_2RK()
{ 
  gROOT->SetStyle("Plain");
  gROOT->ForceStyle();

  Y[0] = Y0;
  V[0] = V0;
  t[0] = tmin;
  for (Int_t i=0; i<Nspace-1; i++)
  {
    t[i+1] = t[i] + dt;
    rk2(i);
    E[i] = 0.5*V[i]*V[i] + 0.5*A*Y[i]*Y[i];
  }

  TCanvas* c1 = new TCanvas("c1","",10,10,500,500); 
  c1->cd();

  g1 = new TGraph(Nspace,t,Y);
  g2 = new TGraph(Nspace-1,t,E);

  g1->SetMarkerSize(0.5);
  g1->SetMarkerStyle(20);
  g2->SetMarkerSize(0.5);
  g2->SetMarkerStyle(20);
  g1->Draw("AP");

  TH2F * h2 = new TH2F("h2","",2,0,40,2,0,0.03);
  TCanvas* c2 = new TCanvas("c2","",10,10,500,500); 
  c2->cd();
  h2->Draw();
  g2->Draw("P");
} 
