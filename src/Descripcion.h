#ifndef DESCRIPCION_H_
#define DESCRIPCION_H_

#ifndef NULL
#define NULL 0
#endif /* NULL*/

#include "Vector.h"
#include "Casillero.h"

/* forward declaration de la clase Casillero */
class Casillero;

class Descripcion {

private:

	unsigned int tipoCasillero;
	unsigned int idJugador;
	unsigned int inactivoHasta;
	unsigned int blindadoHasta;
	Casillero *casilleroAsociado; //Casillero Asociado a este casillero.

public:

	/*
	 * pre : -
	 * post: Inicializa una Descripción con sus atributos en cero y el casilleroAsociado en NULL.
	 */
	Descripcion();

	/*
	 * pre : -
	 * post: Inicializa una Descripción con sus atributos en cero y el casillero Asociado pasado como parámetro.
	 */
	Descripcion(Casillero *casilleroAsociado);

	/*
	 * pre : -
	 * post: Libera los recursos asociados a la Descripción.
	 */
	virtual ~Descripcion();

	/*
	 * pre : -
	 * post: Devuelve el dato tipoCasillero del casillero.
	 */
	unsigned int obtenerTipoCasillero() const;

	/*
	 * pre : -
	 * post: Devuelve el dato idJugador del casillero.
	 */
	unsigned int obtenerIdJugador() const;

	/*
	 * pre : -
	 * post: Devuelve el dato inactivoHasta del casillero.
	 */
	unsigned int obtenerInactivoHasta() const;

	/*
	 * pre : -
	 * post: Devuelve el dato blindadoHasta del casillero.
	 */
	unsigned int obtenerBlindadoHasta() const;

	/*
	 * pre : -
	 * post: Devuelve el casillero Asociado a este casillero.
	 */
	Casillero *obtenerCasilleroAsociado() const;

	/*
	 * pre : -
	 * post: Reemplaza el dato tipoCasillero del casillero.
	 */
	void reemplazarTipoCasillero(unsigned int nuevoTipoCasillero);

	/*
	 * pre : -
	 * post: Reemplaza el dato idJugador del casillero.
	 */
	void reemplazarIdJugador(unsigned int nuevoIdJugador);

	/*
	 * pre : -
	 * post: Reemplaza el dato inactivoHasta del casillero.
	 */
	void reemplazarInactivoHasta(unsigned int nuevoInactivoHasta);

	/*
	 * pre : -
	 * post: Reemplaza el dato blindadoHasta del casillero.
	 */
	void reemplazarBlindadoHasta(unsigned int nuevoBlindadoHasta);

	/*
	 * pre : el casilleroAsociado no pueden ser NULL. En caso de serlo devuelve error (out_of_range).
	 * post: Reemplaza el casilleroAsociado.
	 */
	void reemplazarCasilleroAsociado(Casillero *casilleroAsociado);

};

#endif /* DESCRIPCION_H_ */
