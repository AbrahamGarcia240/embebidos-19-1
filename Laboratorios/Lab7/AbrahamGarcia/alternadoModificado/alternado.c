#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#define NUM_HILOS 4
#define N 256


int contador;
int promedio;
float *A;
pthread_mutex_t bloqueo;
float * reservarMemoria( );
void llenarArreglo( float *datos );
void imprimirArreglo( float *datos );






void * funHilo( void * arg){
    register int i;
    int nh= *(int *)arg; //numero de nucleo
    int sumap;

    for (i=nh; i<N; i+= NUM_HILOS)
    {
        sumap+=A[i];
    }
    pthread_mutex_lock(&bloqueo);
    promedio+=sumap;
    pthread_mutex_unlock(&bloqueo);

    pthread_exit(arg);
}


int main()
{

    srand( getpid() );


    A = reservarMemoria();
    llenarArreglo( A );
    imprimirArreglo( A );
    
   
   

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
   
    printf("%d\n",promedio/N);
    pthread_mutex_destroy(&bloqueo);
    free(A);
    
	return 0;
}


void llenarArreglo( float *datos )
{
        register int i;

        
        for( i = 0; i < N; i++ )
        {
                datos[i] = rand() % 255;
        }
}

float * reservarMemoria( )
{
        float *mem;

        mem = (float *)malloc( sizeof(int) * N  );
        if( !mem )
        {
                perror("Error al asignar memoria...\n");
                exit(EXIT_FAILURE);
        }
        return mem;
}

void imprimirArreglo( float *datos )
{
        register int i;

        for( i = 0; i < N; i++ )
        {
                if( !(i%16) )
                        printf("\n");
                printf("%5f ", datos[i]);
        }
        printf("\n");
}