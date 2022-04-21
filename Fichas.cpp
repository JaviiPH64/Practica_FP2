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

void colorTexto(tColor color) {
	switch (color) {
	case amarillo:
		cout << "\033[1;40;33m";
		break;
	case azul:
		cout << "\033[40;34m";
		break;
	case rojo:
		cout << "\033[40;31m";
		break;
	case verde:
		cout << "\033[40;32m";
		break;
	case blanco:
		cout << "\033[40;37m";
		break;

	}
}