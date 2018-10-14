#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#define NUM_PROCS 4
#define N 32




void procesoHijo(float* A, float *B , int pipedf[], int n){
    //PRODUCTO PUNTO
    close(pipedf[0]);
    register int i=0;
    int tambloque=N/NUM_PROCS;
    float C =0;
    for (i=tambloque*n; i<tambloque*(n+1); i++)
    {
        
        C+=A[i]*B[i];
        
    }
    write(pipedf[1],&C,sizeof(float));
    close(pipedf[1]);
    exit(n);
        
}

void procesoPadre(int pipefd[NUM_PROCS][2]){
    pid_t pid_hijo[NUM_PROCS];
    float total=0,aux=0;
    int numero;
    register int i;
    for (i = 0; i < NUM_PROCS; i++)
    {
        pid_hijo[i]=wait(&numero);
        numero=numero>>8;
        close(pipefd[numero][1]);
        register int i;
        read(pipefd[numero][0],&aux,sizeof(float)*N);
        total+=aux;  
        //printf("%f\n",aux );
         close(pipefd[numero][0]);
    }
     printf("%f\n",total );
}