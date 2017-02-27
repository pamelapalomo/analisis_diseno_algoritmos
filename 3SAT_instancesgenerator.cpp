//============================================================================
// Name        : SAT.cpp
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
using namespace std;


int main(int argc, char** argv) {
	/*Recibe parametros a, b,
	 a=numero de variables
	 b=numero de clausulas*/

	//Generar instancia
	int numero_variables=atoi(argv[1]);
	int numero_clausulas=atoi(argv[2]);

	ofstream instancia;
	instancia.open("/home/pamela/Escritorio/SAT_problem/Debug/instancia.txt");

	if(rand()%2) instancia<<"CNF"<<endl;
	else instancia<<"DNF"<<endl;

	for(int i=0;i<numero_clausulas;i++){
		set<int> variables;
		while (variables.size() < 3) {
			int random_variable = rand() % numero_variables;
			variables.insert(random_variable);
		}

		for(set<int>::iterator it=variables.begin();it!=variables.end();it++){
			if(rand()%2==0) instancia<<"!";
			instancia<<"v"<<*it<<"\t";
		}
		instancia<<endl;
	}
	instancia.close();

	//Generar asignaciones
	ofstream asignaciones;
	asignaciones.open("/home/pamela/Escritorio/SAT_problem/Debug/asignaciones.txt");
	for(int i=0;i<numero_variables;i++){
		if(rand()%2==0){
			asignaciones<<"v"<<i<<"\t0"<<endl;
		}
		else{
			asignaciones<<"v"<<i<<"\t1"<<endl;
		}
	}
	asignaciones.close();

	return 0;
}
