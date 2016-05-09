#include <Riostream.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TDirectory.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TMath.h>
 
#include <sstream>
#include <string>

 using namespace std;


void draw_xPos_zPos()
{

	//open the root files and trees
	TFile *openFile = new TFile("rawData_vacuum.root");
	TTree * GenTree = (TTree *)openFile->Get("GeneratorData");
	TTree * SimTree = (TTree *)openFile->Get("SimulationData");
	//TTree* totTree = new TTree();
	//totTree->AddFriend("GeneratorTree",openFile);
	//totTree->AddFriend("SimulationTree",openFile);

	// make the canvas and histogram
	TCanvas *c1 = new TCanvas("c1","",1000,700);
	TH2D *hist_xz = new TH2D("hist_xz", "x position vs z position on FPD;z(mm);x(mm)",20000, 4600,6600, 14000, 1800, 3200); //for lab frame

	// draw the histogram
	gStyle->SetOptStat(0);
	//SimTree->Draw("x:z","isFPD==1&&pID==2212","");
	SimTree->Draw("x:z>>hist_xz","isFPD==1&&pID==2212","");
	//SimTree->Draw("x:z+x*(TMath::Tan(28.*TMath::Pi()/180))","isFPD==1&&pID==2212","");
	//SimTree->Draw("x:z+x*(TMath::Tan(28.*TMath::Pi()/180))>>hist_xz","isFPD==1&&pID==2212","");

	// save as PDF
	c1->SaveAs("xPos_zPos.pdf");
//	c1->Clear();

	// save as RootFile
	// TFile* outFile = new TFile("yPos_zPos.root","recreate");
	// outFile->cd();
	// hist_yz->Write();
	// outFile->Close();

	return;

}





