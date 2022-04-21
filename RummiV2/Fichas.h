#pragma once
#include "Colores.h"

struct tFicha {
	int numero;
	tColor color;
};

const int NUM_COLORES = 4;

bool operator==(tFicha izq, tFicha der);
bool operator!=(tFicha izq, tFicha der);
bool operator<(tFicha izq, tFicha der);
bool operator>(tFicha izq, tFicha der);
void mostrar(tFicha ficha);
void colorTexto(tColor color);