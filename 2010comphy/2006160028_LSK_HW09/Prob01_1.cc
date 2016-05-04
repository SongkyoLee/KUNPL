
// I want to use the method which professor told me to draw log scale graph.
// Around the name of the graph (say, [the Nuclear Ptl Decay),
// click the right button of mause, and check the "SetLogy" to change the scale!! :)

#include<stdio.h>
#include<math.h>

const static Int_t M = 20; //Nspace (M*dt = b, where b is max for t)

#define dt 0.5 // step size in t
#define tau 1.0 
#define N0 100 // initial value of N

Double_t N_Eul[M];
Double_t N_2RK[M];
Double_t N_4RK[M];
Double_t t[M];

Double_t analytic(Double_t *x, Double_t *par)  //analytic sol.
{
	return N0 * TMath::Exp(-x[0]/tau);
}

void Euler(Int_t i) //Euler method function
{
	N_Eul[i+1] = N_Eul[i] - (N_Eul[i]/tau)*dt;
}

void RK2nd(Int_t i) //2nd Runge-Kutta function
{
//  	Float_t tp = t[i] + 0.5*dt;
	Float_t xp = N_2RK[i] - 0.5*(N_2RK[i]/tau)*dt; //p stands for prime
	N_2RK[i+1] = N_2RK[i] - (xp/tau)*dt;
}

void RK4th(Int_t i) //4th Runge-Kutta function
{
	Float_t xp1 = N_4RK[i];
	Float_t xp2 = N_4RK[i] - 0.5*(N_4RK[i]/tau)*dt;
	Float_t xp3 = N_4RK[i] - 0.5*(xp2/tau)*dt;
	Float_t xp4 = N_4RK[i] - 1.0*(xp3/tau)*dt;
	N_4RK[i+1] = N_4RK[i] - ((1.0/6.0)*(xp1/tau+2.0*xp2/tau+2.0*xp3/tau+xp4/tau))*dt;
}



void Prob01_1()
{ 

	gROOT->SetStyle("Plain");
	gROOT->ForceStyle();

	N_Eul[0] = N0; N_2RK[0] = N0; N_4RK[0] = N0; //initial condition;

	for (Int_t i=0; i<M-1; i++)
	{
		t[i+1] = t[i] + dt;
		Euler(i);
		RK2nd(i);
		RK4th(i);
	}

	TCanvas* c1 = new TCanvas("c1","",10,10,500,500); 
	c1-> cd();
  
	g1 = new TGraph(M,t,N_Eul); //white circle marker for Euler method
	g1->SetMarkerStyle(24);
	g1->Draw("AP");

	g2 = new TGraph(M,t,N_2RK); //white triangle marker for 2nd RK method
	g2->SetMarkerStyle(26);
	g2->Draw("P");
	
	g3 = new TGraph(M,t,N_4RK); //red cross marker for 4th RK method
	g3->SetMarkerStyle(2);
	g3->SetMarkerColor(2);
	g3->Draw("P");
 
	TF1 *anal = new TF1("anal",analytic,0.0,M*dt,1);
	anal->SetLineColor(4);
	anal->Draw("SAME");

} 

