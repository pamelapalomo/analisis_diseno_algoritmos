//============================================================================
// Name        : GeneradorExpresionesBooleanas.cpp
// Author      : Pamela Jocelyn Palomo Martinez. Graduate Program in Systems Engineering. Universidad Autonoma de Nuevo Leon
// Description : Generador de expresiones booleanas
//============================================================================

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <set>
#include <cstring>
#include <sstream>
using namespace std;

string intToString(int number){
	string result;
	ostringstream convert;
	convert << number;
	result = convert.str();

	return result;
}


int main(int argc, char** argv) {
	//Entrada: numero de variables y numero de clausulas

	srand(time(NULL));

	int numero_variables=atoi(argv[1]);
	int numero_clausulas=atoi(argv[2]);

	string nombre_archivo("CNF_");
	nombre_archivo+=intToString(numero_variables)+"_"+intToString(numero_clausulas)+".txt";
	ofstream salida(nombre_archivo.c_str());

	for(int i=0;i<numero_clausulas;i++){
		int nvariables_clausula=(rand()%numero_variables+1)/2+1;

		set<int> variables_clausula;
		while(variables_clausula.size()<nvariables_clausula){
			int variable=rand()%numero_variables+1;
			variables_clausula.insert(variable);
		}

		for(set<int>::iterator it=variables_clausula.begin();it!=variables_clausula.end();it++){
			if(rand()%2==0) salida<<"!";
			salida<<"x"<<*it<<"\t";
		}
		salida<<"\n";

	}

	return 0;
}
