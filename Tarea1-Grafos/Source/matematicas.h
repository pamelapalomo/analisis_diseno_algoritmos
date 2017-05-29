#ifndef MATEMATICAS_H
#define MATEMATICAS_H

#include "header.h"

namespace std {

inline pair<float,float> interseccionCircRecta(float x1, float y1, float x2, float y2, float distancia, float pendiente){
    pair<float,float> punto;
    float numerador_x=pow(distancia,2)
            -20*distancia
            -pow(x1,2)
            +pow(x2,2)
            -pow(y1,2)
            +pow(y2,2)
            +2*(pendiente*x1-y1)*(y2-y1);
    float denominador_x=2*(x2-x1+pendiente*(y2-y1));
    punto.first=numerador_x/denominador_x;
    punto.second=pendiente*(punto.first-x1)+y1;
    return punto;
}


inline pair< pair<float,float>, pair<float,float> > obtenerArco(float x1, float y1, float x2, float y2) {
    pair<float, float> punto_inic, punto_fin;
    float distancia=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    float pendiente=(y1-y2)/(x1-x2);

    //Obtener el punto de interseccion del arco que sale del primero nodo con la circunferencia del otro nodo
    punto_inic=interseccionCircRecta(x1+10.0,y1+10.0,x2+10.0,y2+10.0,distancia,pendiente);

    //Obtener los puntos de interseccion del arco que sale del primer nodo la circunferencia de este mismo nodo
    punto_fin=interseccionCircRecta(x2+10.0,y2+10.0,x1+10.0,y1+10.0,distancia,pendiente);

    pair< pair<float,float>, pair<float,float> > extremos;
    extremos.first=punto_inic;
    extremos.second=punto_fin;

    return extremos;
}

}

#endif // MATEMATICAS_H
