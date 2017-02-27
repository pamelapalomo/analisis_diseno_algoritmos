//============================================================================
// Name        : SAT_problem.cpp
// Description : SAT
//============================================================================

#include <iostream>
#include <map>
#include <fstream>
#include <cstring>
using namespace std;

map<string,bool> leerAsignaciones(char*);
bool resolver(char*, map<string,bool>);

int main(int argc, char** argv) {
	map<string,bool> asignaciones=leerAsignaciones(argv[1]);
	if(resolver(argv[2],asignaciones)){
		cout<<"El valor de la expresion es verdadera"<<endl;
	}
	else{
		cout<<"El valor de la expresion es falsa"<<endl;
	}


	return 0;
}

map<string,bool>leerAsignaciones(char* input_name){
	string file_name(input_name);
	file_name+=".txt";
	ifstream input_asignaciones;
	input_asignaciones.open(file_name.c_str());

	map<string,bool> asignaciones;

	while(!input_asignaciones.eof()){
		string variable;
		int asignacion_variable;
		input_asignaciones>>variable>>asignacion_variable;
		if(asignacion_variable==0){
			asignaciones[variable]=false;
		}
		else{
			asignaciones[variable]=true;
		}
	}

	input_asignaciones.close();
	return asignaciones;
}

bool resolver(char* instancia_input, map<string, bool> asignaciones) {
	string file_name(instancia_input);
	file_name += ".txt";
	ifstream instancia;
	instancia.open(file_name.c_str());

	string tipo;
	string CNF_string("CNF");
	instancia >> tipo;

	if (CNF_string.compare(tipo) == 0) {
		while (!instancia.eof()) {
			int variables_leidas = 0;
			while (variables_leidas < 3) {
				string variable;
				instancia >> variable;
				char inicio_variable = variable[0];

				if ((inicio_variable != '!' && asignaciones[variable])
						|| (inicio_variable == '!' && !asignaciones[variable.substr(1)])){
					//La clausula es verdadera
					for(int i=0;i<3-variables_leidas;i++) {
						string aux;
						instancia >> aux;
						i++;
					}
					break;
				}

				variables_leidas++;
			}
			if (variables_leidas >= 3) {
				return false;
			}
		}
		return true;
	}
	else{
		while(!instancia.eof()){
			int variables_leidas=0;
			while(variables_leidas<3){
				string variable;
				instancia>>variable;
				char inicio_variable=variable[0];

				if((inicio_variable!='!' && !asignaciones[variable])
						|| (inicio_variable == '!' && asignaciones[variable.substr(1)])){
					//La clausula es falsa
					for(int i=0;i<3-variables_leidas;i++){
						string aux;
						instancia>>aux;
						i++;
					}
					break;
				}

				variables_leidas++;
			}
			if(variables_leidas>=3){
				return true;
			}
		}
		return false;
	}

}
