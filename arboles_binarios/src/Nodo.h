/*
 * Nodo.h
 *
 *  Created on: 27/03/2017
 *      Author: pamela
 */

#ifndef NODO_H_
#define NODO_H_

#include <cstdio>
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <set>
#include <fstream>

namespace std {

class Nodo {
private:
	int clave;
	Nodo* padre;
	Nodo* hijo_izquierdo;
	Nodo* hijo_derecho;
public:
	Nodo(int); //Clave
	Nodo(int, Nodo*); //Clave y padre
	virtual ~Nodo();

	//Getters
	int getClave(){return clave;}

	bool agregarNodo(int);
	bool buscar(int, int&);
	void imprimir();
};

} /* namespace std */

#endif /* NODO_H_ */
