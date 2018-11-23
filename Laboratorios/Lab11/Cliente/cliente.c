#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "defs.h"

int main(int argc, char **argv){
	if (argc < 3) {
        	printf("Usage ./cliente [IP] [archivo]");
		return 0;
    	}
	int tamano_direccion, sockfd, servidor_sockfd, contador = 0;
	int recibido = -1;
	struct sockaddr_in direccion_servidor;
	char leer_mensaje[TAM_BUFFER];
	char leer_mensajeS[TAM_BUFFER];
	char leer_mensaje2[50];
	char escribir_mensaje[TAM_BUFFER];
	FILE *imagen;
	imagen = fopen(argv[2], "rb");
	struct stat st;
	stat(argv[2], &st);
	int size = st.st_size;

	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);

	if( inet_pton(AF_INET, argv[1], &direccion_servidor.sin_addr) <= 0 )
	{
		perror("Ocurrio un error al momento de asignar la direccion IP");
		exit(1);
	}

//	printf("Creando Socket ....\n");
	if( (sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
	}

	printf ("Estableciendo conexion...\n");
	if( connect(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor) ) < 0) 
	{
		perror ("Ocurrio un problema al establecer la conexion");
		exit(1);
	}

	
	printf ("Enviando imagen al servidor...\n");
	write(sockfd, &size, sizeof(size));
	while(!feof(imagen))
	{
		contador++;
		fread(escribir_mensaje, sizeof(char), TAM_BUFFER, imagen);
		if(write(sockfd,escribir_mensaje,TAM_BUFFER) == -1)
		{
			perror("Error al enviar el arcchivo:");
		}
	}
	printf("Bytes enviados:%d\n",contador);
	fclose(imagen);

	FILE *imagenDeServidor;
	imagenDeServidor = fopen("archivoRecibidoServidor.bmp","wb");
	contador = 0;
	printf("Recibiendo imagen procesada...\n");
   	while((recibido = read(sockfd, &leer_mensajeS, TAM_BUFFER)) > 0)
   	{
    	contador++;
      	if(contador==size){
		printf ("Guardando Imagen...");
        	fclose(imagenDeServidor);
         	recibido=-1;
         	break;
      	}else fwrite(leer_mensajeS,sizeof(char),1,imagenDeServidor);
   	}
	printf(" Listo!\n");
	close(sockfd);
	return 0;
}
