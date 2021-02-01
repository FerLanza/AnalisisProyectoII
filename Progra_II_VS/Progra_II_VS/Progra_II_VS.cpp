
/*
 * main.cpp
 *
 *  Created on: 6 ene. 2021
 *      Author: dylan
 */

#include "Camion.h"
#include "JsonReader.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <cmath>
#include <thread>
#include <chrono>
#include <mutex>

#include <bitset>
#include <stack>
#include <list>

using namespace std;
using std::bitset;

// Hilos en teoria
#include <vector>
#include <numeric>
#include <sstream>

//CamionTorque* camionesT[256];
//CamionPliegue* camionesP[256];

list<CamionTorque*> camionesT;
list<CamionPliegue*> camionesP;

Camino road;
bool hiloReader = true;
bool hiloGenetico = false;

/*
 *
 */
stack<Camino> loadFiles() {
	fileReader();
	return stackCreator();
}


/*
 *
 * */
void threadReader() {
	stack<Camino> rutas = loadFiles();

	Camino tmp;
	rutas.pop();

	while (true) {
		if (hiloReader) {
			if (rutas.size() != 0) {
				tmp = rutas.top();
				road.kmStart = tmp.kmStart;
				road.kmEnd = tmp.kmEnd;
				road.firmeza = tmp.firmeza;
				road.humedad = tmp.humedad;
				road.agarre = tmp.agarre;
				rutas.pop();
				hiloReader = false;
				hiloGenetico = true;
			}
		}
	}
}


/*
 *
 * */
void algorGenetico() {

}

/*
 *Input:
 *Output: cambia el atributo que indica la adaptabilidad.
 *Funcion:calcula los km que se recorren en el tramo , seguidamente realiza una operacion que calcula que tan apto es el camion
 *esto se logra por medio de un promedio de las energias de los torques a los cuales entra cada atributo del tramo esto entre la energia del
 *camion por los km que debe recorrer.
 */
void fitnessTorque(CamionTorque pCamion, Camino pCamino, int pEnergiaFirmeza, int pEnergiaHumedad, int pEnergiaAgarre) {
	int kmRecorridos = pCamino.kmEnd - pCamino.kmStart;

	double adaptabilidad = (((((double)pEnergiaFirmeza + (double)pEnergiaHumedad + (double)pEnergiaAgarre) / 3) * (double)kmRecorridos)
		/ ((double)pCamion.energia * (double)kmRecorridos));

	pCamion.apto = adaptabilidad;
}

/*
 *Input:
 *Output: cambia el atributo que indica la adaptabilidad.
 *Funcion:calcula los km que se recorren en el tramo , seguidamente realiza una operacion que calcula que tan apto es el camion
 *esto se logra por medio de un promedio de las energias de los pliegues a los cuales entra cada atributo del tramo esto entre la energia del
 *camion por los km que debe recorrer.
 */
void fitnessPliegue(CamionPliegue pCamion, Camino pCamino, int pEnergiaFirmeza, int pEnergiaHumedad, int pEnergiaAgarre) {
	int kmRecorridos = pCamino.kmEnd - pCamino.kmStart;

	double adaptabilidad = (((((double)pEnergiaFirmeza + (double)pEnergiaHumedad + (double)pEnergiaAgarre) / 3) * (double)kmRecorridos)
		/ ((double)pCamion.energia * (double)kmRecorridos));

	pCamion.apto = adaptabilidad;
}

/*
 *Input: objeto tipo camionTorque.
 *Output: cromosoma nuevo en el camion que ingreso.
 *Funcion:Realizar la mutacion del cromosoma, por medio de una selecciona random del bit
 *y le realiza un not.
 */
void mutacionTorque(CamionTorque pCamion) {
	srand(time(0));
	int position = (rand() % 8);
	bitset<8> cromosoma(pCamion.cromosoma);
	if (cromosoma[position] == 1) {
		cromosoma.reset(position);
		pCamion.cromosoma = cromosoma.to_ulong();
	}
	else {
		cromosoma.set(position);
		pCamion.cromosoma = cromosoma.to_ulong();
	}

}

/*
 *Input: un objeto tipo camionPliegue
 *Output:cromosoma nuevo en el camion que ingreso
 *Funcion:Realizar la mutación del cromosoma, por medio de una selección random del bit
 *y le realiza un not.
 */
void mutacionPliegue(CamionPliegue pCamion) {
	srand(time(0));
	int position = (rand() % 8);
	bitset<8> cromosoma(pCamion.cromosoma);
	if (cromosoma[position] == 1) {
		cromosoma.reset(position);
		pCamion.cromosoma = cromosoma.to_ulong();
	}
	else {
		cromosoma.set(position);
		pCamion.cromosoma = cromosoma.to_ulong();
	}

}

/*
 *Input: dos objetos tipo CamionTorque uno se considera la madre y el otro el padre.
 *Output: un int que representa el cromosoma del hijo
 *Funcion:Combinar ambos bytes para crear un hijo.
 */
int combinacionTorque(CamionTorque pCamionMama, CamionTorque pCamionPapa) {
	srand(time(0));
	int cantidadMama = (rand() % 5);
	int cantidadPapa = 8 - cantidadMama;
	bitset<8> cromosomaMama(pCamionMama.cromosoma);
	bitset<8> cromosomaPapa(pCamionPapa.cromosoma);
	bitset<8> cromosomaHijo(0);

	int position = 0;
	for (position; position < cantidadMama; position++) {
		if (cromosomaMama[position] == 1) {
			cromosomaHijo.set(position);
		}
	}
	for (position; position < cantidadPapa; position++) {
		if (cromosomaPapa[position] == 1) {
			cromosomaHijo.set(position);
		}
	}
	return cromosomaHijo.to_ulong();
}

/*
 *Input: dos objetos tipo CamionPliegue uno se considera la madre y el otro el padre.
 *Output: un int que representa el cromosoma del hijo
 *Funcion:Combinar ambos bytes para crear un hijo.
 */
int combinacionPliegue(CamionPliegue pCamionMama, CamionPliegue pCamionPapa) {
	srand(time(0));
	int cantidadMama = (rand() % 5);
	int cantidadPapa = 8 - cantidadMama;
	bitset<8> cromosomaMama(pCamionMama.cromosoma);
	bitset<8> cromosomaPapa(pCamionPapa.cromosoma);
	bitset<8> cromosomaHijo(0);

	int position = 0;
	for (position; position < cantidadMama; position++) {
		if (cromosomaMama[position] == 1) {
			cromosomaHijo.set(position);
		}
	}
	for (position; position < cantidadPapa; position++) {
		if (cromosomaPapa[position] == 1) {
			cromosomaHijo.set(position);
		}
	}
	return cromosomaHijo.to_ulong();
}

/*
 *Input: un int que representa el valor de energia en el genotipo
 *Output: el valor de la energia correspondiente segun la tabla brindada.
 *Funcion:pasa la energia de su valor de genotipo al fenotipo en el caso del torque .
 */
double energyCalcTorque(int value) {
	double resultado;

	if (value <= 102) {
		resultado = (2 * (value / 102)) + 4;
		if (resultado >= 5 && round(resultado) == 5) {
			resultado++;
		}
		if (resultado <= 5 && round(resultado) == 5) {
			resultado--;
		}
	}
	else if (102 < value && value <= 179) {

		resultado = (2 * ((value - 102) / (179 - 102))) + 6;
	}
	else if (179 < value && value <= 230) {

		resultado = (2 * ((value - 179) / (230 - 179))) + 8;
	}
	else {
		resultado = (2 * ((value - 230) / (256 - 230))) + 10;
		if (resultado >= 11 && round(resultado) == 11) {
			resultado++;
		}
		if (resultado <= 11 && round(resultado) == 11) {
			resultado--;
		}
	}

	resultado = round(abs(resultado));
	cout << "torque entrada " << resultado << endl;
	return resultado;
}

/*
 *Input: un int que representa el valor de energia en el genotipo
 *Output: el valor de la energia correspondiente segun la tabla brindada.
 *Funcion:pasa la energia de su valor de genotipo al fenotipo en el caso del pliegue
 */
double energyCalcPliegue(int value) {
	double resultado;

	if (value <= 102) {
		resultado = (2.25 * (value / 102)) + 6;

	}
	else if (102 < value && value <= 179) {
		resultado = (2.25 * ((value - 102) / (179 - 102))) + 8.25;
		if (resultado >= 9 && round(resultado) == 9) {
			resultado++;
		}
		if (resultado <= 9 && round(resultado) == 9) {
			resultado--;
		}
	}
	else if (179 < value && value <= 230) {
		resultado = (2.25 * ((value - 179) / (230 - 179))) + 10.5;
		if (resultado >= 12 && round(resultado) == 12) {
			resultado++;
		}
		if (resultado <= 12 && round(resultado) == 12) {
			resultado--;
		}
	}
	else {
		resultado = (2.25 * ((value - 230) / (256 - 230))) + 12.75;
		if (resultado >= 14 && round(resultado) == 14) {
			resultado++;
		}
		if (resultado <= 14 && round(resultado) == 14) {
			resultado--;
		}
	}
	resultado = round(abs(resultado));
	cout << "pliegue entrada " << resultado << endl;
	return resultado;
}

/*
 *Input: int que representa el valor de la energia segun el fenotipo
 *Output: int representando el valor del torque al que corresponde la energia.
 *Funcion:Calcular el torque segun la energia ingresada.
 */
int calcularTorque(int pEnergia) {
	cout << "Redondeo energia en Torque " << pEnergia << endl;
	int resultado;

	switch (pEnergia) {
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
 *Input: int que representa el valor de la energia segun el fenotipo
 *Output: int representando el valor del torque al que corresponde la energia.
 *Funcion:Calcular el pliegue segun la energia ingresada.
 */
int calcularPliegue(int pEnergia) {
	cout << "Redondeo energia en pliegue " << pEnergia << endl;
	int resultado;

	switch (pEnergia) {
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
		cout << "Fallo en la evaluacion del nivel de pliegue" << endl;
		resultado = 0;
		break;
	}

	return resultado;
}


/*
 *Input: un int que representa la cantidad de camiones por crear.
 *Output:Los arrays llenos de objetos.
 *Funcion:Crear nuevos camiones y guardarlos en los arrays.
 */
void newTrucks(int pCantidadCamiones) {
	srand(time(0));

	list<CamionTorque*> ::iterator it = camionesT.begin();
	list<CamionPliegue*> ::iterator it2 = camionesP.begin();
	for (int position = 0; position < pCantidadCamiones; position++) {

		int cromosoma = (rand() % 256);
		cout << cromosoma << endl;
		int torque = energyCalcTorque(cromosoma);
		cout << "torque salida " << torque << endl;
		int pliegue = energyCalcPliegue(cromosoma);
		cout << "pliegue salida " << pliegue << endl;

		camionesT.insert(it, new CamionTorque(calcularTorque(torque), torque, cromosoma));
		camionesP.insert(it2, new CamionPliegue(calcularPliegue(pliegue), pliegue, cromosoma));

		//camionesT[position] = new CamionTorque(calcularTorque(torque), torque, cromosoma);
		//camionesP[position] = new CamionPliegue(calcularPliegue(pliegue), pliegue, cromosoma);
	}
}

/*
 *Input: dos objetos tipo camionTorque uno se toma como la madre y el otro como el padre
 *Output:Se crea un nuevo objeto tipo camionTorque
 *Funcion:Crear un nuevo hijo apartir de la combinacion de dos hijos.
 */
void newSonTorque(CamionTorque pCamionMom, CamionTorque pCamionDad) {
	//ver donde metemos los hijos
	int cromosoma = combinacionTorque(pCamionMom, pCamionDad);
	int energia = energyCalcTorque(cromosoma);
	int torque = calcularTorque(energia);
}

/*
 *Input: dos objetos tipo camionPliegue uno se toma como la madre y el otro como el padre
 *Output:Se crea un nuevo objeto tipo camionTorque
 *Funcion:Crear un nuevo hijo apartir de la combinacion de dos hijos.
 */
void newSonPliegue(CamionPliegue pCamionMom, CamionPliegue pCamionDad) {
	//ver donde metemos los hijos
	int cromosoma = combinacionPliegue(pCamionMom, pCamionDad);
	int energia = energyCalcPliegue(cromosoma);
	int torque = calcularPliegue(energia);
}


int main() {

	std::thread first (threadReader);
	std::thread second (algorGenetico);

	int cantidadCamiones = 200;
	newTrucks(cantidadCamiones);

	for (list<CamionTorque*>::iterator i = camionesT.begin(); i != camionesT.end(); i++) {
		cout << *i << " ";
	}

	/*
	list<CamionTorque*> ::iterator it = camionesT.begin();
	CamionTorque* tmp = camionesT.front();
	cout << tmp->cromosoma << endl;

	advance(it, 1);
	tmp = *it;

	cout << tmp->cromosoma << endl;
	*/

	first.join();
	second.join();
	


}
