//============================================================================
// Name        : Tarea1-grafos.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Representacion y manipulacion de grafos
//============================================================================

#include "grafo.h"
using namespace std;

int main(int argc, char** argv) {
    srand(time(NULL));
    Grafo _grafo(argc, argv);

    cout<<"Elegir una de las siguientes opciones"<<endl;
    cout<<"[0] Salir"<<endl;
    cout<<"[1] Visualizar el grafo"<<endl;
    cout<<"[2] Generar un archivo latex con el grafo en tikz"<<endl;
    cout<<"[3] Ejecutar BFS"<<endl;
    cout<<"[4] Ejecutar DFS"<<endl;
    cout<<"[5] Encontrar componentes conexas"<<endl;
    cout<<"[6] Calcular la densidad del grafo"<<endl;


    int opcion=-1;
    while(opcion!=0){
        cin>>opcion;
        switch(opcion){
        case 1:{
            _grafo.dibujar();
            break;
        }
        case 2:{
            _grafo.toLatex();
            break;
        }
        case 3:{
            cout<<"Introducir el nodo origen"<<endl;
            int nodo;
            cin>>nodo;
            vector<int>arbol=_grafo.BFS(nodo);
            cout<<"Nodo \tPadre"<<endl;
            for(int i=0;i<_grafo.getNumNodos();i++) cout<<i<<" "<<arbol[i]<<endl;
            break;
        }
        case 4:{
            cout<<"Introducir el nodo origen"<<endl;
            int nodo;
            cin>>nodo;
            vector<int>arbol=_grafo.DFS(nodo);
            cout<<"Nodo \tPadre"<<endl;
            for(int i=0;i<_grafo.getNumNodos();i++) cout<<i<<" "<<arbol[i]<<endl;
            break;
        }
        case 5:{
             pair<list<list<int> > ,vector<int > > componentes_bosque=_grafo.componentesConexas();
             list<list<int> > componentes=componentes_bosque.first;
             int i=1;
             for(list<list<int> >::iterator it=componentes.begin();it!=componentes.end();it++){
                 list<int> _componente=*it;
                 _componente.sort();
                 cout<<"Componente conexa "<<i<<": ";
                 for(list<int>::iterator it2=_componente.begin();it2!=_componente.end();it2++){
                     cout<<*it2<<" ";
                 }
                 cout<<endl;
             }
             break;
        }
        case 6:{
            cout<<"Densidad: "<<_grafo.calcularDensidad()<<endl;
            break;
        }
        }
    }
    return 0;
}
