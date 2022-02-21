// Práctica FP2 Rummikub versión 1

#include <iostream>
using namespace std;

//número de fichas disponibles por cada color
const int NUM_FICHAS = 10;
//número de jugadores
const int NUM_JUGADORES = 2;
//número total de fichas del juego
const int TOTAL_FICHAS = NUM_FICHAS * 8;
//número de fichas que se reparten inicialmente a cada jugador
const int INI_FICHAS = 10;
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
struct tBolsa {
	bool fichas[8][NUM_FICHAS];
	int fichasDisponibles = TOTAL_FICHAS;
};

//aquí cada jugador guarda sus fichas
typedef tFicha tSoporte[MAX_FICHAS];
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
tSoportes soportes;
tTablero tablero;

//subprogramas
int menu() {

}

void inicializarBolsa(tBolsa& bolsa) {

}

tFicha robar(tBolsa& bolsa) {

}

void repartir(tBolsa& bolsa, tSoportes soportes) {

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