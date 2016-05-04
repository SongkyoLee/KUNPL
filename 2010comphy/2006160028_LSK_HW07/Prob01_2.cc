#include "TMinuit.h"

#define NGEN1 10000
#define NGEN2 1000
#define NBIN 100
#define XMAX 85.0 //I changed XMAX to show appropriate graphs and histogram
#define XMIN 0.0

gROOT -> SetStyle("Plain");
gROOT -> ForceStyle();

Int_t n = 30;
Double_t *x1 = new Double_t[n];
Double_t *y1 = new Double_t[n];
Double_t *e1 = new Double_t[n];


float gammln(float xx)
{
	double x, y, tmp, ser;
	static double cof[6] = {76.18009172947146, -86.50532032941677,
			24.01409824083091, -1.231739572450155,
			0.1208650973866179e-2, -0.5395239384953e-5};
	int j;
	
	y = x = xx;
	tmp = x+5.5;
	tmp -= (x+0.5)*log(tmp);
	ser = 1.000000000190015;
	for (j=0; j<=5; j++) ser += cof[j]/++y;
	return -tmp+log(2.5066282746310005*ser/x);
}


Double_t chi(Double_t *x, Double_t *n) //chi-square graph (red line)
{
	Double_t lnf = TMath::Log(1)- n[0]*0.5*TMath::Log(2.0) - gammln(n[0]*0.5)
			+ (n[0]*0.5-1.0)*TMath::Log(x[0]) - x[0]*0.5;
	return TMath::Exp(lnf);
}


Double_t func(Double_t x, Double_t *par)
{
	return par[0];
}


Double_t gaussian(Double_t *x, Double_t *par) //gaussian graph (blue line)
{
	return par[0]
	*1/(TMath::Sqrt(2.0*3.1415926)*par[2])
	*TMath::Exp(-(x[0]-par[1])*(x[0]-par[1])/(2.0*(par[2])*(par[2])));
	//par[1] = mean value
	//par[2] = standard deviation
}


Double_t difference(Double_t *x, Double_t *par) // diffrence graph (gray line)
{
	Double_t lnf = TMath::Log(1)- par[3]*0.5*TMath::Log(2.0) - gammln(par[3]*0.5)
		+ (par[3]*0.5-1.0)*TMath::Log(x[0]) - x[0]*0.5;
	return (  (TMath::Exp(lnf)) - (par[0]*1/(TMath::Sqrt(2.0*3.1415926)*par[2])
	*TMath::Exp(-(x[0]-par[1])*(x[0]-par[1])/(2.0*(par[2])*(par[2]))))  ) ;
}

// above, this difference (chi - gaussian) is not involved in the original assignment. 
// however, fractional difference graph made me confused,
// so I just added this graph (beforing dividing) in order to check my fomula is working well.


Double_t fraction (Double_t *x, Double_t *par) //fractional diff. graph (black line)
{
	Double_t lnf = TMath::Log(1)- par[3]*0.5*TMath::Log(2.0) - gammln(par[3]*0.5)
		+ (par[3]*0.5-1.0)*TMath::Log(x[0]) - x[0]*0.5;
	return (  (TMath::Exp(lnf)) - (par[0]*1/(TMath::Sqrt(2.0*3.1415926)*par[2])
	*TMath::Exp(-(x[0]-par[1])*(x[0]-par[1])/(2.0*(par[2])*(par[2]))))  )
	/ (par[0]*1/(TMath::Sqrt(2.0*3.1415926)*par[2])
	*TMath::Exp(-(x[0]-par[1])*(x[0]-par[1])/(2.0*(par[2])*(par[2]))));
}



void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
	Int_t i;
	
	Double_t chisq = 0;
	Double_t delta;
	
	for (i=0; i<n; i++)
	{
		delta = (y1[i] - func(x1[i],par))/e1[i];
		chisq += delta*delta;
	}
	f = chisq;
}


void Prob01_2()
{
	gRandom->SetSeed(2006160028);
	
	TCanvas* klkl = new TCanvas("klkl","chi-square and Gaussian", 200, 10, 600, 400);
	
	hist = new TH1F("hist", "", NBIN, XMIN, XMAX);
	hist -> SetFillColor(6);
	
	Double_t vstart[1] = {0.0};
	Double_t step[1] = {0.001};
	
	Int_t dum;
	Float_t u1, u2, z1, z2;
	for (Int_t i=0; i<NGEN1; i++)
	{
		for(Int_t j=0; j<n; j++) y1[j] = 0.0;
		for (Int_t j=0; j<NGEN2; j++)
		{
			u1 = gRandom->Rndm(dum);
			for (Int_t k=0; k<n; k++)
			{
				if ((u1>=k/(1.0*n) && (u1 < (k+1)/(1.0*n))))
				y1 [k]++;
			}
		}
		
		for (Int_t l=0; l<n; l++)
		{
			e1[l] = TMath::Sqrt(y1[1]);
		}
	
	TMinuit *gMinuit = new TMinuit(1);
	gMinuit -> SetFCN(fcn);
	gMinuit -> SetPrintLevel(-1);
	Double_t arar[10];
	Int_t ierflg = 0;
	
	arar[0] = 1;
	gMinuit -> mnexcm("SET ERR", arar, 1, ierflg);
	gMinuit -> mnparm(0, "theta_0", vstart[0], step[0], 0, 0, ierflg);
	
	
	arar[0] = 5000;	
	arar[1] = 1.0;
	gMinuit->mnexcm("MINUIT", arar, 2, ierflg);
	
	Double_t amin, edm, errdef;
	Int_t nvpar, nparx, icstat;
	gMinuit -> mnstat(amin, edm, errdef, nvpar, nparx, icstat);
	hist -> Fill(amin);
	}

hist -> Scale(NBIN/(1.0*NGEN1*(XMAX-XMIN)));
hist -> SetMinimum (-0.15);
hist -> SetMaximum(0.1); // I changed the range of Y axis for showing other graphs.
hist -> Draw ();

TF1 * fun1 = new TF1("fun1", chi, XMIN, XMAX, 1);
fun1 -> SetParameter(0, n-1);
fun1 -> SetLineColor(2); //red
fun1 -> Draw("LSAME");

TF1 * fun2 = new TF1 ("fun2", gaussian, XMIN, XMAX, 3);
fun2 -> SetParameters (1.0, 28.0, 6.7);
fun2 -> SetLineColor(4); //blue
fun2 -> Draw("LSAME");

TF1 * fun3 = new TF1 ("fun3", difference, XMIN, XMAX, 4); 
//instead of n[0], I used par[3]. So there are 4 parameters here.
fun3 -> SetParameters (1.0, 28.0, 6.7, n-1);
fun3 -> SetLineColor(8); //gray
fun3 -> Draw("LSAME");

TF1 * fun4 = new TF1 ("fun4", fraction, XMIN, XMAX, 4); 
//It actually diverges, and I guess it's because I divided it by 0 (where gaussian is 0).
fun4 -> SetParameters (1.0, 28.0, 6.7, n-1);
fun4 -> Draw("LSAME"); //black

}
