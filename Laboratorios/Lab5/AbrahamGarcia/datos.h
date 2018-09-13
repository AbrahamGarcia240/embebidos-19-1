#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define N 32

int* reservarMemoria();
void llenarArreglo(int * datos);

void imprimirArreglo(int* datos);