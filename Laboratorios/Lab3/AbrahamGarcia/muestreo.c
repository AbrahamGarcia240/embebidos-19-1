/*
Una señal discreta es un conjunto de valores tomados de forma equidistante 
a partir de una señal continua a intervaos fijos de tamaños Ts

Ts= Es el periodo de muestreo
*/

#include <stdio.h>
#include "archivos.h"
#include "procesamiento.h"
#include <math.h>
#include <stdlib.h>
int main(int argc, char const *argv[])
{
	if(argc>0){
		
		register int n=strtol(argv[1],NULL,10);
		float fn=strtol(argv[2],NULL,10); 
		float x[n+1]; //el numero de muestras que necesito
		genera_seno(x,n,fn);
		guarda_datos(x,n);

		return 0;

	}
}	