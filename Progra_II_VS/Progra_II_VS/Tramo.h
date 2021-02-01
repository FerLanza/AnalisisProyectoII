#pragma once

/*
 * Tramo.h
 *
 *  Created on: 31 ene. 2021
 *      Author: ferla
 */

#ifndef TRAMO_H_
#define TRAMO_H_

/* Objeto en el cual se cargan los datos provenientes del .json
 *		Usado dentro del stack principalmente
 */
struct Camino {

	int kmStart = 0;
	int kmEnd = 0;
	int firmeza = 0;
	int humedad = 0;
	int agarre = 0;

};


#endif /* TRAMO_H_ */
