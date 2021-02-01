#pragma once

#include "Tramo.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <stack>
#include "../../Progra_II/nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;
using namespace std;

stack<Camino*> stackCreator();
void fileReader();