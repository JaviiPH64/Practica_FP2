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
void inicializarBolsa(tBolsa& bolsa);
void inicializarTablero(tTablero& tablero);
int generaFilaAleatoria();
int generaColumnaAleatoria();
string mostrarColor(tColor color);
string mostrarVerdaderoFalso(bool valorFicha);

//Muestra las opciones para las acciones principales del usuario 
//y devuelve la opción elegida por el usuario
int menu() {
	tBolsa bolsa;
	tTablero tablero;
	elegirJugador();
	inicializarBolsa(bolsa);
	return 0;
}

//Programa principal
int main() {
	cout << "Hola mundo" << endl;
	elegirJugador();
	tBolsa bolsa;
	inicializarBolsa(bolsa);
	mostrar(bolsa);

	return 0;
}

//le damos a cada casilla de la bolsa el valor true
//Inicializa la bolsa de fichas de manera que estén todas disponibles
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

//Devuelve una ficha obtenida de la bolsa. Empieza en una ficha situada en una fila
//y una columna seleccionadas aleatoriamente. Si la ficha está disponible, devuelve la misma.
//Si ya ha sido usada, se avanza por el array bidimensional desde esa posición y por filas
//hasta encontrar una ficha disponible que devolver. Si llega al final del array sin encontrar
//una ficha disponible seguirá buscando desde el principio. Si no quedan fichas en la bolsa, 
//devuelve una ficha con el número -1.
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

//REVISAR
//Obtiene INI_FICHAS de la bolsa para cada jugador, colocándolas en sus soportes. Lo hará valiéndose
//del subprograma *robar* para obtener cada una de las fichas.
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

//REVISAR
//hecho en base al ejemplo de la diapositiva 14 del tema 2
//Ordena las fichas del soporte por números, de menor a mayor.
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

//REVISAR
//Ordena las fichas del soporte por colores, y dentro de los colores, de menor a mayor número.
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

//Devuelve true si las fichas son iguales (mismo número y mismo color) y false en caso contrario.
bool operator==(tFicha izq, tFicha der) {
	return ((izq.color == der.color) && (izq.numero == der.numero));
}

//Devuelve la posición (índice) de la ficha en la jugada, o -1 si no está.
int buscar(const tJugada& jugada, tFicha ficha) {
	return 0;
}

//Muestra las posibles series que se pueden crear con las fichas del soporte
void mostrarSeries(tSoporte soporte) {

}

//Muestra las posibles escaleras que se pueden crear con las fichas del soporte
void mostrarEscaleras(tSoporte soporte) {

}

//Añade en el tablero la nueva jugada
void nuevaJugada(tTablero& tablero, const tJugada& jugada) {

}

//Elimina del soporte las fichas que hay en la jugada
void eliminaFichas(tTablero& tablero, const tJugada& jugada) {

}

//Permite al usuario crear una jugada con fichas que haya en su soporte
void nuevaJugada(tSoporte soporte, tJugada& jugada) {

}

//Intenta colocar la ficha en la jugada, sea esta una serie o una escalera, en cuyo caso lo
//intenta en ambos extremos. Devuelve true si consigue colocar la ficha y false en caso contrario.
bool ponerFicha(tJugada& jugada, tFicha ficha) {
	return true;
}

//Permite al usuario colocar fichas de su soporte en el tablero, como nuevas series o escaleras, o
//fichas independientes en jugadas que haya sobre el tablero.
bool jugar(tTablero& tablero, tSoporte& soporte) {
	return true;
}

//REVISAR
//Devuelve la posición (índice) del soporte que acumula el menor número de puntos
//(suma de los números de sus fichas). Se usará para determinar el ganador en caso de bloqueo.
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

//Muestra la ficha: número de la ficha ocupando dos posiciones de pantalla y en el color
//correspondiente, y dejando dos espacios a continuación
void mostrar(tFicha ficha) {

}

//Muestra el estado de la bolsa
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

//Muestra en una línea las fichas de la jugada
void mostrar(const tJugada& jugada) {

}

//Muestra las jugadas del tablero, numeradas desde 1
void mostrar(const tTablero& tablero) {

}

//REVISAR
//Muestra las fichas que hay en el soporte
void mostrar(const tSoporte& soporte) {
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		cout << soporte.numFichasSoporte;

	}
}

//Muestra los números de 1 a num (lo usaremos para mostrarlos debajo de un soporte
//y facilitar así al usuario la selección de fichas).
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
