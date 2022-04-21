#pragma once
#include "Jugadas.h"

typedef tJugada tArrayTablero[MAX_JUGADAS];

struct tTablero {
	tArrayTablero jugadas;
	int numJugadas = 0;
};

void nuevaJugada(tTablero& tablero, const tJugada& jugada);
void mostrar(const tTablero& tablero);