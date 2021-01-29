
/*
 * main.cpp
 *
 *  Created on: 6 ene. 2021
 *      Author: dylan
 */

#include "Camion.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>

#include "../../Progra_II/nlohmann/json.hpp"

 // for convenience
using json = nlohmann::json;
using namespace std;

// Hilos en teoria
#include <vector>
#include <numeric>
#include <cmath>
#include <sstream>
#include <chrono>
#include <mutex>


CamionTorque* camionesT[256];
CamionPliegue* camionesP[256];


/*
 *
 * */
void threadReader() {

}


/*
 *
 * */
void algorGenetico() {

}
void mutacion(CamionTorque pCamion) {
	srand(time(0));
	int position = (rand() % 8);
	pCamion.Cromosoma ^= 1 << position;
}


/*
 *
 * */
double energyCalcTorque(int value) {
	double resultado;

	if (value <= 102) {
		resultado = (2 * (value / 102)) + 4;
		if (resultado >= 5) {
			resultado++;
		}
		else {
			resultado--;
		}
	}
	if (102 < value && value <= 179) {

		resultado = (2 * ((value - 102) / (179 - 102))) + 6;
	}
	if (179 < value && value <= 230) {

		resultado = (2 * ((value - 179) / (230 - 179))) + 8;
	}
	else {
		resultado = (2 * ((value - 230) / (256 - 230))) + 10;
		if (resultado >= 11) {
			resultado++;
		}
		else {
			resultado--;
		}
	}

	return resultado;
}


/*
 *
 * */
double energyCalcPliegue(int value) {
	double resultado;

	if (value <= 102) {
		resultado = (2.25 * (value / 102)) + 6;

	}
	if (102 < value && value <= 179) {
		resultado = (2.25 * ((value - 102) / (179 - 102))) + 8.25;
		if (resultado >= 9) {
			resultado++;
		}
		else {
			resultado--;
		}
	}
	if (179 < value && value <= 230) {
		resultado = (2.25 * ((value - 179) / (230 - 179))) + 10.5;
		if (resultado >= 11) {
			resultado++;
		}
		else {
			resultado--;
		}
	}
	else {
		resultado = (2.25 * ((value - 230) / (256 - 230))) + 12.75;
		if (resultado >= 14) {
			resultado++;
		}
		else {
			resultado--;
		}
	}

	return resultado;
}


/*
 *
 * */
int calcTorque(double pEnergia) {
	int energia = (int)round(pEnergia);
	int resultado;

	switch (energia) {
	case 4:
		resultado = 7;
		break;
	case 6:
		resultado = 6;
		break;
	case 7:
		resultado = 5;
		break;
	case 8:
		resultado = 4;
		break;
	case 9:
		resultado = 3;
		break;
	case 10:
		resultado = 2;
		break;
	case 12:
		resultado = 1;
		break;
	default:
		cout << "Fallo en la evaluacion del nivel de Torque" << endl;
		resultado = 0;
		break;
	}

	return resultado;
}


/*
 *
 * */
int calcPliegue(double pEnergia) {
	int energia = (int)round(pEnergia);
	int resultado;

	switch (energia) {
	case 6:
		resultado = 4;
		break;
	case 7:
		resultado = 5;
		break;
	case 8:
		resultado = 6;
		break;
	case 10:
		resultado = 7;
		break;
	case 11:
		resultado = 8;
		break;
	case 13:
		resultado = 9;
		break;
	case 15:
		resultado = 10;
		break;
	default:
		cout << "Fallo en la evaluacion del nivel de Torque" << endl;
		resultado = 0;
		break;
	}

	return resultado;
}


/*
 *
 * */
void newTruck() {
	srand(time(0));
	int r = (rand() % 256) + 1;
	double Torque = energyCalcTorque(r);
	double Pliegue = energyCalcPliegue(r);

	camionesT[r] = new CamionTorque(calcTorque(r), Torque, r);
	camionesP[r] = new CamionPliegue(calcPliegue(r), Pliegue, r);

}



int main() {

	//std::thread first (threadReader);
	//std::thread second (algorGenetico);



	//first.join();
	//second.join();

}

