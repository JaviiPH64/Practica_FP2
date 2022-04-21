#include "Soportes.h"

int menor(const tSoportes soportes) {
	int puntos1 = 0;
	int puntos2 = 0;
	for (int i = 0; i < soportes[0].numFichasSoporte; i++) {
		puntos1 = puntos1 + soportes[0].fichas[i].numero;
	}
	for (int j = 0; j < soportes[1].numFichasSoporte; j++) {
		puntos1 = puntos1 + soportes[1].fichas[j].numero;
	}
	if (puntos1 < puntos2) {
		return 1;
	}
	else if (puntos2 < puntos1) {
		return 2;
	}
	else {
		return 0;
	}
}