#pragma once
#include "Soporte.h"
#include "Bolsa.h"

const int NUM_JUGADORES = 2;
const int INI_FICHAS = 9;

typedef tSoporte tSoportes[NUM_JUGADORES];

int menor(const tSoportes soportes);