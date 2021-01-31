/*
 * header.h
 *
 *  Created on: 6 ene. 2021
 *      Author: dylan
 */

#ifndef CAMION_H_
#define CAMION_H_

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdio.h>

struct CamionTorque{
	int torque;
	int energia;
	int cromosoma;
	double apto;
	CamionTorque(int pTorque, int pEnergia, int pCromosoma){
		this->torque = pTorque;
		this->energia = pEnergia;
		this->cromosoma = pCromosoma;
		this->apto = 0;
	}
};

struct CamionPliegue{
	int pliegue;
	int energia;
	int cromosoma;
	double apto;
	CamionPliegue(int pPliegue, int pEnergia, int pCromosoma){
		this->pliegue = pPliegue;
		this->energia = pEnergia;
	    this->cromosoma = pCromosoma;
	    this-> apto = 0;
	}
};




#endif /* CAMION_H_ */
