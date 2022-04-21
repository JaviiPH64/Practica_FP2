#include "Bolsa.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

using namespace std;

void inicializarBolsa(tBolsa& bolsa) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < NUM_FICHAS; j++) {
			bolsa.fichas[i][j] = true;
		}
	}
}

tFicha robar(tBolsa& bolsa) {
	tFicha fichaRobada{};
	if (bolsa.fichasDisponibles == 0) {
		fichaRobada.numero = -1;
		return fichaRobada;
	}
	else {
		int fila = rand() % 8;
		int columna = rand() % (NUM_FICHAS);
		bool aux = false;
		if (bolsa.fichas[fila][columna] == true) {
			fichaRobada.numero = columna + 1;
			fichaRobada.color = tColor(fila % NUM_COLORES);
			bolsa.fichasDisponibles--;
			bolsa.fichas[fila][columna] = false;
			aux = true;
			return fichaRobada;
		}
		else { 
			if (fila == 7 && columna == 9) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < NUM_FICHAS; j++) {
						if (bolsa.fichas[i][j] == true) {
							fichaRobada.numero = j + 1;
							fichaRobada.color = tColor(i % NUM_COLORES);
							bolsa.fichasDisponibles--;
							bolsa.fichas[i][j] = false;
							aux = true;
							return fichaRobada;
						}
					}
				}
			}
			else if (fila < 7 && columna == 9) {
				for (int i = fila + 1; i < 8; i++) {
					for (int j = 0; j < NUM_FICHAS; j++) {
						if (bolsa.fichas[i][j] == true) {
							fichaRobada.numero = j + 1;
							fichaRobada.color = tColor(i % NUM_COLORES);
							bolsa.fichasDisponibles--;
							bolsa.fichas[i][j] = false;
							aux = true;
							return fichaRobada;
						}
					}
				}
			}
			else {
				for (int i = fila; i < 8; i++) {
					for (int j = columna + 1; j < NUM_FICHAS; j++) {
						if (bolsa.fichas[i][j] == true) {
							fichaRobada.numero = j + 1;
							fichaRobada.color = tColor(i % NUM_COLORES);
							bolsa.fichasDisponibles--;
							bolsa.fichas[i][j] = false;
							aux = true;
							return fichaRobada;
						}
					}
				}
			}
		}
		if (aux == false) {
			for (int k = 0; k < 8; k++) {
				for (int l = 0; l < NUM_FICHAS; l++) {
					if (bolsa.fichas[k][l] == true) {
						fichaRobada.numero = l + 1;
						fichaRobada.color = tColor(k % NUM_COLORES);
						bolsa.fichasDisponibles--;
						bolsa.fichas[k][l] = false;
						aux = true;
						return fichaRobada;
					}
				}
			}
		}
	}
}

void repartir(tBolsa& bolsa, tSoportes soportes) {
	for (int i = 0; i < INI_FICHAS; i++) {
		tFicha fichaRobada = (robar(bolsa));
		soportes[0].fichas[i] = fichaRobada;
		soportes[0].numFichasSoporte++;
	}
	for (int j = 0; j < INI_FICHAS; j++) {
		tFicha fichaRobada = (robar(bolsa));
		soportes[1].fichas[j] = fichaRobada;
		soportes[1].numFichasSoporte++;
	}
}

void mostrar(const tBolsa& bolsa) {
	for (int fila = 0; fila < 8; fila++) {
		cout << " " << endl;
		for (int columna = 0; columna < NUM_FICHAS; columna++) {
			tFicha ficha{};
			ficha.color = tColor(fila % NUM_COLORES);
			ficha.numero = columna + 1;
			if (bolsa.fichas[fila][columna] == true) {
				mostrar(ficha);
			}
			else {
				cout << " * ";
			}
		}
	}
}