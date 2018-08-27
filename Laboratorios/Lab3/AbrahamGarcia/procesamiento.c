
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void genera_seno(float x[],int n, float fn){
	register int i=0;
	
	float fs=fn*2;
	fs+=(fn*0.10);
		
		for (i = 1; i < n+1; i++)
		{

			x[i]=sinf((2*M_PI*i*fn)/fs);
			//printf("%d %f\n",i,x[i] );
		}
}