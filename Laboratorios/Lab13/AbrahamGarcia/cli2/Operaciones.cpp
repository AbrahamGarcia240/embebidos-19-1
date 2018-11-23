#include <iostream>
#include <string>
#include <string.h>
#include "Operaciones.h"
using namespace std;

void obtieneCoordenadas(double* numeros, string GPS){
	register int i=0;
	char *token = strtok((char*)GPS.c_str(), ",");
	while (token != NULL) { 
		if(i==2){
			numeros[0]=(double)atof(token);
			numeros[0]/=100;
		}
		else if(i==4){
			numeros[1]=(double)atof(token);
			numeros[1]/=100;
		}
	    token = strtok(NULL, ",");
	    i++; 
	}


}