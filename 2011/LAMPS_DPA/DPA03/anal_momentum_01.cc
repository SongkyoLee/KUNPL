#include <fstream>

void anal_momentum_01()
{
  const Int_t n = 7;
  Double_t in_Eloss[n] = {0.3, 0.4, 0.5, 0.6, 0.7, 0.8,0.9}; // large Eloss pnt 
  Double_t in_avg[n] = {0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 }; //avg pnt
  Double_t out_Eloss[n] = {0.291, 0.396, 0.497, 0.596, 0.699, 0.799, 0.899};
  Double_t out_avg[n] = {0.291, 0.396, 0.497, 0.598, 0.699, 0.799, 0.899};
  Double_t ex_Eloss[n] = {0, 0, 0, 0, 0, 0, 0}; //error
  Double_t ex_avg[n] = {0, 0, 0, 0, 0, 0, 0};
  Double_t ey_Eloss[n] = {0.00241, 0.00236, 0.00302, 0.00316, 0.00354, 0.00381, 0.00422};
  Double_t ey_avg[n] = {0.00242, 0.00255, 0.00324, 0.00345, 0.00389, 0.00401, 0.00437};

  Double_t in_real[n] = {0.2, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0}; // real value 
  Double_t out_real[n] = {0.2, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0};

 TCanvas *c1 = new TCanvas("c1", "energy", 200, 10, 800, 600);
 TGraphErrors *gr1 = new TGraphErrors(n, in_Eloss, out_Eloss, ex_Eloss, ey_Eloss);
 gr1->SetMarkerColor(1); //Eloss : black
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(0.5);
// gr1->SetLineColor(1);
// gr1->SetLineWidth(0.3);
 gr1->SetTitle("");
 gr1->GetXaxis()->SetTitle("momentum (GeV/c)");
 gr1->GetYaxis()->SetTitle("momentum (GeV/c)");
 gr1->SetMinimum(0.28);
 gr1->SetMaximum(0.91);
 gr1->Draw("AP");

 TGraphErrors *gr2 =new TGraphErrors(n, in_avg, in_avg, ex_avg, ey_avg);
 gr2->SetMarkerColor(2); //avg : red
 gr2->SetMarkerStyle(20);
 gr2->SetMarkerSize(0.5);
// gr2->SetLineColor(2);
 gr2->Draw("P"); //draw on the graph g1

 TGraph* gr3 = new TGraph(n, in_real, out_real);
 gr3->SetLineColor(4);
 gr3->SetMarkerSize(0);
 gr3->Draw("CP"); //draw on the graph g1

}
