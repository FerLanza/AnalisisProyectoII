#pragma once

/*
 * Tramo.h
 *
 *  Created on: 31 ene. 2021
 *      Author: ferla
 */

#ifndef TRAMO_H_
#define TRAMO_H_

struct Camino {

	int kmStart;
	int kmEnd;
	int firmeza;
	int humedad;
	int agarre;

	Camino() {
		this->kmStart = 0;
		this->kmEnd = 0;
		this->firmeza = 0;
		this->humedad = 0;
		this->agarre = 0;
	}

	Camino(int pKmStart, int pKmEnd, int pFirmeza, int pHumedad, int pAgarre) {
		this->kmStart = pKmStart;
		this->kmEnd = pKmEnd;
		this->firmeza = pFirmeza;
		this->humedad = pHumedad;
		this->agarre = pAgarre;
	}
};




#endif /* TRAMO_H_ */
