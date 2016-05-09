#include <TTree.h>
#include <TFile.h>
#include <TMath.h>

void TWCdata()
{
	Double_t Tl;
	Double_t Tr;
	Double_t Al;
	Double_t Ar;

	const Char_t* treename[9] = {"10cm", "20cm", "30cm", "40cm", "50cm", "60cm",
								"70cm", "80cm", "90cm"};

	const Double_t NOD = 4000;
/*
	//expo
	const Double_t al = -0.00109299;
	const Double_t bl = 2.78141;
	const Double_t ar = -0.000865513;
	const Double_t br = 2.69015;
*/
	//pol1
	const Double_t al = -0.014366;
	const Double_t ar = -0.010128;
	const Double_t bl = 15.911062;
	const Double_t br = 14.549197;

	TFile* fin = new TFile("data_to_tree_t4.root");
	TFile* fout = new TFile("TWCdata.root", "RECREATE");

	TTree* data[9];
	TTree* tree[9];
	for(Int_t i = 0; i < 9; i++)
	{
		data[i] = (TTree*) fin->Get(treename[i]);
		data[i]->SetBranchAddress("Tl", &Tl);
		data[i]->SetBranchAddress("Tr", &Tr);
		data[i]->SetBranchAddress("Al", &Al);
		data[i]->SetBranchAddress("Ar", &Ar);

 		tree[i]= new TTree(treename[i], "TWC t");
		tree[i]->Branch("Tl", &Tl, "Tl/D");
		tree[i]->Branch("Tr", &Tr, "Tr/D");
		tree[i]->Branch("Al", &Al, "Al/D");
		tree[i]->Branch("Ar", &Ar, "Ar/D");
	}

	for(Int_t i = 0; i < 9; i++)
	{
		for(Int_t j = 0; j < NOD; j++)
		{
			data[i]->GetEntry(j);
/*	
			Tl = Tl-TMath::Exp(al*Al)-bl;
			Tr = Tr-TMath::Exp(ar*Ar)-br;
*/
			Tl = Tl-al*Al-bl;
			Tr = Tr-ar*Ar-br;

			tree[i]->Fill();
		}
	}
	fout->Write();
}
