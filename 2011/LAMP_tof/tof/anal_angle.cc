#include <fstream>

void anal_angle()
{
  std::ifstream Fin("angle.txt",std::ios::in);

  const Int_t n = 8; //total line of angle.txt
  Double_t angle[n], data[n];

  for(Int_t i=0; i<n; i++)
  {
    Fin >> angle[i] >> data[i] ;
    std::cout << angle[i] << " " << data[i] << std::endl;
  }

 TCanvas *c1 = new TCanvas("c1", "angle", 200, 10, 800, 600);
 TGraph *gr1 = new TGraph(n, angle, data);
 gr1->SetMarkerColor(1);
 gr1->SetMarkerStyle(20);
 gr1->SetMarkerSize(0.6);
 gr1->SetLineColor(1);
 gr1->SetLineWidth(0.3);
 gr1->SetTitle("Different Incident Angle");
 gr1->GetXaxis()->SetTitle("incident angle (degree)");
 gr1->GetYaxis()->SetTitle("data (MeV)");
 gr1->SetMinimum(145.0); //Yaxis range
 gr1->SetMaximum(152.0); //Yaxis range
 gr1->Draw("ACP");


 Double_t beam[n];

 for(Int_t j =0; j<n; j++)
{
  beam[j] = 150; 
}

 TGraph *gr2 =new TGraph(n, angle, beam);
 gr2->SetLineColor(2);
 gr2->Draw("CP");
}
