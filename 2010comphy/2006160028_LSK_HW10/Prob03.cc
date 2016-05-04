  
#define tmax   5.0
#define tmin   0.0 
#define Y0     2.0 
#define V0    -1.0
#define step  1000 
#define t0     2.0

const static Int_t Nspace = step;
const static Float_t dt   = (tmax-tmin)/step;

Double_t Y[Nspace]; Double_t V[Nspace]; Double_t t[Nspace];
Double_t Y1[Nspace]; Double_t V1[Nspace]; Double_t t1[Nspace];
Double_t Y2[Nspace]; Double_t V2[Nspace]; Double_t t2[Nspace];
Double_t Y3[Nspace]; Double_t V3[Nspace]; Double_t t3[Nspace];
Double_t Y4[Nspace]; Double_t V4[Nspace]; Double_t t4[Nspace];

Double_t theta(Double_t t)		// This is a stepfunction.
{
	if(t<=t0) 	return 0.0;
	else		return 1.0;
}

Double_t analytic1(Double_t *t, Double_t *par) //analytic solution
{
	return (1/5.0)*( 4.0+6.0*exp(t[0]/2.0)*cos((sqrt(19.0)/2.0)*t[0])
			-(16.0/sqrt(19))*sin((sqrt(19)/2.0)*t[0]) )
	              +2.0*( exp(-2.0*(t[0]-t0))-exp((t[0]-t0)/2.0)*cos((sqrt(19.0)/2.0)*(t[0]-t0))
		      +(5.0/sqrt(19.0))*exp((t[0]-t0)/2.0)*sin((sqrt(19.0)/2.0)*(t[0]-t0)) )*theta(t[0]);
}

Double_t analytic2(Double_t *t, Double_t *par) //analytic solution without theta(t-t0) term
{
	return (1/5.0)*(4.0+6.0*exp(t[0]/2.0)*cos((sqrt(19.0)/2.0)*t[0])
			-(16.0/sqrt(19.0))*sin((sqrt(19.0)/2.0)*t[0]));
}


void RK4(Int_t i) //4th Runge-Kutta method
{
	t1[i] = t[i];	t2[i] = t[i] + 0.5*dt;	t3[i] = t[i] + 0.5*dt;	t4[i] = t[i] + dt;
	
	Y1[i] = Y[i];	Y2[i] = Y[i] + 0.5*V1[i]*dt;	Y3[i] = Y[i] + 0.5*V2[i]*dt;	Y4[i] = Y[i] + V3[i]*dt;
	
	V1[i] = V[i];
	V2[i] = V[i] + 0.5*(V1[i]-5.0*Y1[i]+4.0+22.0*theta(t1[i])*exp(4.0-2.0*t1[i]))*dt;
	V3[i] = V[i] + 0.5*(V2[i]-5.0*Y2[i]+4.0+22.0*theta(t2[i])*exp(4.0-2.0*t2[i]))*dt;
	V4[i] = V[i] + (V3[i]-5.0*Y3[i]+4.0+22.0*theta(t3[i])*exp(4.0-2.0*t3[i]))*dt;


	Y[i+1] = Y[i] + (1.0/6.0)*(V1[i]+2.0*V2[i]+2.0*V3[i]+V4[i])*dt;
	V[i+1] = V[i] + (1.0/6.0)*(V1[i]-5.0*Y1[i]+4.0+22.0*theta(t1[i])*exp(4.0-2.0*t1[i])
		+2.0*(V2[i]-5.0*Y2[i]+4.0+22.0*theta(t2[i])*exp(4.0-2.0*t2[i]))
                +2.0*(V3[i]-5.0*Y3[i]+4.0+22.0*theta(t3[i])*exp(4.0-2.0*t3[i]))
		+(V4[i]-5.0*Y4[i]+4.0+22.0*theta(t4[i])*exp(4.0-2.0*t4[i])))*dt;
}


void Prob03()
{
	Y[0] = Y0;
	V[0] = V0;
	t[0] = tmin;
	
	for(Int_t i=0; i<Nspace-1; i++)
	{
		t[i+1] = t[i] + dt;
		RK4(i);
	}

	TCanvas *c1 = new TCanvas("c1","",10,10,800,600 );
	
	TGraph *g1 = new TGraph(Nspace,t,Y); //numerical estimate
	g1->SetMarkerSize(1.0);
	g1->SetMarkerStyle(20);
	g1->Draw("AP");
	
	TF1 *f1 = new TF1("f1",analytic1,0.0,5.0,0);//drawing analytic solution
	f1->SetLineColor(2); //red line
	f1->Draw("same");
	
	TF1 *f2 = new TF1("f2",analytic2,0.0,5.0,0); //drawing analytic solution without theta(t-t0) term
	f2->SetLineColor(4); //blue line
	f2->Draw("same");

}
