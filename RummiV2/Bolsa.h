#pragma once
#include "Fichas.h"
#include "Soportes.h"

const int NUM_FICHAS = 10;
const int TOTAL_FICHAS = NUM_FICHAS * 8;

typedef bool tArrayBolsa[8][NUM_FICHAS];

struct tBolsa {
	tArrayBolsa fichas{};
	int fichasDisponibles = TOTAL_FICHAS;
};

void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);
void repartir(tBolsa& bolsa, tSoportes soportes);
void mostrar(tBolsa& bolsa);