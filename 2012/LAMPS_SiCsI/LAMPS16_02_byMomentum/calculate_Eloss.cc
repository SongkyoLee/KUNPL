#include <TROOT.h>
#include <TSystem.h>
#include <Riostream.h>
#include <TFile.h>
#include <TTree.h>
#include <TMath.h>
#include <TChain.h>

//for proton

void calculate_Eloss(Int_t NE=0, Int_t KE)
{
	TFile *openFile = new TFile(Form("rawData_%dMeV.root",KE), "READ");

	Int_t eventID, trackID, isToF;
	Double_t energyDeposit, hitTime, momentum;
	Double_t pX, pY, pZ;
	Double_t mass = 938.27201; // temporary.. only for proton!

	const int numEvents=NE;
	Double_t energyLoss[numEvents]={0.};

	TTree *GeneratorData = (TTree *) openFile -> Get("GeneratorData");
	TTree *SimulationData = (TTree *) openFile -> Get("SimulationData"); //meaningless?
		SimulationData -> SetBranchAddress("eventID", &eventID);
		SimulationData -> SetBranchAddress("isToF", &isToF);
		SimulationData -> SetBranchAddress("hitTime", &hitTime);
		SimulationData -> SetBranchAddress("postx", &pX); //postx = momentum pX
		SimulationData -> SetBranchAddress("posty", &pY);
		SimulationData -> SetBranchAddress("postz", &pZ);

	ofstream outFile(Form("energyLoss_%dMeV.dat", KE), std::ios::app);

	for (Int_t i=0; i<numEvents ; i ++)
	{
		TTree* tempTree = SimulationData -> CopyTree(Form("eventID==%d&&isToF==1&&pID==2212", i));
		tempTree -> SetBranchAddress("energyDeposit", &energyDeposit);

		Int_t tempEntries = tempTree -> GetEntries(); //num of track per event 
//		cout << i << "th Entries : " << tempEntries << endl;

		Double_t minToF = 1000; // default value (to find minimum tof)

		for (Int_t j=0; j<tempEntries; j++)
		{
			tempTree -> GetEntry(j);
//			cout << "track num j = " << j << endl;
//			cout <<"track " << j <<"th hitTime = " << hitTime << endl;

			if(minToF>hitTime)
			{
				minToF = hitTime;
				momentum= TMath::Sqrt( pX*pX + pY*pY + pZ*pZ );
//				cout  <<" min ToF = " << minToF
//					 << " track momentum=" << momentum << endl;
			energyLoss[i] = KE - (TMath::Sqrt(momentum*momentum + mass*mass) - mass );
			}
//			energyLoss[i] = KE - (TMath::Sqrt(momentum*momentum + mass*mass) - mass );
//			cout << "energyLoss = " << energyLoss[i] << endl;

		}
//	cout << "---------------------------------------------------" << endl;
//	cout << "total momentum of event " << i <<" is "<< momentum << endl;
	cout << "total energy loss of event " << i <<" is "<< energyLoss[i] << endl;
//	cout << "---------------------------------------------------" << endl;

	outFile << setw(5) << i <<  setw(10) << energyLoss[i] << endl;

	}
	openFile -> Close();
	delete openFile;

	return;
}
