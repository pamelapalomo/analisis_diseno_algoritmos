/*
 * Grafo.h
 *
 *  Created on: 20/05/2017
 *      Author: pamela
 */

#ifndef GRAFO_H_
#define GRAFO_H_
#include "nodografo.h"

namespace std {

struct Arco{
    int nodo_destino;
    double peso;
    Arco(int n, double p){nodo_destino=n;peso=p;}
};

struct Nodo{
    int id;
    list<Arco> arcos_salida;
    bool operator==(int i){return id==i;}
    bool operator<(Nodo n){return id<n.id;}
    Nodo(int i){id=i;}
};

class Grafo:public vector<Nodo> {
private:
    bool dirigido;
    int n_nodos;
    int n_arcos;
    int int_arg;
    char** char_arg;
    vector<pair<float,float> > coordenadas;
public:
    Grafo(int, char**);
    virtual ~Grafo();

    void dibujar();
    vector<int> BFS(int);
    vector<int> DFS(int);
    pair<list<list<int> > ,vector<int > > componentesConexas();
    void toLatex();
    void generarCoordenadas();
    float calcularDensidad();

    int getNumNodos(){return n_nodos;}
};

} /* namespace std */

#endif /* GRAFO_H_ */
