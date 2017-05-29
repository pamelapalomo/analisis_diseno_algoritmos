//============================================================================
// Name        : Tarea5-AlgoritmoPrim.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Dos implementaciones del algoritmo de Prim: una usando una cola
//				de prioridad y otra usando un montículo
//============================================================================

#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

struct nodo_explorar{
	int id;
	float distancia;
	nodo_explorar(int i, float d){id=i; distancia=d;}
	bool operator<(const nodo_explorar& otro) const {return distancia>otro.distancia;}
	bool operator==(const nodo_explorar& otro) const {return id==otro.id;}
};

int main(int argc, char** argv) {
	/*
	 * @param: argv Array de argumentos
	 * argv[1] nombre del archivo a leer
	 */

	//Lectura del archivo
	ifstream datos;
	string arch_entrada("Instancias/");
	string argv1=argv[1];
	arch_entrada+=argv1;
	cout<<"Ejecutando "<<arch_entrada<<endl;
	datos.open(arch_entrada.c_str());
	int n_nodos, n_arcos;
	string dummy_str;
	datos>>n_nodos>>n_arcos>>dummy_str;

	/*
	 * Generar matriz de adyacencia
	 * ¡¡¡NOTA!!! Como el objetivo de esta tarea es analizar el comportamiento del algoritmo en grafos densos,
	 * es conveniente utilizar una matriz de adyacencia en lugar de otra estructura de datos como, por ejemplo,
	 * una lista de adyacencia. Ademas, el grafo es dirigido, ya que es uno de los supuestos del algoritmo de Prim.
	 */
	float mat_ady[n_nodos][n_nodos];
	for(int i=0;i<n_nodos;i++){
		for(int j=0;j<n_nodos;j++) mat_ady[i][j]=-1;
	}

	int origen, destino;
	float peso;
	for(int i=0;i<n_arcos;i++){
		datos>>origen>>destino>>peso;
		mat_ady[origen][destino]=peso;
		mat_ady[destino][origen]=peso;
	}

	//Ejecucion del algoritmo
	float distancia[n_nodos];
	int padre[n_nodos];
	vector<nodo_explorar> monticulo;
	float costo=0;

	for(int i=0;i<n_nodos;i++){
		distancia[i]=numeric_limits<float>::max();
		padre[i]=-1;
		monticulo.push_back(nodo_explorar(i,distancia[i]));
	}

	//El primer nodo se elige al azar
	srand(time(NULL));
	int random_int=rand()%n_nodos;
	distancia[random_int]=0;
	monticulo[random_int].distancia=0;
	make_heap(monticulo.begin(), monticulo.end());

	int sel_nodo;
	vector<nodo_explorar>::iterator itv;
	int n_actualizaciones=0;
	while(!monticulo.empty()){
		//Elegir el nodo con menor distancia y eliminarlo del monticulo
		sel_nodo=monticulo.front().id;
		pop_heap(monticulo.begin(), monticulo.end());
		monticulo.pop_back();

		if(padre[sel_nodo]!=-1) costo+=mat_ady[padre[sel_nodo]][sel_nodo];

		//Actualizar las distancias
		for(int i=0;i<n_nodos;i++){

			if(mat_ady[sel_nodo][i]!=-1){
				//Existe un arco entre los nodos
				itv=find(monticulo.begin(), monticulo.end(), nodo_explorar(i,0));

				if(itv!=monticulo.end() && distancia[i]>mat_ady[sel_nodo][i]){
					//El nodo se debe actualizar
					padre[i]=sel_nodo;
					distancia[i]=mat_ady[sel_nodo][i];
					itv->distancia=distancia[i];
					make_heap(monticulo.begin(), monticulo.end());
					n_actualizaciones++;
				}
			}
		}
	}

	//Escribir el numero de actualizaciones que se hacen
	ofstream salida;
	string arch_salida("Resultados/");
	arch_salida+=argv1;
	salida.open(arch_salida.c_str(),ofstream::out | ios::app);
	salida<<n_actualizaciones<<endl;

	return 0;
}
