// Práctica FP2 Rummikub versión 1
// 1.1 Martes 22/02/2022

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h> //rand y RAND_MAX
#include <ctime>
using namespace std;

//número de fichas disponibles por cada color
const int NUM_FICHAS = 10;
//número de jugadores
const int NUM_JUGADORES = 2;
//número total de fichas del juego
const int TOTAL_FICHAS = NUM_FICHAS * 8;
//número de fichas que se reparten inicialmente a cada jugador
const int INI_FICHAS = 9;
//número máximo de fichas por jugador
const int MAX_FICHAS = 50;
//número máximo de jugadas
const int MAX_JUGADAS = NUM_FICHAS * 2;

//colores de las fichas, el color blanco es para el texto
enum tColor { rojo, verde, azul, amarillo, blanco };

//estructura que representa a cada ficha, con un número y un color
struct tFicha {
	int numero;
	tColor color;
};

//aquí están todas las fichas inicialmente, 8 filas, NUM_FICHAS (10) columnas y cantidad de fichas disponibles en la bolsa
typedef bool tArrayBolsa[8][NUM_FICHAS];

struct tBolsa {
	tArrayBolsa fichas;
	int fichasDisponibles = TOTAL_FICHAS;
};

//soporte propuesto en clase, aquí cada jugador guarda sus fichas, inicialmente 10
typedef tFicha tArraySoporte[MAX_FICHAS];

struct tSoporte {
	tArraySoporte fichas;
	int numFichasSoporte;
};

//array con los soportes de los jugadores
typedef tSoporte tSoportes[NUM_JUGADORES];

//cada jugador roba y/o pone fichas
//jugada: una serie o escalera de fichas que está en el tablero (lista de hasta NUM_FICHAS fichas)
typedef tFicha tArrayJugada[NUM_FICHAS];

struct tJugada {
	tArrayJugada filaFichas;
	int cont;
};

//array de jugadas
typedef tJugada tArrayTablero[8];

struct tTablero {
	tArrayTablero jugadas;
	int cont = 0;
};

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

int generaFilaAleatoria() {
	return rand() % 7;
}
int generaColumnaAleatoria() {
	return rand() % (NUM_FICHAS - 1);
}

tFicha robar(tBolsa& bolsa, tSoporte soporte) {
	bool aux = false;
	while (aux) {
		int fila = generaFilaAleatoria();
		int columna = generaColumnaAleatoria();
		if (bolsa.fichas[fila][columna] == true) {
			tFicha ficha{ columna, tColor(fila) };
			aux = true;
			return ficha;
		}
	}
}

void repartir(tBolsa& bolsa, tSoportes soportes) {
	while (soportes[0].numFichasSoporte != 9) {
		int fila = generaFilaAleatoria();
		int columna = generaColumnaAleatoria();
		if (bolsa.fichas[fila][columna] == true) {
			tFicha ficha{ columna, tColor(fila) };
			soportes[0].fichas[soportes[1].numFichasSoporte] = ficha;
			soportes[0].numFichasSoporte++;
			bolsa.fichas[fila][columna] = false;
		}
	}

	while (soportes[1].numFichasSoporte != 9) {
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

//hecho en base al ejemplo de la diapositiva 14 del tema 2
void ordenarPorNum(tSoporte& soporte) {
	int nuevo, pos;
	for (int i = 1; i < soporte.numFichasSoporte; i++) {
		pos = 0;
		while (pos < i && (soporte.fichas[pos].numero <= soporte.fichas[i].numero)) {
			pos++;
		}
		nuevo = soporte.fichas[i].numero;
		for (int j = i; j > pos; j--) {
			soporte.fichas[j].numero = soporte.fichas[j].numero - 1;
		}
		soporte.fichas[pos].numero = nuevo;
	}
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

int main() {
	return 0;
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