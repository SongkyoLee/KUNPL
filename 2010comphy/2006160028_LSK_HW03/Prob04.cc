void Prob04() 
{

   TCanvas *c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);

   c1->SetFillColor(45);
   c1->SetGrid();
   c1->GetFrame()->SetFillColor(21);
   c1->GetFrame()->SetBorderSize(12);

   const Int_t n = 10;
   Float_t x[n]  = {-0.22, 0.05, 0.25, 0.35, 0.5, 0.61,0.7,0.85,0.89,0.95};
   Float_t y[n]  = {1,2.9,5.6,7.4,9,9.6,8.7,6.3,4.5,1};
   Float_t ex[n] = {sqrt(-0.22), sqrt(0.05), sqrt(0.25), sqrt(0.35), sqrt(0.5), sqrt(0.61),sqrt(0.7),sqrt(0.85),sqrt(0.89),sqrt(0.95)};
   Float_t ey[n] = {sqrt(1),sqrt(2.9),sqrt(5.6),sqrt(7.4),sqrt(9),sqrt(9.6),sqrt(8.7),sqrt(6.3),sqrt(4.5),sqrt(1)};
   TGraphErrors *gr = new TGraphErrors(n,x,y,ex,ey);
   gr->SetTitle("TGraphErrors Example");
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->Draw("ALP");

   c1->Update();
}
