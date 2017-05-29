//============================================================================
// Name        : SS_SAT.cpp
// Author      : Pamela Jocelyn Palomo Martinez. Graduate Program in Systems Engineering. Universidad Autonoma de Nuevo Leon
// Description : Scatter search for SAT problem
//============================================================================

#include "ScatterSearch.h"

using namespace std;

int main(int argc, char** argv) {
	/*
	 * @param argv Array de argumentos
	 * argv[1] Nombre del archivo
	 * argv[2] Tamaño del conjunto inicial
	 * argv[3] Tamaño del conjunto de referencia
	 */
	ScatterSearch solver(argv);
	solver.solve();

	return 0;
}
