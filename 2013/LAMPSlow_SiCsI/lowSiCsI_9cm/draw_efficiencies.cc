#include <fstream>
#include <iostream>
//#include <sstream>

void draw_efficiencies()
{
	using namespace std;
	//	std::ifstream Fin1("edep1MeV.out",std::ios::in); // in : read the file
	ifstream Fin;

	// define constants
	const Int_t totalEvents=10000;
	const Double_t threshold1=0.2; //[MeV]
	const Double_t threshold2=1.; //[MeV]

	// file names
	string fileName[] = {"edep1MeV.out", "edep5MeV.out", "edep10MeV.out", "edep15MeV.out", "edep20MeV.out"};
	const int nFile = sizeof(fileName)/sizeof(string);
	cout << " nFile = "<< nFile << endl;

	//define the variables
	Int_t eventNum, acceptedCounts1, acceptedCounts2, generatedCounts;
	Double_t eInit, edep1, edep2; 
	Double_t efficiency1[nFile];
	Double_t efficiency2[nFile];

	for (Int_t i=0; i<nFile; i++){

		//initialize the variables
		eventNum=0;
		acceptedCounts1=0;
		acceptedCounts2=0;
		generatedCounts=0;
		eInit=0;
		edep1=0;
		edep2=0;
		efficiency1[i]=0;
		efficiency2[i]=0;

		// read the files
		Fin.open(fileName[i].c_str());
		if(!Fin.is_open()) { cout << "Warning : can NOT open the file!"<<endl; }
		while(Fin.good()){
			if (generatedCounts >= totalEvents) { break;}
			Fin >> eventNum >> eInit >> edep1 >> edep2;
			generatedCounts++ ;
			if ( edep1 >=threshold1 && edep2 >= threshold2) { acceptedCounts1++; } 
			if ( edep2 >= threshold2) { acceptedCounts2++; } 
			cout<<"generatedCounts="<< generatedCounts<<endl; 
			cout<<"acceptedCounts1="<<acceptedCounts1<<", acceptedCounts2="<< acceptedCounts2<<endl; 
			cout<<"eventNum="<<eventNum <<", eInit=" << eInit <<", edep1="<< edep1 << ", edep2="<<edep2 << endl;
		}
		Fin.close();

		efficiency1[i] = 100*(double)acceptedCounts1/(double)generatedCounts;
		efficiency2[i] = 100*(double)acceptedCounts2/(double)generatedCounts;
		cout << "generated Counts = " << generatedCounts << endl;
		cout << "accepted Counts 1= " << acceptedCounts1 << endl;
		cout << "accepted Counts 2= " << acceptedCounts2 << endl;
 		cout << "efficiency1 for "<< fileName[i].c_str() <<" = "<< efficiency1[i] <<" \%"<< endl;
 		cout << "efficiency2 for "<< fileName[i].c_str() <<" = "<< efficiency2[i] <<" \%"<< endl;
	}

	cout << "--------------- SUMMARY ---------------"<< endl;
	for (Int_t i=0; i<nFile; i++)	{
		cout << fileName[i].c_str() << endl;
		cout << "efficiency 1 (threshold for SI & CsI both) = " << efficiency1[i] <<" \%" << endl;
		cout << "efficiency 2 (threshold for CsI only) = " << efficiency2[i] <<" \%" << endl;
		cout << " " <<endl;
	}

	return;
}

