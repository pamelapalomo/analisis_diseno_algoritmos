#ifndef ENGINE_H
#define ENGINE_H

#include <list>
#include <stack>
#include <cstdlib>
#include <iostream>

using namespace std;

class Engine
{
private:
    int** malla;
    int** estado; //0 si no esta revelada, 1 si esta revelada, 2 si tiene una bandera, 3 si tiene un signo de interrogacion
    bool** visitado;
    int n_celdas;
    int n_celdas_descubiertas;
    int n_minas;
    int altura;
    int anchura;
public:
    Engine(int, int, int);
    ~Engine();

    //Getters
    int getMinas(int i, int j){return malla[i][j];}
    bool tieneBandera(int i,int j){return (estado[i][j]==2);}
    bool estaRevelada(int i, int j){return (estado[i][j]==1);}
    bool tieneInterrogacion(int i, int j){return (estado[i][j]==3);}

    //Setters
    void ponerBandera(int i, int j){estado[i][j]=2;}
    void quitarBandera(int i, int j){estado[i][j]=3;}
    void quitarInterrogacion(int i, int j){estado[i][j]=0;}

    list<pair<int,int> > destaparCeldas(int,int);
    bool partidaGanada(){return (n_celdas_descubiertas+n_minas==n_celdas);}


};

#endif // ENGINE_H
