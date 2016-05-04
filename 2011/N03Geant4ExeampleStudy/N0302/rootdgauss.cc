#include "TFile.h"
#include "TTree.h"
#include <fstream>

#define XMIN 0.0 //set
#define XMAX 35.0 //set

Double_t gaussian(Double_t *x, Double_t *par) //gaussian function
{
 return par[0]*1/(TMath::Sqrt(2.0*3.1415926)*par[2])
 *TMath::Exp(-(x[0]-par[1])*(x[0]-par[1])/(2.0*(par[2])*(par[2])));
 //par[0] = normalization (just 1 would be fine in this case))
 //par[1] = mean value
 //par[2] = standard deviation
}


void rootgauss()
{
 TCanvas *c1 = new TCanvas("c1", "histogram with gaussian");

 TF1* fun1 = new TF1("fun1", gaussian, XMIN, XMAX, 3); //3 parameters
 fun1->SetParameters(10000.0, 15.0, 3.0); 
 fun1->SetLineColor(2); //red
 fun1->Draw();

} 
