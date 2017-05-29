//============================================================================
// Name        : busqueda_binaria.cpp
// Author      : Pamela Jocelyn Palomo Martinez
//============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

vector<int> generar_vector(int);
void imprimir_vector(vector<int>);
bool busqueda(int, int, int, vector<int>);
pair<int,bool> busqueda_i(int, int, int, vector<int>);
pair<int,bool> fuerza_bruta(int,vector<int>);

int main(int argc, char** argv) {
	srand(time(NULL));
	int numero_elementos=atoi(argv[1]);

	vector<int> _vector=generar_vector(numero_elementos);
	imprimir_vector(_vector);

	string path_tb("true_bs.txt");
	string path_fb("false_bs.txt");
	string path_tf("true_bf.txt");
	string path_ff("false_bf.txt");
	ofstream data_tb;
	data_tb.open(path_tb.c_str(), ofstream::out | ios::app);
	ofstream data_fb;
	data_fb.open(path_fb.c_str(), ofstream::out | ios::app);
	ofstream data_ff;
	data_ff.open(path_ff.c_str(), ofstream::out | ios::app);
	ofstream data_tf;
	data_tf.open(path_tf.c_str(), ofstream::out | ios::app);

	float promedio_bint=0;
	float promedio_binf=0;
	float promedio_brutet=0;
	float promedio_brutef=0;
	for(int i=0;i<10;i++){
		//Resultado true
		int elemento_buscar=_vector[rand()%numero_elementos];
		pair<int,bool> resultadot_bs=busqueda_i(elemento_buscar,0,_vector.size()-1,_vector);
		promedio_bint+=resultadot_bs.first;
		pair<int,bool> resultadot_bf=fuerza_bruta(elemento_buscar,_vector);
		promedio_brutet+=resultadot_bf.first;

		//Resultado false
		elemento_buscar=_vector.back()+1;
		pair<int,bool> resultadof_bs=busqueda_i(elemento_buscar,0,_vector.size()-1,_vector);
		promedio_binf+=resultadof_bs.first;
		pair<int,bool> resultadof_bf=fuerza_bruta(elemento_buscar,_vector);
		promedio_brutef+=resultadof_bf.first;
	}

	promedio_bint/=10.0;
	promedio_binf/=10.0;
	promedio_brutet/=10.0;
	promedio_brutef/=10.0;

	data_tb<<promedio_bint<<endl;
	data_fb<<promedio_binf<<endl;
	data_ff<<promedio_brutef<<endl;
	data_tf<<promedio_brutet<<endl;

	return 0;
}

vector<int> generar_vector(int numero_elementos){
	vector<int> _vector(numero_elementos);
	_vector[0]=rand()%10;
	for(int i=1;i<numero_elementos;i++){
		_vector[i]=_vector[i-1]+rand()%10+1;
	}

	return _vector;
}

void imprimir_vector(vector<int> _vector){
	for(int i=0;i<_vector.size(); i++){
		cout<<_vector[i]<<" ";
	}
	cout<<endl;
}

bool busqueda(int elemento_buscar, int min, int max, vector<int> _vector){
	if(min==max){
		if(_vector[min]==elemento_buscar) return true;
		return false;
	}
	int mitad=ceil(min+(max-min)/2.0);

	if(_vector[mitad]==elemento_buscar) return true;
	if(_vector[mitad]<elemento_buscar){
		return busqueda(elemento_buscar,mitad+1,max,_vector);
	}
	if(_vector[mitad]>elemento_buscar){
		return busqueda(elemento_buscar,min,mitad-1,_vector);
	}
}

pair<int,bool> busqueda_i(int elemento_buscar, int min, int max, vector<int> _vector){
	int numero_comparaciones=0;
	while(min<max){
		numero_comparaciones++;
		int mitad=ceil(min+(max-min)/2.0);
		if(_vector[mitad]==elemento_buscar) return pair<int,bool>(numero_comparaciones,true);
		numero_comparaciones++;
		if(_vector[mitad]<elemento_buscar){
			min=mitad+1;
		}
		else{
			max=mitad-1;
		}
	}
	numero_comparaciones++;
	if(_vector[min]==elemento_buscar) return pair<int,bool>(numero_comparaciones,true);
	return pair<int,bool>(numero_comparaciones,false);
}

pair<int,bool> fuerza_bruta(int elemento_buscar,vector<int> _vector){
	int numero_comparaciones=0;
	for(vector<int>::iterator it=_vector.begin();it!=_vector.end();it++){
		numero_comparaciones++;
		if(*it==elemento_buscar) return pair<int,bool>(numero_comparaciones,true);
	}
	return pair<int,bool>(numero_comparaciones,false);
}
