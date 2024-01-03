#include "Plano.h"

void Plano::validarDimensiones(Tablero *tablero) {
	if (tablero->obtenerAlto() < 5 || tablero->obtenerAncho() < 5 || tablero->obtenerProfundidad() < 5) {
		throw std::out_of_range("Dimensiones del tablero inválidas");
	}
}

void Plano::validarPosicion(int fila, int columna) const {
	if (!(((this->columnaOrigen <= columna) && (columna < (this->ancho + this->columnaOrigen)))
			&& ((this->filaOrigen <= fila) && (fila < (this->alto + this->filaOrigen))))) {
		throw std::out_of_range("Las coordenadas no pertenecen al plano");
	}
}


void Plano::inicializarCasilleros() {

	Lista<Casillero*> *punteroColumna;
	Casillero *punteroFila;

	for (int columna = (this->columnaOrigen); columna < (this->columnaOrigen + DIMENSION_PLANO); columna++) {

		punteroColumna = new Lista<Casillero*>();
		this->plano->agregarElemento(punteroColumna);

		for (int fila = (this->filaOrigen); fila < (this->filaOrigen + DIMENSION_PLANO); fila++) {

			switch (this->perspectiva) {
				case (XY):
					punteroFila = this->tablero->obtenerCasillero(columna, fila, this->profundidad);
					break;
				case (XZ):
					punteroFila = this->tablero->obtenerCasillero(columna, this->profundidad, fila);
					break;
				case (YZ):
					punteroFila = this->tablero->obtenerCasillero(this->profundidad, columna, fila);
					break;
			}

			punteroColumna->agregarElemento(punteroFila);
		}
	}
}

int Plano::corregir(int coordenada, int limite) {
	int correccion = ((coordenada - 2) < 0) ? (0 + coordenada) : (2);
	correccion += ((coordenada + 2) > (limite - 1)) ? ((coordenada + 2) - (limite - 1)) : (0);
	return (coordenada - correccion);
}

Plano::Plano(Tablero *tablero, Casillero *casillero, unsigned int perspectiva) {
	this->validarDimensiones(tablero);
	switch (perspectiva) {
	case (XY):
		this->filaCentral = casillero->obtenerCoordenadas()->obtenerElemento(1);
		this->columnaCentral = casillero->obtenerCoordenadas()->obtenerElemento(0);
		this->profundidad = casillero->obtenerCoordenadas()->obtenerElemento(2);
		this->filaOrigen = corregir((this->filaCentral), (tablero->obtenerAlto()));
		this->columnaOrigen = corregir((this->columnaCentral), (tablero->obtenerAncho()));
		break;
	case (XZ):
		this->filaCentral = casillero->obtenerCoordenadas()->obtenerElemento(2);
		this->columnaCentral = casillero->obtenerCoordenadas()->obtenerElemento(0);
		this->profundidad = casillero->obtenerCoordenadas()->obtenerElemento(1);
		this->filaOrigen = corregir((this->filaCentral), (tablero->obtenerProfundidad()));
		this->columnaOrigen = corregir((this->columnaCentral), (tablero->obtenerAncho()));
		break;
	case (YZ):
		this->filaCentral = casillero->obtenerCoordenadas()->obtenerElemento(2);
		this->columnaCentral = casillero->obtenerCoordenadas()->obtenerElemento(1);
		this->profundidad = casillero->obtenerCoordenadas()->obtenerElemento(0);
		this->filaOrigen = corregir((this->filaCentral), (tablero->obtenerProfundidad()));
		this->columnaOrigen = corregir((this->columnaCentral), (tablero->obtenerAlto()));
		break;
	default:
		throw std::invalid_argument("No es posible generar el plano pedido");
	}

	this->ancho = 5;
	this->alto = 5;

	this->perspectiva = perspectiva;

	this->plano = new Lista<Lista<Casillero*>*>();
	this->tablero = tablero;

	this->inicializarCasilleros();
}

Plano::~Plano() {

	plano->iniciarCursor();

	while (plano->avanzarCursor()) {

		Lista<Casillero*> *punteroColumna = plano->obtenerCursor();
		punteroColumna->iniciarCursor();

		delete punteroColumna; // Libera cada punteroColumna
	}
	delete this->plano; // Libera la estructura que contiene al Plano
}

int Plano::obtenerFilaOrigen() const {
	return this->filaOrigen;
}

int Plano::obtenerColumnaOrigen() const {
	return this->columnaOrigen;
}

int Plano::obtenerFilaCentral() const {
	return this->filaCentral;
}

int Plano::obtenerColumnaCentral() const {
	return this->columnaCentral;
}

int Plano::obtenerProfundidad() const {
	return this->profundidad;
}

unsigned int Plano::obtenerAlto() const {
	return this->alto;
}

unsigned int Plano::obtenerAncho() const {
	return this->ancho;
}

int Plano::obtenerPerspectiva() const {
	return this->perspectiva;
}

Casillero* Plano::obtenerCasillero(unsigned int fila, unsigned int columna) const {
	this->validarPosicion(fila, columna);
	return (this->plano->obtenerElemento(columna - this->columnaOrigen)->obtenerElemento(fila - this->filaOrigen));
}

Lista<Lista<Casillero*>*>* Plano::obtenerPlano() const {
	return this->plano;
}
