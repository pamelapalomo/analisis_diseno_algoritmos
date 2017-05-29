//============================================================================
// Name        : arbol_exp_min.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Arbol de expansion minima
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char** argv) {
	//Determinar nodos a verificar

	//Leer archivo
	string file_name=argv[1];
	string path("/home/pamela/workspace/arbol_exp_min/Debug/");
	path+=file_name;

	ifstream data;
	data.open(path.c_str());

	int nnodos;
	data>>nnodos;

	//Inicializar array
	int cconexas[nnodos];
	for(int i=0;i<nnodos;i++) cconexas[i]=nnodos;

	//Inicia algoritmo
	bool alcanzable=false;
	for(int i=0;i<nnodos;i++){
		int a, b;
		data>>a>>b;

		int auxa=cconexas[a];
		int auxb=cconexas[b];

		int id_componente=min(a,b);
		id_componente=min(id_componente,auxa);
		id_componente=min(id_componente,auxb);
		cconexas[a]=id_componente;
		cconexas[b]=id_componente;

		for(int j=0;j<nnodos;j++){
			if(cconexas[j]<nnodos && (cconexas[j]==auxa || cconexas[j]==auxb)) cconexas[j]=id_componente;
		}

		if(cconexas[nodo1]==cconexas[nodo2]){
			cout<<"El nodo "<<nodo2<<" es alcanzable desde el nodo "<<nodo1<<endl;
			alcanzable=true;
			break;
		}


	}

	if(!alcanzable) cout<<"El nodo "<<nodo2<<" no es alcanzable desde el nodo "<<nodo1<<endl;

	return 0;
}

