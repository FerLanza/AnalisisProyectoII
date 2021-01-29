/*
 * main.cpp
 *
 *  Created on: 6 ene. 2021
 *      Author: dylan
 */

#include "header.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include <bitset>

//#include <nlohmann/json.hpp>

// for convenience
//using json = nlohmann::json;
using namespace std;
using std::bitset;
// Hilos en teoria
#include <vector>
#include <numeric>
#include <cmath>
#include <sstream>
#include <chrono>
#include <mutex>


/*
int GetRandom(int max){
    srand(time(NULL));
    return rand() % max;
}


void ExecuteThread(int id){
    // Get current time
    auto nowTime = std::chrono::system_clock::now();

    // Convert to a time we can output
    std::time_t sleepTime =
            std::chrono::system_clock::to_time_t(nowTime);

    // Convert to current time zone
    tm myLocalTime = *localtime(&sleepTime);

    // Print full time information
    std::cout << "Thread " << id <<
            " Sleep Time : " <<
            std::ctime(&sleepTime) << "\n";

    // Get separate pieces
    std::cout << "Month : " <<
            myLocalTime.tm_mon << "\n";
    std::cout << "Day : " <<
            myLocalTime.tm_mday << "\n";
    std::cout << "Year : " <<
            myLocalTime.tm_year + 1900 << "\n";
    std::cout << "Hours : " <<
            myLocalTime.tm_hour << "\n";
    std::cout << "Minutes : " <<
            myLocalTime.tm_min << "\n";
    std::cout << "Seconds : " <<
            myLocalTime.tm_sec << "\n\n";

    // Put the thread to sleep for up to 3 seconds
    std::this_thread::sleep_for (std::chrono::seconds(GetRandom(3)));
    nowTime = std::chrono::system_clock::now();
    sleepTime =
            std::chrono::system_clock::to_time_t(nowTime);
    std::cout << "Thread " << id <<
            " Awake Time : " <<
            std::ctime(&sleepTime) << "\n";

}*/

CamionTorque* camionesT[256];
CamionPliegue* camionesP[256];



/*
 *
 * */
void threadReader(){

}


/*
 *
 * */
void algorGenetico(){

}

//Pasar el cromosoma a int
void mutacion(CamionTorque pCamion){
	srand(time(0));
	int position = (rand() % 8);
	bitset<8> cromosoma(pCamion.Energia);
	if(cromosoma[position]==1){
		cromosoma.reset(position);
		pCamion.Energia =cromosoma.to_ulong();
	}
	else{
		cromosoma.set(position);
		pCamion.Energia =cromosoma.to_ulong();
	}

}

void combinacion(CamionTorque pCamionMama, CamionTorque pCamionPapa){
	srand(time(0));
	int cantidadMama = (rand() % 5); //Saca 0?
	int cantidadPapa = 8 - cantidadMama;
	bitset<8> cromosomaMama(pCamionMama.Energia);
	bitset<8> cromosomaPapa(pCamionPapa.Energia);
	bitset<8> cromosomaHijo(0);
	int position = 0;
	for( position; position < cantidadMama; position++){
		if (cromosomaMama[position] == 1){
			cromosomaHijo.set(position);
		}
	}
	for( position ; position < cantidadPapa; position++){
			if (cromosomaPapa[position] == 1){
				cromosomaHijo.set(position);
			}
	}
	//Agregar el dato de la energia del hijo al objeto
}
/*
 *
 * */
double energyCalcTorque(int value){
	double resultado;

	if(value <= 102){
		resultado = (2 * (value / 102)) + 4;
		if(resultado >= 5 && round(resultado) == 5){
			resultado ++;
		}
		else{
			resultado --;
		}
	}
	if(102 < value && value <= 179){

		resultado = (2 * ((value - 102) / (179 - 102))) + 6;
	}
	if(179 < value && value <= 230){

		resultado = (2 * ((value - 179) / (230 - 179))) + 8;
	}
	else{
		resultado = (2 * ((value - 230) / (256 - 230))) + 10;
		if(resultado >= 11 && round(resultado) == 11){
			resultado ++;
		}
		else{
			resultado --;
		}
	}
	resultado =abs(resultado);

	return resultado;
}


/*
 *
 * */
double energyCalcPliegue(int value){
	double resultado;

	if(value <= 102){
		resultado = (2.25 * (value / 102)) + 6;

	}
	if(102 < value && value <= 179){
		resultado = (2.25 * ((value - 102) / (179 - 102))) + 8.25;
		if(resultado >= 9 && round(resultado) == 9){
			resultado ++;
		}
		else{
			resultado --;
		}
	}
	if(179 < value && value <= 230){
		resultado = (2.25 * ((value - 179) / (230 - 179))) + 10.5;
		if(resultado >= 12 && round(resultado) == 12){
			resultado ++;
		}
		else{
			resultado --;
		}
	}
	else{
		resultado = (2.25 * ((value - 230) / (256 - 230))) + 12.75;
		if(resultado >= 14 && round(resultado) == 14){
			resultado ++;
		}
		else{
			resultado --;
		}
	}
	resultado = abs(resultado);
	return resultado;
}


/*
 *
 * */
int calcTorque(double pEnergia){
	int energia = (int)round(pEnergia);
	int resultado;

	switch(energia){
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

		break;
	}

	return resultado;
}


/*
 *
 * */
int calcPliegue(double pEnergia){
	int energia = (int)round(pEnergia);
	cout <<"Energia" << energia<< endl;
	int resultado;

	switch(energia){
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

		break;
	}

	return resultado;
}


/*
 *
 * */
void newTruck(){
	srand(time(0));
	int r = (rand() % 256) + 1;
	cout <<r << endl;
	double Torque = energyCalcTorque(r);
	double Pliegue = energyCalcPliegue(r);
	cout <<Torque << endl;
	cout <<Pliegue<< endl;

	camionesT[r] = new CamionTorque(calcTorque(Torque), Torque);
	camionesP[r] = new CamionPliegue(calcPliegue(Pliegue), Pliegue);

}



int main(){

	//std::thread first (threadReader);
	//std::thread second (algorGenetico);

	for (int i = 0; i < 10 ; i++){
		srand(time(0));
			int r = (rand() % 256)+1 ;
			cout <<r << endl;
			double Torque = energyCalcTorque(r);
			double Pliegue = energyCalcPliegue(r);
			cout <<Torque << endl;
			cout <<Pliegue<< endl;

			camionesT[i] = new CamionTorque(calcTorque(Torque), Torque);
			camionesP[i] = new CamionPliegue(calcPliegue(Pliegue), Pliegue);
	}
	cout <<"cAMION "<<camionesT[0]->Energia << endl;
	cout <<"cAMION " <<camionesT[0]->Torque << endl;
	cout <<"cAMION "<<camionesP[0]->Pliegue << endl;
	cout <<"cAMION "<<camionesP[0]->Energia << endl;
	//first.join();
	//second.join();

}



