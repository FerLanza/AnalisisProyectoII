
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
int cantidadCamiones = 200;

/*
 *
 */
stack<Camino> loadFiles() {
	fileReader();
	return stackCreator();
}


/*
 *
 */
int energiaTramoTorque() {

	int pEnergia = 0;

	int firmezaE = 0;
	int humedadE = 0;
	int agarreE = 0;

	int firmezaT[7] = { 40,30,20,60,65,80,100 };
	int humedadT[6] = { 100,70,60,55,40,20 };
	int agarreT[7] = { 30,20,10,50,70,90,100 };

	for (int i = 0; i < 7; i++) {
		if (road.firmeza >= firmezaT[i]) {
			pEnergia = i;

		}
	}

	switch (pEnergia)
	{
	case 0:
		firmezaE = 9;
		break;
	case 1:
		firmezaE = 10;
		break;
	case 2:
		firmezaE = 12;
		break;
	case 3:
		firmezaE = 8;
		break;
	case 4:
		firmezaE = 7;
		break;
	case 5:
		firmezaE = 6;
		break;
	case 6:
		firmezaE = 4;
		break;
	}

	for (int i = 0; i < 6; i++) {
		if (road.firmeza >= humedadT[i]) {
			pEnergia = i;
		}
	}

	switch (pEnergia)
	{
	case 0:
		humedadE = 10;
		break;
	case 1:
		humedadE = 9;
		break;
	case 2:
		humedadE = 8;
		break;
	case 3:
		humedadE = 7;
		break;
	case 4:
		humedadE = 6;
		break;
	case 5:
		humedadE = 4;
		break;
	}

	for (int i = 0; i < 7; i++) {
		if (road.firmeza >= agarreT[i]) {
			pEnergia = i;

		}
	}

	switch (pEnergia)
	{
	case 0:
		agarreE = 9;
		break;
	case 1:
		agarreE = 10;
		break;
	case 2:
		agarreE = 12;
		break;
	case 3:
		agarreE = 8;
		break;
	case 4:
		agarreE = 7;
		break;
	case 5:
		agarreE = 6;
		break;
	case 6:
		agarreE = 4;
		break;
	}

	return (firmezaE + agarreE + humedadE);
}


/*
 *
 */
int energiaTramoPliegue() {

	int pEnergia = 0;

	int firmezaE = 0;
	int humedadE = 0;
	int agarreE = 0;

	int firmezaP[7] = { 10,15,20,25,50,75,100 };
	int humedadP[7] = { 100,90,80,75,60,45,20 };
	int agarreP[7] = { 5,10,25,30,50,80,100 };

	for (int i = 0; i < 7; i++) {
		if (road.firmeza >= firmezaP[i]) {
			pEnergia = i;

		}
	}

	switch (pEnergia)
	{
	case 0:
		firmezaE = 15;
		break;
	case 1:
		firmezaE = 13;
		break;
	case 2:
		firmezaE = 11;
		break;
	case 3:
		firmezaE = 10;
		break;
	case 4:
		firmezaE = 8;
		break;
	case 5:
		firmezaE = 7;
		break;
	case 6:
		firmezaE = 6;
		break;
	}

	for (int i = 0; i < 7; i++) {
		if (road.firmeza >= humedadP[i]) {
			pEnergia = i;
		}
	}

	switch (pEnergia)
	{
	case 0:
		firmezaE = 15;
		break;
	case 1:
		firmezaE = 13;
		break;
	case 2:
		firmezaE = 11;
		break;
	case 3:
		firmezaE = 10;
		break;
	case 4:
		firmezaE = 8;
		break;
	case 5:
		firmezaE = 7;
		break;
	case 6:
		firmezaE = 6;
		break;
	}

	for (int i = 0; i < 7; i++) {
		if (road.firmeza >= agarreP[i]) {
			pEnergia = i;

		}
	}

	switch (pEnergia)
	{
	case 0:
		firmezaE = 15;
		break;
	case 1:
		firmezaE = 13;
		break;
	case 2:
		firmezaE = 11;
		break;
	case 3:
		firmezaE = 10;
		break;
	case 4:
		firmezaE = 8;
		break;
	case 5:
		firmezaE = 7;
		break;
	case 6:
		firmezaE = 6;
		break;
	}

	return (firmezaE + agarreE + humedadE);
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
 *Input:
 *Output: cambia el atributo que indica la adaptabilidad.
 *Funcion:calcula los km que se recorren en el tramo , seguidamente realiza una operacion que calcula que tan apto es el camion
 *esto se logra por medio de un promedio de las energias de los torques a los cuales entra cada atributo del tramo esto entre la energia del
 *camion por los km que debe recorrer.
 */
void fitnessTorque(CamionTorque* pCamion, Camino pCamino, int pEnergiaTramo) {
	int kmRecorridos = pCamino.kmEnd - pCamino.kmStart;

	double adaptabilidad = ((((double)pEnergiaTramo / 3) * (double)kmRecorridos)
		/ ((double)pCamion->energia * (double)kmRecorridos));

	pCamion->apto = adaptabilidad;
}

/*
 *Input:
 *Output: cambia el atributo que indica la adaptabilidad.
 *Funcion:calcula los km que se recorren en el tramo , seguidamente realiza una operacion que calcula que tan apto es el camion
 *esto se logra por medio de un promedio de las energias de los pliegues a los cuales entra cada atributo del tramo esto entre la energia del
 *camion por los km que debe recorrer.
 */
void fitnessPliegue(CamionPliegue* pCamion, Camino pCamino, int pEnergiaTramo) {
	int kmRecorridos = pCamino.kmEnd - pCamino.kmStart;

	double adaptabilidad = ((((double)pEnergiaTramo / 3) * (double)kmRecorridos)
		/ ((double)pCamion->energia * (double)kmRecorridos));

	pCamion->apto = adaptabilidad;
}

/*
 *Input: objeto tipo camionTorque.
 *Output: cromosoma nuevo en el camion que ingreso.
 *Funcion:Realizar la mutacion del cromosoma, por medio de una selecciona random del bit
 *y le realiza un not.
 */
void mutacionTorque(CamionTorque* pCamion) {
	srand(time(0));
	int position = (rand() % 8);
	bitset<8> cromosoma(pCamion->cromosoma);
	if (cromosoma[position] == 1) {
		cromosoma.reset(position);
		pCamion->cromosoma = cromosoma.to_ulong();
	}
	else {
		cromosoma.set(position);
		pCamion->cromosoma = cromosoma.to_ulong();
	}

}

/*
 *Input: un objeto tipo camionPliegue
 *Output:cromosoma nuevo en el camion que ingreso
 *Funcion:Realizar la mutación del cromosoma, por medio de una selección random del bit
 *y le realiza un not.
 */
void mutacionPliegue(CamionPliegue* pCamion) {
	srand(time(0));
	int position = (rand() % 8);
	bitset<8> cromosoma(pCamion->cromosoma);
	if (cromosoma[position] == 1) {
		cromosoma.reset(position);
		pCamion->cromosoma = cromosoma.to_ulong();
	}
	else {
		cromosoma.set(position);
		pCamion->cromosoma = cromosoma.to_ulong();
	}

}

/*
 *Input: dos objetos tipo CamionTorque uno se considera la madre y el otro el padre.
 *Output: un int que representa el cromosoma del hijo
 *Funcion:Combinar ambos bytes para crear un hijo.
 */
int combinacionTorque(CamionTorque* pCamionMama, CamionTorque* pCamionPapa) {
	srand(time(0));
	int cantidadMama = (rand() % 5);
	int cantidadPapa = 8 - cantidadMama;
	bitset<8> cromosomaMama(pCamionMama->cromosoma);
	bitset<8> cromosomaPapa(pCamionPapa->cromosoma);
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
int combinacionPliegue(CamionPliegue* pCamionMama, CamionPliegue* pCamionPapa) {
	srand(time(0));
	int cantidadMama = (rand() % 5);
	int cantidadPapa = 8 - cantidadMama;
	bitset<8> cromosomaMama(pCamionMama->cromosoma);
	bitset<8> cromosomaPapa(pCamionPapa->cromosoma);
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
 *Input: dos objetos tipo camionTorque uno se toma como la madre y el otro como el padre
 *Output:Se crea un nuevo objeto tipo camionTorque
 *Funcion:Crear un nuevo hijo apartir de la combinacion de dos hijos.
 */
void newSonTorque(CamionTorque* pCamionMom, CamionTorque* pCamionDad) {
	//ver donde metemos los hijos
	int cromosoma = combinacionTorque(pCamionMom, pCamionDad);
	int energia = energyCalcTorque(cromosoma);
	int torque = calcularTorque(energia);
	//Aplicar la mutacion 
	CamionTorque* tmp = new CamionTorque(torque, energia, cromosoma);
	srand(0);
	if (rand() % 100 < 20) {
		mutacionTorque(tmp);
	}
	camionesT.push_front(tmp);
}

/*
 *Input: dos objetos tipo camionPliegue uno se toma como la madre y el otro como el padre
 *Output:Se crea un nuevo objeto tipo camionTorque
 *Funcion:Crear un nuevo hijo apartir de la combinacion de dos hijos.
 */
void newSonPliegue(CamionPliegue* pCamionMom, CamionPliegue* pCamionDad) {
	//ver donde metemos los hijos
	int cromosoma = combinacionPliegue(pCamionMom, pCamionDad);
	int energia = energyCalcPliegue(cromosoma);
	int pliegue = calcularPliegue(energia);

	CamionPliegue* tmp = new CamionPliegue(pliegue, energia, cromosoma);
	srand(0);
	if (rand() % 100 < 20) {
		mutacionPliegue(tmp);
	}
	camionesP.push_front(tmp);
}


/*
 *
 */
void seleccionPadresTorque() {
	camionesT.sort();
	camionesT.reverse();
	CamionTorque* tmp = new CamionTorque();
	CamionTorque* apto = new CamionTorque();
	srand(0);
	bool first = false;

	for (list<CamionTorque*>::iterator i = camionesT.begin(); i != camionesT.end(); i++) {
		tmp = *i;
		if(!first){
			if (tmp->apto >= (rand() % 100)) {
				apto = tmp;
				first = true;
			}
		}
		else if (tmp->apto >= (rand() % 100)) {
			// se envian apto y tmp a cruce
			newSonTorque(apto,tmp);
			first = false;
		}
	}
}


/*
 *
 */
void seleccionPadresPliegue() {
	camionesP.sort();
	camionesP.reverse();
	CamionPliegue* tmp = new CamionPliegue();
	CamionPliegue* apto = new CamionPliegue();;
	srand(0);
	bool first = false;

	for (list<CamionPliegue*>::iterator i = camionesP.begin(); i != camionesP.end(); i++) {
		tmp = *i;
		if (!first) {
			if (tmp->apto >= (rand() % 100)) {
				apto = tmp;
				first = true;
			}
		}
		else if (tmp->apto >= (rand() % 100)) {
			// se envian apto y tmp a cruce
			newSonPliegue(apto, tmp);
			first = false;
		}
	}
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
 *
 * */
void algorGenetico() {

	while (true) {
		newTrucks(cantidadCamiones);							//Se inicia una poblacion desde 0
		if (hiloGenetico) {
			camionesT.sort();								//Ordeno las listas conforme el parametro de apto , asi llevamos un ranking
			camionesP.sort();

			CamionTorque* tmpTorque;							//Genero un temporal con un puntero al camion que trabajaremos

			for (int first = 0; first < 10; first++) {
				for (list<CamionTorque*>::iterator position = camionesT.begin(); position != camionesT.end(); position++) {
					tmpTorque = *position;
					int pEnergiaTramoTorque = energiaTramoTorque();
					fitnessTorque(tmpTorque, road, pEnergiaTramoTorque);		//Pasa cada uno de los camiones por la funcion de fitness 
				}

				CamionPliegue* tmpPliegue;						//Genero un temporal con un puntero al camion que trabajaremos en el caso del pliegue 
				for (list<CamionPliegue*>::iterator element = camionesP.begin(); element != camionesP.end(); element++) {
					tmpPliegue = *element;
					int pEnergiaTramo = energiaTramoPliegue();
					fitnessPliegue(tmpPliegue, road, pEnergiaTramo);		//Pasa cada uno de los camiones por la funcion de fitness 
				}
				//Combinar  y se muta 
				seleccionPadresTorque();
				seleccionPadresPliegue();

			}
			hiloGenetico = false;
			hiloReader = true;
			// cambiar banderas 

		}
	}

}


/*
 *
 */
int main() {

	std::thread first (threadReader);
	std::thread second (algorGenetico);

	//int cantidadCamiones = 200;
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
