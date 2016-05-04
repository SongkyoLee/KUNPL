#include <fstream>

void anal_01()
{
  const Int_t n = 3; //total line of energy.txt
  Double_t input[n] = {1,2,3}; 
  Double_t simul[n] = {150.4, 150, 147.9};
  Double_t calcul[n] = {150.4462, 150.0171, 147.9008};

 TCanvas *c1 = new TCanvas("c1", "energy", 200, 10, 800, 600);
 TGraph *gr1 = new TGraph(n, input, simul);
 gr1->SetMarkerColor(1); //black
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(1);
// gr1->SetLineColor(1);
// gr1->SetLineWidth(0.3);
 gr1->SetTitle("energy in different materials");
 gr1->GetXaxis()->SetTitle("material (MeV)");
 gr1->GetYaxis()->SetTitle("energy (MeV)");
 gr1->SetMinimum(147.7);
 gr1->SetMaximum(150.6);
 gr1->Draw("AP");

 TGraph *gr2 =new TGraph(n, input, calcul);
 gr2->SetMarkerColor(2);//red
 gr2->SetMarkerStyle(20);
 gr2->SetMarkerSize(1);
// gr2->SetLineColor(2);
 gr2->Draw("P"); //draw on the graph g1

}
