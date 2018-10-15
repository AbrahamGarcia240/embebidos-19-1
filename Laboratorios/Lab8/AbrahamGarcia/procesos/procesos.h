#define NUM_PROCS 4
#define N 8
#ifndef PROCESOS_H
#define PROCESOS_H
	void procesoHijo(float* A, float *B , int pipedf[], int n);
	void procesoPadre(int pipefd[NUM_PROCS][2]);
#endif
