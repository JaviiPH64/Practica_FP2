#pragma once
#include "Fichas.h"
#include "Jugadas.h"

const int MAX_FICHAS = 50;

typedef tFicha tArraySoporte[MAX_FICHAS];

struct tSoporte {
	tArraySoporte fichas{};
	int numFichasSoporte = 0;
};

void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
void mostrarSeries(tSoporte soporte);
void mostrarEscaleras(tSoporte soporte);
void eliminaFichas(tSoporte& soporte, const tJugada& jugada);
void nuevaJugada(tSoporte soporte, tJugada& jugada);
void mostrarIndices(int num);
void mostrar(const tSoporte& soporte);