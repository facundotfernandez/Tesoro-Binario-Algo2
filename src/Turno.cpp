//
// Created by muribe on 09/10/23.
//

#include "Turno.h"


Turno::Turno(Jugador * jugadorActual) {
	// Iniciamos en el turno 1
	this->turnoActual = 1;
	this->rondaActual = 1;
	this->jugadorActual = jugadorActual;
}

Turno::Turno(unsigned int turnoActual, unsigned int rondaActual) {
	this->turnoActual = turnoActual;
	this->jugadorActual = NULL;
	this->rondaActual = rondaActual;
}

Turno::Turno() {
	// Iniciamos en el turno 1
	this->turnoActual = 1;
	this->jugadorActual = NULL;
}


Turno::~Turno() {
	// Auto-generated destructor stub
}


unsigned int Turno::obtenerTurnoActual() {
	return this->turnoActual;
}


void Turno::reemplazarTurnoActual(unsigned int turno) {
	this->turnoActual = turno;
}


Jugador * Turno::obtenerJugadorActual() {
	if (this->jugadorActual == NULL) {
		throw std::string("No se ha asignado un jugador al turno");
	}
	return this->jugadorActual;
}


void Turno::reemplazarJugadorActual(Jugador * nuevoJugadorActual) {
	this->jugadorActual = nuevoJugadorActual;
}

void Turno::avanzarRonda() {
	this->rondaActual += 1;
}

unsigned int Turno::obtenerRondaActual() {
	return this->rondaActual;
}

void Turno::avanzarTurno() {
	this->turnoActual += 1;
}
