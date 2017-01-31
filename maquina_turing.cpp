//============================================================================
// Name        : maquina_turing.cpp
// Author      : Pamela Jocelyn Palomo Martinez
//============================================================================

#include "MaquinaTuring.h"

using namespace std;


int main(int argc, char** argv) {

	Maquina_Turing _maquina(argv);
	_maquina.ejecutar();

	return 0;
}
