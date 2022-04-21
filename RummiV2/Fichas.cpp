#include "Fichas.h"
#include <iomanip>
#include <iostream>

using namespace std;

bool operator==(tFicha izq, tFicha der) {
	return ((izq.color == der.color) && (izq.numero == der.numero));
}

bool operator!=(tFicha izq, tFicha der) {
	return ((izq.color != der.color) || (izq.numero != der.numero));
}

bool operator<(tFicha izq, tFicha der) {
	return (izq.numero < der.numero);
}

bool operator>(tFicha izq, tFicha der) {
	return (izq.numero > der.numero);
}

void mostrar(tFicha ficha) {
	colorTexto(ficha.color);
	cout << setw(2) << ficha.numero << " ";
	colorTexto(blanco);
}

