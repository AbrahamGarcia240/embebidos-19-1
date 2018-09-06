#ifndef PROCESOS_H
#define PROCESOS_H

void procesoPadre(int pipedf[]);
void procesoHijo(int * datos, int n, int pipedf[]);

#endif