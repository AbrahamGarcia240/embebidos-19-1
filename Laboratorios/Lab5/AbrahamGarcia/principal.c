#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 32
#include "procesos.h"
#include "procesamiento.h"
#include "datos.h"



int main(int argc, char const *argv[])
{
	pid_t pid;
	int *datos;
	int pipefd[2], pipe_status;

	datos=reservarMemoria();
	llenarArreglo(datos);
	imprimirArreglo(datos);

	pipe_status=pipe(pipefd);
	if(pipe_status==-1)
	{
		perror("Error al crear laa tiuberia...");
		exit(EXIT_FAILURE);
	}

	register int a=0;
	for(a=0; a<4; a++){
		pid=fork();
		if(!pid){
			procesoHijo(datos,a,pipefd);
		}
	}
	
	

	procesoPadre(pipefd);
	
	
	free(datos);
	return (0);
}

