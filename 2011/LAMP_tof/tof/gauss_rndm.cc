
void gauss_rndm()
{
 gROOT->Reset();

 TCanvas* c1 = new TCanvas("c1", "", 200, 10, 600, 400);
// hist = new TH1F("hist", "gaussian random number", 30, -0.5, 0.5);
 hist = new TH1F("hist", "gaussian random number",60,-1,1);
 hist -> Draw();

 gRandom->SetSeed(); 

 Float_t error;

 for(Int_t i=0; i<100000; i++)
 {
//  data = gRandom->Rndm(dummy); //Rndm from 0 to 1 
    error = gRandom ->Gaus(0, (1.5/2.35)); //(mean, sigma)
//    std::cout<< error <<std::endl;
    hist->Fill(error);
  }
}

