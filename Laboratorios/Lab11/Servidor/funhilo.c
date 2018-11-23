#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "imagen.h"
#include "funcionesprocesamiento.h"
#include "defs.h"

extern unsigned char *imagenRGB, *imagenGray, *imagenAux;
extern pthread_mutex_t bloqueo;
extern bmpInfoHeader info;

extern pthread_mutex_t bloqueo;

void * funHilo(void *arg){

 	int nh=*(int *)arg;
 	int tambloque = info.height/(NUM_HILOS);
 	int iniBloque =  (nh * tambloque);
 	int finBloque = iniBloque + tambloque;
 	


		pthread_mutex_lock(&bloqueo);
		
	 		imagenGray=RGBToGray( imagenRGB,info.width ,iniBloque,finBloque);
		
			filtroPB(imagenGray,imagenAux,info.width,iniBloque,finBloque);
		
			GrayToRGB(imagenRGB, imagenAux, info.width, iniBloque,finBloque );
		
		pthread_mutex_unlock(&bloqueo);
		
 			
		pthread_exit(arg);
	
 		
}
