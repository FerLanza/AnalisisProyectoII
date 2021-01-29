/*
 * header.h
 *
 *  Created on: 6 ene. 2021
 *      Author: dylan
 */

#pragma once

#ifndef HEADER_H_
#define HEADER_H_

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdio.h>

struct CamionTorque {
	int Torque;
	double Energia;
	char Cromosoma;
	CamionTorque(int pTorque, double pEnergia, char pCromosoma) {
		this->Torque = pCromosoma;
		this->Energia = pEnergia;
		this->Cromosoma = pCromosoma;
	}
};

struct CamionPliegue {
	int Pliegue;
	double Energia;
	char Cromosoma;
	CamionPliegue(int pPliegue, double pEnergia, char pCromosoma) {
		this->Pliegue = pCromosoma;
		this->Energia = pEnergia;
		this->Cromosoma = pCromosoma;
	}
};




#endif /* HEADER_H_ */