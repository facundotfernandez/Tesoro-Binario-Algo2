#ifndef TABLERO_H_
#define TABLERO_H_

#include "Casillero.h"
#include "Lista.h"
#include "Vector.h"

class Plano;

class Tablero {

private:

	/* Vector de dimensiones (ancho,alto,profundidad) del Tablero */
	Vector<unsigned int> *dimensiones;

	/* Tablero tridimensional implementado a base de Listas */
	Lista<Lista<Lista<Casillero*>*>*> *tablero;

	/*
	 * pre : -
	 * post: Verifica si las dimensiones son de tamaño mayor a 0 (@throws out_of_range).
	 */
	void validarDimensiones(unsigned int ancho, unsigned int alto,
			unsigned int profundidad) const;

	/*
	 * pre : -
	 * post: Verifica si las coordenadas del Casillero pertenece al Tablero (@throws out_of_range).
	 */
	void validarPosicion(Vector <unsigned int>* coordenadas) const;

	/*
	 * pre : -
	 * post: Inicializa todos los Casilleros del tablero asignandoles
	 * 		 la descripcion correspondiente al tipo de Casillero vacío.
	 */
	void inicializarCasilleros();

	/*
	 * pre : -
	 * post: Inicializa todos los Planos vecinos de cada Casillero del tablero.
	 */
	void inicializarPlanos();

public:

	/*
	 * pre : -
	 * post: Inicializa el Tablero con dimensiones de tamaño 5.
	 */
	Tablero(bool inicializado = false);

	/*
	 * pre : El tamaño de las dimensiones debe ser mayor a 0 (@throws out_of_range).
	 * post: Inicializa el Tablero con dimensiones de tamaño dado, puede inicializar los casilleros con tipo vacio según se indique.
	 */
	Tablero(unsigned int ancho, unsigned int alto, unsigned int profundidad,
			bool inicializado = false);

	/*
	 * pre : -
	 * post: Libera los recursos asociados al Tablero.
	 */
	virtual ~Tablero();

	/*
	 * pre : -
	 * post: Devuelve el ancho del Tablero.
	 */
	unsigned int obtenerAncho() const;

	/*
	 * pre : -
	 * post: Devuelve el alto del Tablero.
	 */
	unsigned int obtenerAlto() const;

	/*
	 * pre : -
	 * post: Devuelve la profundidad del Tablero.
	 */
	unsigned int obtenerProfundidad() const;

	/*
	 * pre : -
	 * post: Devuelve el puntero a la estructura de Listas que contiene al Tablero.
	 */
	Lista<Lista<Lista<Casillero*>*>*>* obtenerTablero() const;

	/*
	 * pre : La posición del Casillero debe pertenecer al Tablero (@throws out_of_range).
	 * post: Devuelve el puntero al Casillero según las coordenadas dadas.
	 */
	Casillero* obtenerCasillero(Vector <unsigned int>* coordenadas);

	/*
	 * pre : La posición del Casillero debe pertenecer al Tablero (@throws out_of_range).
	 * post: Devuelve el puntero al Casillero según las coordenadas dadas.
	 */
	Casillero* obtenerCasillero(unsigned int x, unsigned int y, unsigned int z);

};

#endif /* TABLERO_H_ */
