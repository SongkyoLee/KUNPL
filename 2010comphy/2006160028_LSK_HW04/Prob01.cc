
void Prob01()
{
	TCanvas *c1 = new TCanvas("c1", "Histogram1", 200, 10, 800, 500);
	c1->Divide(2,1);
	
	Float_t data1[30] = {2,4,6,1,7,5,9,5,4,8,7,1,5,7,9,1,10,3,7,4,3,7,8,2,5,10,9,3,7,5};
	
	c1->cd(1);
	h1f = new TH1F ("h1f", "data1", 10, 0.5, 10.5);
	for (Int_t i=0; i<30; i++) h1f->Fill(data1[i]);
	h1f->Draw();
 
	Float_t data2[30] = {8,3,1,1,7,5,3,2,10,8,2,1,8,3,9,1,10,3,6,4,1,6,8,2,10,1,6,7,4,3};
 
	c1->cd(2);
	h2f = new TH1F ("h2f", "data2", 10, 0.5, 10.5);
	for (Int_t i=0; i<30; i++) h2f->Fill(data2[i]);
	h2f->Draw();
          
		  
	TCanvas *c2 = new TCanvas("c2", "Histograms2", 200, 10, 800, 500);

	h1f = new TH1F ("h1f", "title : data1 and data2", 10, 0.5, 10.5);
	h2f = new TH1F ("h2f", "title : data1 and data2", 10, 0.5, 10.5);
	for (Int_t i=0; i<30; i++) h1f->Fill(data1[i]);
	for (Int_t i=0; i<30; i++) h2f->Fill(data2[i]);
	h1f->SetLineColor(2);
	h2f->SetLineColor(4);
	h1f->Draw();
	h2f->Draw("same");
         
    
	TCanvas *c3 = new TCanvas("c3", "Histograms3", 200, 10, 800, 500);    
	c3->Divide(2,1);
		
	h1f = new TH1F ("h1f", "data1", 10, 0.5, 10.5);
	for (Int_t i=0; i<30; i++) h1f->Fill(data1[i]);
	
	h2f = new TH1F ("h2f", "data2", 10, 0.5, 10.5);
	for (Int_t i=0; i<30; i++) h2f->Fill(data2[i]);
	   
	c3->cd(1);
	h3f = new TH1F ("h3f", "addition", 10, 0.5, 10.5);
	h3f -> Add(h1f, h2f, 1, 1);
 	h3f->Draw();
	
	c3->cd(2);
	h4f = new TH1F ("h4f", "subtraction", 10, 0.5, 10.5);
        h4f -> Add(h1f, h2f, 1, -1);
	h4f->Draw();
	            	  
}
