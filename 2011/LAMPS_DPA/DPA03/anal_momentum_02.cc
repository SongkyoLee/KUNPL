#include <fstream>

void anal_momentum_02() //fake nomalization version for out values to visualize
{
  const Int_t n = 7;
  Double_t in_Eloss[n] = {0.3, 0.4, 0.5, 0.6, 0.7, 0.8,0.9}; // large Eloss pnt 
  Double_t in_avg[n] = {0.31, 0.41, 0.51, 0.61, 0.71, 0.81, 0.91 }; //avg pnt
  Double_t out_Eloss[n] = {0.291039, 0.295745, 0.297590, 0.298533,
			 0.299115, 0.299376, 0.299449};
  Double_t out_avg[n] = {0.291111, 0.295788, 0.297539, 0.298458,
			 0.299059, 0.299365, 0.299494};
  Double_t ex_Eloss[n] = {0, 0, 0, 0, 0, 0, 0};
  Double_t ex_avg[n] = {0, 0, 0, 0, 0, 0, 0};
  Double_t ey_Eloss[n] = {0.00240556, 0.00235503, 0.00302904, 0.00316339, 
			0.00353707, 0.00381451, 0.00422290};
  Double_t ey_avg[n] = {0.00242222, 0.00254830, 0.00324464, 0.00344836,
			 0.00389077, 0.00400987, 0.00436759};

  Double_t in_real[n] = {0.2, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0}; // real value 
  Double_t out_real[n] = {0.3, 0.3, 0.3, 0.3, 0.3, 0.3, 0.3};

 TCanvas *c1 = new TCanvas("c1", "energy", 200, 10, 800, 600);
 TGraphErrors *gr1 = new TGraphErrors(n, in_Eloss, out_Eloss, ex_Eloss, ey_Eloss);
 gr1->SetMarkerColor(1); // Eloss : black
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(0.5);
// gr1->SetLineColor(1);
// gr1->SetLineWidth(0.3);
 gr1->SetTitle("");
 gr1->GetXaxis()->SetTitle("momentum (GeV/c)");
 gr1->GetYaxis()->SetTitle("(fake) momentum (GeV/c)");
 gr1->GetYaxis()->SetTitleOffset(1.5);
 gr1->SetMinimum(0.285);
 gr1->SetMaximum(0.305);
 gr1->Draw("AP");

 TGraphErrors *gr2 =new TGraphErrors(n, in_avg, out_avg, ex_avg, ey_avg);
 gr2->SetMarkerColor(2); // avg : red
 gr2->SetMarkerStyle(20);
 gr2->SetMarkerSize(0.5);
// gr2->SetLineColor(2);
 gr2->Draw("P"); //draw on the graph g1

 TGraph* gr3 = new TGraph(n, in_real, out_real);
 gr3->SetLineColor(4);
 gr3->SetMarkerSize(0);
 gr3->Draw("CP"); //draw on the graph g1

}
