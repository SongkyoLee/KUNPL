#include <fstream>

void anal_energy()
{
  std::ifstream Fin("energy.txt",std::ios::in);

  const Int_t n = 12; //total line of energy.txt
  Double_t input[n], output[n];

  for(Int_t i=0; i<n; i++)
  {
    Fin >> input[i] >> output[i] ;
    std::cout << input[i] << " " << output[i] << std::endl;
  }

 TCanvas *c1 = new TCanvas("c1", "energy", 200, 10, 800, 600);
 TGraph *gr1 = new TGraph(n, input, output);
 gr1->SetMarkerColor(1);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(0.6);
 gr1->SetLineColor(1);
 gr1->SetLineWidth(0.3);
 gr1->SetTitle("Different Beam Energy");
 gr1->GetXaxis()->SetTitle("beam energy (MeV)");
 gr1->GetYaxis()->SetTitle("data (MeV)");
 gr1->Draw("ACP");


 Double_t x[n], y[n];

 for(Int_t j =0; j<n; j++)
{
  x[j] = y[j] = input[j]; 
} 

 TGraph *gr2 =new TGraph(n, x, y);
 gr2->SetLineColor(2);
 gr2->Draw("CP"); //draw on the graph g1

}
