#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int i,j;
	float rand0to1[1000];
	float rand0to10[1000];
	int foo[10]={0};

	srand(time(NULL));

	for(i=0;i<1000;i++)
	{
		rand0to1[i] = (float)rand()/RAND_MAX;
	}

	for(i=0;i<1000;i++)
	{
		rand0to10[i] = 10*rand0to1[i];
	}

	for(i=0;i<1000;i++)
	{
		for(j=0;j<10;j++)
		{
			if( (rand0to10[i] <= j+1 ) && ( rand0to10[i] > j ) )
			{
				foo[j] = foo[j] + 1;
			}
		}
		if(rand0to10[i]==0)
		{
			foo[0] = foo[0] + 1;
		}
	}

	for(i=0;i<10;i++)
	{
		printf("foo[%d] = %d\n",i,foo[i]);
	}

	return 0;
}
