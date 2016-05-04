#include <fstream>

void anal_02()
{
  const Int_t n = 3; //total line of energy.txt
  Double_t sinput[n] = {1,2,3}; 
  Double_t cinput[n] = {1.1, 2.1, 3.1};
  Double_t simul[n] = {150.4, 150.1, 147.9};
  Double_t calcul[n] = {150.4, 150.1, 147.9};
  Double_t sx[n] = {0, 0, 0};
  Double_t cx[n] = {0, 0, 0};
  Double_t sy[n] = {0.718, 0.735, 0.747};
  Double_t cy[n] = {0.717, 0.714, 0.697};

 TCanvas *c1 = new TCanvas("c1", "energy", 200, 10, 800, 600);
 TGraphErrors *gr1 = new TGraphErrors(n, sinput, simul, sx, sy);
 gr1->SetMarkerColor(1); //simulation : black
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1);
// gr1->SetLineColor(1);
// gr1->SetLineWidth(0.3);
 gr1->SetTitle("");
// gr1->GetXaxis()->SetTitle("materials");
 gr1->GetYaxis()->SetTitle("energy (MeV)");
 gr1->SetMinimum(146.5);
 gr1->SetMaximum(151.5);
 gr1->Draw("AP");

 TGraphErrors *gr2 =new TGraphErrors(n, cinput, calcul, cx, cy);
 gr2->SetMarkerColor(2);//calculation : red
 gr2->SetMarkerStyle(20);
 gr2->SetMarkerSize(1);
// gr2->SetLineColor(2);
 gr2->Draw("P"); //draw on the graph g1

}
