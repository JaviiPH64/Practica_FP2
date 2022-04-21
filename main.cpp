#define _CRTDBG_MAP_ALLOC():
#include <crtdbg.h>
#include <cstdlib>
#include "Bolsa.h"
#include "Colores.h"
#include "Fichas.h"
#include "Jugadas.h"
#include "Soporte.h"
#include "Soportes.h"
#include "Tablero.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

using namespace std;

int main() {
	srand(time(NULL));
	tBolsa bolsa;
	inicializarBolsa(bolsa);
	cout << "Estado inicial de la bolsa: " << endl;
	mostrar(bolsa);
	cout << endl;

	tTablero tablero;
	mostrar(tablero);
	cout << "Estado inicial del tablero: " << endl;
	cout << "*vacio*" << endl;
	tSoportes soportes = {};

	int bloqueos = 0;
	int bloqueo1 = 0;
	int bloqueo2 = 0;
	bool fin = false;

	repartir(bolsa, soportes);

	cout << "Reparto de fichas: " << endl;
	mostrar(soportes[0]);
	cout << " soporte 1" << endl;
	mostrar(soportes[1]);
	cout << " soporte 2" << endl;

	cout << endl;
	ordenarPorNum(soportes[0]);
	ordenarPorColor(soportes[1]);
	mostrar(soportes[0]);
	cout << " soporte 1 ordenado de menor a mayor" << endl;
	mostrar(soportes[1]);
	cout << " soporte 2 ordenado por colores" << endl;

	cout << endl;
	if (menor(soportes) == 1) {
		cout << "Gana el jugador 1";
	}
	else if (menor(soportes) == 2) {
		cout << "Gana el jugador 2";
	}
	else {
		cout << "Empate";
	}
	cout << endl;



	_CrtDumpMemoryLeaks();
	return 0;
}