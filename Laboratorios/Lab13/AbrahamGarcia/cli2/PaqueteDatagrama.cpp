#include <iostream>
#include <string.h>
#include "PaqueteDatagrama.h"

PaqueteDatagrama::PaqueteDatagrama(char *dats, unsigned int longitud, char *ip, int puerto )
{
	datos = new char[longitud];
	memcpy(datos,dats,longitud);
	this->longitud = longitud;
	memcpy(this->ip,ip,16);
	this->puerto = puerto;
}

PaqueteDatagrama:: PaqueteDatagrama(unsigned int longitud)
{
	this->longitud = longitud;
	datos = new char[longitud];
}

char * PaqueteDatagrama::obtieneDireccion()
{
	return ip;
}   

unsigned int PaqueteDatagrama:: obtieneLongitud()
{
	return longitud;
}

int PaqueteDatagrama:: obtienePuerto()
{
	return puerto;
}

char * PaqueteDatagrama::obtieneDatos()
{
	return datos;
}

void PaqueteDatagrama::inicializaPuerto(int puerto)
{	
	this-> puerto = puerto;
}

void PaqueteDatagrama::inicializaIp(char *ip)
{
	memcpy(this->ip,ip,16);
}

void PaqueteDatagrama::inicializaDatos(char * datos)
{
	memcpy(this->datos,datos,this->longitud);
}


PaqueteDatagrama:: ~PaqueteDatagrama()
{
//	delete [] datos;
}