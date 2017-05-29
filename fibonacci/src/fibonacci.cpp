//============================================================================
// Name        : fibonacci.cpp
// Author      : Pamela Jocelyn Palomo Martinez
//============================================================================

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>

using namespace std;

int fibonacci_recursivo(int);
int fibonacci_iterativo(int);
double timeval_diff(struct timeval *, struct timeval *);

int main(int argc, char** argv) {

	int numero=atoi(argv[1]);

	timeval t_inicioi, t_finr, t_fini;
	double secs_r, secs_i;

	gettimeofday(&t_inicioi, NULL);
	int resultado_iterativo=fibonacci_iterativo(numero);
	gettimeofday(&t_fini, NULL);
	secs_i=timeval_diff(&t_fini, &t_fini);
	cout<<"Algoritmo iterativo\nResultado: "<<resultado_iterativo<<"\nTiempo de ejecucion: "<<secs_i<<" segundos"<<endl;

	int resultado_recursivo=fibonacci_recursivo(numero);
	gettimeofday(&t_finr, NULL);
	secs_r=timeval_diff(&t_finr, &t_fini);

	cout<<"Algoritmo recursivo\nResultado: "<<resultado_recursivo<<"\nTiempo de ejecucion: "<<secs_r<<" segundos"<<endl;
	return 0;
}

int fibonacci_recursivo(int n){
	if(n<2){
		return n;
	}
	return fibonacci_recursivo(n-2)+fibonacci_recursivo(n-1);
}

int fibonacci_iterativo(int n){
	int anterior_anterior=0;
	int anterior=1;
	int resultado;

	for(int i=0;i<n-1;i++){
		resultado=anterior_anterior+anterior;
		anterior_anterior=anterior;
		anterior=resultado;
	}

	return resultado;
}

double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
