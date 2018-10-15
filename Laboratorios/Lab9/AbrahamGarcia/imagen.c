/* Referencia:
   https://poesiabinaria.net/2011/06/leyendo-archivos-de-imagen-en-formato-bmp-en-c/
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "imagen.h"
#include "nodito.h"

#define DIMASK 3



unsigned char* reservarMemoria( uint32_t width, uint32_t height){
  unsigned char * imagen = (unsigned char *)malloc( width*height*sizeof(unsigned char) ); 
   if( imagen == NULL ){
    perror("Error al asignar memoria");
    exit(EXIT_FAILURE);
  }
  return imagen;
}

//void filtroImagen( unsigned char *imagenGray, unsigned char *imagenFiltro,
//     uint32_t width, uint32_t height )

void *filtroImagen(void * arg)
{

  struct nodito nod= *(struct nodito *)arg;

  unsigned char *imagenGray=nod.imgGray;
  unsigned char *imagenFiltro=nod.imgFilt;
  uint32_t width=nod.w;
  uint32_t height=nod.h;

  
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
  for( y = nod.inicio; y <= nod.final; y++ )
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
    
 
  pthread_exit((void*)&nod.nucleo);

}


void *Gauss(void * arg)
{

  struct nodito nod= *(struct nodito *)arg;

  unsigned char *imagenGray=nod.imgGray;
  unsigned char *imagenFiltro=nod.imgFilt;
  uint32_t width=nod.w;
  uint32_t height=nod.h;

  
  register int x, y, xm, ym;
  int conv2, conv1, indice, indicem;
  char Gauss[] =
    {1, 2, 1,
     2, 4, 2,
     1, 2, 1};
  
  for( y = nod.inicio; y <= nod.final; y++ )
    for( x = 0; x <= width-DIMASK; x++ )
    {
      conv1 = 0;
      indicem = 0;
      for( ym = 0; ym < DIMASK; ym++  )
      {
        for( xm = 0; xm < DIMASK; xm++ )
        {
          indice = ((y+ym)*width + (x+xm));
          conv1 += imagenGray[indice]*Gauss[indicem++];
          
        }
      }
      conv1 = conv1 / 16;
      indice = ((y+1)*width + (x+1));
      imagenFiltro[indice] = conv1;
    }
    
 
  pthread_exit((void*)&nod.nucleo);

}

void brilloImagen( unsigned char* imagenGray, uint32_t width, uint32_t height){
  register int p;
  short int pixel; //2 bytes 
  for (p = 0; p < width*height; p++)
  {
    pixel = imagenGray[p] + 80;
    imagenGray[p] = (pixel > 255)? 255 : (unsigned) pixel;
  }
}



void GraytoRGB(unsigned char* imagenGray, unsigned char* imagenRGB, uint32_t width, uint32_t height){
  register  int x,y; 
  int indiceRGB, indiceGray; //los indices para las dos imagenes

  for ( y = 0; y < height; y++)
  {
    for ( x = 0; x < width; x++)
    {
      indiceGray = width*y+x; //wiith*y es la fila, x es la columna en memoria lineal
      indiceRGB =  indiceGray * 3; //es el indice normal pero por 3 bytes
  

      imagenRGB[indiceRGB+0] = imagenGray[indiceGray];
      imagenRGB[indiceRGB+1] = imagenGray[indiceGray];
      imagenRGB[indiceRGB+2] = imagenGray[indiceGray];

      }
  }

}


unsigned char* RGBtoGray(unsigned char* imagenRGB, uint32_t width, uint32_t height){
  unsigned char* imagenGray;
  imagenGray = (unsigned char *)malloc( width*height*sizeof(unsigned char) );
  register  int x,y; //para moverse en X y Y
  int indiceRGB, indiceGray; //los indices para las dos imagenes
  unsigned char grayLevel; //valor de pixel en gris
  

  if( imagenGray == NULL ){
    perror("Error al asignar memoria");
    exit(EXIT_FAILURE);
  }
  //ciclo para sustituir el RGB por BN 
  //el valor del pixel BN=(R+G+B)/3
  for ( y = 0; y < height; y++)
  {
    for ( x = 0; x < width; x++)
    {
      indiceGray = (width*y)+x; //wiith*y es la fila, x es la columna en memoria lineal
      indiceRGB =  (indiceGray<<1) + indiceGray; //es el indice normal pero por 3 bytes
      //arriba hice indiceGray*3 pero con menos ciclos de relojo, ya que hice indiceGRay*(2+1)
      //indiceRGB me ubica en el pixel R del RGB,
      grayLevel = (imagenRGB[indiceRGB]*30+ 
                  imagenRGB[indiceRGB+1]*59+
                  imagenRGB[indiceRGB+2]*11)/100;

      //ahora coloco el valor en el pixel
      imagenGray[indiceGray] = grayLevel;
    }
  }
  return imagenGray;
}

unsigned char *abrirBMP(char *filename, bmpInfoHeader *bInfoHeader)
{

  	FILE *f;
  	bmpFileHeader header;     /* cabecera */
  	unsigned char *imgdata;   /* datos de imagen */
 	uint16_t type;        /* 2 bytes identificativos */

  	f = fopen (filename, "r");
	if( f  == NULL )
	{
		perror("Error al abrir el archivo en lectura");
		exit(EXIT_FAILURE);
	}

  	/* Leemos los dos primeros bytes */
  	fread( &type, sizeof(uint16_t), 1, f );
  	if( type != 0x4D42 )        /* Comprobamos el formato */
    	{
		printf("Error en el formato de imagen, debe ser BMP de 24 bits");
      		fclose(f);
      		return NULL;
    	}

  	/* Leemos la cabecera de fichero completa */
  	fread( &header, sizeof(bmpFileHeader), 1, f );

  	/* Leemos la cabecera de información completa */
  	fread( bInfoHeader, sizeof(bmpInfoHeader), 1, f );

  	/* Reservamos memoria para la imagen, ¿cuánta?
     	Tanto como indique imgsize */
  	imgdata = (unsigned char *)malloc( bInfoHeader->imgsize );
	if( imgdata == NULL )
	{
		perror("Error al asignar memoria");
		exit(EXIT_FAILURE);
	}
  	/* Nos situamos en el sitio donde empiezan los datos de imagen,
   	nos lo indica el offset de la cabecera de fichero*/
  	fseek(f, header.offset, SEEK_SET);

  	/* Leemos los datos de imagen, tantos bytes como imgsize */
  	fread(imgdata, bInfoHeader->imgsize,1, f);

  	/* Cerramos el apuntador del archivo de la imagen*/
  	fclose(f);

  	/* Devolvemos la imagen */
  	return imgdata;
}

void guardarBMP( char *filename, bmpInfoHeader *info, unsigned char *imgdata )
{
	bmpFileHeader header;
  	FILE *f;
  	uint16_t type;

  	f = fopen(filename, "w+");
	if( f  == NULL )
	{
		perror("Error al abrir el archivo en escritura");
		exit(EXIT_FAILURE);
	}

  	header.size = info->imgsize + sizeof(bmpFileHeader) + sizeof(bmpInfoHeader);
  	/* header.resv1=0; */
  	/* header.resv2=1; */
  	/* El offset será el tamaño de las dos cabeceras + 2 (información de fichero)*/
  	header.offset = sizeof(bmpFileHeader) + sizeof(bmpInfoHeader) + 2;
  	/* Escribimos la identificación del archivo */
  	type = 0x4D42;
  	fwrite( &type, sizeof(type), 1, f );
  	/* Escribimos la cabecera de fichero */
  	fwrite(&header, sizeof(bmpFileHeader),1,f);
  	/* Escribimos la información básica de la imagen */
  	fwrite(info, sizeof(bmpInfoHeader),1,f);
  	/* Escribimos la imagen */
  	fwrite(imgdata, info->imgsize, 1, f);
  	fclose(f);
}

void displayInfo( bmpInfoHeader *info )
{
  	printf("Tamaño de la cabecera: %u\n", info->headersize);
  	printf("Anchura: %d\n", info->width);
  	printf("Altura: %d\n", info->height);
  	printf("Planos (1): %d\n", info->planes);
  	printf("Bits por pixel: %d\n", info->bpp);
  	printf("Compresión: %d\n", info->compress);
  	printf("Tamaño de datos de imagen: %u\n", info->imgsize);
  	printf("Resolucón horizontal: %u\n", info->bpmx);
  	printf("Resolucón vertical: %u\n", info->bpmy);
  	printf("Colores en paleta: %d\n", info->colors);
  	printf("Colores importantes: %d\n", info->imxtcolors);
}
