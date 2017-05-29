/*
 * DistribucionesProbabilidad.h
 *
 *  Created on: 23/05/2017
 *      Author: pamela
 */

#ifndef DISTRIBUCIONESPROBABILIDAD_H_
#define DISTRIBUCIONESPROBABILIDAD_H_

#include <cstdlib>
#include <cmath>

using namespace std;

int uniformeDiscreta(int lim_inferior, int lim_superior){
	return rand()%(lim_superior-lim_inferior+1)+lim_inferior;
}

float uniformeContinua(float lim_inferior, float lim_superior){
	return (lim_superior-lim_inferior)*(float(rand())/ float (RAND_MAX))+lim_inferior;
}

float normal(float media, float desv_std){
	float u011=uniformeContinua(0,1);
	float u012=uniformeContinua(0,1);
	float n01=sqrt(-2*log(u011))*cos(2*3.14159*u012);
	return media+desv_std*(n01);
}

float numeroAleatorio(int dist_prob, float arg1, float arg2){
	switch(dist_prob){
	case 1:{
		return uniformeDiscreta(arg1, arg2);
	}
	case 2:{
		return uniformeContinua(arg1, arg2);
	}
	case 3:{
		return normal(arg1, arg2);
	}
	}
	return 0;
}


#endif /* DISTRIBUCIONESPROBABILIDAD_H_ */
