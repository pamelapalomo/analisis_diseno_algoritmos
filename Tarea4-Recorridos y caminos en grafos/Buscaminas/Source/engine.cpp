#include "engine.h"

using namespace std;
Engine::Engine(int al, int an, int minas)
{
    n_celdas_descubiertas=0;
    n_minas=minas;
    altura=al;
    anchura=an;
    n_celdas=altura*anchura;

    //Generar malla
    malla=new int*[altura];
    for(int i=0;i<altura;i++){
        malla[i]=new int[anchura];
        for(int j=0;j<anchura;j++) malla[i][j]=0;
    }

    //Colocar minas
    int minas_colocadas=0;
    int x, y;
    while(minas_colocadas<n_minas){
        x=rand()%altura;
        y=rand()%anchura;
        if(malla[x][y]==0){
            malla[x][y]=-1;
            minas_colocadas++;
        }
    }

    //Colocar en cada celda el numero de minas en celdas vecinas
    int minas_vecinas=0;
    for(int i=0;i<altura;i++){
        for(int j=0;j<anchura;j++){
            if(malla[i][j]!=-1){
                if(i>0){
                    //Arriba
                    if(malla[i-1][j]==-1) minas_vecinas++;

                    //Arriba izquierda
                    if(j>0){
                        if(malla[i-1][j-1]==-1) minas_vecinas++;
                    }

                    //Arriba derecha
                    if(j<anchura-1){
                         if(malla[i-1][j+1]==-1) minas_vecinas++;
                    }
                }
                if(i<altura-1){
                    //Abajo
                    if(malla[i+1][j]==-1) minas_vecinas++;

                    //Abajo izquierda
                    if(j>0){
                        if(malla[i+1][j-1]==-1) minas_vecinas++;
                    }

                    //Abajo derecha
                    if(j<anchura-1){
                        if(malla[i+1][j+1]==-1) minas_vecinas++;
                    }
                }

                //Izquierda
                if(j>0) {
                    if(malla[i][j-1]==-1) minas_vecinas++;
                }

                //Derecha
                if(j<anchura-1){
                    if(malla[i][j+1]==-1) minas_vecinas++;
                }

                malla[i][j]=minas_vecinas;
                minas_vecinas=0;
            }
        }
    }

    //Al inicio ninguna celda esta revelada
    estado=new int*[altura];
    for(int i=0;i<altura;i++){
        estado[i]=new int[anchura];
        for(int j=0;j<anchura;j++){
            estado[i][j]=0;
        }
    }

    //Al inicio ninguna celda se ha visitado
    visitado=new bool*[altura];
    for(int i=0;i<altura;i++){
        visitado[i]=new bool[anchura];
        for(int j=0;j<anchura;j++){
            visitado[i][j]=false;
        }
    }

}

Engine::~Engine(){
    for(int i=0;i<altura;i++){
        delete[] malla[i];
        delete[] estado[i];
        delete[] visitado[i];
    }
    delete[] malla;
    delete[] estado;
    delete[] visitado;
}

list<pair<int,int> > Engine::destaparCeldas(int renglon, int columna){
    //Basado en DFS
    list<pair<int,int> > celdas_destapadas;
    pair<int,int> celda(renglon,columna);

    if(malla[renglon][columna]>0){
        n_celdas_descubiertas++;
        estado[celda.first][celda.second]=1;
        celdas_destapadas.push_back(celda);
        return celdas_destapadas;
    }

    //Inicializar la celda origen como visitada e inicializar la pila
    visitado[renglon][columna]=true;
    stack<pair<int,int> > celdas_explorar;
    celdas_explorar.push(celda);

    //Inicia el algoritmo de busqueda
    while(!celdas_explorar.empty()){
        pair<int,int> sel_celda=celdas_explorar.top();
        celdas_explorar.pop();
        celdas_destapadas.push_back(sel_celda);
        estado[sel_celda.first][sel_celda.second]=1;
        n_celdas_descubiertas++;

        if(malla[sel_celda.first][sel_celda.second]==0){
            if(sel_celda.first>0){
                //Arriba
                if(malla[sel_celda.first-1][sel_celda.second]!=-1 && !visitado[sel_celda.first-1][sel_celda.second]){
                    visitado[sel_celda.first-1][sel_celda.second]=true;
                    celda.first=sel_celda.first-1;
                    celda.second=sel_celda.second;
                    celdas_explorar.push(celda);
                }

                //Arriba izquierda
                if(sel_celda.second>0){
                    if(malla[sel_celda.first-1][sel_celda.second-1]!=-1 && !visitado[sel_celda.first-1][sel_celda.second-1]){
                        visitado[sel_celda.first-1][sel_celda.second-1]=true;
                        celda.first=sel_celda.first-1;
                        celda.second=sel_celda.second-1;
                        celdas_explorar.push(celda);
                    }
                }

                //Arriba derecha
                if(sel_celda.second<anchura-1){
                     if(malla[sel_celda.first-1][sel_celda.second+1]!=-1 && !visitado[sel_celda.first-1][sel_celda.second+1]){
                         visitado[sel_celda.first-1][sel_celda.second+1]=true;
                         celda.first=sel_celda.first-1;
                         celda.second=sel_celda.second+1;
                         celdas_explorar.push(celda);
                     }
                }
            }
            if(sel_celda.first<altura-1){
                //Abajo
                if(malla[sel_celda.first+1][sel_celda.second]!=-1 && !visitado[sel_celda.first+1][sel_celda.second]){
                    visitado[sel_celda.first+1][sel_celda.second]=true;
                    celda.first=sel_celda.first+1;
                    celda.second=sel_celda.second;
                    celdas_explorar.push(celda);
                }

                //Abajo izquierda
                if(sel_celda.second>0){
                    if(malla[sel_celda.first+1][sel_celda.second-1]!=-1 && !visitado[sel_celda.first+1][sel_celda.second-1]){
                        visitado[sel_celda.first+1][sel_celda.second-1]=true;
                        celda.first=sel_celda.first+1;
                        celda.second=sel_celda.second-1;
                        celdas_explorar.push(celda);
                    }
                }

                //Abajo derecha
                if(sel_celda.second<anchura-1){
                    if(malla[sel_celda.first+1][sel_celda.second+1]!=-1 && !visitado[sel_celda.first+1][sel_celda.second+1]){
                        visitado[sel_celda.first+1][sel_celda.second+1]=true;
                        celda.first=sel_celda.first+1;
                        celda.second=sel_celda.second+1;
                        celdas_explorar.push(celda);
                    }
                }
            }

            //Izquierda
            if(sel_celda.second>0) {
                if(malla[sel_celda.first][sel_celda.second-1]!=-1 && !visitado[sel_celda.first][sel_celda.second-1]){
                    visitado[sel_celda.first][sel_celda.second-1]=true;
                    celda.first=sel_celda.first;
                    celda.second=sel_celda.second-1;
                    celdas_explorar.push(celda);
                }
            }

            //Derecha
            if(sel_celda.second<anchura-1){
                if(malla[sel_celda.first][sel_celda.second+1]!=-1 && !visitado[sel_celda.first][sel_celda.second+1]){
                    visitado[sel_celda.first][sel_celda.second+1]=true;
                    celda.first=sel_celda.first;
                    celda.second=sel_celda.second+1;
                    celdas_explorar.push(celda);
                }
            }
        }
    }

    return celdas_destapadas;
}
