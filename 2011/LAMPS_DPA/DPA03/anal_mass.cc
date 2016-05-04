#include <fstream>

void anal_mass()
{
  const Int_t n = 7;
  Double_t in_Eloss[n] = {0.3, 0.4, 0.5, 0.6, 0.7, 0.8,0.9}; // large Eloss pnt 
  Double_t in_avg[n] = {0.31, 0.41, 0.51, 0.61, 0.71, 0.81, 0.91 }; //avg pnt
  Double_t out_Eloss[n] = {943.9, 939.9, 939.6, 939.3, 939.2, 939.3, 938.5};
  Double_t out_avg[n] = {944.1, 939.9, 939.7, 939.3, 939.3, 939.3, 938.8};
  Double_t ex_Eloss[n] = {0, 0, 0, 0, 0, 0, 0}; //error
  Double_t ex_avg[n] = {0, 0, 0, 0, 0, 0, 0};
  Double_t ey_Eloss[n] = {8.49, 10.5, 9.88, 8.71, 8.51, 7.89, 7.99};
  Double_t ey_avg[n] = {8.38, 10.5, 10.1, 9.00, 8.73, 8.07, 8.43};

  Double_t in_real[n] = {0.2, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0}; // real value 
  Double_t out_real[n] = {938.272, 938.272, 938.272, 938.272, 938.272, 938.272, 938.272};

 TCanvas *c1 = new TCanvas("c1", "energy", 200, 10, 800, 600);
 TGraphErrors *gr1 = new TGraphErrors(n, in_Eloss, out_Eloss, ex_Eloss, ey_Eloss);
 gr1->SetMarkerColor(1); //Eloss : black
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(0.5);
// gr1->SetLineColor(1);
// gr1->SetLineWidth(0.3);
 gr1->SetTitle("");
 gr1->GetXaxis()->SetTitle("momentum (GeV/c)");
 gr1->GetYaxis()->SetTitle("mass (MeV/c^2)");
 gr1->SetMinimum(925.0); //y axis range
 gr1->SetMaximum(955.0);
 gr1->Draw("AP");

 TGraphErrors *gr2 =new TGraphErrors(n, in_avg, out_avg, ex_avg, ey_avg);
 gr2->SetMarkerColor(2);//avg : red
 gr2->SetMarkerStyle(20);
 gr2->SetMarkerSize(0.5);
// gr2->SetLineColor(2);
// gr2->SetLineWidth(0.3);
 gr2->Draw("P"); //draw on the graph g1

 TGraph* gr3 = new TGraph(n, in_real, out_real);
 gr3->SetLineColor(4);
 gr3->SetMarkerSize(0);
 gr3->Draw("CP"); //draw on the graph g1

}

