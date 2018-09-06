#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 32
int* reservarMemoria(){
	return (int* )malloc(sizeof(int) *N);
}

void llenarArreglo(int * datos){
	srand(getpid());
	register int i;
	for ( i = 0; i < N; i++)
	{
		datos[i]=rand()%255; //genero numero de 8 bits
	}
}

void imprimirArreglo(int* datos){
	printf("\n");
	register int i;
	for (i = 0; i < N; i++)
	{
		if(i%16==0)
			printf("\n");
		printf("%3d ",datos[i]);	
	}
	printf("\n");
	printf("\n");
}
