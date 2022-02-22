// Pr�ctica FP2 Rummikub versi�n 1
// 1.1 Martes 22/02/2022

#include <iostream>
#include <stdio.h>
#include <stdlib.h> //rand y RAND_MAX
using namespace std;

//n�mero de fichas disponibles por cada color
const int NUM_FICHAS = 10;
//n�mero de jugadores
const int NUM_JUGADORES = 2;
//n�mero total de fichas del juego
const int TOTAL_FICHAS = NUM_FICHAS * 8;
//n�mero de fichas que se reparten inicialmente a cada jugador
const int INI_FICHAS = 10;
//n�mero m�ximo de fichas por jugador
const int MAX_FICHAS = 50;
//n�mero m�ximo de jugadas
const int MAX_JUGADAS = NUM_FICHAS * 2;

//colores de las fichas, el color blanco es para el texto
enum tColor { rojo, verde, azul, amarillo, blanco };

//estructura que representa a cada ficha, con un n�mero y un color
struct tFicha {
	int numero;
	tColor color;
};

/* struct para la bolsa propuesto por la profesora(cuidado, NumColores * 2 = 10)
typedef bool tArrayBolsa[NumColores * 2][NumFichas];
struct tBolsa_ {
	tArrayBolsa fichas;
	int cont;
}*/

//aqu� est�n todas las fichas inicialmente, 8 filas, NUM_FICHAS (10) columnas y cantidad de fichas disponibles en la bolsa
struct tBolsa {
	bool fichas[8][NUM_FICHAS];
	int fichasDisponibles = TOTAL_FICHAS;
};

//soporte propuesto en clase, aqu� cada jugador guarda sus fichas, inicialmente 10
typedef tFicha tArraySoporte[MAX_FICHAS];
struct tSoporte {
	tArraySoporte fichas;
	int numFichasSoporte;
};

//array con los soportes de los jugadores
typedef tSoporte tSoportes[NUM_JUGADORES];
//cada jugador roba y/o pone fichas
typedef tFicha tJugada[NUM_FICHAS];
//array de jugadas
typedef tJugada tTablero[MAX_JUGADAS];

//inicializamos las estructuras de datos
tBolsa bolsa;
tSoporte soporte1;
tSoporte soporte2;
tSoportes soportes { soporte1, soporte2 };
tTablero tablero;

//subprogramas
int menu() {

}

//le damos a cada casilla de la bolsa el valor true
void inicializarBolsa(tBolsa& bolsa) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < NUM_FICHAS; j++) {
			bolsa.fichas[i][j] = true;
		}
	}
}

tFicha robar(tBolsa& bolsa) {

}

int generaFilaAleatoria() {
	return 0 + rand() / (RAND_MAX / (8 - 0 + 1) + 1);
}
int generaColumnaAleatoria() {
	return 0 + rand() / (RAND_MAX / (NUM_FICHAS - 0 + 1) + 1);
}

void repartir(tBolsa& bolsa, tSoportes soportes) {
	while (soportes[0].numFichasSoporte != 10) {
		int fila  = generaFilaAleatoria();
		int columna = generaColumnaAleatoria();
		if (bolsa.fichas[fila][columna] == true) {
			tFicha ficha{ columna, tColor(fila) };
			soportes[0].fichas[soportes[1].numFichasSoporte] = ficha;
			soportes[0].numFichasSoporte++;
			bolsa.fichas[fila][columna] = false;
		}
	}

	while (soportes[1].numFichasSoporte != 10) {
		int fila = generaFilaAleatoria();
		int columna = generaColumnaAleatoria();
		if (bolsa.fichas[fila][columna] == true) {
			tFicha ficha{ columna, tColor(fila) };
			soportes[1].fichas[soportes[1].numFichasSoporte] = ficha;
			soportes[1].numFichasSoporte++;
			bolsa.fichas[fila][columna] = false;
		}
	}
}

void ordenarPorNum(tSoporte& soporte) {

}

void ordenarPorColor(tSoporte& soporte) {

}

bool operator==(tFicha izq, tFicha der) {

}

int buscar(const tJugada& jugada, tFicha ficha) {

}

void mostrarSeries(tSoporte soporte) {

}

void mostrarEscaleras(tSoporte soporte) {

}

void nuevaJugada(tTablero& tablero, const tJugada& jugada) {

}

void eliminarFichas(tTablero& tablero, const tJugada& jugada) {

}

void nuevaJugada(tSoporte soporte, tJugada& jugada) {

}

bool ponerFicha(tJugada& jugada, tFicha ficha) {

}

bool jugar(tTablero& tablero, tSoporte& soporte) {

}

int menor(const tSoportes soportes) {

}

void mostrar(tFicha ficha) {

}

void mostrar(const tBolsa& bolsa) {

}

void mostrar(const tJugada& jugada) {

}

void mostrar(const tTablero& tablero) {

}

void mostrar(const tSoporte& soporte) {

}

void mostrarIndices(int num) {

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