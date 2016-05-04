#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>
#include <fstream>

iqmd4root(void)
 {
  Int_t event = 0;
  Double_t NumTrack;
  Double_t PID;
  Double_t Mass;
  Double_t px;
  Double_t py;
  Double_t pz;
  Int_t temp;

  Char_t* iqmdfile = "iqmd4.dat";

  Char_t* treename = "iqmd";

  TFile *f = new TFile("iqmd4root.root", "RECREATE");
    
  TTree *tree = new TTree("iqmd","");

  tree -> Branch("event", &event, "event/I");
  tree -> Branch("PID", &PID, "PID/D");
  tree -> Branch("Mass", &Mass, "Mass/D");
  tree -> Branch("px", &px, "px/D");
  tree -> Branch("py", &py, "py/D");
  tree -> Branch("pz", &pz, "pz/D");

  stringstream f_name;

  ifstream fdata;
  fdata.open(iqmdfile);

     if (fdata.is_open())
     {
       fdata >> NumTrack >> PID >> Mass >> px >> py >> pz;
      while(fdata)
      {

        temp = NumTrack;

      for(Int_t i = 0; i < temp; i++)
       {
        tree ->Fill();
       fdata >> NumTrack >> PID >> Mass >> px >> py >> pz;

       }
       event++;
      }
     }
     else
     {
      cout << "Error Opening file" << endl;
      break;
     }

     fdata.close();

     tree -> Write();
     delete tree;

     f -> Close();
     return 0;
 }

