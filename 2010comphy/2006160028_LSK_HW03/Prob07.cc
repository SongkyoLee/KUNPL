#include <iostream>
#include <list>


using namespace std;

 int main()
{

 list<int> LIST;
 L.push_back(0);
 L.push_back(21);
 L.push_back(3);
 L.push_back(5);
 L.push_back(6);
 
 list<int>::iterator i;
 
 for (i=L.begin(); i !=L.end(); ++i) 
 cout<< *i << ""<< endl;

  return 0;
 
}
