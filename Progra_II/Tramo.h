/*
 * Tramo.h
 *
 *  Created on: 31 ene. 2021
 *      Author: ferla
 */

#ifndef TRAMO_H_
#define TRAMO_H_

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdio.h>

struct Camino{

	int kmStart;
	int kmEnd;
	int firmeza;
	int humedad;
	int agarre;

	Camino(int pKmStart,int pKmEnd, int pFirmeza, int pHumedad, int pAgarre){
		this->kmStart = pKmStart;
		this->kmEnd = pKmEnd;
		this->firmeza = pFirmeza;
		this->humedad = pHumedad;
		this->agarre = pAgarre;
	}
};




#endif /* TRAMO_H_ */
