// Práctica FP2 Rummikub versión 1
// 1.4 Jueves 24/03/2022
// F. Javier Peña Hernández
// 54212187Z

#include <iostream>
#include <ostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h> //rand y RAND_MAX
#include <ctime>
using namespace std;

//Ficha: caracterizada por su color y su nº

enum tColor { rojo, verde, azul, amarillo, blanco };

struct tFicha {
	int numero;
	tColor color;
};

//Bolsa donde se encuentran las fichas que se reparten y se roban, inicialmente tiene todas las fichas

const int NUM_FICHAS = 10;
const int NUM_COLORES = 4;
const int TOTAL_FICHAS = NUM_FICHAS * 8;  //2 fichas iguales de cada número y color
const int INI_FICHAS = 9;

typedef bool tArrayBolsa[8][NUM_FICHAS];

struct tBolsa {
	tArrayBolsa bolsa_fichas{};
	int fichasDisponibles = TOTAL_FICHAS;
};

//Soporte: lista de tamaño variable de hasta MAX_FICHAS fichas

const int MAX_FICHAS = 50;
const int NUM_JUGADORES = 2;

typedef tFicha tArraySoporte[MAX_FICHAS];

struct tSoporte {
	tArraySoporte fichas{};
	int numFichasSoporte = 0;
};

typedef tSoporte tSoportes[NUM_JUGADORES];

const int MAX_JUGADAS = NUM_FICHAS * 2;

typedef tFicha tArrayJugada[NUM_FICHAS];

struct tJugada {
	tArrayJugada filaFichas;
	int cont = 0;
};

typedef tJugada tArrayTablero[MAX_JUGADAS];

struct tTablero {
	tArrayTablero jugadas;
	int numJugadas = 0;
};

//subprogramas

int menu();
void inicializarBolsa(tBolsa& bolsa);
tFicha robar(tBolsa& bolsa);
void repartir(tBolsa& bolsa, tSoportes soportes);
void ordenarPorNum(tSoporte& soporte);
void ordenarPorColor(tSoporte& soporte);
bool operator==(tFicha izq, tFicha der);
int buscar(const tJugada& jugada, tFicha ficha);
void mostrarSeries(tSoporte soporte);
void mostrarEscaleras(tSoporte soporte);
void nuevaJugada(tTablero& tablero, const tJugada& jugada);
void eliminaFichas(tSoporte& soporte, const tJugada& jugada);
void nuevaJugada(tSoporte soporte, tJugada& jugada);
bool ponerFicha(tJugada& jugada, tFicha ficha);
bool jugar(tTablero& tablero, tSoporte& soporte);
int menor(const tSoportes soportes);
void mostrar(tFicha ficha);
void mostrar(const tBolsa& bolsa);
void mostrar(const tJugada& jugada);
void mostrar(const tTablero& tablero);
void mostrar(const tSoporte& soporte);
void mostrarIndices(int num);

//mis subprogramas
string mostrarColor(tColor color);
string mostrarVerdaderoFalso(bool valorFicha);

//le damos a cada casilla de la bolsa el valor true
void inicializarBolsa(tBolsa& bolsa) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < NUM_FICHAS; j++) {
			bolsa.bolsa_fichas[i][j] = true;
		}
	}
}

//REVISAR
void inicializarTablero(tTablero& tablero) {
	for (int i = 0; i < MAX_JUGADAS; i++) {
		tablero.jugadas[i] = {};
		for (int j = 0; j < NUM_FICHAS; j++) {
			tablero.jugadas[i].filaFichas[j].color = blanco;
			tablero.jugadas[i].filaFichas[j].numero = 0;
		}
	}
}

int generaFilaAleatoria() {
	srand(time(NULL));
	return rand() % 8;
}
int generaColumnaAleatoria() {
	srand(time(NULL));
	return rand() % (NUM_FICHAS);
}

/*tFicha robar(tBolsa& bolsa, tSoporte soporte) {
	bool aux = false;
	while (aux) {
		int fila = generaFilaAleatoria();
		int columna = generaColumnaAleatoria();
		if (bolsa.bolsa_fichas[fila][columna] == true) {
			tFicha ficha{ columna, tColor(fila) };
			aux = true;
			return ficha;
		}
	}
}*/

tFicha robar(tBolsa& bolsa) {
	int fila = generaFilaAleatoria();
	int columna = generaColumnaAleatoria();
	tFicha fichaRobada;
	fichaRobada.numero = columna;
	fichaRobada.color = tColor(fila % NUM_COLORES);
	if (bolsa.fichasDisponibles == 0) {
		fichaRobada.numero = -1;
	}
	else if (bolsa.bolsa_fichas[fila][columna] == true) {
		bolsa.fichasDisponibles--;
		bolsa.bolsa_fichas[fila][columna] = false;
	}
	else if (bolsa.bolsa_fichas[fila][columna] == false) {
		for (int i = fila; i < (8); i++) {
			for (int j = columna; j < NUM_FICHAS; j++) {
				if (bolsa.bolsa_fichas[i][j] == true) {
					fichaRobada.numero = columna;
					fichaRobada.color = tColor(fila % NUM_COLORES);
					bolsa.fichasDisponibles--;
					bolsa.bolsa_fichas[fila][columna] = false;
					break;
				}
				if (bolsa.bolsa_fichas[8][NUM_FICHAS] == false) {
					for (int i = 0; i < (8); i++) {
						for (int j = 0; j < NUM_FICHAS; j++) {
							if (bolsa.bolsa_fichas[i][j] == true) {
								fichaRobada.numero = columna;
								fichaRobada.color = tColor(fila % NUM_COLORES);
								bolsa.fichasDisponibles--;
								bolsa.bolsa_fichas[fila][columna] = false;
								break;
							}
						}
					}
				}
			}
		}
	}
	return fichaRobada;
}

void repartir(tBolsa& bolsa, tSoportes soportes) {
	while (soportes[0].numFichasSoporte != INI_FICHAS) {
		int fila = generaFilaAleatoria();
		int columna = generaColumnaAleatoria();
		if (bolsa.bolsa_fichas[fila][columna] == true) {
			tFicha ficha{ columna, tColor(fila % NUM_COLORES) };
			soportes[0].fichas[soportes[0].numFichasSoporte] = ficha;
			soportes[0].numFichasSoporte++;
			bolsa.bolsa_fichas[fila][columna] = false;
		}
	}

	while (soportes[1].numFichasSoporte != INI_FICHAS) {
		int fila = generaFilaAleatoria();
		int columna = generaColumnaAleatoria();
		if (bolsa.bolsa_fichas[fila][columna] == true) {
			tFicha ficha{ columna, tColor(fila) };
			soportes[1].fichas[soportes[1].numFichasSoporte] = ficha;
			soportes[1].numFichasSoporte++;
			bolsa.bolsa_fichas[fila][columna] = false;
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
	tArraySoporte fichasRojas{};
	tArraySoporte fichasVerdes{};
	tArraySoporte fichasAzules{};
	tArraySoporte fichasAmarillas{};
	int rojas = 0;
	int verdes = 0;
	int azules = 0;
	int amarillas = 0;
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		if (soporte.fichas[i].color == rojo) {
			fichasRojas[rojas] = soporte.fichas[i];
			rojas++;
		}
		else if (soporte.fichas[i].color == verde) {
			fichasVerdes[verdes] = soporte.fichas[i];
			verdes++;
		}
		else if (soporte.fichas[i].color == amarillo) {
			fichasAzules[azules] = soporte.fichas[i];
			azules++;
		}
		else {
			fichasAmarillas[amarillas] = soporte.fichas[i];
			amarillas++;
		}
	}
	soporte.numFichasSoporte = 0;
	if (rojas > 0) {
		for (int i = 0; i < rojas; i++) {
			soporte.fichas[i + soporte.numFichasSoporte] = fichasRojas[i];
			soporte.numFichasSoporte++;
		}
	}
	if (verdes > 0) {
		for (int i = 0; i < verdes; i++) {
			soporte.fichas[i + soporte.numFichasSoporte] = fichasVerdes[i];
			soporte.numFichasSoporte++;
		}
	}
	if (azules > 0) {
		for (int i = 0; i < azules; i++) {
			soporte.fichas[i + soporte.numFichasSoporte] = fichasAzules[i];
			soporte.numFichasSoporte++;
		}
	}
	if (amarillas > 0) {
		for (int i = 0; i < amarillas; i++) {
			soporte.fichas[i + soporte.numFichasSoporte] = fichasAmarillas[i];
			soporte.numFichasSoporte++;
		}
	}
}

bool operator==(tFicha izq, tFicha der) {
	return ((izq.color == der.color) && (izq.numero == der.numero));
}

int buscar(const tJugada& jugada, tFicha ficha) {
	return 0;
}

void mostrarSeries(tSoporte soporte) {

}

void mostrarEscaleras(tSoporte soporte) {

}

void nuevaJugada(tTablero& tablero, const tJugada& jugada) {

}

void eliminaFichas(tTablero& tablero, const tJugada& jugada) {

}

void nuevaJugada(tSoporte soporte, tJugada& jugada) {

}

bool ponerFicha(tJugada& jugada, tFicha ficha) {
	return true;
}

bool jugar(tTablero& tablero, tSoporte& soporte) {
	return true;
}

int menor(const tSoportes soportes) {
	int a = 0;
	int b = 0;
	for (int i = 0; i < soportes[0].numFichasSoporte; i++) {
		a = a + soportes[0].fichas[i].numero;
	}
	for (int j = 0; j < soportes[1].numFichasSoporte; j++) {
		b = b + soportes[1].fichas[j].numero;
	}
	if (a < b) {
		return a;
	}
	else if (b < a) {
		return b;
	}
	else {
		return 0;
	}
}

void mostrar(const tBolsa& bolsa) {
	for (int fila = 0; fila < 8; fila++) {
		cout << " " << endl;
		for (int columna = 0; columna < NUM_FICHAS; columna++) {
			tColor colorFicha = tColor(fila % NUM_COLORES);
			string color = mostrarColor(colorFicha);
			int colum = columna + 1;
			cout << "color: " << color << " numero: " << colum << " valor: " << mostrarVerdaderoFalso(bolsa.bolsa_fichas[fila][columna]) << " ";
		}
	}
}

void mostrar(const tJugada& jugada) {

}

void mostrar(const tTablero& tablero) {

}

void mostrar(const tSoporte& soporte) {
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		cout << soporte.numFichasSoporte;

	}
}

void mostrarIndices(int num) {

}

string mostrarColor(tColor color) {
	switch (color) {
	case 0:
		return "Rojo";
		break;
	case 1:
		return "Azul";
		break;
	case 2:
		return "Verde";
		break;
	case 3:
		return "Amarillo";
		break;
	}
}

string mostrarVerdaderoFalso(bool valorFicha) {
	if (valorFicha == 0) {
		return "false";
	}
	else {
		return "true";
	}
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

void mostrar(tFicha ficha) {
	colorTexto(ficha.color);
	cout << setw(2) << ficha.numero << " ";
	colorTexto(blanco);
}

void elegirJugador() {
	srand(time(NULL));
	int a = rand() % 2;
	a++;
	cout << "El jugador elegido es el: " << a << endl;
}

int menu() {
	tBolsa bolsa;
	tTablero tablero;
	elegirJugador();
	inicializarBolsa(bolsa);
	return 0;
}

int main() {
	cout << "Hola mundo" << endl;
	elegirJugador();
	tBolsa bolsa;
	inicializarBolsa(bolsa);
	mostrar(bolsa);


	return 0;
}
