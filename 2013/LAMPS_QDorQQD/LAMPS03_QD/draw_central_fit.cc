#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TF1.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TMath.h>
#include <TStyle.h>
 
#include <sstream>
#include <string>

 using namespace std;


void draw_central_fit()
{

	//open the root files and trees
	TFile *openFile = new TFile("rawData_7000.root");
	TTree * GenTree = (TTree *)openFile->Get("GeneratorData");
	TTree * SimTree = (TTree *)openFile->Get("SimulationData");
	//TTree* totTree = new TTree();
	//totTree->AddFriend("GeneratorTree",openFile);
	//totTree->AddFriend("SimulationTree",openFile);

	// Set branches 
	Int_t geventID=0; Int_t gtrackID=0; Int_t seventID=0; Int_t strackID=0; Int_t gpID=0; Int_t spID=0;
	Int_t isFPD=0;
	Double_t pX=0; Double_t pY=0; Double_t pZ=0; Double_t hitTime=0;
	Double_t x=0; Double_t y=0; Double_t z=0;
	Double_t momx=0; Double_t momy=0; Double_t momz=0;

	GenTree->SetBranchAddress("eventID",&geventID); //GeneratorTree.eventID
	GenTree->SetBranchAddress("trackID",&gtrackID);
	GenTree->SetBranchAddress("pID",&gpID);
	GenTree->SetBranchAddress("pX",&pX);
	GenTree->SetBranchAddress("pY",&pY);
	GenTree->SetBranchAddress("pZ",&pZ);

	SimTree->SetBranchAddress("eventID",&seventID); //SimulationTree.eventID
	SimTree->SetBranchAddress("trackID",&strackID);
	SimTree->SetBranchAddress("pID",&spID);
	SimTree->SetBranchAddress("hitTime", &hitTime);
	SimTree->SetBranchAddress("x", &x);
	SimTree->SetBranchAddress("y", &y);
	SimTree->SetBranchAddress("z", &z);
	SimTree->SetBranchAddress("isFPD", &isFPD);
	SimTree->SetBranchAddress("postx", &momx);
	SimTree->SetBranchAddress("posty", &momy);
	SimTree->SetBranchAddress("postz", &momz);

	// make the canvas and histogram
	TCanvas *c1 = new TCanvas("c1","",750,500);
//	TCanvas *c2 = new TCanvas("c2","",1150,600);
	TCanvas *c2 = new TCanvas("c2","",750,500);
	TH2D *hist_yz = new TH2D("hist_yz", "central #theta vs momentum;P_{tot}(MEV/c);#theta(mrad)",50, 160, 230, 100, 940, 1170); //for FPD frame
//	TH1D *hist_z = new TH1D("hist_z", "z position on FPD;z(mm);Counts/binWidth",230,5700,8000);
	TH1D *hist_z = new TH1D("hist_z", "central #theta;#theta(mrad);Counts",2300, 940, 1170);

	Int_t simEntryNum = SimTree -> GetEntries();
	std:: cout << "simEntryNum = " << simEntryNum << endl;
	
	// find fastest hit point for each event and fill the histogram
	Double_t pointTime=531531; //default value
	Int_t testEventID=0;
	Double_t pointX=0; Double_t pointY=0; Double_t pointZ=0; 
	Double_t pointPx=0; Double_t pointPy=0; Double_t pointPz=0;
	Double_t pointPp=0; Double_t pointTheta=0; Double_t pointPhi=0;

	for (Int_t i=0; i< simEntryNum; i++) {
		SimTree->GetEntry(i);
		if ( seventID!=testEventID) { 
			//cout << " "<<endl;
			//cout << "*****************"<<endl;
			//cout<<"seventID is "<<seventID <<", but testEventID is "<<testEventID<<endl;
			//
			//cout << "Fill the histrogram for eventID=" <<seventID << endl;
//			cout << "Fill the histrogram for eventID=" <<testEventID << endl;
//			cout << "corresponding pointTime="<< pointTime<<", pointZ="<<pointZ <<", pointY"<< pointY << endl;
			//hist_yz->Fill(pointZ,pointY);
			//hist_yz->Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),pointY);
			//pointPp = TMath::Sqrt(pointPx*pointPx+pointPz+pointPz);
			pointPp = TMath::Sqrt(pointPx*pointPx+pointPy*pointPy+pointPz*pointPz);
			pointTheta=TMath::ATan(pointPx/pointPz)*1000; //rad to mrad
//			hist_z->Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),0.1);
//				cout << "total p="<<TMath::Sqrt(pointPx*pointPx+pointPy*pointPy+pointPz*pointPz)<<", pointTheta=" << pointTheta <<" (mrad)" << endl;
			hist_yz->Fill(pointPp,pointTheta);
			hist_z->Fill(pointTheta,1);
			testEventID=testEventID+1; 
			pointTime = 531531;
			//cout << "Now calculate the next eventID ="<<seventID <<", with initialized pointTime =" << pointTime << endl;
			//cout << "*****************"<<endl;
			//cout << " "<<endl;
		}
		if (seventID==testEventID && isFPD==1 && spID==2212 && hitTime < pointTime ) {
			pointTime = hitTime;
			pointX = x;
			pointY = y;
			pointZ = z;
			pointPx=momx;
			pointPy=momy;
			pointPz=momz;
			//cout << "selected minimum time i="<<i<<", seventID=" <<seventID <<", pointTime=" <<pointTime<< endl;
			//cout << "pointX="<<pointX<<", pointY="<<pointY<<", pointZ="<<pointZ<<endl;
		}
	} 
	// for the last events
//	cout << "Fill the histogram fot the \"last\" eventID =" << seventID << endl;
//	cout << "corresponding pointTime="<< pointTime<<", pointZ="<<pointZ <<", pointY"<< pointY << endl;
	//hist_yz -> Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),pointY);
//	hist_z->Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),0.1);
			pointPp = TMath::Sqrt(pointPx*pointPx+pointPy*pointPy+pointPz*pointPz);
			pointTheta=TMath::ATan(pointPx/pointPz)*1000; //rad to mrad
			//hist_yz->Fill(TMath::Sqrt(pointPx*pointPx+pointPy*pointPy+pointPz*pointPz),pointTheta);
			hist_yz->Fill(pointPp,pointTheta);
			hist_z->Fill(pointTheta,1);

	// draw the histogram
	c1->cd();
	//SimTree->Draw("y:z+x*(TMath::Tan(33.*TMath::Pi()/180))","isFPD==1","");
	//SimTree->Draw("y:z+x*(TMath::Tan(33.*TMath::Pi()/180))","isFPD==1&&pID==2212","");
	gStyle->SetOptStat(0);
	hist_yz->Draw("colz");
	c1->SaveAs("central_fit_2d.pdf");
	//c1->Clear();
	c2->cd();
	hist_z->Draw();
	c2->SaveAs("central_fit_1d.pdf");//temp

	return;
		
	//define Gaussian function for fitting
	TF1* g1= new TF1("g1", "gaus", 5950, 6050); //name, type, min, max
	TF1* g2= new TF1("g2", "gaus", 6130, 6250);
	TF1* g3= new TF1("g3", "gaus", 6340, 6440);
	TF1* g4= new TF1("g4", "gaus", 6540, 6680);
	TF1* g5= new TF1("g5", "gaus", 6760, 6880);
	TF1* g6= new TF1("g6", "gaus", 7000, 7100);
	TF1* g7= new TF1("g7", "gaus", 7210, 7340);

	TF1* g_tot = new TF1("g_tot","gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)",5700,8000);

	hist_z->Fit(g1,"RN");
	hist_z->Fit(g2,"RN+");
	hist_z->Fit(g3,"RN+");
	hist_z->Fit(g4,"RN+");
	hist_z->Fit(g5,"RN+");
	hist_z->Fit(g6,"RN+");
	hist_z->Fit(g7,"RN+");

	Double_t par[21];
	g1->GetParameters(&par[0]); //0,1,2 : const, mean, sigma	
	g2->GetParameters(&par[3]); //3,4,5	
	g3->GetParameters(&par[6]); //6,7,8	
	g4->GetParameters(&par[9]);	
	g5->GetParameters(&par[12]);	
	g6->GetParameters(&par[15]);	
	g7->GetParameters(&par[18]);	
	g_tot->SetParameters(par); //use above obtained parameters for total fit
	hist_z->Fit(g_tot,"R+");

	cout << setw(10)<<"constant" <<setw(10)<< "mean" << setw(10)<<"sigma" << endl;
	cout << setw(10) <<  par[0] <<	setw(10)<< par[1] << setw(10) << par[2] << endl;
	c2->SaveAs("central_fit.pdf");

	// save as RootFile
	// TFile* outFile = new TFile("yPos_zPos.root","recreate");
	// outFile->cd();
	// hist_yz->Write();
	// outFile->Close();

	return;

}





