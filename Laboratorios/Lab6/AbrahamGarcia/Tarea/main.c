#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM_HILOS 4
#define N 80000

 int *datos;
 int respuesta[3];
 int contador;
 int* lista;
pthread_mutex_t bloqueo;
int* reservarMemoria(){
    return (int*)malloc(sizeof(int) *N);
}

void llenarArreglo(int * datos){
    srand(getpid());
    register int i;
    for ( i = 0; i < N; i++)
    {
        datos[i]=rand()%2550000; //genero numero de 8 bits
    }
}

void imprimirArreglo(int* datos){
    printf("\n");
    register int i;
    for (i = 0; i < N; i++)
    {
        if(i%16==0)
            printf("\n");
        printf("%3d ",datos[i]);    
    }
    printf("\n");
    printf("\n");
}



void sort(int lista[], int limizq, int limder){

    int izq,der,pivot,pivoPosc, temp;

    //elegir un pivote en medio de la lista
    pivoPosc=(limder+limizq)/2; //posicion del pivote en la lista

    pivot=lista[pivoPosc]; //pivote
   
    //inicializamos valores
    izq=limizq;
    der=limder;

    //empezamos a recorrer lista
    do{

        while(lista[izq]<pivot && izq<limder){
            izq++;
            //si del lado izquiero del pivote encuentra un elemento mayor al pivote, entonces para.
        }
        while(lista[der]>pivot && der>limizq){
            der--;
            //ahora busco un elemento de la derecha que sea menor al pivote, puede ser tambien el mismo pivote el elemento que elegi
        }

            //ahora que ya tengo los dos elementos a cambiar, los cambio
        if(izq<=der){
            temp=lista[izq];
            lista[izq]=lista[der];
            lista[der]=temp;
            izq++;
            der--;
        }

    }while(izq<der);

    if(limizq<der)
        sort(lista,limizq,der);
    if(limder>izq)
        sort(lista,izq,limder);

}
void quicksort(int lista[],int limizq, int limder, int nuevalista[]){
    sort(lista,limizq,limder);
    
}


float mayorArreglo(int *datos){
    register int i;
    int mayor=datos[0];
    for (i = 1; i < N; i++)
    {
        if(datos[i]>mayor)
            mayor=datos[i];
    }
    return mayor;
}

float menorArreglo(int *datos){
    register int i;
    int menor=datos[0];
    for (i = 1; i < N; i++)
    {
        if(datos[i]<menor)
            menor=datos[i];
    }
    return menor;
}

float promedioArreglo(int *datos){
    float n;
    register int i;
    for ( i = 0; i < N; i++)
    {
        
        n+=datos[i];
        
    }
    n/=N;
    return n;
}



void * funHilo( void * arg){
    int nh= *(int *)arg;
    
    switch(nh){
        case 0:
            printf("Soy el hilo %d y yo busco el mayor\n",nh);
            pthread_mutex_unlock(&bloqueo);
            respuesta[nh] = mayorArreglo( datos );
            pthread_mutex_unlock(&bloqueo);
             //printf(" mayor %d\n",respuesta[nh] );
            pthread_exit((void *) &respuesta[nh]);
            break;
        case 1:
            printf("Soy el hilo %d  yo busco el menor\n",nh);
            pthread_mutex_unlock(&bloqueo);
            respuesta[nh] = menorArreglo( datos );
            pthread_mutex_unlock(&bloqueo);
             //printf(" menor %d\n",respuesta[nh] );
            pthread_exit((void *) &respuesta[nh]);
            break;
        case 2:
            printf("Soy el hilo %d y yo hare el promedio\n",nh);
             pthread_mutex_lock(&bloqueo);
            respuesta[nh] = promedioArreglo( datos );
             
            pthread_mutex_unlock(&bloqueo);
            //printf(" promedio %d\n",respuesta[nh] );

            pthread_exit((void *) &respuesta[nh]);
            break;
        case 3:
            printf("Soy el hilo %d y yo ordenare el arreglo\n",nh);
           
            //pthread_mutex_unlock(&bloqueo);
            quicksort(datos,0,N-1,lista);
            //pthread_mutex_unlock(&bloqueo);
            
            pthread_exit((void *) datos);
            break;
        

    }
}


int main()
{

    contador=0;
	int nhs[NUM_HILOS], *res;
	pthread_t tids[NUM_HILOS];
    int* result=(int*)malloc(sizeof(int)*N);
    pthread_mutex_init(&bloqueo,NULL);
	printf("Probando hilos ...\n");

        datos = reservarMemoria();
        llenarArreglo( datos );
        imprimirArreglo( datos);
        

    register int nh;
    for (nh = 0; nh < NUM_HILOS; nh++)
    {
        nhs[nh]=nh;
        pthread_create( &tids[nh], NULL, funHilo, (void *)&nhs[nh] );

    }

	for (nh = 0; nh < NUM_HILOS; nh++)
    {
        if(nh!=3){
            pthread_join(tids[nh], (void **)&res );
            printf("Hilo %d terminado resultado: %d\n",nh, *res);
        }
        else{
            pthread_join(tids[nh], (void **)&result );
            printf("%d\n",result[0] );
            printf("%d\n",result[N-1] );
            //imprimirArreglo(result);
        }
       
    }
    
    pthread_mutex_destroy(&bloqueo);
	return 0;
}


