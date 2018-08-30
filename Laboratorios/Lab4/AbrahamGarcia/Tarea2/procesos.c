#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 32

void procesoHijo(int * datos, int n){
	pid_t pid;
	int respuesta;
	switch(n){
		case 0:
			printf("Soy el proceso %d mi pid es %d y yo busco el mayor\n",n,getpid());
			respuesta = mayorArreglo( datos );
			exit( respuesta );
		break;

		case 1:
			printf("Soy el proceso %d mi pid es %d y yo busco el menor\n",n,getpid());
			respuesta = menorArreglo( datos );
			exit ( respuesta );
		break;

		case 2:
			printf("Soy el proceso %d mi pid es %d y yo hare el promedio\n",n,getpid());
			respuesta = promedioArreglo( datos );
			exit ( respuesta );
		break;

		case 3:
			printf("Soy el proceso %d mi pid es %d y yo ordenare el arreglo\n",n,getpid());
			quicksort(datos,0,N-1);
			imprimirArreglo(datos);
			exit( pid );
		break;}
	}
void procesoPadre(){
	pid_t pid_hijo;
	int  numero;
	register int np;
	printf("Soy el proceso padre ejecutado con pid %d\n",getpid());
	for(np=0; np<4; np++){
		//hasta que el wait se ejectue, los hijos son zombies
		pid_hijo=wait(&numero);
		//hago un corrimiento a la derecha de 8 bits porque wait me regresa
		//el numero en los bits  de la  parte alta
		//supongamos que el pid=10
		// 0000 0000 0000 1010 ----> este es el 10 que yo espero
		// 0000 1010 0000 0000 ----> esto es lo que me da wait
		printf("Proceso hijo %d terminado con dato recibido: %d\n",pid_hijo,numero>>8);
	}
	

}