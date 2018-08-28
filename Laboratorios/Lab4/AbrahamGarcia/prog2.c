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
	register int i;
	for ( i = 0; i < N; i++)
	{
		datos[i]=rand()%255;
	}
}
void main(int argc, char const *argv[])
{
	int *datos;
	datos=reservarMemoria();
	llenarArreglo(datos);

}
