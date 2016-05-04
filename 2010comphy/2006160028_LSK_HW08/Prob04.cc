# include "TMinuit.h"

const static Int_t Ngen = 1000;
const static Int_t Nbin = 100;
const static Float_t Xmax = 1.0;
const static Float_t Xmin = -1.0;
const static Float_t Fmax = 0.95;
const static Float_t Alpha0 = 0.5;
const static Float_t Beta0 = 0.5;
const static Float_t Nps = 500;
const static Float_t psmax = 1.0;
const static Float_t psmin = -1.0;

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

Double_t gaussian(Double_t *x, Double_t *par)
{
  	return (Nps*(psmax-psmin)/Nbin)/
	(TMath::Sqrt(2.0*3.141592)*par[1])* TMath::Exp(-0.5*(x[0]-par[0])*(x[0]-par[0])/(par[1]*par[1]));
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

void Prob04()
{
	TCanvas *c1 = new TCanvas("c1","",200,10,1200,600);	
	c1->Divide(2,1);

	gROOT -> SetStyle("Plain");
	gROOT -> ForceStyle();
	gRandom -> SetSeed(2006160028);

	histl = new TH1F("hist1","alpha", Nbin, -3.0, 3.0);
	hist2 = new TH1F("hist2","beta", Nbin, -3.0, 3.0);

	Double_t alpha, beta, ealpha, ebeta;

	for(Int_t n=0; n<Nps; n++)
	{
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
			if (u2 < funct) {  gdata[i] = u1; i++;}
		}
	
	TMinuit *gMinuit = new TMinuit(2);
	gMinuit->SetFCN(summ);
	gMinuit->SetPrintLevel(-1);	

	Double_t arglist[10];
	Int_t ierflg = 0;

	arglist[0] = 0.5;
	gMinuit->mnexcm("SET ERR", arglist, 1, ierflg);
	Double_t vstart[2] = {0.0, 1.0};
	Double_t step[2] = {0.1, 0.1};
	gMinuit->mnparm(0,"alpha",vstart[0],step[0],0,0,ierflg);
	gMinuit->mnparm(1,"beta",vstart[1],step[1],0,0,ierflg);

	arglist[0] = 500;
	arglist[1] = 1.;
	gMinuit->mnexcm("MIGRAD", arglist, 2, ierflg);

	Double_t amin, edm, errdef;
	Int_t nvpar, nparx, icstat;
	gMinuit->mnstat(amin, edm, errdef, nvpar, nparx, icstat);


	Double_t alpha, ealpha, beta, ebeta;
	gMinuit->GetParameter(0, alpha, ealpha);
	gMinuit->GetParameter(1, beta, ebeta);

	hist1->Fill(alpha);
	hist2->Fill(beta);
	
	}

	TF1* g1 = new TF1("g1",gaussian, psmin, psmax, 2);

	c1->cd(1);
	hist1->Draw();
	g1->SetParameters(0.5,0.5,0.5);
	g1->Draw("same");
		
	c1->cd(2);
	hist2->Draw();
	g1->SetParameters(0.5,0.5,0.5);
	g1->Draw("same");

}
