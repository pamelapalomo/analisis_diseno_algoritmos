/*
 * Nodo.cpp
 *
 *  Created on: 27/03/2017
 *      Author: pamela
 */

#include "Nodo.h"

namespace std {

Nodo::Nodo(int c) {
	clave=c;
	padre=NULL;
	hijo_izquierdo=NULL;
	hijo_derecho=NULL;
}

Nodo::Nodo(int c, Nodo* p){
	clave=c;
	padre=p;
	hijo_izquierdo=NULL;
	hijo_derecho=NULL;
}

Nodo::~Nodo() {
	// TODO Auto-generated destructor stub
}

bool Nodo::agregarNodo(int nueva_clave){
	if(nueva_clave==clave) return false;

	if(nueva_clave<clave){
		if(hijo_izquierdo==NULL){
			hijo_izquierdo=new Nodo(nueva_clave, this);
			return true;
		}
		return hijo_izquierdo->agregarNodo(nueva_clave);
	}
	else {
		if (hijo_derecho == NULL) {
			hijo_derecho = new Nodo(nueva_clave, this);
			return true;
		}
		return hijo_derecho->agregarNodo(nueva_clave);
	}
	return true;
}

bool Nodo::buscar(int clave_buscar, int &nconsultas){
	nconsultas++;
	if(clave_buscar==clave) return true;

	if(clave_buscar<clave){
		if(hijo_izquierdo==NULL) return false;
		return hijo_izquierdo->buscar(clave_buscar,nconsultas);
	}
	if(hijo_derecho==NULL) return false;
	return hijo_derecho->buscar(clave_buscar,nconsultas);
}

void Nodo::imprimir(){
	cout<<"Clave: "<<clave<<endl;
	if(padre!=NULL) cout<<"Padre: "<<padre->getClave()<<endl;
	else cout<<"Padre: ---"<<endl;
	if(hijo_izquierdo!=NULL) cout<<"Hijo izquierdo: "<<hijo_izquierdo->getClave()<<endl;
	else cout<<"Hijo izquierdo: ---"<<endl;
	if(hijo_derecho!=NULL) cout<<"Hijo derecho: "<<hijo_derecho->getClave()<<endl;
	else cout<<"Hijo derecho: ---"<<endl;
	cout<<endl;

	if(hijo_izquierdo!=NULL) hijo_izquierdo->imprimir();
	if(hijo_derecho!=NULL) hijo_derecho->imprimir();
}

} /* namespace std */
