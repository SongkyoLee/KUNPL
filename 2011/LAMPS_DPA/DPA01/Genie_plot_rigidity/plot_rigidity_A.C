#include <Riostream.h>
#include <TROOT.h>
#include <TSystem.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <fstream>

struct aEntry_t {
	char		particleName[6];
	Double_t	atomicNumber;
	Double_t	protonNumber;
	Double_t	minKEpu;
	Double_t	maxKEpu;
	Double_t	minppu;
	Double_t	maxppu;
};

void plot_rigidity_A () {
	const Int_t totalEntry = 9;
	const Double_t mField = 1.0;

	aEntry_t	aEntry[totalEntry];
	Double_t	orderDisplay[totalEntry];
	Double_t	tempAtomicNumberArray[totalEntry];
	Double_t	tempProtonNumberArray[totalEntry];
	Double_t	tempMeanKEpAArray[totalEntry];
	Double_t	tempKEpARangeArray[totalEntry];
	Double_t	tempMeanppZArray[totalEntry];
	Double_t	tempppZRangeArray[totalEntry];
	Double_t	width[totalEntry];

	char fileName[40];
	sprintf(fileName, "./data/MField_%.1fT.dat", mField);

	ifstream dataFile;
	dataFile.open(fileName);
	if ( dataFile.is_open() ) {
		for (Int_t i = 0; i != totalEntry; i++) {
/*			dataFile >> aEntry.particleName >> aEntry.atomicNumber >> aEntry.protonNumber >> aEntry.minKEpu >> aEntry.maxKEpu >> aEntry.minppu >> aEntry.maxppu;
			cout << std::setw(20) << "Particle Name: " << aEntry.particleName << endl;
			cout << std::setw(20) << "Atomic Number: " << aEntry.atomicNumber << endl;
			cout << std::setw(20) << "Proton Number: " << aEntry.protonNumber << endl;
			cout << std::setw(20) << "Min. K.E. per u: " << aEntry.minKEpu << endl;
			cout << std::setw(20) << "Max. K.E. per u: " << aEntry.maxKEpu << endl;
			cout << std::setw(20) << "Min. p per u: " << aEntry.minppu << endl;
			cout << std::setw(20) << "Max. p per u: " << aEntry.maxppu << endl << endl;
*/

			dataFile >> aEntry[i].particleName >> aEntry[i].atomicNumber >> aEntry[i].protonNumber >> aEntry[i].minKEpu
				 >> aEntry[i].maxKEpu >> aEntry[i].minppu >> aEntry[i].maxppu;

			orderDisplay[i] = (i+0.5);
			tempAtomicNumberArray[i] = aEntry[i].atomicNumber;
			tempProtonNumberArray[i] = aEntry[i].protonNumber;
			tempMeanKEpAArray[i] = (aEntry[i].maxKEpu + aEntry[i].minKEpu)/2/1000;
			tempKEpARangeArray[i] = (aEntry[i].maxKEpu - aEntry[i].minKEpu)/2/1000;
			tempMeanppZArray[i] = (aEntry[i].maxppu + aEntry[i].minppu)*aEntry[i].atomicNumber/2/aEntry[i].protonNumber/1000;
			tempppZRangeArray[i] = (aEntry[i].maxppu - aEntry[i].minppu)*aEntry[i].atomicNumber/2/aEntry[i].protonNumber/1000;
			width[i] = 0.2;
		}
	}
	
	gStyle -> SetPadLeftMargin(0.13);
	gStyle -> SetTitleYOffset(1.5);
	gStyle -> SetPadTickY(0);

	TCanvas *cvs = new TCanvas("KE/A vs. A plot", "KE/A vs. A", 1000, 1000);
	cvs -> cd();

	char plotTitle[20];
	sprintf(plotTitle, "KE/A vs. A (B=%.1fT)", mField);

	TGraphErrors *graph = new TGraphErrors(totalEntry, orderDisplay, tempMeanKEpAArray, width, tempKEpARangeArray);
	graph -> SetMarkerStyle(0);
	graph -> SetTitle(plotTitle);
	graph -> GetYaxis() -> SetTitle("KE/A (GeV)");
	graph -> GetYaxis() -> CenterTitle();
	graph -> GetYaxis() -> SetRangeUser(0.0, 3.2);
	graph -> GetXaxis() -> Set(totalEntry, 0, totalEntry);
	for (Int_t i = 0; i != totalEntry; i++) {
		graph -> GetXaxis() -> SetBinLabel(i+1, aEntry[i].particleName);
	}
	graph -> GetXaxis() -> LabelsOption("h");
	graph -> SetFillColor(4);
	graph -> Draw("A2");

	char saveName[40];
	sprintf(saveName, "KEpA_%.1fT.png", mField);
	cvs -> SaveAs(saveName);

	TCanvas *cvs_2 = new TCanvas("p/Z vs. A plot", "p/Z vs. A", 1000, 1000);
	cvs_2 -> cd();

	sprintf(plotTitle, "p/Z vs. A (B=%.1fT)", mField);

	TGraphErrors *graph2 = new TGraphErrors(totalEntry, orderDisplay, tempMeanppZArray, width, tempppZRangeArray);
	graph2 -> SetMarkerStyle(0);
	graph2 -> SetTitle(plotTitle);
	graph2 -> GetYaxis() -> SetTitle("p/Z (GeV/c)");
	graph2 -> GetYaxis() -> CenterTitle();
	graph2 -> GetYaxis() -> SetRangeUser(0.05, 4.0);
	graph2 -> GetXaxis() -> Set(totalEntry, 0, totalEntry);
	for (Int_t i = 0; i != totalEntry; i++) {
		graph2 -> GetXaxis() -> SetBinLabel(i+1, aEntry[i].particleName);
	}
	graph2 -> GetXaxis() -> LabelsOption("h");
	graph2 -> SetFillColor(4);
	graph2 -> Draw("A2");

	sprintf(saveName, "ppZ_%.1fT.png", mField);
	cvs_2 -> SaveAs(saveName);

}
