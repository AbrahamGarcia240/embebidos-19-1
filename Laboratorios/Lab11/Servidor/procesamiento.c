#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"
#include "funcionesprocesamiento.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "funHilo.h"
#include "defs.h"


// Miercoles 25/04/2018
//filtro gauss y usar 4 hilos, dividir la imagen en 4 hilos en forma horizontal.

/*Proyecto Martes 08/05
	-un servidor en la Raspberry (agregar señales) y no procesos zombies
	- cada cliente enviar una imagen 
	- servidor recibir imagen
	- el servidor calcula el operador de Sobel( deteccion de bordes basico) con hilos
	- regresa el resultado al cliente
	- cliente lo guarda como archivo de imagen
*/

extern unsigned char *imagenRGB, *imagenGray, *imagenAux;
extern bmpInfoHeader info;
extern pthread_mutex_t bloqueo;
extern char fname[100];

void procesarImagen( void )
{
	
	printf("La imagen sera procesada\n");
	register int nh;
	int nhs[NUM_HILOS];
	int *hilo;
	pthread_t tids[NUM_HILOS];

	imagenRGB = abrirBMP( fname, &info );
	displayInfo( &info );

	imagenAux=reservarMemoria(info.width,info.height);
	imagenGray = reservarMemoria(info.width,info.height);
	

	pthread_mutex_init(&bloqueo,NULL);

	for(nh = 0; nh < NUM_HILOS; nh ++ ){
		nhs[nh] = nh;
		pthread_create(&tids[nh],NULL,funHilo,(void *) &nhs[nh]);
	}

	for(nh = 0; nh < NUM_HILOS; nh ++){

		pthread_join(tids[nh], ( void ** ) &hilo);
		printf("Hilo %d terminado\n",*hilo );
	}

	pthread_mutex_destroy(&bloqueo);

	strcpy(fname,"imagenFiltro.bmp");

	guardarBMP( "imagenFiltro.bmp", &info, imagenRGB );

	//free(imagenAux);
	//free( imagenRGB );
	//free( imagenGray );


}
