
//the acceptance-rejection method

void Prob01()
{
	gROOT->Reset();
	TCanvas* c1 = new TCanvas("c1", "", 200, 10, 1800, 400);
	c1 -> Divide(3,1);
	
	
	c1->cd(1);
	hist1 = new TH1F("hist1", "N=100", 100, -1.0, 2.0);
	hist1 -> SetFillColor(11);
	hist1 -> GetYaxis()->SetTitle("# of events");
	hist1-> Draw();
	
	gRandom->SetSeed(2006160028);
	Float_t func;
	Int_t dum;
	Int_t dum2;
	for (Int_t i=0; i<10000/30; i++)
	{
		Float_t a = gRandom->Rndm(dum); //r1
		Float_t x = -1.0+a*3.0;  //generate a randomnumber x = x_min+r1(x_max-x_min)
		Float_t b = gRandom->Rndm(dum2); //r2
		Float_t u = b*(0.117); //generate a randomnumber u = r2*f_max
		func = (1.0/36.0)*((x*x*x*x/5.0)+1.0); 
		if (u < func) { hist1->Fill(x);}
		if (i%100 == 0) {c1 -> Modified(); c1->Update();}
	}
	
	const Int_t n = 300;
	Float_t m[n], p[n];
	for (Int_t i=0; i<n; i++)
	{
		m[i]=(i/100.0)-1.0;		
		p[i]=25*(1.0/36.0)*((m[i]*m[i]*m[i]*m[i]/5.0)+1.0);
	}	
	gr1 = new TGraph(n,m,p);
	gr1->Draw("CP");	
	
		
	c1->cd(2);	
	hist2 = new TH1F("hist2", "N=1000", 100, -1.0, 2.0);
	hist2 -> SetFillColor(11);
	hist2 -> GetYaxis()->SetTitle("# of events");
	hist2-> Draw();
		
	gRandom->SetSeed(2006160028);
	Float_t func;
	Int_t dum;
	Int_t dum2;
	for (Int_t i=0; i<100000/33-47; i++)
	{
		Float_t a = gRandom->Rndm(dum);
		Float_t x = -1.0+a*3.0; 
		Float_t b = gRandom->Rndm(dum2);
		Float_t u = b*(0.117);
		func = (1.0/36.0)*((x*x*x*x/5.0)+1.0);
		if (u < func) { hist2->Fill(x);}
		if (i%100 == 0) {c1 -> Modified(); c1->Update();}
	}
	
	const Int_t n = 300;
	Float_t m[n], p[n];
	for (Int_t i=0; i<n; i++)
	{
		m[i]=(i/100.0)-1.0;		
		p[i]=250*(1.0/36.0)*((m[i]*m[i]*m[i]*m[i]/5.0)+1.0);
	}	
	gr2 = new TGraph(n,m,p);
	gr2->Draw("CP");	
	
		
	c1->cd(3);
	hist3 = new TH1F("hist3", "N=10000", 100, -1.0, 2.0);
	hist3 -> SetFillColor(11);
	hist3 -> GetYaxis()->SetTitle("# of events");
	hist3-> Draw();
	
	gRandom->SetSeed(2006160028);
	Float_t func;
	Int_t dum;
	Int_t dum2;
	for (Int_t i=0; i<1000000/34+3; i++)
	{
		Float_t a = gRandom->Rndm(dum);
		Float_t x = -1.0+a*3.0;
		Float_t b = gRandom->Rndm(dum2);
		Float_t u = b*(0.117);
		func = (1.0/36.0)*((x*x*x*x/5.0)+1.0);
		if (u < func) { hist3->Fill(x);}
		if (i%100 == 0) {c1 -> Modified(); c1->Update();}
	}
		
	const Int_t n = 300;
	Float_t m[n], p[n];
	for (Int_t i=0; i<n; i++)
	{
		m[i]=(i/100.0)-1.0;		
		p[i]=2500*(1.0/36.0)*((m[i]*m[i]*m[i]*m[i]/5.0)+1.0);
	}	
	gr3 = new TGraph(n,m,p);
	gr3->Draw("CP");	
		
}
