#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "procesamiento.h"
#include "datos.h"
#define N 32

void procesoHijo(int * datos, int n, int pipedf[]){

	int respuesta;
	close(pipedf[0]); //cierro el descriptor de lectura, porque no estoy leyendo
	switch(n){
		case 0:
			printf("Soy el proceso %d mi pid es %d y yo busco el mayor\n",n,getpid());
			respuesta = mayorArreglo( datos );
			//printf(" respuesta %d\n",respuesta );
			write(pipedf[1],&respuesta,sizeof(float));
			close(pipedf[1]);
			
		break;

		case 1:
			printf("Soy el proceso %d mi pid es %d y yo busco el menor\n",n,getpid());
			respuesta = menorArreglo( datos );
			write(pipedf[1],&respuesta,sizeof(float));
			close(pipedf[1]);
			
		break;

		case 2:
			printf("Soy el proceso %d mi pid es %d y yo hare el promedio\n",n,getpid());
			respuesta = promedioArreglo( datos );
			write(pipedf[1],&respuesta,sizeof(float));
			close(pipedf[1]);
			
		break;

		case 3:
			printf("Soy el proceso %d mi pid es %d y yo ordenare el arreglo\n",n,getpid());
			
			int* lista=(int*)malloc(sizeof(int)*N);
			quicksort(datos,0,N-1,lista);
			write(pipedf[1],lista,sizeof(int)*N);
			
			close(pipedf[1]);
			
		break;}
		 //como ya no uso este descriptor tambien lo cierro
			exit( n );
	}
void procesoPadre(int pipedf[]){
	pid_t pid_hijo;
	int  numero, resultado;
	int* result=(int*)malloc(sizeof(int)*N);
	register int np;
	printf("Soy el proceso padre ejecutado con pid %d\n",getpid());
	close(pipedf[1]);
	for(np=0; np<4; np++){
		//hasta que el wait se ejectue, los hijos son zombies
		pid_hijo=wait(&numero);
		
		if(numero>>8==3){
			
			read(pipedf[0],result,sizeof(int)*N);
			printf("Termina el proceso %d y el resultado es:\n",pid_hijo );
			imprimirArreglo(result);
		}
	
		else{
			
			read(pipedf[0],&resultado,sizeof(float));
			printf("Termina el proceso %d y el resultado es %d\n",pid_hijo,resultado );
			
		}

		//hago un corrimiento a la derecha de 8 bits porque wait me regresa
		//el numero en los bits  de la  parte alta
		//supongamos que el pid=10
		// 0000 0000 0000 1010 ----> este es el 10 que yo espero
		// 0000 1010 0000 0000 ----> esto es lo que me da wait
		//printf("Proceso hijo %d terminado %d con dato recibido: %d\n",pid_hijo,numero>>8);
	}
	close(pipedf[0]);
	

}