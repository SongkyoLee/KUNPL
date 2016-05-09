#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TMath.h>
 
#include <sstream>
#include <string>

 using namespace std;


void draw_yPos_zPos()
{

	//open the root files and trees
	TFile *openFile = new TFile("rawData_vacuum.root");
	TTree * GenTree = (TTree *)openFile->Get("GeneratorData");
	TTree * SimTree = (TTree *)openFile->Get("SimulationData");
	//TTree* totTree = new TTree();
	//totTree->AddFriend("GeneratorTree",openFile);
	//totTree->AddFriend("SimulationTree",openFile);

	// make the canvas and histogram
	TCanvas *c1 = new TCanvas("c1","",1150,400);
	//TH2D *hist_yz = new TH2D("hist_yz", "y position vs z position on FPD;z(mm);y(mm)",20000, 4500,6500, 7000, -350, 350);
	TH2D *hist_yz = new TH2D("hist_yz", "y position vs z position on FPD;z(mm);y(mm)",23000, 5700, 8000, 8000, -400, 400); //for FPD frame

	// draw the histogram
	gStyle->SetOptStat(0);
	//SimTree->Draw("y:z","isFPD==1","");
	//SimTree->Draw("y:z+x*(TMath::Tan(28.*TMath::Pi()/180))","isFPD==1&&pID==2212","");
	SimTree->Draw("y:z+x*(TMath::Tan(28.*TMath::Pi()/180))>>hist_yz","isFPD==1&&pID==2212","");

	// save as PDF
	c1->SaveAs("yPos_zPos.pdf");
//	c1->Clear();

	// save as RootFile
	// TFile* outFile = new TFile("yPos_zPos.root","recreate");
	// outFile->cd();
	// hist_yz->Write();
	// outFile->Close();

	return;

}





