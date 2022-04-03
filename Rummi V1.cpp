// Práctica FP2 Rummikub versión 1
// F. Javier Peña Hernández
// 54212187Z
// Entrega: 05/04/2022

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
	int numFichasJugada = 0;
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
	tSoporte soporte1 {};
	tSoporte soporte2 {};
	tSoportes soportes = {};	//soportes
	soportes[0] = soporte1;
	soportes[1] = soporte2;

	cout << "numero fichas soporte 1:" << soporte1.numFichasSoporte << endl;
	cout << "numero fichas soporte 2:" << soporte2.numFichasSoporte << endl;
	
	//repartir(bolsa, soportes);

	cout << "numero fichas soporte 1:" << soporte1.numFichasSoporte << endl;
	cout << "numero fichas soporte 2:" << soporte2.numFichasSoporte << endl;
	
	//mostrar(bolsa);

	//----------------------------------------------------------------------------------------//

	tFicha ficha0 = { 1, rojo };
	tFicha ficha1 = { 3, azul };
	tFicha ficha2 = { 8, amarillo };
	tFicha ficha3 = { 4, azul };
	tFicha ficha4 = { 5, verde };
	tFicha ficha5 = { 1, amarillo };
	tFicha ficha6 = { 2, rojo };
	tFicha ficha7 = { 3, rojo };
	tFicha ficha8 = { 2, azul };
	tFicha ficha9 = { 9, verde };
	soporte1.fichas[0] = ficha0;
	soporte1.fichas[1] = ficha1;
	soporte1.fichas[2] = ficha2;
	soporte1.fichas[3] = ficha3;
	soporte1.fichas[4] = ficha4;
	soporte1.fichas[5] = ficha5;
	soporte1.fichas[6] = ficha6;
	soporte1.fichas[7] = ficha7;
	soporte1.fichas[8] = ficha8;
	soporte1.fichas[9] = ficha9;
	soporte1.numFichasSoporte = 10;
	mostrar(soporte1); cout << " orden original";
	ordenarPorNum(soporte1);
	cout << endl;
	mostrar(soporte1); cout << " orden numeros";
	cout << endl;
	ordenarPorColor(soporte1);
	mostrar(soporte1); cout << " orden color";
	

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

//OK
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
			//cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
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
							//cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
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
							//cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
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
							//cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
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
						//cout << "Ficha asignada: " << fichaRobada.numero << "," << mostrarColor(fichaRobada.color) << endl;
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
		mostrar(soportes[0].fichas[i]);
		soportes[0].numFichasSoporte++;
	}
	cout << "fichas soporte 1 bucle: " << soportes[0].numFichasSoporte << endl;
	for (int j = 0; j < INI_FICHAS; j++) {
		tFicha fichaRobada = (robar(bolsa));
		soportes[1].fichas[j] = fichaRobada;
		mostrar(soportes[1].fichas[j]);
		soportes[1].numFichasSoporte++;
	}
	cout << "fichas soporte 2 bucle: " << soportes[1].numFichasSoporte << endl;
}

//OK
//Devuelve true si las fichas son iguales (mismo número y mismo color) y false en caso contrario.
bool operator==(tFicha izq, tFicha der) {
	return ((izq.color == der.color) && (izq.numero == der.numero));
}

bool operator<(tFicha izq, tFicha der) {
	return (izq.numero < der.numero);
}

bool operator>(tFicha izq, tFicha der) {
	return (izq.numero > der.numero);
}

//OK
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

//OK
//Ordena las fichas del soporte por colores, y dentro de los colores, de menor a mayor número.
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

//OK
//Devuelve la posición (índice) de la ficha en la jugada, o -1 si no está.
int buscar(const tJugada& jugada, tFicha ficha) {
	if (jugada.numFichasJugada == 0) {
		return -1;
	}
	else {
		for (int i = 0; i < jugada.numFichasJugada; i++) {
			if (jugada.filaFichas[i] == ficha) {
				return i + 1;
			}
		}
	}
}

tJugada esSerie(tSoporte soporte) {
	ordenarPorNum(soporte);
	mostrar(soporte);
	int num;
	int aux = 0;
	cout << "Elige el numero para la serie: ";
	cin >> num;
	tJugada serie{};
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		while (serie.numFichasJugada < 5) {
			if (soporte.fichas[i].numero = num) {
				serie.filaFichas[serie.numFichasJugada] = soporte.fichas[i];
				serie.numFichasJugada++;
			}
		}		
	}
	tColor colorSerie;
	for (int j = 0; j < serie.numFichasJugada; j++) {

	}
}

//Muestra las posibles series que se pueden crear con las fichas del soporte
void mostrarSeries(tSoporte soporte) {
	ordenarPorNum(soporte);
	tJugada serie{};
	int num = 0;
	int aux;
	for (int i = 0; i < soporte.numFichasSoporte; i++) {
		num++;
		aux = 0;
		for (int j = 0; j < soporte.numFichasSoporte; j++) {
			if (soporte.fichas[j].numero = num) {
				serie.filaFichas[aux] = soporte.fichas[j];
				serie.numFichasJugada++;
			}
		}
		if (serie.numFichasJugada > 2) {
			for (int k = 0; k < serie.numFichasJugada; k++) {

			}
		}
	}
}

//Muestra las posibles escaleras que se pueden crear con las fichas del soporte
void mostrarEscaleras(tSoporte soporte) {

}

//OK
//Añade en el tablero la nueva jugada
void nuevaJugada(tTablero& tablero, const tJugada& jugada) {
	tablero.jugadas[tablero.numJugadas] = jugada;
	tablero.numJugadas++;
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
	for (int i = 0; i < jugada.numFichasJugada; i++) {
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
