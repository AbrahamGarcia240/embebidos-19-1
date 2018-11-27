#include <iostream>
#include <string.h>
using namespace std;


void obtieneCoordenadas(double* numeros, string GPS);
int config_serial( char *dispositivo_serial, speed_t baudios );
double convierteAGD(string num, int n);
string vigila();