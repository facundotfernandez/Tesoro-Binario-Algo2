#ifndef PLANO_H_
#define PLANO_H_

#include "Tablero.h"
#include "Constantes.h"

class Plano {

private:

	/* Es la fila del plano desde el que se comienzan los casilleros. */
	int filaOrigen;
	/* Es la columna del plano desde el que se comienzan los casilleros. */
	int columnaOrigen;

	/* Es la fila del casillero central del plano. */
	int filaCentral; 
	/* Es la columna del casillero central del plano. */
	int columnaCentral;

	/* Ancho y alto son las dimensiones del tablero. Siempre son iguales a 5*/
	int ancho; 
	int alto;

	/* Almacena el valor de la coordenada no observada en la perspectiva. */
	int profundidad;

	/* Perspectiva (XY,XZ,YZ) del Plano */
	int perspectiva;

	/* Plano bidimensional implementado a base de Listas */
	Lista<Lista<Casillero*>*> *plano;

	/* Plano tridimensional implementado a base de Listas */
	Tablero *tablero;

	/*
	 * pre : -
	 * post: Verifica si la posición del Casillero pertenece al Plano (@throws out_of_range).
	 */
	void validarPosicion(int fila, int columna) const;

	/*
	 * pre: -
	 * post: verifica que el tamaño del tablero ingresado sea >=5 (@throws out_of_range).
	 */
	void validarDimensiones(Tablero *tablero);

	/*
	 * pre : -
	 * post: Inicializa los punteros a Casilleros del Tablero.
	 */
	void inicializarCasilleros();

	/*
	 * pre: -
	 * post: Corrige la coordenada de Fila/Columna para obtener el origen de coordenadas
	 */
	int corregir(int coordenada, int limite);


public:

	/*
	 * pre : El Casillero debe pertenecer al Tablero y el Tablero debe tener dimensiones >= 5 (@throws out_of_range).
	 * post: Inicializa el Plano con dimensiones de tamaño 5, alrededor del Casillero dado.
	 */
	Plano(Tablero *tablero, Casillero *casillero, unsigned int perspectiva);

	/*
	 * pre : -
	 * post: Libera los recursos asociados al Plano.
	 */
	virtual ~Plano();

	/*
	 * pre : -
	 * post: Devuelve la fila de origen del plano.
	 */
	int obtenerFilaOrigen() const;

	/*
	 * pre : -
	 * post: Devuelve la columna de origen del plano.
	 */
	int obtenerColumnaOrigen() const;

	/*
	 * pre : -
	 * post: Devuelve la fila de cetral del plano.
	 */
	int obtenerFilaCentral() const;

	/*
	 * pre : -
	 * post: Devuelve la columna de central del plano.
	 */
	int obtenerColumnaCentral() const;

	/*
	 * pre : -
	 * post: Devuelve la profundidad del plano.
	 */
	int obtenerProfundidad() const;

	/*
	 * pre : -
	 * post: Devuelve el alto del Plano.
	 */
	unsigned int obtenerAlto() const;

	/*
	 * pre : -
	 * post: Devuelve el ancho del Plano.
	 */
	unsigned int obtenerAncho() const;

	/*
	 * pre : -
	 * post: Devuelve la perspectiva del Plano.
	 */
	int obtenerPerspectiva() const;

	/*
	 * pre : La posición del Casillero debe pertenecer al Plano (@throws out_of_range).
	 * post: Devuelve el puntero al Casillero según las coordenadas dadas.
	 */
	Casillero* obtenerCasillero(unsigned int fila, unsigned int columna) const;

	/*
	 * pre : -
	 * post: Devuelve el puntero a la estructura de Listas que contiene al Plano.
	 */
	Lista<Lista<Casillero*>*>* obtenerPlano() const;
};

#endif /* PLANO_H_ */
