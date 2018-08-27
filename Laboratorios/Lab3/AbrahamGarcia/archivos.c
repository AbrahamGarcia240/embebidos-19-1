#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//M_PI es pi
void guarda_datos(float x[],int n){
	FILE * archivo;
	register int i;
	archivo=fopen("seno.dat","w");
	if(!archivo){
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);

	}
	fprintf(archivo, "#X #Y\n" );
	for (i = 0; i < n; i++)
	{
		fprintf(archivo, "%f %f  \n",(float)i,x[i] );
	}
	fclose(archivo);
}