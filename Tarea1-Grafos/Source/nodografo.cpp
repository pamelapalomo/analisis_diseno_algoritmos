#include "nodografo.h"

namespace std {

NodoGrafo::NodoGrafo(int i, int r, int mia, float maa)
{
    id=i;
    radio=r;
    min_angulo=mia;
    max_angulo=maa;
    angulo=(max_angulo-min_angulo)/2.0+min_angulo;
    padre=NULL;
    x_rect=radio*cos(angulo*3.14159/180);
    y_rect=-radio*sin(angulo*3.14159/180);
    if(fabs(x_rect)<0.001) x_rect=0.0;
    if(fabs(y_rect)<0.001) y_rect=0.0;
}

NodoGrafo::NodoGrafo(int i, NodoGrafo* p){
    id=i;
    padre=p;
    radio=padre->radio+50;
}

void NodoGrafo::establecerConosHijos(){
     if(hijos.size()<1) return;

    int mayor_anterior=min_angulo;
    float tamano_cono=(max_angulo-min_angulo)/float (hijos.size());
    for(list<NodoGrafo*>::iterator it=hijos.begin();it!=hijos.end();it++){
        NodoGrafo* _hijo=*it;
        _hijo->min_angulo=mayor_anterior;
        _hijo->max_angulo=mayor_anterior+tamano_cono;
        _hijo->establecerAngulo();
        mayor_anterior+=tamano_cono;
    }
}

void NodoGrafo::establecerAngulo(){
    angulo=(max_angulo-min_angulo)/2.0+min_angulo;
    x_rect=radio*cos(angulo*3.14159/180);
    y_rect=-radio*sin(angulo*3.14159/180);
    if(fabs(x_rect)<0.001) x_rect=0.0;
    if(fabs(y_rect)<0.001) y_rect=0.0;
}
}
