#ifndef CARTA_H_
#define CARTA_H_

#include "Constantes.h"
#include <cstdlib>

class Carta {

private:

	unsigned int tipoCarta;

public:

	/*
	 Pre: -
	 Post: Se crea una carta del tipo indicado

	 */
	Carta(unsigned int tipoCarta);
	/*
	 Pre: Se le entrega a la funcion un objeto Carta

	 Post: Se liberan los recursos asociados a la Carta
	 */
	virtual ~Carta();

	/*
	 Pre: -

	 Post: Devuelve un numero que indica el tipo de la carta

	 */
	unsigned int obtenerTipoCarta() const;

	/*
	 Pre: -

	 Post: Cambia el tipo de la carta por el especificado
	 */
	void reemplazarTipoCarta(unsigned int nuevoTipoCarta);

};

#endif /* CARTA_H_ */
