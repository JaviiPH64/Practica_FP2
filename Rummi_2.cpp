// Práctica FP2 Rummikub versión 1
// F. Javier Peña Hernández
// 54212187Z
// Última actualización: 1.4 Jueves 24/03/2022
// Entrega: 03/04/2022

#include <iostream>
#include <istream>
#include <ostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h> //rand
#include <time.h>
#include <conio.h>
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
	tArrayJugada filaFichas{};
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
void colorTexto(tColor color);

//mis subprogramas
void ordenarNumBurbuja(tSoporte& soporte);
void elegirJugador();
int generaFilaAleatoria();
int generaColumnaAleatoria();
tFicha creaFicha();
string mostrarColor(tColor color);
string mostrarVerdaderoFalso(bool valorFicha);

void ordenarBurbuja();
void ordenamiento();

bool operator<(tFicha izq, tFicha der);
bool operator>(tFicha izq, tFicha der);

int numeroAleatorio();

//OK
//Muestra las opciones para las acciones principales del usuario 
//y devuelve la opción elegida por el usuario
int menu() {
	int opcion;
	cout << "Elige que quieres hacer: " << endl;
	cout << "1: ordenar por numero, 2: ordenar por color, 3: sugerir, 4: poner, 0: FIN" << endl;
	cin >> opcion;
	return opcion;
}

//Programa principal
int main() {
	//Inicializar el estado del juego: la bolsa con todas las fichas + el tablero sin jugadas
	//+ el contador de jugadores en bloqueo a 0 + el fin del juego a false
	srand(time(NULL));
	tBolsa bolsa;
	inicializarBolsa(bolsa);						//se inicializa la bolsa
	mostrar(bolsa);
	cout << endl;
	tTablero tablero;								//se inicializa el tablero
	tSoporte soporte1;
	tSoporte soporte2;
	tSoportes soportes = { soporte1, soporte2 };	//soportes

	cout << "numero fichas soporte 1:" << soporte1.numFichasSoporte << endl;
	
	repartir(bolsa, soportes);
	cout << bolsa.fichasDisponibles << endl;
	mostrar(soporte1);
	cout << endl;
	cout << soporte1.numFichasSoporte << endl;
	mostrar(soporte2);
	mostrar(bolsa);

	return 0;
}

int numeroAleatorio() {
	int num = rand() % 10;
	cout << num << endl;
	return num;
}

//OK
//Elegimos aleatoriamente quién empieza el juego.
void elegirJugador() {
	string jugador1, jugador2;
	cout << "Introduce el nombre del primer jugador " << endl;
	cin >> jugador1;
	cout << "Introduce el nombre del segundo jugador " << endl;
	cin >> jugador2;
	int a = rand() % 2;
	a++;
	if (a == 1) {
		cout << "El jugador que comienza es: " << jugador1 << endl;
	}
	else {
		cout << "El jugador que comienza es: " << jugador2 << endl;
	}
}

//OK
//Le damos a cada casilla de la bolsa el valor true
//Inicializa la bolsa de fichas de manera que estén todas disponibles
void inicializarBolsa(tBolsa& bolsa) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < NUM_FICHAS; j++) {
			bolsa.bolsa_fichas[i][j] = true;
		}
	}
}

//OK
//Genera un valor aleatorio para seleccionar una fila
int generaFilaAleatoria() {
	srand(time(NULL));
	return rand() % 8;
}

//OK
//Genera un valor aleatorio para seleccionar una columna
int generaColumnaAleatoria() {
	srand(time(NULL));
	return rand() % (NUM_FICHAS);
}

//OK
tFicha creaFicha() {
	tFicha fichaGenerada{};
	fichaGenerada.numero = generaColumnaAleatoria() + 1;
	fichaGenerada.color = tColor(generaFilaAleatoria() % NUM_COLORES);
	return fichaGenerada;
}

//REVISAR
//Devuelve una ficha obtenida de la bolsa. Empieza en una ficha situada en una fila
//y una columna seleccionadas aleatoriamente. Si la ficha está disponible, devuelve la misma.
//Si ya ha sido usada, se avanza por el array bidimensional desde esa posición y por filas
//hasta encontrar una ficha disponible que devolver. Si llega al final del array sin encontrar
//una ficha disponible seguirá buscando desde el principio. Si no quedan fichas en la bolsa, 
//devuelve una ficha con el número -1.

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
		if (bolsa.bolsa_fichas[fila][columna] == true) {
			fichaRobada.numero = columna + 1;
			fichaRobada.color = tColor(fila % NUM_COLORES);
			bolsa.fichasDisponibles--;
			bolsa.bolsa_fichas[fila][columna] = false;
			aux = true;
			cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
			return fichaRobada;
		}
		else { //if (bolsa.bolsa_fichas[fila][columna] == false)
			if (fila == 7 && columna == 9) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < NUM_FICHAS; j++) {
						if (bolsa.bolsa_fichas[i][j] == true) {
							fichaRobada.numero = j + 1;
							fichaRobada.color = tColor(i % NUM_COLORES);
							bolsa.fichasDisponibles--;
							bolsa.bolsa_fichas[i][j] = false;
							aux = true;
							cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
							return fichaRobada;
						}
					}
				}
			}
			else if (fila < 7 && columna == 9) {
				for (int i = fila + 1; i < 8; i++) {
					for (int j = 0; j < NUM_FICHAS; j++) {
						if (bolsa.bolsa_fichas[i][j] == true) {
							fichaRobada.numero = j + 1;
							fichaRobada.color = tColor(i % NUM_COLORES);
							bolsa.fichasDisponibles--;
							bolsa.bolsa_fichas[i][j] = false;
							aux = true;
							cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
							return fichaRobada;
						}
					}
				}
			}
			else {
				for (int i = fila; i < 8; i++) {
					for (int j = columna + 1; j < NUM_FICHAS; j++) {
						if (bolsa.bolsa_fichas[i][j] == true) {
							fichaRobada.numero = j + 1;
							fichaRobada.color = tColor(i % NUM_COLORES);
							bolsa.fichasDisponibles--;
							bolsa.bolsa_fichas[i][j] = false;
							aux = true;
							cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
							return fichaRobada;
						}
					}
				}
			}
		}
		if (aux == false) {
			for (int k = 0; k < 8; k++) {
				for (int l = 0; l < NUM_FICHAS; l++) {
					if (bolsa.bolsa_fichas[k][l] == true) {
						fichaRobada.numero = l + 1;
						fichaRobada.color = tColor(k % NUM_COLORES);
						bolsa.fichasDisponibles--;
						bolsa.bolsa_fichas[k][l] = false;
						aux = true;
						cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
						return fichaRobada;
					}
				}
			}
		}
	}
}

//REVISAR
//Obtiene INI_FICHAS de la bolsa para cada jugador, colocándolas en sus soportes. Lo hará valiéndose
//del subprograma *robar* para obtener cada una de las fichas.

void repartir(tBolsa& bolsa, tSoportes soportes) {
	for (int i = 0; i < INI_FICHAS; i++) {
		tFicha fichaRobada = (robar(bolsa));
		soportes[0].fichas[i] = fichaRobada;
		soportes[0].numFichasSoporte++;
	}

	/*while (soportes[0].numFichasSoporte != INI_FICHAS) {
		soportes[0].fichas[soportes[0].numFichasSoporte] == robar(bolsa);
		soportes[0].numFichasSoporte++;
	}
	while (soportes[1].numFichasSoporte != INI_FICHAS) {
		soportes[1].fichas[soportes[1].numFichasSoporte] == robar(bolsa);
		soportes[1].numFichasSoporte++;
	}*/
}

//REVISAR
//hecho en base al ejemplo de la diapositiva 14 del tema 2
//Ordena las fichas del soporte por números, de menor a mayor.
void ordenamiento() {
	int numeros[] = { 4,2,3,1,5 };
	int i, pos, aux;

	for (i = 0; i < 5; i++) {
		pos = i;
		aux = numeros[i];

		while ((pos > 0) && (numeros[pos - 1] > aux)) {
			numeros[pos] = numeros[pos - 1];
			pos--;
		}
		numeros[pos] = aux;
	}

	cout << "Orden ascendente: ";
	for (i = 0; i < 5; i++) {
		cout << numeros[i] << " ";
	}
}

void ordenarBurbuja() {
	int numeros[5] = { 4,1,2,3,5 };
	int i, j, aux;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (numeros[j] > numeros[j + 1]) {
				aux = numeros[j];
				numeros[j] = numeros[j + 1];
				numeros[j + 1] = aux;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		cout << numeros[i] << endl;
	}
}

bool operator<(tFicha izq, tFicha der) {
	return (izq.numero < der.numero);
}

bool operator>(tFicha izq, tFicha der) {
	return (izq.numero > der.numero);
}

void ordenarPorNum(tSoporte& soporte) {
	int i, pos, aux;
	tColor colorAux = rojo;

	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		pos = i;
		aux = soporte.fichas[i].numero;
		colorAux = soporte.fichas[i].color;

		while ((pos > 0) && (soporte.fichas[i - 1].numero > aux)) {
			soporte.fichas[pos] = soporte.fichas[pos - 1];
			pos--;
		}
		soporte.fichas[pos].numero = aux;
		soporte.fichas[pos].color = colorAux;
	}
}

void ordenarNumBurbuja(tSoporte& soporte) {
	int aux;
	tColor caux{};
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		for (int j = 0; j < soporte.numFichasSoporte; j++) {
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

//OK
//Devuelve true si las fichas son iguales (mismo número y mismo color) y false en caso contrario.
bool operator==(tFicha izq, tFicha der) {
	return ((izq.color == der.color) && (izq.numero == der.numero));
}

//OK
//Devuelve la posición (índice) de la ficha en la jugada, o -1 si no está.
int buscar(const tJugada& jugada, tFicha ficha) {
	if (jugada.cont == 0) {
		return -1;
	}
	else {
		for (int i = 0; i < jugada.cont; i++) {
			if (jugada.filaFichas[i] == ficha) {
				return i + 1;
			}
		}
	}
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
void eliminaFichas(tSoporte& soporte, const tJugada& jugada) {

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

//OK
//Devuelve la posición (índice) del soporte que acumula el menor número de puntos
//(suma de los números de sus fichas). Se usará para determinar el ganador en caso de bloqueo.
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

//OK
//Muestra la ficha: número de la ficha ocupando dos posiciones de pantalla y en el color
//correspondiente, y dejando dos espacios a continuación
void mostrar(tFicha ficha) {
	colorTexto(ficha.color);
	cout << setw(2) << ficha.numero << " ";
	colorTexto(blanco);
}

//OK
//Muestra el estado de la bolsa
void mostrar(const tBolsa& bolsa) {
	for (int fila = 0; fila < 8; fila++) {
		cout << " " << endl;
		for (int columna = 0; columna < NUM_FICHAS; columna++) {
			tFicha ficha{};
			ficha.color = tColor(fila % NUM_COLORES);
			ficha.numero = columna + 1;
			if (bolsa.bolsa_fichas[fila][columna] == true) {
				mostrar(ficha);
			}
			else {
				cout << " * ";
			}
		}
	}
}

//OK
//Muestra en una línea las fichas de la jugada
void mostrar(const tJugada& jugada) {
	for (int i = 0; i < jugada.cont; i++) {
		mostrar(jugada.filaFichas[i]);
	}
}

//OK
//Muestra las jugadas del tablero, numeradas desde 1
void mostrar(const tTablero& tablero) {
	for (int i = 0; i < tablero.numJugadas; i++) {
		cout << i + 1 << ": ";
		mostrar(tablero.jugadas[i]);
		cout << endl;
	}
}

//OK
//Muestra las fichas que hay en el soporte
void mostrar(const tSoporte& soporte) {
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		mostrar(soporte.fichas[i]);
	}
}

//OK
//Muestra los números de 1 a num (lo usaremos para mostrarlos debajo de un soporte
//y facilitar así al usuario la selección de fichas).
void mostrarIndices(int num) {
	for (int i = 0; i < num; i++) {
		cout << i + 1;
	}
}

//OK
string mostrarColor(tColor color) {
	switch (color) {
	case 0:
		return "Rojo";
		break;
	case 1:
		return "Verde";
		break;
	case 2:
		return "Azul";
		break;
	case 3:
		return "Amarillo";
		break;
	}
}

//OK
string mostrarVerdaderoFalso(bool valorFicha) {
	if (valorFicha == 0) {
		return "false";
	}
	else {
		return "true";
	}
}

//OK
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