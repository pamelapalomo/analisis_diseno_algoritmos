#ifndef NODOGRAFO_H
#define NODOGRAFO_H
#include "matematicas.h"

namespace std{
class NodoGrafo{
private:
    int id;
    float x_rect;
    float y_rect;
    int radio;
    float angulo;
    float min_angulo;
    float max_angulo;
    list<NodoGrafo*> hijos;
    NodoGrafo* padre;
public:
    NodoGrafo(int, int, int, float);
    NodoGrafo(int, NodoGrafo*);

    //Getters
    int getID(){return id;}
    int getRadio(){return radio;}
    pair<float,float> getRectCoordenadas(){pair<float,float> c(x_rect,y_rect);return c;}

    //Setters
    void setHijo(NodoGrafo* h){hijos.push_back(h);}

    void establecerConosHijos();
    void establecerAngulo();
};

}

#endif // NODOGRAFO_H
