#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 32

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
	register int i;
	for ( i = 0; i < N; i++)
	{
		nuevalista[i]=lista[i];
	}
}