//============================================================================
// Name        : quickSort.cpp
// Author      : Pamela Jocelyn Palomo Martinez
// Description : Quick sort
//============================================================================

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cstdio>
#include <fstream>

using namespace std;

//#define DEBUG 1
int n_operaciones=0;

void quickSort(vector<int>&, int, int);

int main(int argc, char** argv) {
	int numero_elementos=atoi(argv[1]);

	//Crear arreglo
	srand(time(NULL));

	float promedio=0;
	for(int i=0;i<10;i++){
		n_operaciones=0;

		vector<int> arreglo;
		for(int i=0;i<numero_elementos;i++){
			arreglo.push_back(rand()%100);

		}

		//Ordenar arreglo
		quickSort(arreglo,0,numero_elementos-1);

		for(int i=0;i<numero_elementos;i++) cout<<arreglo[i]<<" ";
		cout<<endl;

		promedio+=float(n_operaciones)/10.0;
	}

	ofstream output("resultados.txt", ofstream::out | ios::app);
	output<<numero_elementos<<"\t"<<promedio<<endl;


	return 0;
}

void quickSort(vector<int> &arreglo, int start, int end){
#ifdef DEBUG
	cout<< start <<" "<< end <<endl;
#endif
	if(start >= end) return;

	//Elegir pivote
	int pos = rand()%(end + 1 - start) + start;
    int pivote = arreglo[pos];
	arreglo[pos] = arreglo[start];
	arreglo[start] = pivote;
	n_operaciones=n_operaciones+4;

#ifdef DEBUG
	cout<<pivote<<endl;
	for(int i=start;i<=end;i++) cout<<arreglo[i]<<" ";
	cout<<endl;
#endif

	//Comienzo del algoritmo
	int izq = start + 1;
	n_operaciones++;
	while (arreglo[izq] == pivote){
		n_operaciones++;
		izq++;
	}
	if (izq > end){
		n_operaciones++;
		return;
	}
	int der = end;
	n_operaciones++;
	while (1) {
		while(arreglo[izq] <= pivote && izq <= end){
			izq++;
			n_operaciones+=3;
		}
		while(arreglo[der] > pivote && der >= start){
			der--;
			n_operaciones+=3;
		}
		if (izq < der) {
#ifdef DEBUG
			cout << "swap " << arreglo[izq] << " con " << arreglo[der] << endl;
#endif
			int aux = arreglo[der];
			arreglo[der] = arreglo[izq];
			arreglo[izq] = aux;
			n_operaciones+=3;
		} else
			break;
	}
	quickSort(arreglo,start,izq-1);
#ifdef DEBUG
	cout << "menores ";
	for(int i=start;i<izq;i++) cout<<arreglo[i]<<" ";
	cout<<endl;
	cout << "mayores ";
	for(int i=izq;i<=end;i++) cout<<arreglo[i]<<" ";
	cout<<endl;
#endif
	//getchar();
	quickSort(arreglo,izq,end);
}
