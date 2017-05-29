//============================================================================
// Name        : pol_vs_exp.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {

	double exponente=atoi(argv[1]);
	double base=atoi(argv[2]);

	unsigned long int n=2;
	long double polinomial=pow(n,exponente);
	long double exponencial=pow(base,n);
	while(polinomial>exponencial){
		cout<<endl<<"n: "<<n<<endl;
		cout<<"P: "<<polinomial<<endl;
		cout<<"E: "<<exponencial<<endl;
		n*=2;
		polinomial=pow(n,exponente);
		exponencial=pow(base,n);
	}

	cout<<"Con un valor de n="<<n<<" el valor de la funcion polinomial es menor que el valor de la funcion exponencial"<<endl;

	return 0;
}
