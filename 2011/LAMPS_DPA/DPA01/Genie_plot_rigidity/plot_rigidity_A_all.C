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

void plot_rigidity_A_all () {
	const Int_t totalEntry = 9;
	const Int_t totalCase = 3;
	const Double_t mField[totalCase] = {1.0, 1.5, 4.0};

	aEntry_t	aEntry[totalEntry];
	Double_t	orderDisplay[totalCase][totalEntry];
	Double_t	tempAtomicNumberArray[totalCase][totalEntry];
	Double_t	tempProtonNumberArray[totalCase][totalEntry];
	Double_t	tempMeanKEpAArray[totalCase][totalEntry];
	Double_t	tempKEpARangeArray[totalCase][totalEntry];
	Double_t	tempMeanppZArray[totalCase][totalEntry];
	Double_t	tempppZRangeArray[totalCase][totalEntry];
	Double_t	width[totalCase][totalEntry];

	for (Int_t j = 0; j != totalCase; j++) {
	char fileName[40];
	sprintf(fileName, "./data/MField_%.1fT.dat", mField[j]);

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

			orderDisplay[j][i] = i + j*0.2 + 0.3;
			tempAtomicNumberArray[j][i] = aEntry[i].atomicNumber;
			tempProtonNumberArray[j][i] = aEntry[i].protonNumber;
			tempMeanKEpAArray[j][i] = (aEntry[i].maxKEpu + aEntry[i].minKEpu)/2/1000;
			tempKEpARangeArray[j][i] = (aEntry[i].maxKEpu - aEntry[i].minKEpu)/2/1000;
			tempMeanppZArray[j][i] = (aEntry[i].maxppu + aEntry[i].minppu)*aEntry[i].atomicNumber/2/aEntry[i].protonNumber/1000;
			tempppZRangeArray[j][i] = (aEntry[i].maxppu - aEntry[i].minppu)*aEntry[i].atomicNumber/2/aEntry[i].protonNumber/1000;
			width[j][i] = 0.1;
		}
	}
	}
	
	gStyle -> SetPadLeftMargin(0.13);
	gStyle -> SetTitleYOffset(1.5);
	gStyle -> SetPadTickY(0);
	gStyle -> SetOptTitle(0);

	TCanvas *cvs = new TCanvas("KE/A vs. A plot", "KE/A vs. A", 1000, 1000);
	cvs -> cd();

	char plotTitle[20];
	sprintf(plotTitle, "KE/A vs. A", mField);

	TGraphErrors *graph1 = new TGraphErrors(totalEntry, orderDisplay[0], tempMeanKEpAArray[0], width[0], tempKEpARangeArray[0]);
	graph1 -> SetMarkerStyle(0);
	graph1 -> SetTitle(plotTitle);
	graph1 -> GetYaxis() -> SetTitle("KE/A (GeV)");
	graph1 -> GetYaxis() -> CenterTitle();
	graph1 -> GetYaxis() -> SetRangeUser(0.0, 3.2);
	graph1 -> GetXaxis() -> Set(totalEntry, 0, totalEntry);
	for (Int_t i = 0; i != totalEntry; i++) {
		graph1 -> GetXaxis() -> SetBinLabel(i+1, aEntry[i].particleName);
	}
	graph1 -> GetXaxis() -> LabelsOption("h");
	graph1 -> SetFillColor(2);
	graph1 -> Draw("A2");

	TGraphErrors *graph1_1 = new TGraphErrors(totalEntry, orderDisplay[1], tempMeanKEpAArray[1], width[1], tempKEpARangeArray[1]);
	graph1_1 -> SetMarkerStyle(0);
	graph1_1 -> SetFillColor(3);
	graph1_1 -> Draw("2 SAME");

	TGraphErrors *graph1_2 = new TGraphErrors(totalEntry, orderDisplay[2], tempMeanKEpAArray[2], width[2], tempKEpARangeArray[2]);
	graph1_2 -> SetMarkerStyle(0);
	graph1_2 -> SetFillColor(4);
	graph1_2 -> Draw("2 SAME");

	TLegend *list1 = new TLegend(0.33, 0.97, 0.53, 0.92);
		list1 -> AddEntry(graph1, "1 T", "f");
		list1 -> SetFillStyle(0);
		list1 -> SetBorderSize(0);
		list1 -> Draw("same");

	TLegend *list1_1 = new TLegend(0.45, 0.97, 0.64, 0.92);
		list1_1 -> AddEntry(graph1_1, "1.5 T", "f");
		list1_1 -> SetFillStyle(0);
		list1_1 -> SetBorderSize(0);
		list1_1 -> Draw("same");

	TLegend *list1_2 = new TLegend(0.58, 0.97, 0.78, 0.92);
		list1_2 -> AddEntry(graph1_2, "4 T", "f");
		list1_2 -> SetFillStyle(0);
		list1_2 -> SetBorderSize(0);
		list1_2 -> Draw("same");

	char saveName[40];
	sprintf(saveName, "KEpA.png", mField);
	cvs -> SaveAs(saveName);

	sprintf(saveName, "KEpA_log.png", mField);
	graph1 -> GetYaxis() -> SetRangeUser(0.009, 4.0);
	cvs -> SetLogy();
	cvs -> SaveAs(saveName);

	TCanvas *cvs_2 = new TCanvas("p/Z vs. A plot", "p/Z vs. A", 1000, 1000);
	cvs_2 -> cd();

	sprintf(plotTitle, "p/Z vs. A", mField);

	TGraphErrors *graph2 = new TGraphErrors(totalEntry, orderDisplay[0], tempMeanppZArray[0], width[0], tempppZRangeArray[0]);
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
	graph2 -> SetFillColor(2);
	graph2 -> Draw("A2");

	TGraphErrors *graph2_1 = new TGraphErrors(totalEntry, orderDisplay[1], tempMeanppZArray[1], width[1], tempppZRangeArray[1]);
	graph2_1 -> SetMarkerStyle(0);
	graph2_1 -> SetFillColor(3);
	graph2_1 -> Draw("2 SAME");

	TGraphErrors *graph2_2 = new TGraphErrors(totalEntry, orderDisplay[2], tempMeanppZArray[2], width[2], tempppZRangeArray[2]);
	graph2_2 -> SetMarkerStyle(0);
	graph2_2 -> SetFillColor(4);
	graph2_2 -> Draw("2 SAME");
	
	TLegend *list2 = new TLegend(0.33, 0.97, 0.53, 0.92);
		list2 -> AddEntry(graph2, "1 T", "f");
		list2 -> SetFillStyle(0);
		list2 -> SetBorderSize(0);
		list2 -> Draw("same");

	TLegend *list2_1 = new TLegend(0.45, 0.97, 0.64, 0.92);
		list2_1 -> AddEntry(graph2_1, "1.5 T", "f");
		list2_1 -> SetFillStyle(0);
		list2_1 -> SetBorderSize(0);
		list2_1 -> Draw("same");

	TLegend *list2_2 = new TLegend(0.58, 0.97, 0.78, 0.92);
		list2_2 -> AddEntry(graph2_2, "4 T", "f");
		list2_2 -> SetFillStyle(0);
		list2_2 -> SetBorderSize(0);
		list2_2 -> Draw("same");

	sprintf(saveName, "ppZ.png", mField);
	cvs_2 -> SaveAs(saveName);

	sprintf(saveName, "ppZ_log.png", mField);
	graph2 -> GetYaxis() -> SetRangeUser(0.18, 4.5);
	cvs_2 -> SetLogy();
	cvs_2 -> SaveAs(saveName);

}
