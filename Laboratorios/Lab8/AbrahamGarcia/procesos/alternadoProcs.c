#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>
#include "datos.h"
#include "procesos.h"
#define NUM_PROCS 4
#define N 32


int main()
{
    float *A,*B;
    pid_t pid[NUM_PROCS];
    int pipefd[NUM_PROCS][2], pipe_status[NUM_PROCS];
    register int i;


    A = reservarMemoria();
    llenarArreglo( A );
    printf("\n");
    imprimirArreglo( A );

    B = reservarMemoria();
    llenarArreglo( B );
    printf("\n");
    imprimirArreglo( B );

   
    //CREO LOS PIPES A USAR
    for ( i = 0; i < NUM_PROCS; i++)
    {
        
        pipe_status[i]=pipe(pipefd[i]);
        if(pipe_status[i]==-1){
            perror("Error al crear el proceso ");
            exit(EXIT_FAILURE);
        }
    }


    //GENERO LOS PROCESOS HIJO
    for (i = 0; i < NUM_PROCS; i++)
    {
        
        pid[i]=fork();
        if(!pid[i]){
            procesoHijo(A,B,pipefd[i],i);
        }

    }

    //aqui esta el proceso padre
    /***********************************************/
    procesoPadre(pipefd);
    /************************************************/
   
   
    free(A);
    free(B);
    

    return 0;
}


