
#include "JsonReader.h"

Camino Tramos[100];
int contador = 0;

/*  Crea el stack a partir de los datos cargados en el array Tramos, generando el stack enviable a el hilo de lectura.
 * Inputs: Ninguno
 * Outputs: El stack con los datos de los tramos
 */
stack<Camino> stackCreator() {
    
    stack<Camino> mystack;
    for (int i = contador - 1; i >= 0; i--) {

        mystack.push(Tramos[i]);
    }
    return mystack;
}


/*	Encargado de leer el json entrante, del cual descompone la informacion a valores de entrada dados en el array de Tramos.
 * Inputs: Ninguno
 * Outputs: Ninguno
 */
void fileReader() {

	string value = "value";
	string jsonValue;

	json J =
	{
		{"value0", "0,5,44,18,65"},
		{"value1", "33,40,17,67,35"},
		{"value2", "60,70,17,67,55"},
		{"value3", "75,100,17,67,37"},
		{"value4", "105,116,17,67,55"},
		{"value5", "133,160,17,67,55"}
	};

	for (int i = 0; i < 6; i++) {
		jsonValue = value + to_string(i);
		jsonValue = J.at(jsonValue);
		int counter = 0;

		string x = "";
		x += jsonValue[counter];
		if (jsonValue[counter + 1] != ',') {
			x += jsonValue[counter + 1];
			counter++;
			if (jsonValue[counter + 1] != ',') {
				x += jsonValue[counter + 1];
				counter++;
			}
		}

		counter++;
		counter++;

		//Tramos[i] = new Camino();
		Tramos[i].kmStart = stoi(x);

		x = "";
		x += jsonValue[counter];
		if (jsonValue[counter + 1] != ',') {
			x += jsonValue[counter + 1];
			counter++;
			if (jsonValue[counter + 1] != ',') {
				x += jsonValue[counter + 1];
				counter++;
			}
		}

		counter++;
		counter++;
		Tramos[i].kmEnd = stoi(x);

		x = "";
		x += jsonValue[counter];
		if (jsonValue[counter + 1] != ',') {
			x += jsonValue[counter + 1];
			counter++;
			if (jsonValue[counter + 1] != ',') {
				x += jsonValue[counter + 1];
				counter++;
			}
		}

		counter++;
		counter++;
		Tramos[i].firmeza = stoi(x);

		x = "";
		x += jsonValue[counter];
		if (jsonValue[counter + 1] != ',') {
			x += jsonValue[counter + 1];
			counter++;
			if (jsonValue[counter + 1] != ',') {
				x += jsonValue[counter + 1];
				counter++;
			}
		}

		counter++;
		counter++;
		Tramos[i].humedad = stoi(x);

		x = "";
		x += jsonValue[counter];
		if (jsonValue[counter + 1] != ',') {
			x += jsonValue[counter + 1];
			counter++;
			if (jsonValue[counter + 1] != ',') {
				x += jsonValue[counter + 1];
				counter++;
			}
		}

		counter++;
		counter++;
		Tramos[i].agarre = stoi(x);

		contador++;
		
	}
}