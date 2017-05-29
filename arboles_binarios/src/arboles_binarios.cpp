//============================================================================
// Name        : arboles_binarios.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Llenado y consulta en arboles binarios
//============================================================================
#include "Nodo.h"

using namespace std;



int main(int argc, char** argv) {

	//Crear arbol aleatorio
	srand(time(NULL));
	Nodo* raiz=new Nodo(rand()%100);

	int numero_nodos=atoi(argv[1]);
	int nodos_agregados=1;
	while(nodos_agregados<numero_nodos){
		if(raiz->agregarNodo(rand()%(numero_nodos*2))) nodos_agregados++;
	}

	//Buscar elementos en el arbol
	set<int>elementos_buscar;
	while(elementos_buscar.size()<10){
		elementos_buscar.insert(rand()%(numero_nodos*2));
	}

	ofstream resultados;
	int consultas_totales=0;
	for(set<int>::iterator it=elementos_buscar.begin();it!=elementos_buscar.end();it++){
		int numero_consultas=0;
		raiz->buscar(*it,numero_consultas);
		consultas_totales+=numero_consultas;
	}

	float promedio_consultas=consultas_totales/10.0;

	resultados.open("resultados.txt",ofstream::out | ios::app);
	resultados<<numero_nodos<<"\t"<<promedio_consultas<<endl;

	return 0;
}
