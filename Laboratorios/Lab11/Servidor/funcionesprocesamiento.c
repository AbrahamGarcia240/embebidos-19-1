#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "imagen.h"
#include "funcionesprocesamiento.h"

#define DIMASK 3
extern bmpInfoHeader info;

void filtroPB(unsigned char *imagenO, unsigned char *imagenP, uint32_t width, uint32_t iniBloque, uint32_t finBloque ){
	
	register int x,y,ym,xm;
	int indiceI,indiceM,convFil,convCol;
	int sobelFil[DIMASK*DIMASK] = {
		1,0,-1,
		2,0,-2,
		1,0,-1};
	 int sobelCol[DIMASK*DIMASK] = {
		-1,-2,-1,
		0,0,0,
		1,2,1};
	 
	 int pixel;
			

		if(iniBloque>0){
			iniBloque -=DIMASK*DIMASK;
		}
		if(finBloque<info.height){
			finBloque += DIMASK*DIMASK ;
		}
	
		printf("ini%d\n",iniBloque );
		printf("fin%d\n",finBloque );
	
		for( y = iniBloque ; y < finBloque ; y++){
			for( x = 0; x < width ; x++){
				convFil = 0;
				convCol = 0;
				//indiceM = 0; 

				for( ym = y ; ym < y+DIMASK; ym++){
					for( xm = x; xm < x+DIMASK; xm++ ){

						indiceM = (ym-y) * DIMASK + (xm - x);						
						
						if(ym < 0 || ym >info.height-1){
							convFil += 255 *sobelFil[indiceM];
							convCol += 255 *sobelCol[indiceM];
						}else{
							indiceI = ym * width + xm;
							convFil += imagenO[indiceI] * sobelFil[indiceM];
							convCol += imagenO[indiceI] * sobelCol[indiceM] ;
							
						}

					}
				}

				
				convFil = convFil >> 2;
				convCol = convCol >> 2;
				convFil = convFil * convFil;
				convCol = convCol * convCol;
				pixel = sqrt(convFil+convCol);

				imagenP[indiceI] = pixel;

			}
			
		}


}

unsigned char * reservarMemoria(uint32_t width, uint32_t height){
	unsigned char *imagen;
	imagen = (unsigned char *)malloc(width*height*sizeof(unsigned char));
	if(imagen==NULL){
		perror("Error al asignar memoria a la imagen...");
		exit(EXIT_FAILURE);
	}
	return imagen;
}

void brilloImagen(unsigned char *imagenGray, uint32_t width, uint32_t height){
	register int x, y;
	int indiceGray,brillo;

	for( y = 0; y < height; y++ )
		for( x = 0; x < width; x++ )
		{
			indiceGray = (y * width + x);
			brillo=imagenGray[indiceGray]+40;

			imagenGray[indiceGray]=(brillo>255)? 255: brillo;
		}
}

void GrayToRGB (unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t iniBloque, uint32_t finBloque ){
	register int x, y;
	int indiceRGB, indiceGray;
	unsigned char nivelGris;


	for( y = iniBloque; y <= finBloque; y++ )
		for( x = 0; x < width; x++ )
		{
			indiceGray = (y * width + x);
			indiceRGB = indiceGray*3;

			nivelGris= imagenGray[indiceGray];
			imagenRGB[indiceRGB]   = nivelGris;
			imagenRGB[indiceRGB+1]   = nivelGris;
			imagenRGB[indiceRGB+2]   = nivelGris;
		}		
}

unsigned char * RGBToGray( unsigned char *imagenRGB, uint32_t width, uint32_t iniBloque, uint32_t finBloque )
{
	register int x, y;
	int indiceRGB, indiceGray;
	unsigned char nivelGris;
	extern unsigned char *imagenGray;


	

	for( y = iniBloque; y <= finBloque; y++ ){
		
		for( x = 0; x < width; x++ )
		{
	
			indiceGray = (y * width + x);
			indiceRGB = indiceGray*3;
			nivelGris =
			((imagenRGB[indiceRGB]*11 + imagenRGB[indiceRGB+1]*59 + imagenRGB[indiceRGB+2]*30)/100);
			imagenGray[indiceGray]   = nivelGris;

		}
	}

	return imagenGray;	
}

