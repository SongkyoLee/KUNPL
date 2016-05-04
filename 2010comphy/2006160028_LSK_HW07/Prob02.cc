
gROOT -> SetStyle("Plain");
gROOT -> ForceStyle();
	
Int_t n = 4;
Double_t *x1 = new Double_t[n];
Double_t *y1 = new Double_t[n];
Double_t *e1 = new Double_t[n];
	
x1[0] = 1.0; x1[1] = 2.0; x1[2] = 3.0; x1[3] = 4.0;
y1[0] = 5.5;  y1[1] = 4.6;  y1[2] = 6.1; y1[3] = 5.9;
e1[0] = 1.0;  e1[1] = 1.5;  e1[2] = 1.5; e1[3] = 1.0;

Double_t f1(Double_t *x, Double_t *par)
{
	return par[0];
}

void Prob02()
{

	TCanvas  * c1 = new TCanvas ("c1", "", 200, 10, 600, 1200);
	c1 -> Divide (1,3);

// first, make a chi-square fit and obtain errors for the parameters.

	c1->cd(1);
	TF1 *func = new TF1 ("func", f1, -1.0, 1.0, 1); //1 parameters
	TGraphErrors *gr1 = new TGraphErrors (n, x1, y1, 0, e1);
	gr1 -> SetMarkerStyle (24);
	gr1 -> SetMaximum (10.0);
	gr1 -> SetMinimum (0.0);
	gr1 -> Draw("ap");
	gr1->Fit("func");


//
//Mimuit Result was as followings.
//
//	No. 	par name	value		error		stepsize	
//	1 	p0(par[0])	5.60235e+00	3.25396e-01	3.00000e-04	
//
	
	
// Now, draw a chi-square vs par[0] plot.
	
	c1 -> cd(2);
	
	const Int_t N = 15;
	Double_t xx[N], yy[N];
			
	for (Int_t i=0; i<N; i++)
	{	
		xx[i] = i;
		yy[i] = (((5.5-xx[i])/1.0)*((5.5-xx[i])/1.0)) 
			+ (((4.6-xx[i])/1.5)*((4.6-xx[i])/1.5))
			+ (((6.1-xx[i])/1.5)*((6.1-xx[i])/1.5))
			+ (((5.9-xx[i])/1.0)*((5.9-xx[i])/1.0))	;
	}
			
	gr2 = new TGraph(N, xx, yy);
	gr2 -> SetTitle("chi-square vs parameter");
	gr2 -> SetMaximum (200.0);
	gr2 -> SetMinimum (-10.0);
	gr2 -> Draw ("ACP");

// As you can see in this graph,chi-square has minimum value around parameter value 5.6. 

// I'll hand out reduction later T^T
	
}


 
