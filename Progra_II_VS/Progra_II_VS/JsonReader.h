#pragma once

#include "Tramo.h"

#include <cstdlib>
#include <iostream>
#include <string>

#include <stack>
#include "../../Progra_II/nlohmann/json.hpp"	// Libreria de terceros utilizada para la lectura de json

// Para conveniencia
using json = nlohmann::json; 
using namespace std;

/* LLamadas de las funciones en JsonReader para su uso en el cpp principal.
*/
stack<Camino> stackCreator();
void fileReader();