/*
 * MaquinaTuring.cpp
 *
 *  Created on: 30/01/2017
 *      Author: pamela
 */

#include "MaquinaTuring.h"

namespace std {

Maquina_Turing::Maquina_Turing(char** entrada) {
	string archivo_entrada=entrada[1];
	archivo_entrada+=".txt";

	fstream entrada_maquina;
	entrada_maquina.open(archivo_entrada.c_str());

	entrada_maquina>>cinta;

	while(!entrada_maquina.eof()){
		string ei, ef;
		char si, sf, d;
		entrada_maquina>>ei>>si>>ef>>sf>>d;
		if(!entrada_maquina.eof()){
			funcion_transicion.push_back(elemento_transicion(ei,si,ef,sf,d));
		}
	}

	apuntador=0;
	estado_actual="s";

	imprimir_maquina();
}

Maquina_Turing::~Maquina_Turing() {
	// TODO Auto-generated destructor stub
}

void Maquina_Turing::imprimir_cinta(){
	cout<<"Cinta:";

	for(unsigned int i=0;i<cinta.size();i++){
		if(i==( unsigned int) apuntador){
			cout<<"["<<cinta[i]<<"]";
		}
		else{
			cout<<cinta[i];
		}
	}
}

void Maquina_Turing::imprimir_maquina(){
	imprimir_cinta();
	cout<<endl<<endl;

	cout<<"Funcion de transicion:\n";
	for(unsigned int i=0;i<funcion_transicion.size();i++){
		cout<<"("<<funcion_transicion[i].estado_inicial<<","<<funcion_transicion[i].simbolo_inicial<<") -> ("<<funcion_transicion[i].estado_final<<","
				<<funcion_transicion[i].simbolo_final<<","<<funcion_transicion[i].direccion<<")"<<endl;
	}
}


void Maquina_Turing::ejecutar(){

	string alto("alto");
	string si("si");
	string no("no");

	while(alto.compare(estado_actual)!=0 && si.compare(estado_actual)!=0 && no.compare(estado_actual)!=0){
		cout<<"Estado: "<<estado_actual<<endl;
		imprimir_cinta();
		cout<<endl<<"-----------"<<endl;

		//Buscar el estado con el simbolo actual
		for(vector<elemento_transicion>::iterator it=funcion_transicion.begin();it!=funcion_transicion.end();it++){
			if(it->estado_inicial.compare(estado_actual)==0 && it->simbolo_inicial==cinta[apuntador]){
				//Actualizar estado y escribir en la cinta
				estado_actual=it->estado_final;
				cinta[apuntador]=it->simbolo_final;

				//Si el ultimo simbolo de la cinta no es vacio, agregar un simbolo vacio al final de la misma
				if(apuntador==cinta.size()-1 && cinta[apuntador]!='v'){
					cinta+="v";
				}

				//Mover el apuntador
				if(it->direccion=='d') apuntador++;
				else if(it->direccion=='i') apuntador--;
				break;
			}
		}
	}
	cout<<"Estado: "<<estado_actual<<endl;
	imprimir_cinta();
	cout<<endl<<"-----------"<<endl;

}
} /* namespace std */
