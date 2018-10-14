#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//recibe la señal que la esta invocando
void ISRsw( int sig ){
	if( sig == SIGINT ){

		printf("Señal SIGINT detectada, No voy a terminar prro :v \n");
	}
	if( sig == SIGTERM ){

		printf("Señal SIGINT detectada, No voy a terminar prro :v \n");
	}
}


int main(int argc, char const *argv[])
{

	//el primer parametro es ctrl c, luego la funcion a ejecutar 
	if(signal( SIGINT, ISRsw )== SIG_ERR){
		perror("Error al crear el manejador");
		exit(EXIT_FAILURE);
	} 

	if(signal( SIGTERM, ISRsw )== SIG_ERR){
		perror("Error al crear el manejador");
		exit(EXIT_FAILURE);
	}

	printf("Señal ejecutada\n");
	while(1){
		pause();
	}

	return 0;
}