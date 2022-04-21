#pragma once
#include "Fichas.h"
#include "Bolsa.h"

typedef tFicha tArrayJugada[NUM_FICHAS];

struct tJugada {
	tArrayJugada filaFichas{};
	int numFichasJugada = 0;
};

const int MAX_JUGADAS = NUM_FICHAS * 2;

int buscar(const tJugada& jugada, tFicha ficha);
void mostrar(const tJugada& jugada);