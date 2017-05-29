//============================================================================
// Name        : Tarea2-InstanciasGrafos.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Generador de grafos aleatorios
//============================================================================

#include "DistribucionesProbabilidad.h"
#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

struct Arco{
	int origen, destino;
	float peso;
	bool dirigido;
	bool operator==(const Arco &other){
		if(dirigido) return (origen==other.origen && destino==other.destino);
		return ((origen==other.origen && destino==other.destino) || (origen==other.destino && destino==other.origen));
	}
	bool operator<(const Arco &other){
		if(origen<other.origen) return true;
		if(origen>other.origen) return false;
		return destino<other.destino;
	}
};

int main(int argc, char** argv) {
	/*@param argv Array de argumentos:
	 * argv[1] Numero de nodos
	 * argv[2] Numero de arcos
	 * argv[3]
	 * 			0: No dirigido
	 * 			1: Dirigido
	 * argv[4] Distribucion de probabilidad de los pesos
	 * 			0: No ponderado
	 * 			1: Uniforme discreta
	 * 			2: Uniforme continua
	 * 			3: Normal
	 * argv[5] Irrelevante si el grafo es no ponderado.
	 * 			Limite inferior si es ponderado con distribucion uniforme discreta o continua.
	 * 			Media si es ponderado con distribucion normal.
	 * argv[6] Irrelevante si el grafo es no ponderado.
	 * 			Limite superior si es ponderado con distribucion uniforme discreta o continua.
	 * 			Desviacion estandar si es ponderado con distribucion normal.
	 	 */

	int n_nodos=atoi(argv[1]);
	int n_arcos=atoi(argv[2]);
	bool dirigido=true;
	if(atoi(argv[3])==0) dirigido=false;
	int dist_prob=atoi(argv[4]);
	float arg1=atof(argv[5]);
	float arg2=atof(argv[6]);

	srand(time(NULL));
	int origen, destino;
	list<Arco> grafo;
	list<Arco>::iterator it_grafo;
	Arco _arco;
	_arco.dirigido=dirigido;
	_arco.peso=1;

	while(grafo.size()<n_arcos){
		//Seleccionar el arco
		origen=rand()%n_nodos;
		destino=origen;
		while(destino==origen) destino=rand()%n_nodos;
		_arco.origen=origen;
		_arco.destino=destino;

		//Verificar que el arco no se haya generado antes
		it_grafo=find(grafo.begin(), grafo.end(), _arco);

		if(it_grafo==grafo.end()){
			//El arco no se ha generado antes. Agregar peso y guardarlo en el grafo
			if(dist_prob!=0) _arco.peso=fabs(numeroAleatorio(dist_prob,arg1,arg2));
			grafo.push_back(_arco);
		}
	}
	grafo.sort();

	//Escribir el archivo
	string nombre_archivo("Instancias/Grafo_");
	nombre_archivo+=string(argv[1])+"_"+string(argv[2])+"_";
	if(dirigido) nombre_archivo+="D";
	else nombre_archivo+="ND";
	switch(dist_prob){
	case 0:{
		nombre_archivo+=".txt";
		break;
	}
	case 1: {
		nombre_archivo+="_UD_"+string (argv[5])+"_"+string (argv[6])+".txt";
		break;
	}
	case 2: {
		nombre_archivo+="_UC_"+string (argv[5])+"_"+string (argv[6])+".txt";
		break;
	}
	case 3: {
		nombre_archivo+="_N_"+string (argv[5])+"_"+string (argv[6])+".txt";
		break;
	}
	}

	ofstream salida(nombre_archivo.c_str());
	salida<<n_nodos<<" "<<n_arcos<<" ";
	if(dirigido) salida<<"D"<<endl;
	else salida<<"ND"<<endl;

	for(list<Arco>::iterator it=grafo.begin();it!=grafo.end();it++) salida<<it->origen<<" "<<it->destino<<" "<<it->peso<<endl;

	return 0;
}
