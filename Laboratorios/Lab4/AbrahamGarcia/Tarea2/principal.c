#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 32
#include "procesos.h"
#include "procesamiento.h"
#include "datos.h"



void main(int argc, char const *argv[])
{
	pid_t pid,pid_hijo;
	int *datos,mayor, menor;
	datos=reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);

	register int a=0;
	for(a=0; a<4; a++){
		pid=fork();
		if(!pid){
			procesoHijo(datos,a);
		}
	}
	
	

	procesoPadre();
	
	
	free(datos);

}

