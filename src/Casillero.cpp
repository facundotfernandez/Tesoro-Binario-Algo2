#include "Casillero.h"
#include "Plano.h"

void Casillero::validarDescripcion(unsigned int tipoCasillero) const {
	if (this->descripcion->obtenerTipoCasillero() != tipoCasillero) {
		throw std::logic_error("El casillero no corresponde al tipo buscado");
	}
}

void Casillero::asignarCoordenadas(unsigned int x, unsigned int y, unsigned int z) {
	this->coordenadas->reemplazarElemento(0, x);
	this->coordenadas->reemplazarElemento(1, y);
	this->coordenadas->reemplazarElemento(2, z);
}

void Casillero::asignarDescripcionCorta(unsigned int tipoCasillero, unsigned int idJugador) {
	this->descripcion->reemplazarTipoCasillero(tipoCasillero);
	this->descripcion->reemplazarIdJugador(idJugador);
}

void Casillero::asignarInactivoHasta(unsigned int inactivoHasta) {
	try {
		this->validarDescripcion(INACTIVO);
	} catch (const std::logic_error &e) {
		this->validarDescripcion(DESTRUIDO);
	}
	this->descripcion->reemplazarInactivoHasta(inactivoHasta);
}

void Casillero::asignarBlindadoHasta(unsigned int blindadoHasta) {
	this->validarDescripcion(BLINDADO);
	this->descripcion->reemplazarBlindadoHasta(blindadoHasta);
}

Casillero::Casillero(unsigned int x, unsigned int y, unsigned int z) {
	this->coordenadas = new Vector<unsigned int>(3);
	this->asignarCoordenadas(x, y, z);
	this->descripcion = new Descripcion();
	this->planoXY = NULL;
	this->planoXZ = NULL;
	this->planoYZ = NULL;
}

Casillero::~Casillero() {
	delete this->coordenadas;
	delete this->descripcion;
	delete this->planoXY;
	delete this->planoXZ;
	delete this->planoYZ;
}

unsigned int Casillero::obtenerX() const {
	return this->coordenadas->obtenerElemento(0);
}

unsigned int Casillero::obtenerY() const {
	return this->coordenadas->obtenerElemento(1);
}

unsigned int Casillero::obtenerZ() const {
	return this->coordenadas->obtenerElemento(2);
}

Vector<unsigned int>* Casillero::obtenerCoordenadas() const {
	return this->coordenadas;
}

unsigned int Casillero::obtenerTipoCasillero() const {
	return this->descripcion->obtenerTipoCasillero();
}

unsigned int Casillero::obtenerIdJugador() const {
	return this->descripcion->obtenerIdJugador();
}

unsigned int Casillero::obtenerInactivoHasta() const {
	try {
		this->validarDescripcion(INACTIVO);
	} catch (const std::logic_error &e) {
		this->validarDescripcion(DESTRUIDO);
	}
	return this->descripcion->obtenerInactivoHasta();
}

unsigned int Casillero::obtenerBlindadoHasta() const {
	this->validarDescripcion(BLINDADO);
	return this->descripcion->obtenerBlindadoHasta();
}

void Casillero::reemplazarCoordenadas(Vector<unsigned int> *coordenadas) {
	delete this->coordenadas;
	this->coordenadas = coordenadas;
}

Plano* Casillero::obtenerPlanoXY() const {
	return this->planoXY;
}

Plano* Casillero::obtenerPlanoXZ() const {
	return this->planoXZ;
}

Plano* Casillero::obtenerPlanoYZ() const {
	return this->planoYZ;
}

void Casillero::asignarPlanoXY(Plano *planoXY) {
	this->planoXY = planoXY;
}

void Casillero::asignarPlanoXZ(Plano *planoXZ) {
	this->planoXZ = planoXZ;
}

void Casillero::asignarPlanoYZ(Plano *planoYZ) {
	this->planoYZ = planoYZ;
}

void Casillero::convertirAVacio() {
	delete this->descripcion;
	this->descripcion = new Descripcion();
}

void Casillero::convertirATesoro(unsigned int idJugador) {
	delete this->descripcion;
	this->descripcion = new Descripcion();
	this->asignarDescripcionCorta(TESORO, idJugador);
}

void Casillero::convertirAEspia(unsigned int idJugador) {
	delete this->descripcion;
	this->descripcion = new Descripcion();
	this->asignarDescripcionCorta(ESPIA, idJugador);
}

void Casillero::convertirAInactivo(unsigned int idJugador, unsigned int inactivoHasta) {
	delete this->descripcion;
	this->descripcion = new Descripcion();
	this->asignarDescripcionCorta(INACTIVO, idJugador);
	this->asignarInactivoHasta(inactivoHasta);
}

void Casillero::convertirABlindado(unsigned int idJugador, unsigned int blindadoHasta) {
	delete this->descripcion;
	this->descripcion = new Descripcion();
	this->asignarDescripcionCorta(BLINDADO, idJugador);
	this->asignarBlindadoHasta(blindadoHasta);
}

void Casillero::convertirAMina(unsigned int idJugador) {
	delete this->descripcion;
	this->descripcion = new Descripcion();
	this->asignarDescripcionCorta(MINA, idJugador);
}

void Casillero::convertirAPartido(unsigned int idJugador, Casillero *casilleroAsociado) {
	delete this->descripcion;
	this->descripcion = new Descripcion(casilleroAsociado);
	this->asignarDescripcionCorta(PARTIDO, idJugador);
}

Casillero * Casillero::obtenerAsociado() const {
    validarDescripcion(PARTIDO);
    return this->descripcion->obtenerCasilleroAsociado();
}

void Casillero::convertirADestruido(unsigned int inactivoHasta) {
	delete this->descripcion;
	this->descripcion = new Descripcion();
	this->asignarDescripcionCorta(DESTRUIDO, 0);
	this->asignarInactivoHasta(inactivoHasta);
}

bool Casillero::compararCoordenadas(Vector<unsigned int> *coordenadas) {
	if (coordenadas == NULL) {
		throw std::out_of_range("coordenadas invalidas");
	}
	Vector<unsigned int> *coordenadasActuales = this->obtenerCoordenadas();
	if (coordenadasActuales->obtenerElemento(0) == coordenadas->obtenerElemento(0) && coordenadasActuales->obtenerElemento(1) == coordenadas->obtenerElemento(1)
			&& coordenadasActuales->obtenerElemento(2) == coordenadas->obtenerElemento(2)) {
		return true;
	}
	return false;
}
