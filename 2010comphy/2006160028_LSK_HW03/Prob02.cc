// Explain what 
// x main = gRandom->Gaus(-1, 1.5) ; does.
//
// In this toturial, there are three histograms ; main, s1, s2.
// main is gray-coloured (colour #16), and xmain fills this histgram. 
// 'TRandom' is a simple 'basic Random number generator class',
// and we can write this object as a Root file,
// as part of another object or with its own key 
// (e.g. gRandom->Write("Random");
//
// 'Gaus' allows us to generate a random number
// which forms the standard Normal Gaussian Distribution.
// Gaus( mean, sigma)
// We can give mean value and standard deviation of the distrubution 
// by putting mean value on the 1st term, 
// and standard deviation on the 2nd term of parenthesis.
