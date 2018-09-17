#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#define NUM_PROCS 4
#define N 256


int contador;


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



void procesoHijo(float* A, float *B , int pipedf[], int n){
    //printf("Estoy en el proceso hijo\n");
    close(pipedf[0]);
    register int i=0;
    int tambloque=N/NUM_PROCS;
    float * C = (float *)malloc( sizeof(float) * N );
    int p=0;
    for (i=tambloque*n; i<tambloque*(n+1); i++)
    {
        
        C[i]=A[i]*B[i];
        
    }
    //imprimirArreglo(C);
    write(pipedf[1],C,sizeof(float)*N);
    close(pipedf[1]);
    exit(n);
        
}

/*void procesopadre(int pipedf[2]){
   
    float * C = reservarMemoria();
    
   
    register int nh;
   
        int numero;
        pid_t pid_hijo;
        close(pipedf[1]);
        int tambloque=N/NUM_PROCS;
        pid_hijo=wait(&numero);
        float * Caux= (float *)malloc( sizeof(int) * N );
        numero=numero>>8;
        register int i;
        read(pipedf[0],Caux,sizeof(float)*tambloque);
        // imprimirArreglo( Caux );   
        int p=0;

        for (i=tambloque*numero; i<tambloque*(numero+1); i++)
        {
            //printf("%d\n",i );
            C[i]+=Caux[i];

            p++;
        }
        
         close(pipedf[0]);
       
    
    

    
   // imprimirArreglo( C );   
    //guarda_datos(C,3);
}
*/

int main()
{
    float *A;
    float *B,*C;

    pid_t pid[NUM_PROCS];
    int pipefd[NUM_PROCS][2], pipe_status[NUM_PROCS];


    A = reservarMemoria();
    genera_seno( A );
    //llenarArreglo( A );
    imprimirArreglo( A );
    guarda_datos(A,1);

    B = reservarMemoria();
    genera_Hamming( B );
    //llenarArreglo( B );
    imprimirArreglo( B );
    guarda_datos(B,2);

    C = reservarMemoria();
   
   

    contador=0;
    register int i;
	for ( i = 0; i < NUM_PROCS; i++)
    {
        
        pipe_status[i]=pipe(pipefd[i]);
        if(pipe_status[i]==-1){
            perror("Error al crear el proceso ");
            exit(EXIT_FAILURE);
        }
    }


    register int nh;
    for (i = 0; i < NUM_PROCS; i++)
    {
        
        pid[i]=fork();
        if(!pid[i]){
            procesoHijo(A,B,pipefd[i], i);
        }

    }

    /***********************************************/
    pid_t pid_hijo[NUM_PROCS];
    for (i = 0; i < NUM_PROCS; i++)
    {
         
    
        int numero;
        
        
        int tambloque=N/NUM_PROCS;
        pid_hijo[i]=wait(&numero);
        float * Caux= (float *)malloc( sizeof(int) * N );
        numero=numero>>8;
        close(pipefd[numero][1]);
        register int i;
        read(pipefd[numero][0],Caux,sizeof(float)*N);
         //imprimirArreglo( Caux );   
        int p=0;
        for (i=tambloque*numero; i<tambloque*(numero+1); i++)
        {
            //printf("%d\n",i );
            C[i]=Caux[i];

            p++;
        }
        
         close(pipefd[numero][0]);
    }
    /************************************************/
    imprimirArreglo(C);
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