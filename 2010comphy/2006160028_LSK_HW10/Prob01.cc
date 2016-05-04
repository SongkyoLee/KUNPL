
#define A      1.0   
#define tmax  10.0
#define tmin   0.0 
#define Y0     0.2 
#define V0     0.0
#define step  4000 
#define l 1.0
#define g 9.8
#define q1 1.0
#define q2 5.0
#define q3 10.0

const static Int_t Nspace = step;
const static Float_t dt   = (tmax-tmin)/step;

Double_t Y1[Nspace]; Double_t V1[Nspace];
Double_t Y2[Nspace]; Double_t V2[Nspace];
Double_t Y3[Nspace]; Double_t V3[Nspace];
Double_t t[Nspace];


void Euler1(Int_t i)
{

	V1[i+1] = V1[i] + (-(g/l)*Y1[i]- q1*V1[i])*dt;	Y1[i+1] = Y1[i] + V1[i]*dt;
}

void Euler2(Int_t i)
{

	V2[i+1] = V2[i] + (-(g/l)*Y2[i]- q2*V2[i])*dt;	Y2[i+1] = Y2[i] + V2[i]*dt;
}
void Euler3(Int_t i)
{

	V3[i+1] = V3[i] + (-(g/l)*Y3[i]- q3*V3[i])*dt;	Y3[i+1] = Y3[i] + V3[i]*dt;
}


void Prob01()
{ 
	gROOT->SetStyle("Plain");
	gROOT->ForceStyle();

	Y1[0] = Y0;	V1[0] = V0;	
	Y2[0] = Y0;	V2[0] = V0;
	Y3[0] = Y0;	V3[0] = V0;
	
		for (Int_t i=0; i<Nspace-1; i++)
		{
		t[i+1] = t[i] + dt;
		Euler1(i);	Euler2(i);	Euler3(i);
		}

	TCanvas* c1 = new TCanvas("c1","",10,10,500,500); 

	g1 = new TGraph(Nspace,t,Y1);	//q = 1.0 (black)
	g1->GetXaxis()->SetTitle("time (s)");
	g1->GetYaxis()->SetTitle("Theta (radians)");
	g1->SetMarkerSize(0.3);
	g1->SetMarkerStyle(20);
	g1->SetMarkerColor(1);
	g1->Draw("AP");
	
	g2 = new TGraph(Nspace,t,Y2);	//q = 5.0 (red)
	g2->SetMarkerSize(0.3);
	g2->SetMarkerStyle(20);
	g2->SetMarkerColor(2);
	g2->Draw("P");
	
	g2 = new TGraph(Nspace,t,Y3);	//q = 10.0 (blue)
	g2->SetMarkerSize(0.3);
	g2->SetMarkerStyle(20);
	g2->SetMarkerColor(4);
	g2->Draw("P");

} 
