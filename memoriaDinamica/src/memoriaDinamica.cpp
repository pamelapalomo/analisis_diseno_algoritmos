//============================================================================
// Name        : memoriaDinamica.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Memoria dinamica
//============================================================================

#include <iostream>
#include <cstdlib>
#include <list>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
	srand(time(NULL));

	int tamano=100;
	int tamano_max=tamano;
	int n_cambios=0;

	int n_elementos=0;
	int costo=0;

	//Generar operaciones
	list<int> operaciones;

	if(atoi(argv[1])==0){
		//Operaciones aleatorias
		for(int i=0;i<200;i++){
			operaciones.push_back(rand()%2);
		}
	}else{
		//Operaciones en bloques
		bool insert=true;
		int i=0;
		while(i<200){
			int tam_bloque=rand()%(200-operaciones.size())+1;
			if(insert){
				for(int j=0;j<tam_bloque;j++){
					operaciones.push_back(1);
					i++;
				}
				insert=false;
			}
			else{
				for(int j=0;j<tam_bloque;j++){
					operaciones.push_back(0);
					i++;
				}
				insert=true;
			}
		}
	}

	//Generar umbrales
	float umbral_max, umbral_min;
	switch(atoi(argv[2])){
	case 0:{
		umbral_max=0.9;
		umbral_min=0.1;
		break;
	}
	case 1:{
		umbral_max=0.75;
		umbral_min=0.25;
		break;
	}
	case 2:{
		umbral_max=0.5;
		umbral_min=0.5;
	}
	}

	for(list<int>::iterator it=operaciones.begin();it!=operaciones.end();it++){
		if(*it==1){
			//Insertar nuevo valor
			n_elementos++;
			costo++;
			if(n_elementos>umbral_max*float(tamano)){
				tamano*=2;
				n_cambios++;
				costo+=n_elementos;
				if(tamano>tamano_max) tamano_max=tamano;
			}
		}
		else{
			//Eliminar un valor
			n_elementos--;
			costo++;
			if(n_elementos<umbral_min*float(tamano)){
				if(tamano/2>100){
					tamano/=2;
					costo+=n_elementos;
					n_cambios++;
				}
			}
		}
	}

	float costo_am=float(costo)/200;

	ofstream output("resultados.txt", ofstream::out | ios::app);
	if(atoi(argv[1])==0) output<<"Random\t";
	else output<<"Bloques\t";
	output<<umbral_min<<"\t"<<umbral_max<<"\t"<<costo_am<<"\t"<<costo<<"\t"<<n_cambios<<endl;

	return 0;
}
