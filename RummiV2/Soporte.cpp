#include "Soporte.h"
#include <iostream>

using namespace std;

void ordenarPorNum(tSoporte& soporte) {
	int aux;
	tColor caux{};
	for (int i = 0; i < soporte.numFichasSoporte - 1; i++) {
		for (int j = 0; j < soporte.numFichasSoporte - 1; j++) {
			if (soporte.fichas[j].numero > soporte.fichas[j + 1].numero) {
				aux = soporte.fichas[j].numero;
				caux = soporte.fichas[j].color;
				soporte.fichas[j].numero = soporte.fichas[j + 1].numero;
				soporte.fichas[j + 1].numero = aux;
				soporte.fichas[j].color = soporte.fichas[j + 1].color;
				soporte.fichas[j + 1].color = caux;
			}
		}
	}
}

void ordenarPorColor(tSoporte& soporte) {
	ordenarPorNum(soporte);
	int aux;
	tColor caux{};
	for (int i = 0; i < soporte.numFichasSoporte - 1; i++) {
		for (int j = 0; j < soporte.numFichasSoporte - 1; j++) {
			if (soporte.fichas[j].color > soporte.fichas[j + 1].color) {
				aux = soporte.fichas[j].numero;
				caux = soporte.fichas[j].color;
				soporte.fichas[j].numero = soporte.fichas[j + 1].numero;
				soporte.fichas[j + 1].numero = aux;
				soporte.fichas[j].color = soporte.fichas[j + 1].color;
				soporte.fichas[j + 1].color = caux;
			}
		}
	}
}

void mostrarIndices(int num) {
	for (int i = 0; i < num; i++) {
		cout << " " << i + 1 << " ";
	}
}

void mostrar(const tSoporte& soporte) {
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		mostrar(soporte.fichas[i]);
	}
	cout << endl;
	mostrarIndices(soporte.numFichasSoporte);
}