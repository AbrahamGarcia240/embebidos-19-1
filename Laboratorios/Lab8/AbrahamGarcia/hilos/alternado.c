#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include "datos.h"
#define NUM_HILOS 4
#define N 32


int contador;
int promedio;
float *A, *B, *C;
pthread_mutex_t bloqueo;



void * funHilo( void * arg){
    register int i;
    int nh= *(int *)arg; //numero de nucleo
    int sumap;

    for (i=nh; i<N; i+= NUM_HILOS)
    {
        C[i]=A[i]*B[i];
        sumap+=C[i];
    }
    pthread_mutex_lock(&bloqueo);
    promedio+=sumap;
    pthread_mutex_unlock(&bloqueo);

    pthread_exit(arg);
}


int main()
{
    int nhs[NUM_HILOS], *res;
    register int nh;
    pthread_t tids[NUM_HILOS];
    contador=0;
    //srand( getpid() );


    A = reservarMemoria();
    llenarArreglo( A );
    imprimirArreglo( A );

    B = reservarMemoria();
    llenarArreglo( B );
    imprimirArreglo( B );
    
    C = reservarMemoria();
    
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
   
    printf("%d\n",promedio);
    pthread_mutex_destroy(&bloqueo);
    free(A);
    
	return 0;
}


