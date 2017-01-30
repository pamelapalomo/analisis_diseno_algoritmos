#include <iostream>
#include <cmath>
#include <cstdlib>
#include <time.h>
#include <sys/time.h>

using namespace std;

double timeval_diff(struct timeval *, struct timeval *);


int main(int argc, char** argv){

	int base=atoi(argv[1]);
	int exponente=atoi(argv[2]);
	int modulo=atoi(argv[3]);

	struct timeval t_inicio1, t_final1, t_inicio2, t_final2;
	double secs1, secs2;

	gettimeofday(&t_inicio1, NULL);
	int resultado_potencia=((unsigned long int) pow(base,exponente))%modulo;
	gettimeofday(&t_final1, NULL);
	secs1 = timeval_diff(&t_final1, &t_inicio1);
	cout <<"El resultado usando los operadores de C++ es "<<resultado_potencia<<" en un tiempo de "<<secs1<<" segundos"<<endl;
	

	gettimeofday(&t_inicio2, NULL);
	int resultado=1;
	int num=base;
	while(exponente>0){
		if(exponente%2==1){
			resultado*=num;
			resultado=resultado%modulo;
		}
		num*=num;
		num=num%modulo;
		exponente=exponente>>1;
	}
	gettimeofday(&t_final2, NULL);
	secs2 = timeval_diff(&t_final2, &t_inicio2);

	cout<<"El resultado utilizando el algoritmo es "<<resultado<<" en un tiempo de "<< secs2<<" segundos"<<endl;
}

/* retorna "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}


