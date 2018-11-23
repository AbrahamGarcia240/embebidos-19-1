#include <iostream>
#include "SocketDatagrama.h"
#include <string.h>
#include <stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>

using namespace std;

SocketDatagrama::SocketDatagrama( int puerto )
{
	s = socket(AF_INET, SOCK_DGRAM, 0);
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
   	direccionLocal.sin_family = AF_INET;
   	direccionLocal.sin_addr.s_addr = INADDR_ANY;
   	direccionLocal.sin_port = htons(puerto);
   	bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
   
}

int SocketDatagrama::recibe(PaqueteDatagrama & p)
{
	char datos[p.obtieneLongitud()]; 
	socklen_t len=sizeof(direccionForanea);
	int rc=recvfrom(s, (char *)datos , p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *)&direccionForanea, &len);  
	char cadena[16];
  p.inicializaPuerto(htons(direccionForanea.sin_port)); 
  memcpy(cadena,inet_ntoa(direccionForanea.sin_addr),16);
  p.inicializaIp(cadena);
  p.inicializaDatos(datos);
  cout<< "Ip:"<< cadena << " Puerto: " << p.obtienePuerto() <<endl;
  return rc;
}


int SocketDatagrama::envia(PaqueteDatagrama & p)
{ 
   	bzero((char *)&direccionForanea, sizeof(direccionForanea));
   	direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());
	 return sendto(s, (char *)p.obtieneDatos(), p.obtieneLongitud() * sizeof(char), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));

}

SocketDatagrama::~SocketDatagrama()
{
	
}