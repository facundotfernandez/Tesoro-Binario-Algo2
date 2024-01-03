//
// Created by muribe on 09/10/23.
//

#ifndef TURNO_H
#define TURNO_H


#include "Jugador.h"

class Turno {
private:
	unsigned int turnoActual;
	Jugador * jugadorActual;
	unsigned int rondaActual;

public:

	/*
	 * Pre:
	 * Pos: Crea un turno con el turno actual en 1
	 */
	Turno();

	/*
	 * Pre:
	 * Pos: Crea un turno con el turno actual en 1 y la ronda en 1
	 */
	Turno(Jugador *);

	/*
	 * Pre:
	 * Pos: Crea un turno con el turnoActual y rondaActual dados
	 */
	Turno(unsigned int turnoActual, unsigned int rondaActual);

	/*
	 * Pos: Libera los recursos asociados al turno
	 */
	~Turno(); // TDA Turno

	/*
	 * Pre:
	 * Pos: Devuelve el turno actual
	 */
	unsigned int obtenerTurnoActual();

	/*
	 * Pre:
	 * Pos: Reemplaza el jugador actual por el pasado por parametro
	 */
	void reemplazarJugadorActual(Jugador *nuevoJugadorActual);

	/*
	 * Pre:
	 * Pos: Aumenta en uno (+1) el turno actual
	 */
	void avanzarRonda();

	/*
	 * Pre: -
	 * Pos: Devuelve la ronda actual.
	 */
	unsigned int obtenerRondaActual();

	/*
	 * Pre:
	 * Pos: Devuelve un puntero al jugador que debe jugar el turno actual
	 */
	Jugador *obtenerJugadorActual();

	/*
	 * Pre:
	 * Pos: Reemplaza el turno actual por el pasado por parametro
	 */
	void reemplazarTurnoActual(unsigned int nuevoTurnoActual);

	/*
	 * Pre:
	 * Pos: Aumenta en uno (+1) el turno actual
	 */
	void avanzarTurno();
};


#endif //TURNO_H
