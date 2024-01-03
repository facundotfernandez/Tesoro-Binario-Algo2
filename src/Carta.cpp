
#include "Carta.h"

Carta::Carta(unsigned int tipoCarta) {

	this->tipoCarta = tipoCarta;
}

Carta::~Carta() {

}

unsigned int Carta::obtenerTipoCarta() const {

	return this->tipoCarta;
}

void Carta::reemplazarTipoCarta(unsigned int nuevoTipoCarta) {

	this->tipoCarta = nuevoTipoCarta;

}
