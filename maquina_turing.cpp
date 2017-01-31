//============================================================================
// Name        : maquina_turing.cpp
// Author      : Pamela Jocelyn Palomo Martinez
//============================================================================

#include "MaquinaTuring.h"

using namespace std;


int main(int argc, char** argv) {
	
	/*Recibe un archivo de texto cuya primer linea tiene el contenido original de la cinta
	y cada renglon restante contiene la definicion de la funcion de transicion, haciendo uso 
	de cinco elementos: e s e' s' d
	Siendo e: estado
		s: sìmbolo
		e' el estado resultante
		s' el simbolo resultante
		d: la direccion en la cual se mueve el apuntador (d,i,n)
		En este repositorio se tienen tres ejemplos de archivos de entrada:
		entrada_es_par.txt, entrada_multiplicarx2.txt y entrada_sumar1.txt
		*/
	Maquina_Turing _maquina(argv);
	_maquina.ejecutar();

	return 0;
}
