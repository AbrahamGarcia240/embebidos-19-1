#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "imagen.h"
#define DIMASK 3

unsigned char * RGBtoGray( unsigned char *imagenRGB,
	uint32_t width, uint32_t height );
void GraytoRGB( unsigned char *imagenGray, unsigned char *imagenRGB,
	uint32_t width, uint32_t height );
void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height );
unsigned char * reservarMemoria( uint32_t width, uint32_t height );
void filtroImagen( unsigned char *imagenGray, unsigned char *imagenFiltro,
		 uint32_t width, uint32_t height );

int main()
{
	bmpInfoHeader info;
	unsigned char *imagenRGB, *imagenGray, *imagenFiltro;

	imagenRGB = abrirBMP("calle1.bmp", &info);
	displayInfo( &info );

	printf("Abriendo imagen RGB\n");
	imagenGray = RGBtoGray( imagenRGB, info.width, info.height );

	//procesamiento
	//brilloImagen( imagenGray, info.width, info.height );
	imagenFiltro = reservarMemoria( info.width, info.height );
	filtroImagen( imagenGray, imagenFiltro, info.width, info.height );

	GraytoRGB( imagenFiltro,  imagenRGB, info.width, info.height );
	guardarBMP( "calle2.bmp", &info, imagenRGB );

	free(imagenRGB);
	free(imagenGray);
	return 0;
}

void filtroImagen( unsigned char *imagenGray, unsigned char *imagenFiltro,
		 uint32_t width, uint32_t height )
{
	register int x, y, xm, ym;
	int conv2, conv1, indice, indicem;
	char GradC[] =
		{-1, -2, -1,
		 0, 0, 0,
		 1, 2, 1};
	char GradF[] =
		{1, 0, -1,
		 2, 0, -2,
		 1, 0, -1};
    /*unsigned char mascara[] =
		{1, 0, -1,
		 2, 0, -2,
		 1, 0, -1};*/
	for( y = 0; y <= height-DIMASK; y++ )
		for( x = 0; x <= width-DIMASK; x++ )
		{
			conv1 = 0;
			indicem = 0;
			for( ym = 0; ym < DIMASK; ym++  )
			{
				for( xm = 0; xm < DIMASK; xm++ )
				{
					indice = ((y+ym)*width + (x+xm));
					conv1 += imagenGray[indice]*GradF[indicem];
					conv2 += imagenGray[indice]*GradC[indicem++];

				}
			}
			conv1 = conv1 / 4;
			conv2 = conv2 / 4;
			conv1 = sqrt(pow(conv1,2)-pow(conv2,2));
			indice = ((y+1)*width + (x+1));
			imagenFiltro[indice] = conv1;
		}
}

unsigned char * reservarMemoria( uint32_t width, uint32_t height )
{
	unsigned char *imagen;

	imagen = (unsigned char *)malloc( width*height*sizeof(unsigned char) );
	if( imagen == NULL )
	{
		perror("Error al signar memoria");
		exit(EXIT_FAILURE);
	}

	return imagen;
}

void brilloImagen( unsigned char *imagenGray, uint32_t width, uint32_t height )
{
	register int p;
	unsigned short int pixel;

	for( p = 0; p < width*height; p++ )
	{
		pixel = imagenGray[p] + 80;
		imagenGray[p] = (pixel > 255)? 255 : (unsigned char)pixel;
	}
}

void GraytoRGB( unsigned char *imagenGray, unsigned char *imagenRGB,
	uint32_t width, uint32_t height )
{
	register int x, y;
	int indiceRGB, indiceGray;

	for( y = 0; y < height; y++ )
		for( x = 0; x < width; x++ )
	{
		indiceGray = (y*width + x);
		indiceRGB = indiceGray * 3;

		imagenRGB[indiceRGB+0] = imagenGray[indiceGray];
		imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
		imagenRGB[indiceRGB+2] = imagenGray[indiceGray];
	}
}
unsigned char * RGBtoGray( unsigned char *imagenRGB,
	uint32_t width, uint32_t height )
{
	register int x, y;
	int indiceRGB, indiceGray;
	unsigned char grayLevel;
	unsigned char *imagenGray;

	imagenGray = reservarMemoria( width, height );

	for( y = 0; y < height; y++ )
		for( x = 0; x < width; x++ )
	{
		indiceGray = (y*width + x);
		indiceRGB = ((indiceGray << 1) + indiceGray); //indiceGray * 3
		grayLevel = (30*imagenRGB[indiceRGB] +
			    59*imagenRGB[indiceRGB+1] + 11*imagenRGB[indiceRGB+2])/100;
		imagenGray[indiceGray] = grayLevel;
	}
	return imagenGray;
}


