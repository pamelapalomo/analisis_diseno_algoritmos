#ifndef MATUTILIDADES_H
#define MATUTILIDADES_H
#include "header.h"

namespace std {

pair< pair<float,float>, pair<float,float> > interseccionCircRecta(float x_centro, float y_centro, float radio, float x1, float y1, float x2, float y2){
    float pendiente=(y1-y2)/(x1-x2);
    float b=-2.0*x_centro
            +pow(pendiente,2)
            -2.0*pow(pendiente,2)*x1
            +2.0*pendiente*y1
            -2.0*pendiente*y_centro;
    float c=-pow(radio,2)
            +pow(y1-y_centro,2)
            +pow(x_centro,2)
            +pow(pendiente*x1,2)
            -2*pendiente*x1*(y1+y_centro);

    pair<float,float> punto1, punto2;

    punto1.first=(-b+sqrt(pow(b,2)-4*c))/2.0;
    punto1.second=pendiente*(punto1.first-x1)+y1;

    punto2.first=(-b-sqrt(pow(b,2)-4*c))/2.0;
    punto2.second=pendiente*(punto2.first-x1)+y1;

    pair< pair<float,float>, pair<float,float> > puntos(punto1,punto2);
    return puntos;

}

}

#endif // MATUTILIDADES_H
