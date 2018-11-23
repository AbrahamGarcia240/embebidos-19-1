#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"
#include "nodito.h"
#include <pthread.h>
#define NUM_HILOS 4
#define DIMASK 3



int main(int argc, char const *argv[])
{
	//respuesta del hilo
	int *res;
	//arreglo con el id de cada hilo
	int nhs[NUM_HILOS];
	//arreglo con los hilos
	pthread_t tids[NUM_HILOS];



	bmpInfoHeader info;
	unsigned char* imagenRGB, *imagenGRay, *imagenFiltrada, *imagenFiltrada2;
	
	imagenRGB = abrirBMP("calle1.bmp", &info);
	displayInfo( &info );

	//quitamos el color
	//la imagen que recibimos es imagenGray, con un tamaño en alto y hancho
	imagenGRay=RGBtoGray( imagenRGB,info.width, info.height );
	//procesamiento

	//brilloImagen(imagenGRay,info.width, info.height);
	imagenFiltrada = reservarMemoria(info.width, info.height);
	
	/////////////////////////////////////////////////////
	register int nh;
	int inc=(info.height-DIMASK)/4;
	inc++;
	struct nodito nod[NUM_HILOS];
	 for (nh = 0; nh < NUM_HILOS; nh++)
    {
    
		nod[nh].imgGray=imagenGRay;
		nod[nh].imgFilt=imagenFiltrada;
		nod[nh].w=info.width;
		nod[nh].h=info.height;
		nod[nh].inicio=nh*inc;
		nod[nh].final=((nh*inc)+inc)-1;


        nhs[nh]=nh;
        nod[nh].nucleo=nh;
        pthread_create( &tids[nh], NULL, filtroImagen, (void *)&nod[nh] );

    }

    for (nh = 0; nh < NUM_HILOS; nh++)
    {
        pthread_join(tids[nh], (void **)&res );
        //printf("Hilo %d terminado\n", *res);
    }

    GraytoRGB( imagenFiltrada	, imagenRGB, info.width, info.height );
	guardarBMP( "calle1Bordes.bmp", &info, imagenRGB );
    imagenFiltrada2 = reservarMemoria(info.width, info.height);

    for (nh = 0; nh < NUM_HILOS; nh++)
    {
    
		nod[nh].imgGray=imagenFiltrada;
		nod[nh].imgFilt=imagenFiltrada2;
		nod[nh].w=info.width;
		nod[nh].h=info.height;
		nod[nh].inicio=nh*inc;
		nod[nh].final=((nh*inc)+inc)-1;


        nhs[nh]=nh;
        nod[nh].nucleo=nh;
        pthread_create( &tids[nh], NULL, Gauss, (void *)&nod[nh] );

    }

    for (nh = 0; nh < NUM_HILOS; nh++)
    {
        pthread_join(tids[nh], (void **)&res );
        //printf("Hilo %d terminado\n", *res);
    }

    //filtroImagen(imagenGRay,imagenFiltrada,info.width, info.height);

    ///////////////////////////////////////////////////
	
	//fin de procesamiento
	GraytoRGB( imagenFiltrada2	, imagenRGB, info.width, info.height );
	guardarBMP( "calle1Bordes2.bmp", &info, imagenRGB );
	free( imagenRGB );
	free( imagenGRay );
	free( imagenFiltrada );
	free( imagenFiltrada2 );
	
	return 0;
}