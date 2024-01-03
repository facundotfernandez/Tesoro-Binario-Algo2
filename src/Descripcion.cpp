#include "Descripcion.h"

Descripcion::Descripcion() {
	this->tipoCasillero = 0;
	this->idJugador = 0;
	this->inactivoHasta = 0;
	this->blindadoHasta = 0;
	this->casilleroAsociado = NULL;
}

Descripcion::Descripcion(Casillero *casilleroAsociado) {
	this->tipoCasillero = 0;
	this->idJugador = 0;
	this->inactivoHasta = 0;
	this->blindadoHasta = 0;
	this->casilleroAsociado = casilleroAsociado;
}

Descripcion::~Descripcion() {
}

unsigned int Descripcion::obtenerTipoCasillero() const {
	return this->tipoCasillero;
}

unsigned int Descripcion::obtenerIdJugador() const {
	return this->idJugador;
}

unsigned int Descripcion::obtenerInactivoHasta() const {
	return this->inactivoHasta;
}

unsigned int Descripcion::obtenerBlindadoHasta() const {
	return this->blindadoHasta;
}

Casillero *Descripcion::obtenerCasilleroAsociado() const {
	return this->casilleroAsociado;
}

void Descripcion::reemplazarTipoCasillero(unsigned int nuevoTipoCasillero) {
	this->tipoCasillero = nuevoTipoCasillero;
}

void Descripcion::reemplazarIdJugador(unsigned int nuevoIdJugador) {
	this->idJugador = nuevoIdJugador;
}

void Descripcion::reemplazarInactivoHasta(unsigned int nuevoInactivoHasta) {
	this->inactivoHasta = nuevoInactivoHasta;
}

void Descripcion::reemplazarBlindadoHasta(unsigned int nuevoBlindadoHasta) {
	this->blindadoHasta = nuevoBlindadoHasta;
}

void Descripcion::reemplazarCasilleroAsociado(Casillero *casilleroAsociado) {
	if (casilleroAsociado == NULL){
		throw std::out_of_range("casilleroAsociado invalido");
	}
	this->casilleroAsociado = casilleroAsociado;
}
