#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#define NUM_HILOS 4
#define N 256


int contador;

float *A;
float *B,*C;
float * reservarMemoria( );
void llenarArreglo( float *datos );
void imprimirArreglo( float *datos );

void genera_seno(float x[]){
    register int i=0;
    
 
        
        for (i = 1; i < N; i++)
        {

            //x[i]=sinf((2*M_PI*i*fn)/fs);
            x[i]=sinf((2*M_PI*i*10000)/45000);
            //printf("%d %f\n",i,x[i] );
        }
}

void genera_Hamming(float x[]){
    register int i=0;
    
 
        
        for (i = 1; i < N; i++)
        {

            //x[i]=sinf((2*M_PI*i*fn)/fs);
            x[i]=0.54-0.46*cosf((2*M_PI*i)/N);
            //printf("%d %f\n",i,x[i] );
        }
}


void guarda_datos(float x[], int n){
    FILE * archivo, *archivo2;
    register int i;
    if(n==1){
        archivo=fopen("seno.dat","w");
         archivo2=fopen("sin.txt","w");
    }
    else if(n==2){
        archivo=fopen("hamming.dat","w");
        archivo2=fopen("hamming.txt","w");
    }
    
    else{
        archivo=fopen("result.dat","w");
        archivo2=fopen("result.txt","w");
    }
    if(!archivo){
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);

    }
    fprintf(archivo, "#X #Y\n" );
    for (i = 0; i < N; i++)
    {
        fprintf(archivo2, "%f\n",x[i] );
        fprintf(archivo, "%f %f  \n",(float)i,x[i] );
    }
    fclose(archivo);
    fclose(archivo2);
}



void * funHilo( void * arg){
    register int i;
    int nh= *(int *)arg; //numero de nucleo
    

    for (i=nh; i<N; i+= NUM_HILOS)
    {
        C[i]=A[i]*B[i];
    }



    pthread_exit(arg);
}


int main()
{

    srand( getpid() );


    A = reservarMemoria();
    genera_seno( A );
    imprimirArreglo( A );
    guarda_datos(A,1);

    B = reservarMemoria();
    genera_Hamming( B );
    imprimirArreglo( B );
    guarda_datos(B,2);

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

    imprimirArreglo( C );   
    guarda_datos(C,3);
    free(A);
    free(B);
    free(C);

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