//============================================================================
// Name        : grafos.cpp
// Author      : Pamela Jocelyn Palomo Martinez. Graduate Program in Systems Engineering. Universidad Autonoma de Nuevo Leon
// Description : Representacion y manipulacion de grafos
//============================================================================

#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <limits>

using namespace std;
struct Arco{
	int nodo_destino;
	double peso;
	Arco(int n, double p){nodo_destino=n; peso=p;}
	bool operator==(int n){return nodo_destino==n;}
};

struct Nodo{
	int id;
	list<Arco> arcos_incidentes;
	Nodo(int i){id=i;}
	bool operator==(int i){return id==i;}
	bool operator<(Nodo n){return id<n.id;}
};

struct nodo_explorar{
	int id;
	double ddistancia;
	nodo_explorar(int i,double d){id=i;ddistancia=d;}
	bool operator<(const nodo_explorar& otro) const {return ddistancia>otro.ddistancia;}
};

list<Nodo> generarGrafo(string);
void manipularGrafo(list<Nodo> &, int);
void imprimirGrafo(list<Nodo>);

int main(int argc, char** argv) {
	/*Almacena y manipula grafos dirigidos.
	Recibe como entrada un fichero que contiene una lista de los arcos del grafo en el formato
	n1  n2
	donde n1 es el id del nodo origen y n2 es el id del nodo destino
	*/


	//Leer archivo
	list<Nodo>grafo=generarGrafo(argv[1]);

	while(true){
		cout<<"Agregar un nodo. Presione 0."<<endl;
		cout<<"Eliminar un nodo. Presione 1."<<endl;
		cout<<"Agregar un arco. Presione 2."<<endl;
		cout<<"Eliminar un arco. Presione 3."<<endl;
		cout<<"Verificar si existe un camino entre dos nodos. Presione 4."<<endl;
		cout<<"Encontrar el camino mas corto entre dos nodos. Presione 5."<<endl;
		cout<<"Imprimir el grafo. Presione 6."<<endl;

		cout<<"Salir. Presione 7."<<endl;
		int respuesta;
		cin>>respuesta;

		if(respuesta==7) break;

		manipularGrafo(grafo,respuesta);
		}

	return 0;
}


list<Nodo> generarGrafo(string archivo_entrada){
	list<Nodo>grafo;

	ifstream datos_entrada;
	datos_entrada.open(archivo_entrada.c_str());

	while(true){
		int nodo_origen, nodo_destino;
		double peso;
		datos_entrada>>nodo_origen>>nodo_destino>>peso;

		if(datos_entrada.eof()) break;

		list<Nodo>::iterator itg=find(grafo.begin(),grafo.end(),nodo_origen);
		if(itg==grafo.end()){
			//El nodo origen no ha sido agregado previamente. Agregarlo al grafo.
			Nodo nuevo_nodo(nodo_origen);
			nuevo_nodo.arcos_incidentes.push_back(Arco(nodo_destino,peso));
			grafo.push_back(nuevo_nodo);
		}
		else{
			//El nodo origen ya se encuentra en el grafo. Agregar arco.
			itg->arcos_incidentes.push_back(Arco(nodo_destino,peso));
		}

		//Verificar que el nodo destino sea parte del grafo. Si no lo es, agregarlo.
		itg=find(grafo.begin(),grafo.end(),nodo_destino);
		if(itg==grafo.end()){
			grafo.push_back(Nodo(nodo_destino));
		}

	}
	grafo.sort();
	return grafo;
}

void manipularGrafo(list<Nodo> &grafo, int accion){

	switch(accion){
	case 0:{
		//Agregar un nuevo nodo.
		grafo.push_back(grafo.back().id+1);
		imprimirGrafo(grafo);
		break;
	}
	case 1:{
		//Remover un nodo.
		cout<<"Ingresar el id del nodo a eliminar."<<endl;
		int nodo_eliminar;
		cin>>nodo_eliminar;
		list<Nodo>::iterator it=find(grafo.begin(),grafo.end(),nodo_eliminar);
		grafo.erase(it);

		for(list<Nodo>::iterator itg=grafo.begin();itg!=grafo.end();itg++){
			list<Arco>::iterator ita=find(itg->arcos_incidentes.begin(),itg->arcos_incidentes.end(),nodo_eliminar);
			if(ita!=itg->arcos_incidentes.end()){
				itg->arcos_incidentes.erase(ita);
			}
		}
		imprimirGrafo(grafo);

		break;
	}
	case 2:{
		//Agregar un arco
		int nodo_origen, nodo_destino;
		double peso;
		cout<<"Ingresar el nodo origen."<<endl;
		cin>>nodo_origen;
		cout<<"Ingresar el nodo destino."<<endl;
		cin>>nodo_destino;
		cout<<"Ingresar el peso del arco."<<endl;
		cin>>peso;

		list<Nodo>::iterator it=find(grafo.begin(),grafo.end(),nodo_origen);
		if(it==grafo.end()){
			//El nodo origen no existe. Se genera el nodo origen.
			Nodo nuevo_nodo(nodo_origen);
			nuevo_nodo.arcos_incidentes.push_back(Arco(nodo_destino,peso));
			grafo.push_back(nuevo_nodo);
		}
		else{
			it->arcos_incidentes.push_back(Arco(nodo_destino,peso));
		}
		imprimirGrafo(grafo);
		break;
	}
	case 3:{
		//Eliminar un arco
		int nodo_origen, nodo_destino;
		cout<<"Ingresar el nodo origen."<<endl;
		cin>>nodo_origen;
		cout<<"Ingresar el nodo destino."<<endl;
		cin>>nodo_destino;
		list<Nodo>::iterator it=find(grafo.begin(),grafo.end(),nodo_origen);
		if(it!=grafo.end()){
			list<Arco>::iterator ita=find(it->arcos_incidentes.begin(),it->arcos_incidentes.end(),nodo_destino);
			if(ita!=it->arcos_incidentes.end()){
				it->arcos_incidentes.erase(ita);
			}
		}
		imprimirGrafo(grafo);
		break;
	}
	case 4:{
		//Busqueda por anchura
		bool accesible=false;
		int nodo_origen, nodo_destino;
		cout<<"Ingresar el nodo origen."<<endl;
		cin>>nodo_origen;
		cout<<"Ingresar el nodo destino."<<endl;
		cin>>nodo_destino;

		vector<int> padre_nodo(grafo.back().id+1,-1);
		vector<bool> estado_nodo(grafo.back().id+1,false); //true si ya fue visitado, false en otro caso
		estado_nodo[nodo_origen]=true;
		queue<int> nodos_por_explorar;
		nodos_por_explorar.push(nodo_origen);

		while(!nodos_por_explorar.empty()){
			int nodo_elegido=nodos_por_explorar.front();

			list<Nodo>::iterator it=find(grafo.begin(), grafo.end(), nodo_elegido);
			for(list<Arco>::iterator ita=it->arcos_incidentes.begin(); ita!=it->arcos_incidentes.end(); ita++){
				if(ita->nodo_destino==nodo_destino){
					cout<<"El nodo "<<nodo_destino<<" es alcanzable desde el nodo "<<nodo_origen<<" a traves del camino:"<<endl;
					cout<<nodo_destino<<"<-";
					int padre=nodo_elegido;
					while(padre!=-1){
						cout<<padre<<"<-";
						padre=padre_nodo[padre];
					}
					accesible=true;
					break;
				}
				if(!estado_nodo[ita->nodo_destino]){
					estado_nodo[ita->nodo_destino]=true;
					padre_nodo[ita->nodo_destino]=nodo_elegido;
					nodos_por_explorar.push(ita->nodo_destino);
				}
			}
			if(accesible) break;
			nodos_por_explorar.pop();
		}
		if(!accesible){
			cout<<"El nodo "<<nodo_destino<<" no es alcanzable desde el nodo "<<nodo_origen<<endl;
		}
		break;
	}
	case 5:{
		//Algoritmo de Dijkstra
		int nodo_origen, nodo_destino;
		cout<<"Ingresar el nodo origen."<<endl;
		cin>>nodo_origen;
		cout<<"Ingresar el nodo destino."<<endl;
		cin>>nodo_destino;

		vector<double> distancia(grafo.back().id+1,numeric_limits<double>::max());
		vector<int> padre(grafo.back().id+1,-1);
		vector<bool> marcado(grafo.back().id+1,false);
		distancia[nodo_origen]=0;

		priority_queue<nodo_explorar> nodos_por_explorar;
		nodo_explorar _nodo(nodo_origen,0);
		nodos_por_explorar.push(_nodo);

		while(!nodos_por_explorar.empty()){
			int nodo_elegido=nodos_por_explorar.top().id;
			nodos_por_explorar.pop();
			marcado[nodo_elegido]=true;

			list<Nodo>::iterator itg=find(grafo.begin(),grafo.end(),nodo_elegido);
			for(list<Arco>::iterator ita=itg->arcos_incidentes.begin();ita!=itg->arcos_incidentes.end();ita++){
				if(!marcado[ita->nodo_destino] && distancia[ita->nodo_destino]>distancia[nodo_elegido]+ita->peso){
					distancia[ita->nodo_destino]=distancia[nodo_elegido]+ita->peso;
					padre[ita->nodo_destino]=nodo_elegido;
					nodo_explorar nuevo_nodo(ita->nodo_destino,distancia[ita->nodo_destino]);
					nodos_por_explorar.push(nuevo_nodo);
				}
			}
		}

		if(distancia[nodo_destino]<numeric_limits<double>::max()){
			cout<<"El camino mas corto del nodo "<<nodo_origen<<" al nodo "<<nodo_destino<<" es: "<<endl;
			int anterior=padre[nodo_destino];
			cout<<nodo_destino<<"<-";
			while(anterior!=-1){
				cout<<anterior<<"<-";
				anterior=padre[anterior];
			}
			cout<<endl<<"con un costo igual a "<<distancia[nodo_destino]<<endl;
		}
		else{
			cout<<"No existe un camino entre los nodos "<<nodo_origen<<" y "<<nodo_destino<<endl;
		}
		break;
	}
	case 6:{
		imprimirGrafo(grafo);
		break;
	}
}
}

void imprimirGrafo(list<Nodo> grafo){
	cout<<"Arcos: (origen,destino,peso)"<<endl;
	for(list<Nodo>::iterator it=grafo.begin();it!=grafo.end();it++){
		cout<<"Nodo: "<<it->id<<endl;
		list<Arco> arcos_incidentes=it->arcos_incidentes;
		for(list<Arco>::iterator ita=arcos_incidentes.begin();ita!=arcos_incidentes.end();ita++){
			cout<<"("<<it->id<<","<<ita->nodo_destino<<","<<ita->peso<<")"<<endl;
		}
		cout<<endl;
	}
}
