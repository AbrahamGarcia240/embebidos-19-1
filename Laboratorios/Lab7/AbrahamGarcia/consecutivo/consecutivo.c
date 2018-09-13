#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_HILOS 4
#define N 8000000


int contador;


int *A,*B,*C;
int * reservarMemoria( );
void llenarArreglo( int *datos );
void imprimirArreglo( int *datos );


void * funHilo( void * arg){

    int nh= *(int *)arg; //numero de nucleo
    int tamBloque=N/NUM_HILOS;
    register int inicio=nh*tamBloque;
    int fin=inicio+tamBloque;

    for (inicio = inicio; inicio < fin; inicio++)
    {
        C[inicio]=A[inicio]*B[inicio];
    }



    pthread_exit(arg);
}


int main()
{

    srand( getpid() );


    A = reservarMemoria();
    llenarArreglo( A );
    //imprimirArreglo( A );

    B = reservarMemoria();
    llenarArreglo( B );
    //imprimirArreglo( B );

    C = reservarMemoria();
   
   

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

    //imprimirArreglo( C );   

    free(A);
    free(B);
    free(C);

	return 0;
}


void llenarArreglo( int *datos )
{
        register int i;

        
        for( i = 0; i < N; i++ )
        {
                datos[i] = rand() % 255;
        }
}

int * reservarMemoria( )
{
        int *mem;

        mem = (int *)malloc( sizeof(int) * N  );
        if( !mem )
        {
                perror("Error al asignar memoria...\n");
                exit(EXIT_FAILURE);
        }
        return mem;
}

void imprimirArreglo( int *datos )
{
        register int i;

        for( i = 0; i < N; i++ )
        {
                if( !(i%16) )
                        printf("\n");
                printf("%5d ", datos[i]);
        }
        printf("\n");
}