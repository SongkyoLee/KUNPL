# include <stdio.h>

 int main(void)
 {
  /*
 int foo[5]; : There are 5 element. The first element is 0, and the last one is 4.
 for(i=1,i<=5,i=i+1) : The array should start from 0 (not from 1)
 foo[i]=0;*/
 

int i;
int foo[5];
for(i=0; i<=4; i=i+1) 
 {
 foo[i] = 0;
 printf("%d\n", foo[i]);
 }
}

