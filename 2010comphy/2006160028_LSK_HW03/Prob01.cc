
void Prob01()
{

    Float_t data[29] = {1,5,9,3,2,4,5,1,6,9,4,2,2,3,4,8,9,4,5,6,3,2,6,5,4,3,4,5,2};


    h1f = new TH1F ("h1f", "title : HW03_01", 5, 0, 10);
    for (Int_t i=0; i<29; i++) h1f->Fill(data[i]);
    h1f->Draw();
    
}
    
   
//
// Relationship b/w RMS and variance :
//
// "Mean" (4.345) and "RMS" (2.248) are informed 
// on the upper right side of the histogram.
// RMS(rootmeansquare) is Sqrt[<(x-<x>)^2>],
// where x stands for data and <> stands for meanvalue.
// (Usually, RMS is calculated for data (x), such as Sqrt[<(x)^2>].
// Here, however, it is for deviation (x-<x>).)
// We define variance as <(x-<x>)^2>,
// Therefore, this "RMS" squared equals variance.
//
// Variance = "RMS"^2 = (2.248)^2 = 5.054
//
