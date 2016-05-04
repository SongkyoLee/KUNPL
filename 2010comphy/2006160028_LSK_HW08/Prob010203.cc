# include "TMinuit.h"

const static Int_t Ngen = 1000;
const static Int_t Nbin = 100;
const static Float_t Xmax = 1.0;
const static Float_t Xmin = -1.0;
const static Float_t Fmax = 0.95;
const static Float_t Alpha0 = 0.5;
const static Float_t Beta0 = 0.5;

double* gdata;
gdata = new double[100000];

Double_t f1(Double_t *x, Double_t *par)
{
	return (1.0+par[0]*x[0]+par[1]*x[0]*x[0])
		/( Xmax-Xmin+(par[0]/2)*(Xmax*Xmax-Xmin*Xmin)+(par[1]/3)*(Xmax*Xmax*Xmax-Xmin*Xmin*Xmin) );
}

Double_t f2(Double_t x, Double_t *par)
{
	return (1.0+par[0]*x+par[1]*x*x)
		/( Xmax-Xmin+(par[0]/2)*(Xmax*Xmax-Xmin*Xmin)+(par[1]/3)*(Xmax*Xmax*Xmax-Xmin*Xmin*Xmin) );
}


void summ(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{
	Int_t i;
	
	Double_t loglike = 0;
	Double_t sumlike = 0;
	for (i=0; i<Ngen; i++)
	{
		loglike = -1.0*TMath::Log(f2(gdata[i],par));
		sumlike += loglike;
	}
	f = sumlike;
}


void Prob010203(void)
{
	TCanvas *c1 = new TCanvas("c1","likelyhood",200,10,1800,600);	
	c1->Divide(3,1);

	gROOT -> SetStyle("Plain");
	gROOT -> ForceStyle();
	gRandom -> SetSeed(2006160028);


	TH1F* hist[3];  Char_t hhh[20] = "h1"; Char_t title[20] = "1000";
	TMinuit* gMinuit[3];
	TF1* gr1[3];	Char_t ggg1[20] = "graph";
	TF1* gr2[3];	Char_t ggg2[20] = "fitting";

	for(Int_t n=0; n<3; n++)
	{
		c1->cd(n+1);
		hist[n] = new TH1F(hhh,title, Nbin, Xmin, Xmax);

		Float_t funct;
		Int_t dum1, dum2;
		for (Int_t i=0; i<Ngen;)
		{
			Float_t r1 = gRandom->Rndm(dum1);
			Float_t u1 = Xmin+r1*(Xmax-Xmin); 
			Float_t r2 = gRandom->Rndm(dum2);
			Float_t u2 = r2*Fmax; 
			funct = (1.0+Alpha0*u1+Beta0*u1*u1)
			/( Xmax-Xmin+(Alpha0/2)*(Xmax*Xmax-Xmin*Xmin)+(Beta0/3)*(Xmax*Xmax*Xmax-Xmin*Xmin*Xmin) );
			if (u2 < funct) {  gdata[i] = u1; hist[n]->Fill(u1); i++;}
		}
		
	gMinuit[n] = new TMinuit(2);
	gMinuit[n]->SetFCN(summ);
	gMinuit[n]->SetPrintLevel(-1);	

	Double_t arglist[10];
	Int_t ierflg = 0;

	arglist[0] = 0.5;
	gMinuit[n]->mnexcm("SET ERR", arglist, 1, ierflg);
	Double_t vstart[2] = {0.0, 1.0};
	Double_t step[2] = {0.1, 0.1};
	gMinuit[n]->mnparm(0,"alpha",vstart[0],step[0],0,0,ierflg);
	gMinuit[n]->mnparm(1,"beta",vstart[1],step[1],0,0,ierflg);

	arglist[0] = 500;
	arglist[1] = 1.;
	gMinuit[n]->mnexcm("MIGRAD", arglist, 2, ierflg);

	Double_t amin, edm, errdef;
	Int_t nvpar, nparx, icstat;
	gMinuit[n]->mnstat(amin, edm, errdef, nvpar, nparx, icstat);


	Double_t alpha[3], ealpha[3], beta[3], ebeta[3];
	gMinuit[n]->GetParameter(0, alpha[n], ealpha[n]);
	gMinuit[n]->GetParameter(1, beta[n], ebeta[n]);

	hist[n]->Scale(Nbin/(1.0*Ngen*(Xmax-Xmin)));
	hist[n]->Draw("");

	gr1[n] =  new TF1(ggg1, f1, Xmin, Xmax, 2);
	gr1[n]->SetParameters(Alpha0, Beta0);
	gr1[n]->Draw("same");

	gr2[n] =  new TF1(ggg2, f1, Xmin, Xmax, 2);
	gr2[n]->SetParameters(alpha[n], beta[n]);
	gr2[n]->SetLineStyle(2);
	gr2[n]->SetLineColor(4);
	gr2[n]->Draw("same");

	hhh[1] ++; 	title[4+n] = '0';
	ggg1[1] ++;	ggg2[1] ++; 	Ngen *=10;

	printf(" process %d \n", n+1);
	printf(" alpha = %5.5f +- %5.5f \n", alpha[n], ealpha[n]);
	printf(" beta = %5.5f +- %5.5f \n", beta[n], ebeta[n]);

}

// Q : Do they have 1/sqrt(N) behaviour? 
// A : Yes.

}

