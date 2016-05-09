#include <fstream>
#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TAxis.h>
#include <TMath.h>
#include <TChain.h>

void draw_graph()
{
  const Int_t n = 5;
  Double_t in_Eloss[n] = {20, 23, 24, 25, 50}; // x-axis (helium bag) 
  Double_t in_avg[n] = {20, 23, 24, 25, 50}; // x-axis (vacuum) 
  //Double_t in_avg[n] = {0.31, 0.41, 0.51, 0.61, 0.71, 0.81, 0.91 }; //avg pnt
  Double_t out_Eloss[n] = {18.5, 13.8, 12.8, 12.06, 5.568};
  Double_t out_avg[n] = {14.09, 10.93, 10.31, 9.789, 5.015};
  Double_t ex_Eloss[n] = {0, 0, 0, 0, 0}; //error
  Double_t ex_avg[n] = {0, 0, 0, 0, 0};
  Double_t ey_Eloss[n] = {0.7213, 0.3863,0.3409, 0.3083, 0.216};
  Double_t ey_avg[n] = {0.3748, 0.2712, 0.2648, 0.2347, 0.1964};

//  Double_t in_real[n] = {0.2, 0.4, 0.5, 0.6, 0.7, 0.8, 1.0}; // real value 
//  Double_t out_real[n] = {938.272, 938.272, 938.272, 938.272, 938.272, 938.272, 938.272};

 TCanvas *c1 = new TCanvas("c1", "", 200, 10, 800, 600);
 TGraphErrors *gr1 = new TGraphErrors(n, in_Eloss, out_Eloss, ex_Eloss, ey_Eloss);
 gr1->SetMarkerColor(4); //Eloss : blue
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(0.9);
// gr1->SetLineColor(1);
// gr1->SetLineWidth(0.3);
 gr1->SetTitle("");
 gr1->GetXaxis()->SetTitle("Initial Kinetic energy (MeV)");
 gr1->GetYaxis()->SetTitle("energy loss (MeV)");
// gr1->SetMinimum(925.0); //y axis range
// gr1->SetMaximum(955.0);
 gr1->Draw("AP");

 TGraphErrors *gr2 =new TGraphErrors(n, in_avg, out_avg, ex_avg, ey_avg);
 gr2->SetMarkerColor(2);//avg : red
 gr2->SetMarkerStyle(20);
 gr2->SetMarkerSize(0.9);
// gr2->SetLineColor(2);
// gr2->SetLineWidth(0.3);
 gr2->Draw("P"); //draw on the graph g1

// TGraph* gr3 = new TGraph(n, in_real, out_real);
// gr3->SetLineColor(4);
// gr3->SetMarkerSize(0);
// gr3->Draw("CP"); //draw on the graph g1

}

