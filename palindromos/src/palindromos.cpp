//============================================================================
// Name        : palindromos.cpp
// Author      : Pamela Jocelyn Palomo Martinez
//============================================================================

#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <cmath>
#include <cstring>

using namespace std;

bool palindromo_iterativo(char*);
bool palindromo_recursivo(string);
double timeval_diff(struct timeval *, struct timeval *);

int main(int argc, char** argv) {

	char* palabra=argv[1];

	timeval t_inicioi, t_finr, t_fini;
	double secs_r, secs_i;

	gettimeofday(&t_inicioi, NULL);
	bool resultado_iterativo=palindromo_iterativo(palabra);
	gettimeofday(&t_fini, NULL);
	secs_i=timeval_diff(&t_fini, &t_fini);
	cout<<"Algoritmo iterativo"<<endl;
	if(resultado_iterativo) cout<<palabra<<" es un palindromo"<<endl;
	else cout<<palabra<<" no es un palindromo"<<endl;
	cout<<"\nTiempo de ejecucion: "<<secs_i<<" segundos"<<endl;

	bool resultado_recursivo=palindromo_recursivo(palabra);
	gettimeofday(&t_finr, NULL);
	secs_r=timeval_diff(&t_finr, &t_fini);

	cout<<"Algoritmo recursivo"<<endl;
	if(resultado_recursivo) cout<<palabra<<" es un palindromo"<<endl;
	else cout<<palabra<<" no es un palindromo"<<endl;
	cout<<"\nTiempo de ejecucion: "<<secs_r<<" segundos"<<endl;

	return 0;
}

bool palindromo_iterativo(char* p){
	int ultimo_indice=strlen(p)-1;
	int primer_indice=0;

	while(primer_indice!=ultimo_indice){
		if(p[primer_indice++]!=p[ultimo_indice--]) return false;
	}

	return true;
}

bool palindromo_recursivo(string p){
	int ultimo_indice=p.size()-1;
	int primer_indice=0;

	if(primer_indice==ultimo_indice) return true;
	if(p[primer_indice]==p[ultimo_indice]){
		return palindromo_recursivo(p.substr(primer_indice+1,ultimo_indice-1));
	}
	return false;
}

double timeval_diff(struct timeval *a, struct timeval *b)
{
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
