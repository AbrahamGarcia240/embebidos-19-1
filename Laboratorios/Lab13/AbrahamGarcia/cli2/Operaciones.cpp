#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
#include <math.h>
#include <string>
#include <string.h>
#include "Operaciones.h"
using namespace std;
#define N  1024
#define EVER 1

void obtieneCoordenadas(double* numeros, string GPS){
	register int i=0;
	int grados[2], minutos[2], segundos[2];
	char *token = strtok((char*)GPS.c_str(), ",");
	while (token != NULL) { 
		cout<<token<<endl;
		if(i==0){
			numeros[0]=convierteAGD(token,0);

			
		}
		else if(i==1){
			numeros[1]=convierteAGD(token, 1);
			
		}
	    token = strtok(NULL, ",");
	    i++; 
	}
	


}

double convierteAGD(string num, int n){
	string aux;
	double grados, minutos, segundos;
	register int j;
	for(j=0; j<num.size(); j++){
		switch(j){
			case 0:
				if(n==0)
					aux+=num[j];

				break;
			case 1:
				if(n==0){
					aux+=num[j];
					grados=(double)atof(aux.c_str());
					aux.clear();
				}
				else{
					aux+=num[j];
				}
				break;
			case 2:
				if(n==0)
					aux+=num[j];
				else{
					aux+=num[j];
					grados=(double)atof(aux.c_str());
					aux.clear();
				}
				break;
			case 3:
				if(n==0){
					aux+=num[j];
					minutos=(double)atof(aux.c_str());
					aux.clear();}
				else{
					aux+=num[j];
				}
				break;
			case 5:
				if(n==0)
					aux+=num[j];
				break;
			case 6:
				if(n==0){
					aux+=num[j];
					minutos=(double)atof(aux.c_str());
					aux.clear();}
				else{
					aux+=num[j];
				}
				break;
			case 7:
				if(n==1){
					aux+=num[j];
					segundos=(double)atof(aux.c_str());
					aux.clear();
				}
			case 8:
				
					aux+=num[j];
					
				
				break;
			case 9:
				if(n==1){
					aux+=num[j];
					
				}
				else{
					aux+=num[j];
					segundos=(double)atof(aux.c_str());
					aux.clear();
				}

				break;
			case 10:
				if(n==1){
					aux+=num[j];
					
				}
				break;
			case 11:
				if(n==1){
					aux+=num[j];
					
				}
				break;
		}
	}
	minutos+=segundos/60;
	grados+=minutos/60;
	if(n==1){
		grados*=-1;
		cout<<segundos<<","<<minutos<<","<<grados<<endl;
	}
	
	return grados;
}



string vigila(){
	string cadena;
	register int i;
    int fd_serie;
    unsigned char dato;
 
    fd_serie = config_serial( "/dev/ttyACM0", B9600 );
    //printf("serial abierto con descriptor: %d\n", fd_serie);
 
    //Leemos N datos del UART
    for(;EVER;)
    {
        read ( fd_serie, &dato, 1 );
        //printf("%c", dato);
        if(dato=='$'){
        	//cadena+=dato;
        	read( fd_serie, &dato, 1 );
        	if(dato=='G'){
        		//cadena+=dato;
        		read ( fd_serie, &dato, 1 );
        		if(dato=='P'){
        			//cadena+=dato;
        			read ( fd_serie, &dato, 1 );
        			if(dato=='G'){
        				//cadena+=dato;
        				read ( fd_serie, &dato, 1 );
        				if(dato=='G'){
        					//cadena+=dato;
        					read ( fd_serie, &dato, 1 );
        					if(dato=='A'){
        						//cadena+=dato;
        						register int j=0;
        						//cadena+=' ';
        						do{
        							read ( fd_serie, &dato, 1 );
        							if(dato==','){
        								j++;
        								if(j==3)
        									cadena+=dato;
        							}
        							else if(j==2 || j==4){
        								cadena+=dato;
        							}
        							else if(j==5){
        								 close( fd_serie );
        								return cadena;
        							}
        							

        						}while(j<6);

        					}
        				}
        			}
        		}
        	}
        }
        cadena.clear();
        //printf("%c", dato);
    }
 
   
}

int config_serial( char *dispositivo_serial, speed_t baudios )
{
    struct termios newtermios;
    int fd;
/*
 * Se abre un descriptor de archivo para manejar la interfaz serie
 * O_RDWR - Se abre el descriptor para lectura y escritura
 * O_NOCTTY - El dispositivo terminal no se convertira en el terminal del proceso
 * ~O_NONBLOCK - Se hace bloqueante la lectura de datos
 */
    fd = open( dispositivo_serial, (O_RDWR | O_NOCTTY) & ~O_NONBLOCK );
    if( fd == -1 )
    {
        printf("Error al abrir el dispositivo tty \n");
        exit( EXIT_FAILURE );
    }
/*
 * cflag - Proporciona los indicadores de modo de control
 *  CBAUD   - Velocidad de transmision en baudios.
 *  CS8 - Especifica los bits por dato, en este caso 8
 *  CLOCAL  - Ignora las lineas de control del modem: CTS y RTS
 *  CREAD   - Habilita el receptor del UART
 * iflag - proporciona los indicadores de modo de entrada
 *  IGNPAR  - Ingnora errores de paridad, es decir, comunicación sin paridad
 * oflag - Proporciona los indicadores de modo de salida
 * lflag - Proporciona indicadores de modo local
 *  TCIOFLUSH - Elimina datos recibidos pero no leidos, como los escritos pero no transmitidos
 *  ~ICANON - Establece modo no canonico, en este modo la entrada esta disponible inmediatamente
 * cc[]  - Arreglo que define caracteres especiales de control
 *  VMIN > 0, VTIME = 0 - Bloquea la lectura hasta que el numero de bytes (1) esta disponible
 */
    newtermios.c_cflag  = CBAUD | CS8 | CLOCAL | CREAD;
    newtermios.c_iflag  = IGNPAR;
    newtermios.c_oflag  = 0;
    newtermios.c_lflag  = TCIOFLUSH | ~ICANON;
    newtermios.c_cc[VMIN]   = 1;
    newtermios.c_cc[VTIME]  = 0;
 
// Configura la velocidad de salida del UART
    if( cfsetospeed( &newtermios, baudios ) == -1 )
    {
        printf("Error al establecer velocidad de salida \n");
        exit( EXIT_FAILURE );
    }
// Configura la velocidad de entrada del UART
    if( cfsetispeed( &newtermios, baudios ) == -1 )
    {
        printf("Error al establecer velocidad de entrada \n" );
        exit( EXIT_FAILURE );
    }
// Limpia el buffer de entrada
    if( tcflush( fd, TCIFLUSH ) == -1 )
    {
        printf("Error al limpiar el buffer de entrada \n" );
        exit( EXIT_FAILURE );
    }
// Limpia el buffer de salida
    if( tcflush( fd, TCOFLUSH ) == -1 )
    {
        printf("Error al limpiar el buffer de salida \n" );
        exit( EXIT_FAILURE );
    }
/*
 * Se establece los parametros de terminal asociados con el
 * descriptor de archivo fd utilizando la estructura termios
 * TCSANOW - Cambia los valores inmediatamente
 */
    if( tcsetattr( fd, TCSANOW, &newtermios ) == -1 )
    {
        printf("Error al establecer los parametros de la terminal \n" );
        exit( EXIT_FAILURE );
    }
//Retorna el descriptor de archivo
    return fd;
}
