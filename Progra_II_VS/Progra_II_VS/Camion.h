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
	int torque;
	int energia;
	int cromosoma;
	CamionTorque(int pTorque, int pEnergia, int pCromosoma) {
		this->torque = pTorque;
		this->energia = pEnergia;
		this->cromosoma = pCromosoma;
	}
};

struct CamionPliegue {
	int pliegue;
	int energia;
	int cromosoma;
	CamionPliegue(int pPliegue, int pEnergia, int pCromosoma) {
		this->pliegue = pPliegue;
		this->energia = pEnergia;
		this->cromosoma = pCromosoma;
	}
};




#endif /* HEADER_H_ */