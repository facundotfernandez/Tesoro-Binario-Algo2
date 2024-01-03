#ifndef CASILLERO_H_
#define CASILLERO_H_

#include "Descripcion.h"
#include "Constantes.h"
#include "Vector.h"

/* forward declaration de la clase Plano */
class Plano;

/* forward declaration de la clase Tablero */
class Tablero;

/* forward declaration de la clase Tablero */
class Descripcion;

class Casillero {

private:

	/* Coordenadas (x,y,z) del Casillero. */
	Vector<unsigned int> *coordenadas;

	/* Descripción del Casillero. */
	Descripcion *descripcion;

	Plano *planoXY;
	Plano *planoXZ;
	Plano *planoYZ;

	/*
	 * pre : -
	 * post: Verifica que el Casillero tenga el tipoCasillero buscado (@throws logic_error).
	 */
	void validarDescripcion(unsigned int tipoCasillero) const;

	/*
	 * pre : -
	 * post: Asigna las coordenadas dadas al atributo coordenadas.
	 */
	void asignarCoordenadas(unsigned int x, unsigned int y, unsigned int z);

	/*
	 * pre : -
	 * post: Asigna los datos tipoCasillero y idJugador del Casillero.
	 */
	void asignarDescripcionCorta(unsigned int tipoCasillero, unsigned int idJugador);

	/*
	 * pre : El Casillero debe ser de tipo inactivo (@throws logic_error).
	 * post: Asigna el dato inactivoHasta del Casillero.
	 */
	void asignarInactivoHasta(unsigned int inactivoHasta);

	/*
	 * pre : El Casillero debe ser de tipo blindado (@throws logic_error).
	 * post: Asigna el dato blindadoHasta del Casillero.
	 */
	void asignarBlindadoHasta(unsigned int blindadoHasta);

	/*
	 * pre : El Casillero debe ser de tipo partido (@throws logic_error).
	 * post: Asigna el dato de las coordenadas del otro tesoro partido asociado al Casillero.
	 */
	void asignarCoordenadasPartido(Vector<unsigned int> *coordenadasPartido);

public:

	/*
	 * pre : -
	 * post: Se inicializa el Casillero con las coordenadas (x,y,z) dadas y la descripción corresponde a un Casillero vacío.
	 */
	Casillero(unsigned int x, unsigned int y, unsigned int z);

	/*
	 * pre : -
	 * post: Devuelve la coordenada X del Casillero.
	 */
	unsigned int obtenerX() const;

	/*
	 * pre : -
	 * post: Devuelve la coordenada Y del Casillero.
	 */
	unsigned int obtenerY() const;

	/*
	 * pre : -
	 * post: Devuelve la coordenada Z del Casillero.
	 */
	unsigned int obtenerZ() const;

	/*
	 * pre : El casillero debe ser de tipo inactivo o destruido (@throws logic_error).
	 * post: Devuelve el dato inactivoHasta del casillero, dato que figura en su descripción.
	 */
	unsigned int obtenerInactivoHasta() const;

	/*
	 * pre : -.
	 * post: Devuelve el plano de 5x5 con perspectiva XY asociado al casillero, dato que figura en su descripción.
	 */
	Plano* obtenerPlanoXY() const;

	/*
	 * pre : -.
	 * post: Devuelve el plano de 5x5 con perspectiva XZ asociado al casillero, dato que figura en su descripción.
	 */
	Plano* obtenerPlanoXZ() const;

	/*
	 * pre : -.
	 * post: Devuelve el plano de 5x5 con perspectiva YZ asociado al casillero, dato que figura en su descripción.
	 */
	Plano* obtenerPlanoYZ() const;

	/*
	 * pre : -.
	 * post: Asigna el plano de 5x5 con perspectiva XY asociado al casillero en su descripción.
	 */
	void asignarPlanoXY(Plano *planoXY);

	/*
	 * pre : -.
	 * post: Asigna el plano de 5x5 con perspectiva XZ asociado al casillero en su descripción.
	 */
	void asignarPlanoXZ(Plano *planoXZ);

	/*
	 * pre : -.
	 * post: Asigna el plano de 5x5 con perspectiva YZ asociado al casillero en su descripción.
	 */
	void asignarPlanoYZ(Plano *planoYZ);

	/*
	 * pre : -
	 * post: Libera los recursos asociados al Casillero.
	 */
	virtual ~Casillero();

	/*
	 * pre : -
	 * post: Devuelve el puntero al Vector de coordenadas del casillero.
	 */
	Vector<unsigned int>* obtenerCoordenadas() const;

	/*
	 * pre : -
	 * post: Devuelve el dato tipoCasillero, dato que figura en su descripción.
	 */
	unsigned int obtenerTipoCasillero() const;

	/*
	 * pre : -
	 * post: Devuelve el dato idJugador del casillero, dato que figura en su descripción.
	 */
	unsigned int obtenerIdJugador() const;

	/*
	 * pre : El casillero debe ser de tipo blindado (@throws logic_error).
	 * post: Devuelve el dato blindadoHasta del casillero, dato que figura en su descripción.
	 */
	unsigned int obtenerBlindadoHasta() const;

	/*
	 * pre : El casillero debe ser de tipo partido (@throws logic_error).
	 * post: Devuelve un puntero al tesoro asociado al casillero, dato que figura en su descripción.
	 */
	Casillero * obtenerAsociado() const;

	/*
	 * pre : -
	 * post: Reemplaza las coordenadas del Casillero, a partir de un puntero a Vector<unsigned int> dado.
	 */
	void reemplazarCoordenadas(Vector<unsigned int> *coordenadas);

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo vacío.
	 */
	void convertirAVacio();

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo tesoro, con el idJugador dado.
	 */
	void convertirATesoro(unsigned int idJugador);

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo espía, con el idJugador dado.
	 */
	void convertirAEspia(unsigned int idJugador);

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo inactivo, con el idJugador y inactivoHasta dados.
	 */
	void convertirAInactivo(unsigned int idJugador, unsigned int inactivoHasta);

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo blindado, con el idJugador y blindadoHasta dados.
	 */
	void convertirABlindado(unsigned int idJugador, unsigned int blindadoHasta);

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo mina, con el idJugador dado.
	 */
	void convertirAMina(unsigned int idJugador);

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo partido, con el idJugador y coordenadas dados.
	 */
	void convertirAPartido(unsigned int idJugador, Casillero *casilleroAsociado);

	/*
	 * pre : -
	 * post: Reemplaza la descripción del Casillero y lo convierte a Casillero de tipo destruido con inactivoHasta dado.
	 */
	void convertirADestruido(unsigned int inactivoHasta);

	/*
	 * pre : las coordenadas no pueden ser NULL. En caso de serlo devuelve error (out_of_range)
	 * post: devuelve true si las coordenadas pasadas por parámetro son las mismas que las del casillero.
	 */
	bool compararCoordenadas(Vector<unsigned int> *coordenadas);
};

#endif /* CASILLERO_H_ */
