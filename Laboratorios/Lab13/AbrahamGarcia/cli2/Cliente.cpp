#include <iostream>
#include "SocketDatagrama.h"
#include "Operaciones.h"
using namespace std;


int main(int argc, char const *argv[])
{
	
	if(argc<2){
		cout<<"Ussage ./Cliente <ip servidor>"<<endl;
		return 0;
	}

	//VARIABLES
	int puerto=7201;
	int tamMensaje=2*sizeof(double);
	int tamMensajeRecibido=sizeof(int);
	double num[2];
	int respuesta=0;
	string GPS="$GPGGA,000000.000,4883.78551,S,234.96879,W,1,8,0,2600,M,0,M,,*7B";

	//OPERACIONES
	obtieneCoordenadas(num,GPS);
	cout<<num[0]<<","<<num[1]<<endl;
	
	

	//ENVIO
	PaqueteDatagrama pds((char*)num,tamMensaje,(char *)argv[1],7300);
	SocketDatagrama sd(puerto);
	cout<<sd.envia(pds)<<endl;
	
	//RECIBO
	PaqueteDatagrama pdr(tamMensajeRecibido);
	sd.recibe(pdr);
	memcpy(&respuesta,pdr.obtieneDatos(),pdr.obtieneLongitud());
	

	//OPERACIONES
	cout<<"El usuario ha contestado: "<<respuesta<<endl;
	

	return 0;
}