#include "Tablero.h"
#include <iostream>

using namespace std;

void nuevaJugada(tTablero& tablero, const tJugada& jugada) {
	tablero.jugadas[tablero.numJugadas] = jugada;
	cout << "Nueva jugada: ";
	mostrar(tablero.jugadas[tablero.numJugadas]);
	cout << endl;
	tablero.numJugadas++;
}

void mostrar(const tTablero& tablero) {
	for (int i = 0; i < tablero.numJugadas; i++) {
		cout << i + 1 << ": ";
		mostrar(tablero.jugadas[i]);
		cout << endl;
	}
}