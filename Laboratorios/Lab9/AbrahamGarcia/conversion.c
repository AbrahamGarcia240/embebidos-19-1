#include <stdio.h>
#include <stdlib.h>
#include "imagen.h"

int main(int argc, char const *argv[])
{
	bmpInfoHeader info;
	unsigned char* imagenRGB, *imagenGRay, *imagenFiltrada;
	
	imagenRGB = abrirBMP("calle1.bmp", &info);
	displayInfo( &info );

	//quitamos el color
	//la imagen que recibimos es imagenGray, con un tamaño en alto y hancho
	imagenGRay=RGBtoGray( imagenRGB,info.width, info.height );
	//procesamiento

	//brilloImagen(imagenGRay,info.width, info.height);
	imagenFiltrada = reservarMemoria(info.width, info.height);
	filtroImagen(imagenGRay,imagenFiltrada,info.width, info.height);

	//fin de procesamiento
	printf("s\n");
	GraytoRGB( imagenFiltrada	, imagenRGB, info.width, info.height );
	printf("l\n");
	guardarBMP( "calle1Bordes.bmp", &info, imagenRGB );
	free( imagenRGB );
	free( imagenGRay );

	return 0;
}