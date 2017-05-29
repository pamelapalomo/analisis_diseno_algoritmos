/*
 * Grafo.cpp
 *
 *  Created on: 20/05/2017
 *      Author: pamela
 */

#include "grafo.h"

namespace std {

Grafo::Grafo(int argc, char** argv){
    int_arg=argc;
    char_arg=argv;

    //Apertura del archivo
    string path("/home/pamela/qt_workspace/Tarea1-grafos/");
    string archivo=argv[1];
    path+=archivo;
    ifstream datos;
    datos.open(path.c_str());


    //Lectura del tipo de grafo
    string dir_aux;
    datos>>n_nodos>>n_arcos>>dir_aux;
    string d_str("D");
    if(dir_aux.compare(d_str)==0) dirigido=true;
    else dirigido=false;

    //Inicializacion del grafo

    for(int i=0;i<n_nodos;i++) this->push_back(Nodo(i));

    //Lectura de arcos
    int origen, destino, peso;
    if(dirigido){
        for(int i=0;i<n_arcos;i++){
            datos>>origen>>destino>>peso;
            if(datos.eof()) break;
            this->at(origen).arcos_salida.push_back(Arco(destino, peso));
        }
    }
    else{
        for(int i=0;i<n_arcos;i++){
            datos>>origen>>destino>>peso;
            if(datos.eof()) break;
            this->at(origen).arcos_salida.push_back(Arco(destino, peso));
            this->at(destino).arcos_salida.push_back(Arco(origen, peso));
        }
    }
}

Grafo::~Grafo() {
    // TODO Auto-generated destructor stub
}

void Grafo::dibujar(){
    if(coordenadas.size()==0) generarCoordenadas();

    //Establecer tamano de la ventana
    QApplication app(int_arg, char_arg);
    QGraphicsScene scene;
    float min_x=numeric_limits<float>::max();
    float min_y=numeric_limits<float>::max();
    float max_x=numeric_limits<float>::min();
    float max_y=numeric_limits<float>::min();
    for(int i=0;i<n_nodos;i++){
        if(min_x>coordenadas[i].first) min_x=coordenadas[i].first;
        if(min_y>coordenadas[i].second) min_y=coordenadas[i].second;
        if(max_x<coordenadas[i].first) max_x=coordenadas[i].first;
        if(max_y<coordenadas[i].second) max_y=coordenadas[i].second;
    }
    scene.setSceneRect( min_x-50.0,min_y-50.0, max_x-min_x+100, max_y-min_y+100 );


    //Dibujar grafo
    for(int i=0;i<n_nodos;i++){
        QGraphicsEllipseItem *item=new QGraphicsEllipseItem(coordenadas[i].first,coordenadas[i].second, 20.0,20.0);
        QGraphicsTextItem * label = new QGraphicsTextItem;
        label->setPos(coordenadas[i].first,coordenadas[i].second);
        label->setPlainText(QString::number(i));
        scene.addItem(item);
        scene.addItem(label);

        list<Arco> arcos=this->at(i).arcos_salida;
        for(list<Arco>::iterator it=arcos.begin();it!=arcos.end();it++){
            pair< pair<float,float>, pair<float,float> > extremos_recta= obtenerArco(coordenadas[i].first, coordenadas[i].second,
                                                          coordenadas[it->nodo_destino].first,coordenadas[it->nodo_destino].second);
            QGraphicsLineItem *line=new QGraphicsLineItem(extremos_recta.first.first,extremos_recta.first.second, extremos_recta.second.first, extremos_recta.second.second);
            scene.addItem(line);
        }
    }

    QGraphicsView view( &scene );
    view.setRenderHints( QPainter::Antialiasing );
    view.show();
    app.exec();


}

vector<int> Grafo::BFS(int nodo_origen){
    //Inicializar todos los nodos como no visitados y sin establecer quien es su padre
    bool visitado[n_nodos];
    vector<int>padre;
    for(int i=0;i<n_nodos;i++){
        visitado[i]=false;
        padre.push_back(-1);
    }

    //Inicializar el nodo origen como visitado e inicializar la cola
    visitado[nodo_origen]=true;
    padre.push_back(nodo_origen);
    queue<int> nodos_explorar;
    nodos_explorar.push(nodo_origen);

    //Inicia el algoritmo de busqueda
    while(!nodos_explorar.empty()){
        int sel_nodo=nodos_explorar.front();
        nodos_explorar.pop();

        //Explorar los nodos adyacentes
        list<Arco> adyacentes=this->at(sel_nodo).arcos_salida;
        for(list<Arco>::iterator it=adyacentes.begin();it!=adyacentes.end();it++){
            if(!visitado[it->nodo_destino]){
                visitado[it->nodo_destino]=true;
                padre[it->nodo_destino]=sel_nodo;
                nodos_explorar.push(it->nodo_destino);
            }
        }
    }

    return padre;
}

vector<int> Grafo::DFS(int nodo_origen){
    //Exploracion sobre el grafo completo

    //Inicializar todos los nodos como no visitados y sin establecer quien es su padre
    bool visitado[n_nodos];
    vector<int>padre;
    for(int i=0;i<n_nodos;i++){
        visitado[i]=false;
        padre.push_back(-1);
    }

    //Inicializar el nodo origen como visitado e inicializar la cola
    visitado[nodo_origen]=true;
    padre.push_back(nodo_origen);
    stack<int> nodos_explorar;
    nodos_explorar.push(nodo_origen);

    //Inicia el algoritmo de busqueda
    while(!nodos_explorar.empty()){
        int sel_nodo=nodos_explorar.top();
        nodos_explorar.pop();

        //Explorar los nodos adyacentes
        list<Arco> adyacentes=this->at(sel_nodo).arcos_salida;
        for(list<Arco>::iterator it=adyacentes.begin();it!=adyacentes.end();it++){
            if(!visitado[it->nodo_destino]){
                visitado[it->nodo_destino]=true;
                padre[it->nodo_destino]=sel_nodo;
                nodos_explorar.push(it->nodo_destino);
            }
        }
    }

    return padre;
}

pair<list<list<int> > ,vector<int > > Grafo::componentesConexas(){
    //Basado en BFS
    //Retorna una lista de componentes conexas y el bosque generado por el BFS

    //Inicializar todos los nodos como no visitados y sin establecer quien es su padre
    bool visitado[n_nodos];
    vector<int>padre;
    for(int i=0;i<n_nodos;i++){
        visitado[i]=false;
        padre.push_back(-1);
    }

    int sel_nodo, nodo_origen;
    queue<int> nodos_explorar;
    list<list<int> > componentes_conexas;
    list<int> _componente;

    while(true){
        //Selecciona como nodo origen el nodo no visitado con mas arcos de salida
        int mayor=-1;
        nodo_origen=-1;
        int n_arcos;
        for(int i=0;i<n_nodos;i++){
            if(!visitado[i]){
                n_arcos=this->at(i).arcos_salida.size();
                if(n_arcos>mayor){
                    mayor=n_arcos;
                    nodo_origen=i;
                }
            }
        }
        if(nodo_origen==-1) break;

        //Inicializar el nodo origen como visitado e inicializar la cola
        visitado[nodo_origen]=true;
        padre[nodo_origen]=nodo_origen;
        nodos_explorar.push(nodo_origen);
        _componente.push_back(nodo_origen);

        //Inicia el algoritmo de busqueda
        while(!nodos_explorar.empty()){
            sel_nodo=nodos_explorar.front();
            nodos_explorar.pop();

            //Explorar los nodos adyacentes
            list<Arco> adyacentes=this->at(sel_nodo).arcos_salida;
            for(list<Arco>::iterator it=adyacentes.begin();it!=adyacentes.end();it++){
                if(!visitado[it->nodo_destino]){
                    visitado[it->nodo_destino]=true;
                    padre[it->nodo_destino]=sel_nodo;
                    nodos_explorar.push(it->nodo_destino);
                    _componente.push_back(it->nodo_destino);
                }
            }
        }
        componentes_conexas.push_back(_componente);
        _componente.clear();
    }

    pair<list<list<int> > ,vector<int > > componentes_bosque;
    componentes_bosque.first=componentes_conexas;
    componentes_bosque.second=padre;
    return componentes_bosque;
}

void Grafo::generarCoordenadas(){
    //Encontrar componentes conexas
    pair<list<list<int> > ,vector<int > > componentes_bosque=componentesConexas();
    vector<int > arboles=componentes_bosque.second;

    //Decidir las coordenadas polares de cada nodo
    pair<int,int> pair_aux (0,0);
    for(int i=0;i<n_nodos;i++) coordenadas.push_back(pair_aux);

    list<int> padres;
    for(int i=0;i<n_nodos;i++){
        if(arboles[i]==i){
            padres.push_back(i);
        }
    }

    list<NodoGrafo*> padres_grafo;
    queue<NodoGrafo*> nodos_explorar;
    int n_cconexas=padres.size();
    if(n_cconexas==1){
        //El grafo es conexo
        float angulo=180;
        if(this->at(padres.front()).arcos_salida.size()>1) angulo=360;
        NodoGrafo* _nodo=new NodoGrafo(padres.front(),0,0,angulo);
        padres_grafo.push_back(_nodo);
        nodos_explorar.push(_nodo);
    }
    else{
        //El grafo no es conexo
        int max_anterior=0;
        for(list<int>::iterator it=padres.begin();it!=padres.end();it++){
            //Establecer las coordenadas polares de las raices de cada arbol
            NodoGrafo* _nodo=new NodoGrafo(*it,50,max_anterior, max_anterior+360.0/float (n_cconexas));
            padres_grafo.push_back(_nodo);
            max_anterior+=360.0/float (n_cconexas);
            nodos_explorar.push(_nodo);
        }
    }

    //Establecer coordenadas polares del resto de los nodos
    while(!nodos_explorar.empty()){

        NodoGrafo* nodo_sel=nodos_explorar.front();
        nodos_explorar.pop();

        //Establecer las coordenadas polares del resto de los nodos del arbol
        for(int i=0;i<n_nodos;i++){
            if(arboles[i]==nodo_sel->getID() && i!=nodo_sel->getID()){
                NodoGrafo* nuevo_hijo=new NodoGrafo(i,nodo_sel);
                nodo_sel->setHijo(nuevo_hijo);
                nodos_explorar.push(nuevo_hijo);
            }
        }
        nodo_sel->establecerConosHijos();
        coordenadas[nodo_sel->getID()]=nodo_sel->getRectCoordenadas();
    }
}

void Grafo::toLatex(){
    if(coordenadas.size()==0) generarCoordenadas();

    string archivo=char_arg[1];
    archivo+=".tex";
    ofstream salida(archivo.c_str());

    salida<<"\\usepackage{tikz}"<<endl;
    salida<<"\\resizebox{\\textwidth}{!}{"<<endl;
    salida<<"\t\\begin{tikzpicture}"<<endl;

    //Generar nodos
    salida<<"\t\t%Nodos"<<endl;
    for(int i=0;i<n_nodos;i++) salida<<"\t\t\\node [draw,circle] (nodo"<<i<<") at ("<<coordenadas[i].first/50.0<<","<<coordenadas[i].second/50.0<<") {"<<i<<"};"<<endl;

    //Generar arcos
    salida<<"\n\t\t%Arcos"<<endl;
    list<Arco> arcos;
    for(int i=0;i<n_nodos;i++){
        arcos=this->at(i).arcos_salida;
        for(list<Arco>::iterator it=arcos.begin(); it!=arcos.end();it++){
            if(dirigido) salida<<"\t\t\\draw[->] (nodo"<<i<<")--(nodo"<<it->nodo_destino<<");"<<endl;
            else if(i<it->nodo_destino) salida<<"\t\t\\draw[-] (nodo"<<i<<")--(nodo"<<it->nodo_destino<<");"<<endl;
        }
    }
    salida<<"\\end{tikzpicture}\n}";

    cout<<"Archivo "<<archivo<<" generado"<<endl;
}

float Grafo::calcularDensidad(){
    if(dirigido) return float(2.0*n_arcos)/float(n_nodos*(n_nodos-1));
    return float(n_arcos)/float(n_nodos*(n_nodos-1));
}
} /* namespace std */
