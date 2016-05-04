
#define xmax  10.0
#define xmin   0.0
#define Y10     0.0
#define Y20     1.0
#define step  150

const static Int_t Nspace = step;
const static Float_t dx  = (xmax-xmin)/step;

Double_t Y1[Nspace];	Double_t Y2[Nspace];	Double_t x[Nspace];	

double graph1(Double_t x)
{
	return -0.5*exp(-x)*(-1.0+exp(2.0*x));
}

double graph2(Double_t x)
{
	return 0.5*exp(-x)*(1.0+exp(2.0*x));
}

double funcY1 (Double_t Y2)
{
	return -Y2;
}

double funcY1 (Double_t *Y2)
{
	return -Y2;
}

double funcY2 (Double_t Y1)
{
	return -Y1;
}

double funcY2 (Double_t *Y1)
{
	return -Y1;
}

void Prob02()
{ 
	gROOT->SetStyle("Plain");
	gROOT->ForceStyle();

	Y1[0] = Y10;
	Y2[0] = Y20;
	x[0] = xmin;
    
	Double_t Y1p, Y2p; 
    
	for (Int_t i=0; i<Nspace-1; i++)
	{
		x[i+1] = x[i] + dx;
    
	Y1p = Y1[i] + 0.5 * funcY1(Y2[i]) * dx;
	Y2p = Y2[i] + 0.5 * funcY2(Y1[i]) * dx;
    
	Y1[i+1] = Y1[i] + funcY1(Y2p) * dx;
	Y2[i+1] = Y2[i] + funcY2(Y1p) * dx;
	}

	TCanvas *cc1 = new TCanvas("cc1", "Coupled Diff. eqn.", 10, 10, 1000, 500);
	cc1->Divide(2,1);

	cc1->cd(1);
	f1 = new TF1("f1", "graph1(x)", xmin, xmax);
	f1->SetLineColor(4);
	f1->Draw();

	g1 = new TGraph(Nspace, x, Y1);
	g1->SetMarkerStyle(24);
	g1->Draw("PSAME");

	cc1->cd(2);
	f2 = new TF1("f2", "graph2(x)", xmin, xmax);
	f2->SetLineColor(4);
	f2->Draw();

	g2 = new TGraph(Nspace, x, Y2);
	g2->SetMarkerStyle(24);
	g2->Draw("PSAME");
} 
