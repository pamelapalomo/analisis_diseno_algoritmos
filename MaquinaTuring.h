/*
 * MaquinaTuring.h
 *
 *  Created on: 30/01/2017
 *      Author: pamela
 */

#ifndef MAQUINATURING_H_
#define MAQUINATURING_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>


namespace std {

struct elemento_transicion{
	string estado_inicial;
	char simbolo_inicial;
	string estado_final;
	char simbolo_final;
	char direccion;
	elemento_transicion(string ei, char si, string ef, char sf, char d){
		estado_inicial=ei;
		simbolo_inicial=si;
		estado_final=ef;
		simbolo_final=sf;
		direccion=d;
	}
};

class Maquina_Turing {
private:
	int apuntador;
	string estado_actual;
	string cinta;
	vector<elemento_transicion> funcion_transicion;
public:
	Maquina_Turing(char**);
	virtual ~Maquina_Turing();

	void imprimir_cinta();
	void imprimir_maquina();
	void ejecutar();
};

} /* namespace std */

#endif /* MAQUINATURING_H_ */
