# define N 200
# define XMIN 0.0
# define XMAX 3.0

Double_t f1(Double_t *x, Double_t *par)
 {
  return 1/10.5*(x[0]*x[0]+0.5); // I set the proper value of "a" for normalization.
 }

 void Prob03_1()
 {
   gROOT -> SetStyle("Plain");
   gROOT -> ForceStyle();
  
  TCanvas *c1 = new TCanvas("c1", "", 200, 10, 800, 600);
  TPad *pad1 = new TPad("pad1", "pad1", .02, .02, 0.48, 0.98);
 //(bottomleft x, y, topright x, y) 
  TPad *pad2 = new TPad("pad2", "pad2", .52, .02, 0.98, 0.98);
  pad1->Draw();
  pad2->Draw(); 
 
 pad1->cd();
 TF1 *func = new TF1 ("func", f1, XMIN, XMAX,3);
 func->SetTitle("p.d.f. func.");
 func->Draw();
 

 double xx[1], par[3];
 par[0] = 1.0;
 par[1] = 2.0;
 par[2] = 1.0;
 
 
 double ycum[N], xcum[N];
 double sum = 0;
 
   for(int i=0;i<N;i++)
    {
      double xx[0] = XMIN+(XMAX-XMIN)/N*i;
      sum += f1(xx, par);
      xcum[i] = xx[0];
      ycum[i] = sum*((XMAX-XMIN)/N);
    }

 pad2->cd();    
    gr = new TGraph(N,xcum,ycum);
    gr->SetTitle("cumulative func.");
    gr->Draw("ACP");

 }
