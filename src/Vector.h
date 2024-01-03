#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdexcept>

template<class T> class Vector {

private:

	unsigned int longitud;
	T *elementos;

	/*
	 * pre : -
	 * post: Verifica si la posición pertenece al intervalo: [0, obtenerlongitud() - 1] (@throws out_of_range).
	 */
	void validarPosicion(unsigned int posicion) {
		if (!(posicion < this->longitud)) {
			throw std::out_of_range("El posicion no pertenece al vector");
		}
	}

public:

	/*
	 * pre : La longitud dada debe ser mayor a 0 (@throws invalid_argument).
	 * post: Inicializa un Vector de longitud dada y elementos en 0.
	 */
	Vector(unsigned int longitud) {

		if (longitud <= 0) {
			throw std::invalid_argument("La longitud debe ser mayor a 0");
		}

		this->longitud = longitud;
		this->elementos = new T[this->longitud];

		for (unsigned int i = 0; i < this->longitud; i++) {
			this->elementos[i] = 0;
		}
	}

	/*
	 * pre: -
	 * post: Libera los recursos asociados al vector.
	 */
	virtual ~Vector() {
		delete[] this->elementos;
	}

	/*
	 * pre: La posición pertenece al intervalo: [0, obtenerlongitud() - 1] (@throws out_of_range).
	 * post: Devuelve el elemento en la posición indicada.
	 */
	T obtenerElemento(unsigned int posicion) {
		this->validarPosicion(posicion);
		return this->elementos[posicion];
	}

	/*
	 * pre: -
	 * post: Devuelve la longitud del Vector
	 */
	unsigned int obtenerLongitud() {
		return this->longitud;
	}

	/*
	 * pre: La posición pertenece al intervalo: [0, obtenerlongitud() - 1] (@throws out_of_range).
	 * post: Reemplaza el elemento en la posición indicada por el elemento dado
	 */
	void reemplazarElemento(unsigned int posicion, T elemento) {
		this->validarPosicion(posicion);
		this->elementos[posicion] = elemento;
	}

	/*
	 * pre : Posición pertenece al intervalo: [0, obtenerlongitud() - 1] (@throws out_of_range).
	 * post: Devuelve el elemento en la posición indicada, utilizando el operador [].
	 */
	T & operator[](unsigned int posicion) {
		return obtenerElemento(posicion);
	}

};

#endif /* VECTOR_H_ */
