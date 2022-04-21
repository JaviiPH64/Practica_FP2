#include "Jugadas.h"

int buscar(const tJugada& jugada, tFicha ficha) {
	if (jugada.numFichasJugada == 0) {
		return -1;
	}
	else {
		for (int i = 0; i < jugada.numFichasJugada; i++) {
			if (jugada.filaFichas[i] == ficha) {
				return i + 1;
			}
		}
	}
}

void mostrar(const tJugada& jugada) {
	for (int i = 0; i < jugada.numFichasJugada; i++) {
		mostrar(jugada.filaFichas[i]);
	}
}