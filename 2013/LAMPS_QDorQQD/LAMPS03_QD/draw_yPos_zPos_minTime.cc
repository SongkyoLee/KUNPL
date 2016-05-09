#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TMath.h>
#include <TStyle.h>
 
#include <sstream>
#include <string>

 using namespace std;


void draw_yPos_zPos_minTime()
{

	//open the root files and trees
	TFile *openFile = new TFile("rawData_vacuum.root");
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

	// make the canvas and histogram
	TCanvas *c1 = new TCanvas("c1","",1150,400);
	TCanvas *c2 = new TCanvas("c2","",1150,600);
	//TH2D *hist_yz = new TH2D("hist_yz", "y position vs z position on FPD;z(mm);y(mm)",20000, 4500,6500, 7000, -350, 350);
	TH2D *hist_yz = new TH2D("hist_yz", "y position vs z position on FPD;z(mm);y(mm)",23000, 5700, 8000, 8000, -400, 400); //for FPD frame
	TH1D *hist_z = new TH1D("hist_z", "z position on FPD;z(mm);Counts/binWidth",230,5700,8000);

	Int_t simEntryNum = SimTree -> GetEntries();
	std:: cout << "simEntryNum = " << simEntryNum << endl;
	
	// find fastest hit point for each event and fill the histogram
	Double_t pointTime=531531; //default value
	Int_t testEventID=0;
	Double_t pointX=0; Double_t pointY=0; Double_t pointZ=0; 

	for (Int_t i=0; i< simEntryNum; i++) {
//	for (Int_t i=0; i< 1000; i++) {
		SimTree->GetEntry(i);
		//if(isFPD==1 && spID==2212){
		//cout << "i="<<i <<", seventID="<< seventID<<", hitTime="<< hitTime << endl;
		//cout <<"isFPD="<<isFPD<<", spID="<<spID<<", x="<< x<<", y="<<y<<", z="<< z<< endl;
		//}
		if ( seventID!=testEventID) { 
			//cout << " "<<endl;
			//cout << "*****************"<<endl;
			//cout<<"seventID is "<<seventID <<", but testEventID is "<<testEventID<<endl;
			//
			//cout << "Fill the histrogram for eventID=" <<seventID << endl;
//			cout << "Fill the histrogram for eventID=" <<testEventID << endl;
//			cout << "corresponding pointTime="<< pointTime<<", pointZ="<<pointZ <<", pointY"<< pointY << endl;
			//hist_yz->Fill(pointZ,pointY);
			hist_yz->Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),pointY);
			hist_z->Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),0.1);
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
			//cout << "selected minimum time i="<<i<<", seventID=" <<seventID <<", pointTime=" <<pointTime<< endl;
			//cout << "pointX="<<pointX<<", pointY="<<pointY<<", pointZ="<<pointZ<<endl;
		}
	//	hist_yz->Fill(z+x*(TMath::Tan(33.*TMath::Pi()/180)),y);

	} 
	// for the last events
//	cout << "Fill the histogram fot the \"last\" eventID =" << seventID << endl;
//	cout << "corresponding pointTime="<< pointTime<<", pointZ="<<pointZ <<", pointY"<< pointY << endl;
	hist_yz -> Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),pointY);
	hist_z->Fill(pointZ+pointX*(TMath::Tan(33.*TMath::Pi()/180)),0.1);

	// draw the histogram
	c1->cd();
	//SimTree->Draw("y:z+x*(TMath::Tan(33.*TMath::Pi()/180))","isFPD==1","");
	//SimTree->Draw("y:z+x*(TMath::Tan(33.*TMath::Pi()/180))","isFPD==1&&pID==2212","");
	gStyle->SetOptStat(0);
	hist_yz->Draw();
	c1->SaveAs("yPos_zPos_minTime.pdf");
	//c1->Clear();
	c2->cd();
	hist_z->Draw();
	c2->SaveAs("yPos_zPos_minTime_histz.pdf");

	// save as RootFile
	// TFile* outFile = new TFile("yPos_zPos.root","recreate");
	// outFile->cd();
	// hist_yz->Write();
	// outFile->Close();

	return;

}





