#include "Tablero.h"
#include "Plano.h"

void Tablero::validarDimensiones(unsigned int ancho, unsigned int alto, unsigned int profundidad) const {
	if (!((1 <= ancho) && (1 <= alto) && (1 <= profundidad))) {
		throw std::out_of_range("Las dimensiones son invalidas");
	}
}

void Tablero::validarPosicion(Vector<unsigned int> *coordenadas) const {

	unsigned int x = coordenadas->obtenerElemento(0);
	unsigned int y = coordenadas->obtenerElemento(1);
	unsigned int z = coordenadas->obtenerElemento(2);

	unsigned int alto = this->obtenerAlto();
	unsigned int ancho = this->obtenerAncho();
	unsigned int profundidad = this->obtenerProfundidad();

	if (!(x < ancho && y < alto && z < profundidad)) {
		throw std::out_of_range("Las coordenadas no pertenecen al tablero");
	}
}

void Tablero::inicializarCasilleros() {

	Lista<Lista<Casillero*>*> *columna;
	Lista<Casillero*> *fila;
	Casillero *casillero;

	/* Recorre el tablero para crear los punteros a Casilleros */
	for (unsigned int x = 0; x < this->obtenerAncho(); x++) {

		columna = new Lista<Lista<Casillero*>*>();
		this->tablero->agregarElemento(columna);

		for (unsigned int y = 0; y < this->obtenerAlto(); y++) {

			fila = new Lista<Casillero*>();
			columna->agregarElemento(fila);

			for (unsigned int z = 0; z < this->obtenerProfundidad(); z++) {

				casillero = new Casillero(x, y, z);
				fila->agregarElemento(casillero);
			}
		}
	}

	this->inicializarPlanos();
}

void Tablero::inicializarPlanos() {

	Lista<Lista<Casillero*>*> *columna;
	Lista<Casillero*> *fila;
	Casillero *casillero;
	Plano *planoXY;
	Plano *planoXZ;
	Plano *planoYZ;

	/* Recorre el tablero para asignarle a los Casilleros sus Planos con Casilleros vecinos */
	tablero->iniciarCursor();

	while (tablero->avanzarCursor()) {

		columna = tablero->obtenerCursor();
		columna->iniciarCursor();

		while (columna->avanzarCursor()) {

			fila = columna->obtenerCursor();
			fila->iniciarCursor();

			while (fila->avanzarCursor()) {

				casillero = fila->obtenerCursor();

				planoXY = new Plano(this, casillero, XY);
				planoXZ = new Plano(this, casillero, XZ);
				planoYZ = new Plano(this, casillero, YZ);

				casillero->asignarPlanoXY(planoXY);
				casillero->asignarPlanoXZ(planoXZ);
				casillero->asignarPlanoYZ(planoYZ);

			}
		}
	}
}

Tablero::Tablero(bool inicializado) {

	this->dimensiones = new Vector<unsigned int>(3);
	this->dimensiones->reemplazarElemento(0, 5);
	this->dimensiones->reemplazarElemento(1, 5);
	this->dimensiones->reemplazarElemento(2, 5);

	this->tablero = new Lista<Lista<Lista<Casillero*>*>*>();

	if (inicializado) {
		this->inicializarCasilleros();
	}
}

Tablero::Tablero(unsigned int ancho, unsigned int alto, unsigned int profundidad, bool inicializado) {

	this->validarDimensiones(ancho, alto, profundidad);

	this->dimensiones = new Vector<unsigned int>(3);
	this->dimensiones->reemplazarElemento(0, ancho);
	this->dimensiones->reemplazarElemento(1, alto);
	this->dimensiones->reemplazarElemento(2, profundidad);

	this->tablero = new Lista<Lista<Lista<Casillero*>*>*>();

	if (inicializado) {
		this->inicializarCasilleros();
	}
}

Tablero::~Tablero() {

	delete this->dimensiones;

	tablero->iniciarCursor();

	while (tablero->avanzarCursor()) {

		Lista<Lista<Casillero*>*> *punteroX = tablero->obtenerCursor();
		punteroX->iniciarCursor();

		while (punteroX->avanzarCursor()) {

			Lista<Casillero*> *punteroY = punteroX->obtenerCursor();
			punteroY->iniciarCursor();

			while (punteroY->avanzarCursor()) {

				Casillero *punteroZ = punteroY->obtenerCursor();

				delete punteroZ; // Libera cada punteroZ
			}
			delete punteroY; // Libera cada punteroY
		}
		delete punteroX; // Libera cada punteroX
	}
	delete this->tablero; // Libera la estructura que contiene al Tablero
}

unsigned int Tablero::obtenerAncho() const {
	return this->dimensiones->obtenerElemento(0);
}

unsigned int Tablero::obtenerAlto() const {
	return this->dimensiones->obtenerElemento(1);
}

unsigned int Tablero::obtenerProfundidad() const {
	return this->dimensiones->obtenerElemento(2);
}

Lista<Lista<Lista<Casillero*>*>*>* Tablero::obtenerTablero() const {
	return this->tablero;
}

Casillero* Tablero::obtenerCasillero(Vector<unsigned int> *coordenadas) {
	this->validarPosicion(coordenadas);
	unsigned int x = coordenadas->obtenerElemento(0);
	unsigned int y = coordenadas->obtenerElemento(1);
	unsigned int z = coordenadas->obtenerElemento(2);
	return (this->tablero->obtenerElemento(x)->obtenerElemento(y)->obtenerElemento(z));
}

Casillero* Tablero::obtenerCasillero(unsigned int x, unsigned int y, unsigned int z) {
	return (this->tablero->obtenerElemento(x)->obtenerElemento(y)->obtenerElemento(z));
}
