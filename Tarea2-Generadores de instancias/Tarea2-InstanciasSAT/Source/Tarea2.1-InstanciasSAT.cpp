//============================================================================
// Name        : 1-InstanciasSAT.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Generador de instancias del SAT problem
//============================================================================

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include <algorithm>
#include <set>

using namespace std;


int main(int argc, char** argv) {
	/*@param argv Array de argumentos:
	 argv[1]: Numero de variables
	 argv[2]: Numero de clausulas
	 argv[3]: Longitud de las clausulas, 0 si se desean clausulas de diferentes longitudes aleatorias
	 argv[4]: "H" si se requieren clausulas de Horn, cualquier otro caracter en otro caso
	 */

	int n_variables=atoi(argv[1]);
	int n_clausulas=atoi(argv[2]);
	int tamano_clausulas=atoi(argv[3]);
	string horn_string=argv[4];
	string h_str("H");

	//Crear el archivo de salida
	string directorio("./Instancias/");
	if(tamano_clausulas>0) directorio+=string(argv[3]);
	directorio+="SAT_CNF_"+string(argv[1])+"_"+string(argv[2]);
	if(horn_string.compare(h_str)==0) directorio+="_H";
	directorio+=".txt";
	ofstream salida(directorio.c_str());

	//Generar la instancia en formato CNF
	salida<<"CNF "<<n_variables<<" "<<n_clausulas<<endl;

	int tamano=tamano_clausulas;
	int variable;
	set<int> clausula, copia_clausula;
	list<set<int> > instancia;

	srand(time(NULL));
	while(instancia.size()<n_clausulas){
		//Generar la clausula
		if(tamano_clausulas<1) tamano=rand()%(n_variables/4)+1;
		if(horn_string.compare(h_str)==0){
			while(clausula.size()<tamano) clausula.insert(-1*(rand()%n_variables+1));
		}
		else{
			while(clausula.size()<tamano) clausula.insert(rand()%n_variables+1);
			for(set<int>::iterator it=clausula.begin();it!=clausula.end();it++){
				if(rand()%2==0){
					variable=*it;
					copia_clausula.insert(-1*variable);
				}
				else copia_clausula.insert(*it);
			}
			clausula=copia_clausula;
			copia_clausula.clear();
		}

		//Verificar que la clausula no se haya generado previamente
		list<set<int> >::iterator it= find(instancia.begin(), instancia.end(), clausula);
		if(it==instancia.end()){
			instancia.push_back(clausula);

			//Escribir la clausula en el archivo de salida
			for(set<int>::iterator its=clausula.begin();its!=clausula.end();its++) salida<<*its<<" ";
			salida<<"0"<<endl;
		}

		clausula.clear();
	}

	return 0;
}
