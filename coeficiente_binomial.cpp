#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

int calcularCoeficiente(int, int, bool);

int main(int argc, char** argv){
	/* Recibe n, k y un 1 si se requiere el cálculo exacto o un 0 si se requiere el cálculo aproximado*/

	int n=atoi(argv[1]);
	int k=atoi(argv[2]);
	bool exacto=true;
	if(atoi(argv[3])==0){
		exacto=false;
	}
	int coeficiente=calcularCoeficiente(n,k,exacto);
	cout<<"Coeficiente binomial con x="<<n<<" y k="<<k<<" es "<<coeficiente<<endl;
}


int calcularCoeficiente(int n, int k, bool exacto){
	
	int mayor_abajo=max(n-k,k);
	int menor_abajo=min(n-k,k);

	int coeficiente=0;
	if(exacto){
		int coeficiente_arriba=1;
		for(int i=mayor_abajo;i<n;i++){
			coeficiente_arriba*=i+1;
		}
		int coeficiente_abajo=1;
		for(int i=0;i<menor_abajo;i++){
			coeficiente_abajo*=i+1;
		}
		coeficiente=coeficiente_arriba/coeficiente_abajo;
		
	}
	else{
		double coeficiente_arriba=0;
		for(int i=mayor_abajo;i<n;i++){
			coeficiente_arriba+=log(i+1);
		}
		double coeficiente_abajo=0;
		for(int i=0;i<menor_abajo;i++){
			coeficiente_abajo+=log(i+1);
		}
		double coeficiente_d=coeficiente_arriba-coeficiente_abajo;
		coeficiente_d=exp(coeficiente_d);
		coeficiente=int (round(coeficiente_d));
	}

	return coeficiente;
}

