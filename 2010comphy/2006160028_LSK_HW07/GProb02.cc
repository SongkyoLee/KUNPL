using namespace std;

chisq(double x)		
{
	return (1.25 * x * x - 5.5 * x + 6.25) ;  //chisquare function
}

void Prob02()
{
	TCanvas *c1 = new TCanvas("c1","",200,10,800,600);

	TF1 *cs = new TF1("cs","chisq(x)",0,4);
	cs->SetLineColor(1);
	cs->Draw();

	double x[3];
	double y[3];

	double x[0] = 2.2 - 0.894427 ;
	double y[0] = chisq(2.2 - 0.894427) ;
	double x[1] = 2.2 ;
	double y[1] = chisq(2.2);
	double x[2] = 2.2 + 0.894427 ;
	double y[2] = chisq(2.2 + 0.894427) ;

	double reduc = y[0] - y[1];      // reduction of chi-square value ^^
	
	TGraph *point = new TGraph(3,x,y);
	point->SetMarkerStyle(20);
	point->SetMarkerColor(2);
	point->Draw("PSAME");
}
