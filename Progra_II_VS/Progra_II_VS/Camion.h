/*
 * header.h
 *
 *  Created on: 6 ene. 2021
 *      Author: dylan
 */

#pragma once

#ifndef HEADER_H_
#define HEADER_H_

struct CamionTorque {
	int torque;
	int energia;
	int cromosoma;
	double apto;
	CamionTorque(int pTorque, int pEnergia, int pCromosoma) {
		this->torque = pTorque;
		this->energia = pEnergia;
		this->cromosoma = pCromosoma;
		this->apto = 0;
	}
};

struct CamionPliegue {
	int pliegue;
	int energia;
	int cromosoma;
	double apto;
	CamionPliegue(int pPliegue, int pEnergia, int pCromosoma) {
		this->pliegue = pPliegue;
		this->energia = pEnergia;
		this->cromosoma = pCromosoma;
		this->apto = 0;
	}
};

#endif /* HEADER_H_ */