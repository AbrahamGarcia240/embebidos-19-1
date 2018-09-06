#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_HILOS 4

int contador;


/*

int * reservarMemoria( );
void llenarArreglo( int *datos );
void imprimirArreglo( int *datos );
void * mayorArreglo( void *arg );
void * menorArreglo( void *arg );
*/
void * funHilo( void * arg){

    register int i=0;
    int nh= *(int *)arg;

    contador++;

    printf("Iniciando hilo %d con contador %d\n",nh, contador );
    while(--i){
    }
    printf("Terminando hilo %d con contador %d\n",nh, contador );
    pthread_exit(arg);
}


int main()
{
    contador=0;
	int nhs[NUM_HILOS], *res;
	pthread_t tids[NUM_HILOS];
	printf("Probando hilos ...\n");
/*
        datos = reservarMemoria();
        llenarArreglo( datos );
        imprimirArreglo( datos);
*/
    register int nh;
    for (nh = 0; nh < NUM_HILOS; nh++)
    {
        nhs[nh]=nh;
        pthread_create( &tids[nh], NULL, funHilo, (void *)&nhs[nh] );

    }

	for (nh = 0; nh < NUM_HILOS; nh++)
    {
        pthread_join(tids[nh], (void **)&res );
        printf("Hilo %d terminado\n", *res);
    }

	return 0;
}
