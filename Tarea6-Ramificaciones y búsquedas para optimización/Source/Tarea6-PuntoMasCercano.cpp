//============================================================================
// Name        : Tarea6-PuntoMasCercano.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Dado un conjunto de puntos y un punto P, este programa ejecuta
//				un algoritmo de tipo dividir y conquistar que encuentra el punto
//				del conjunto mas cercano a P
//============================================================================

#include "DistribucionesProbabilidad.h"
#include <iostream>
#include <list>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>

using namespace std;

int n_calculos=0;

pair<float,float> puntoMasCercano(list<pair<float,float> > conjunto, pair<float,float> punto){

	//Caso base
	if(conjunto.size()==1) return conjunto.front();

	//Seleccionar al azar un punto del conjunto
	int random_int=numeroAleatorio(1,0,conjunto.size()-1);
	list<pair<float,float> >::iterator it=conjunto.begin();
	advance(it,random_int);
	pair<float,float> punto_comparacion=*it;

	//Calcular la distancia del punto al punto de comparacion
	float distancia=sqrt(pow(punto.first-punto_comparacion.first,2)+pow(punto.second-punto_comparacion.second,2));
	n_calculos++;

	//Calcular las rectas del cuadradado cuyos puntos interiores seran aceptados
	float x_max=punto.first+distancia;
	float x_min=punto.first-distancia;
	float y_max=punto.second+distancia;
	float y_min=punto.second-distancia;

	//Determinar los puntos que estan dentro del cuadrado
	int tamano_inic=conjunto.size();
	it=conjunto.begin();
	while(it!=conjunto.end()){
		if((it->first>x_min-0.00001) && (it->first<x_max+0.00001) && (it->second>y_min-0.00001) && (it->second<y_max+0.00001)) it++;
		else it=conjunto.erase(it);
	}

	if(conjunto.size()==tamano_inic){
		//Retornar el punto con menor distancia
		float min_dist=distancia+1;
		pair<float,float>punto_cercano;
		for(it=conjunto.begin();it!=conjunto.end();it++){
			distancia=sqrt(pow(punto.first-it->first,2)+pow(punto.second-it->second,2));
			n_calculos++;
			if(distancia<min_dist){
				min_dist=distancia;
				punto_cercano=*it;
			}
		}
		return punto_cercano;

	}

	return puntoMasCercano(conjunto,punto);
}

int main(int argc, char** argv) {
	/*
	 * @param argv Array de argumentos
	 * argv[1] Numero de puntos
	 * argv[2] Distribucion de probabilidad de las coordenadas de los puntos
	 * 			2: Uniforme continua
	 * 			3: Normal
	 * argv[3] Si la distribucion es uniforme continua, el limite inferior.
	 * 			Si es normal, la media.
	 * argv[4] Si la distribucion es uniforme continua, el limite superior.
	 * 			Si es normal, le desviacion estaandar.
	 */

	int n_puntos=atoi(argv[1]);
	int dist_prob=atoi(argv[2]);
	int arg1=atoi(argv[3]);
	int arg2=atoi(argv[4]);
	srand(time(NULL));

	//Generar el conjunto de puntos
	list<pair<float,float> > conjunto_puntos;
	pair<float,float> punto;
	for(int i=0;i<n_puntos;i++){
		punto.first=numeroAleatorio(dist_prob,arg1,arg2);
		punto.second=numeroAleatorio(dist_prob,arg1,arg2);
		conjunto_puntos.push_back(punto);
	}

	//Generar el punto al cual se buscara el que tenga menor distancia
	punto.first=numeroAleatorio(dist_prob,arg1,arg2);
	punto.second=numeroAleatorio(dist_prob,arg1,arg2);

	//Buscar el punto de conjunto_puntos con menor distancia a punto
	puntoMasCercano(conjunto_puntos,punto);

	//Escribir el numero de veces que se calculó la distancia entre dos puntos
	ofstream salida;
	string archivo("Resultados/");
	string npuntos_str=argv[1];
	archivo+=npuntos_str+".txt";
	salida.open(archivo.c_str(),ofstream::out | ios::app);
	salida<<n_calculos<<endl;

	return 0;
}
