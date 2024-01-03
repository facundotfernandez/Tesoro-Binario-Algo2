#ifndef PILA_H_
#define PILA_H_

#include "Nodo.h"
#include <stdexcept>

template<class T> class Pila {

private:

	Nodo<T> *tope;

	void validarTope() const {
		if (this->estaVacia()) {
			throw std::out_of_range("La pila esta vacia");
		}
	}

public:

	/*
	 * pre : -
	 * post: Inicializa una Pila vacía.
	 */
	Pila() {
		this->tope = NULL;
	}

	/*
	 * pre : -
	 * post: Libera los recursos asociados a la Pila.
	 */
	virtual ~Pila() {

		while (this->tope != NULL) {
			Nodo<T> *aBorrar = this->tope;
			this->tope = this->tope->obtenerSiguiente();
			delete aBorrar;
		}
	}

	/*
	 * pre : La pila NO está vacía. (@throws out_of_range).
	 * post: Devuelve el tope de la Pila.
	 */
	T verTope() const {
		this->validarTope();
		return this->tope->obtenerDato();
	}

	/*
	 * pre : -
	 * post: Indica si la Pila tiene algún elemento.
	 */
	bool estaVacia() const {
		return (this->tope == NULL);
	}

	/*
	 * pre : -
	 * post: Agrega el elemento en el tope de la Pila.
	 */
	void apilar(T elemento) {
		Nodo<T> *nuevo = new Nodo<T>(elemento);
		nuevo->reemplazarSiguiente(this->tope);
		this->tope = nuevo;
	}

	/*
	 * pre:  La pila NO está vacía. (@throws out_of_range).
	 * post: Desapila el elemento que está en el tope de la pila y lo devuelve.
	 */
	T desapilar() {

		this->validarTope();

		T elemento = this->tope->obtenerDato();
		Nodo<T> *aBorrar = this->tope;
		this->tope = this->tope->obtenerSiguiente();

		delete aBorrar;
		return elemento;
	}

};

#endif /* PILA_H_ */
