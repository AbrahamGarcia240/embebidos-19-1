#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define NUM_PROC 8

void procesohijo(int np){
	printf("Soy el proceso hijo %d ejecutado con pid %d\n",np,getpid());
	while(1);
	exit(np);

}

void procesoPadre(){
	pid_t pid_hijo;
	int  estado;
	register int np;
	printf("Soy el proceso padre ejecutado con pid %d\n",getpid());
	for(np=0; np<NUM_PROC; np++){
		//hasta que el wait se ejectue, los hijos son zombies
		pid_hijo=wait(&estado);
		//hago un corrimiento a la derecha de 8 bits porque wait me regresa
		//el numero en los bits  de la  parte alta
		//supongamos que el pid=10
		// 0000 0000 0000 1010 ----> este es el 10 que yo espero
		// 0000 1010 0000 0000 ----> esto es lo que me da wait
		printf("Proceso hijo %d terminado con pid %d\n",estado>>8,pid_hijo);
	}
	

}

void main(int argc, char const *argv[])
{

	pid_t pid;
	register int np;
	
	printf("probando procesos...\n");

	for(np=0; np<NUM_PROC; np++){
		pid=fork();
		if(pid ==-1){
			perror("No se creo el proceso...");
			exit(EXIT_FAILURE);
		}
		if(!pid){
			procesohijo(np);
			
		}

		
	}
	procesoPadre();
	

	

}
