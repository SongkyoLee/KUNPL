
# include <iostream>

 using namespace std;
 
 class Mem
  {
   float a, b, c, d, e, f, g, h, i ;
   public:
     Mem ();
     Mem (float, float, float, float, float, float, float, float, float);
     float first_mem () {return ((a+b+c+d+e+f+g+h+i)/9);};
     float second_mem () {return
    
(((a-first_mem ())*(a-first_mem ())+(b-first_mem ())*(b-first_mem ())+(c-first_mem ())*(c-first_mem ())+(d-first_mem
())*(d-first_mem ())+(e-first_mem ())*(e-first_mem ())+(f-first_mem ())*(f-first_mem ())+(g-first_mem ())*(g-first_mem
())+(h-first_mem ())*(h-first_mem ())+(i-first_mem ())*(i-first_mem()))/9);}
 
    
  } ;
  
 Mem::Mem ()
  { 
   a = 0;
   b = 0;  
   c = 0;
   d = 0;
   e = 0;
   f = 0;
   g = 0;
   h = 0;
   i = 0;
  }
  
  Mem::Mem (float n1, float n2, float n3, float n4, float n5, float n6, float n7, float n8, float n9)
  { 
   a = n1;
   b = n2;  
   c = n3;
   d = n4;
   e = n5;
   f = n6;
   g = n7;
   h = n8;
   i = n9;
  }
  
   int main ()
  { Mem foo;
    Mem bar(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  cout<< "foo ave = " << foo.first_mem ()<<endl;
  cout<< "foo var = " << foo.second_mem ()<<endl;
  cout<< "bar ave = " << bar.first_mem ()<<endl;
  cout<< "bar var = " << bar.second_mem ()<<endl;
  return 0;
  }
  
  
