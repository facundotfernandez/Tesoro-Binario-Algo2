#include "Jugador.h"
#include <climits>
#include<stdlib.h>
#include<time.h>

Jugador::Jugador(unsigned int id) {
	this->id = id;
	this->cantidadTesorosActivos = 0;
	this->cantidadTesorosObtenidos = 0;
	this->cambios = new Pila<std::string>;
	this->casilleros = new Lista<Casillero*>;
	this->tesorosInactivos = new Lista<Casillero*>;
	this->tesorosBlindados = new Lista<Casillero*>;
	this->cartasDisponibles = new Lista<Carta*>;
}

Jugador::~Jugador() {

	while (!(cambios->estaVacia())) {
		this->cambios->desapilar();
	}
	delete this->cambios;

	// Se vacian los todos los Casilleros propios

    delete this->casilleros;
	delete this->tesorosInactivos;
	delete this->tesorosBlindados;

	// Destructor de Cartas
	this->cartasDisponibles->iniciarCursor();
	while (this->cartasDisponibles->avanzarCursor()) {
		delete this->cartasDisponibles->obtenerCursor();
	}
	delete this->cartasDisponibles;
}

Lista<Casillero*>* Jugador::obtenerCasilleros() {
	return this->casilleros;
}

unsigned int Jugador::obtenerCantidadDeCasilleros() {
	return this->casilleros->obtenerLongitud();
}

unsigned int Jugador::obtenerId() {
	return this->id;
}

unsigned int Jugador::obtenerCantidadTesorosActivos() {
	return this->cantidadTesorosActivos;
}

unsigned int Jugador::obtenerCantidadTesorosObtenidos() {
	return this->cantidadTesorosObtenidos;
}

unsigned int Jugador::obtenerCantidadDeCartas() {
	return this->cartasDisponibles->obtenerLongitud();
}

unsigned int Jugador::obtenerCantidadTesorosInactivos() {
	return this->tesorosInactivos->obtenerLongitud();
}

Carta* Jugador::obtenerCarta(unsigned int tipoCarta) {
	this->cartasDisponibles->iniciarCursor();
	while (this->cartasDisponibles->avanzarCursor()) {
		Carta *cartaActual = this->cartasDisponibles->obtenerCursor();
		if (tipoCarta == cartaActual->obtenerTipoCarta()) {
			return cartaActual;
		}
	}
	throw std::out_of_range("El jugador no posee una carta del tipo indicado");
}

Casillero* Jugador::obtenerCasilleroPropio(Vector<unsigned int> *coordenada) {
	this->casilleros->iniciarCursor();
	while (this->casilleros->avanzarCursor()) {
		Casillero *casilleroActual = this->casilleros->obtenerCursor();
		if (casilleroActual->compararCoordenadas(coordenada)) {
			return casilleroActual;
		}
	}
	throw std::out_of_range("El jugador no posee un casillero con las coordenadas indicadas");
}

Lista<Casillero*>* Jugador::obtenerTesorosInactivos() {
	return this->tesorosInactivos;
}

Lista<Casillero*>* Jugador::obtenerTesorosBlindados(){
	return this->tesorosBlindados;
}

Carta* Jugador::obtenerCartaRandom() {
	unsigned int cantidadDeCartas = this->obtenerCantidadDeCartas();
	if (cantidadDeCartas == 0) {
		return NULL;
	}

	srand(time(NULL));
	unsigned int posicionRandom = rand() % cantidadDeCartas;
	return this->cartasDisponibles->obtenerElemento(posicionRandom);
}

Pila<std::string>* Jugador::obtenerCambios() {
	return this->cambios;
}

Lista<Carta*>* Jugador::obtenerCartas() {
	return this->cartasDisponibles;
}

void Jugador::reemplazarTesorosActivos(unsigned int cantidadActivos) {
	this->cantidadTesorosActivos = cantidadActivos;
}

void Jugador::reemplazarTesorosObtenidos(unsigned int cantidadObtenidos) {
	this->cantidadTesorosObtenidos = cantidadObtenidos;
}

void Jugador::reemplazarId(unsigned int id) {
	this->id = id;
}

void Jugador::reemplazarCarta(unsigned int tipoCarta, Carta *carta) {
	this->cartasDisponibles->iniciarCursor();
	unsigned int posicion = 0;
	while (this->cartasDisponibles->avanzarCursor()) {
		if (this->cartasDisponibles->obtenerCursor()->obtenerTipoCarta() == tipoCarta) {
			this->cartasDisponibles->removerElemento(posicion);
			this->cartasDisponibles->agregarElemento(carta);
			return;
		}
		posicion++;
	}
	throw std::out_of_range("El jugador no posee una carta del tipo indicado");
}

void Jugador::agregarCarta(Carta *carta) {
	this->cartasDisponibles->agregarElemento(carta);
}

void Jugador::agregarCasilleroPropio(Casillero *casilleroPropio) {
	this->casilleros->iniciarCursor();
	while (this->casilleros->avanzarCursor()) { //Chequea que el casillero a agregar no pertenezca ya a la lista de casilleros.
		Casillero *casilleroActual = this->casilleros->obtenerCursor();
		if (casilleroActual == casilleroPropio) {
			throw std::logic_error("No se puede agregar un casillero ya existente.");
		}
	}
	if (casilleroPropio->obtenerTipoCasillero() == INACTIVO) {
		this->tesorosInactivos->agregarElemento(casilleroPropio);
	} else if (casilleroPropio->obtenerTipoCasillero() == BLINDADO){
		this->tesorosBlindados->agregarElemento(casilleroPropio);
	}
	this->casilleros->agregarElemento(casilleroPropio);
}

void Jugador::agregarCambio(std::string cambio) {
	this->cambios->apilar(cambio);
}

void Jugador::agregarTesoroInactivo(Casillero *tesoroInactivo) {
	this->tesorosInactivos->iniciarCursor();
	while (this->tesorosInactivos->avanzarCursor()) {
		Casillero *tesoroActual = this->tesorosInactivos->obtenerCursor();
		if (tesoroActual == tesoroInactivo) {
			return;
		}
	}
	this->tesorosInactivos->agregarElemento(tesoroInactivo);
}

void Jugador::agregarTesoroBlindado(Casillero *tesoroBlindado){
	this->tesorosInactivos->iniciarCursor();
	while (this->tesorosInactivos->avanzarCursor()){
		Casillero *tesoroActual = this->tesorosInactivos->obtenerCursor();
		if (tesoroActual == tesoroBlindado){
			return;
		}
	}
	this->tesorosInactivos->agregarElemento(tesoroBlindado);
}	
void Jugador::aumentarTesoroActivo() {
	this->cantidadTesorosActivos += 1;
}

void Jugador::aumentarTesoroObtenido() {
	this->cantidadTesorosObtenidos += 1;
}

void Jugador::disminuirTesoroActivo() {
	if (this->cantidadTesorosActivos == 0) {
		throw "No hay tesoros activos";
	}
	this->cantidadTesorosActivos -= 1;
}

void Jugador::disminuirTesoroObtenidos() {
	if (this->cantidadTesorosObtenidos == 0) {
		throw "No hay tesoros obtenidos";
	}
	this->cantidadTesorosObtenidos -= 1;
}

void Jugador::eliminarCarta(unsigned int tipoCarta) {
	this->cartasDisponibles->iniciarCursor();
	unsigned int posicion = 0;
	while (this->cartasDisponibles->avanzarCursor()) {
		Carta *cartaActual = this->cartasDisponibles->obtenerCursor();
		if (cartaActual->obtenerTipoCarta() == tipoCarta) {
			this->cartasDisponibles->removerElemento(posicion);
			delete cartaActual;
			return;
		}
		posicion++;
	}
	throw std::out_of_range("El jugador no posee una carta del tipo indicado");
}

void Jugador::eliminarCasilleroPropio(Casillero *aEliminar) {
	this->casilleros->iniciarCursor();
	unsigned int posicion = 0;
	while (this->casilleros->avanzarCursor()) {

		Casillero *casilleroActual = this->casilleros->obtenerCursor();

		if (casilleroActual == aEliminar) {

			if (casilleroActual->obtenerTipoCasillero() == INACTIVO) {
				this->eliminarTesoroInactivo(casilleroActual);

			} else if (casilleroActual->obtenerTipoCasillero() == BLINDADO){
				this->eliminarTesoroBlindado(casilleroActual);
			}
			this->casilleros->removerElemento(posicion); // Este recorrido se evita con eliminarPrimeraAparicio() en TDA lista
			return;
		}
		posicion++;
	}
	throw std::out_of_range("El jugador no posee un casillero con las coordenadas indicadas");
}

void Jugador::eliminarCasilleroPropio(Vector<unsigned int> *coordenada) {
	this->casilleros->iniciarCursor();
	unsigned int posicion = 0;
	while (this->casilleros->avanzarCursor()) {

		Casillero *casilleroActual = this->casilleros->obtenerCursor();

		if (casilleroActual->compararCoordenadas(coordenada)) {

			if (casilleroActual->obtenerTipoCasillero() == INACTIVO) {
				this->eliminarTesoroInactivo(casilleroActual);

			} else if (casilleroActual->obtenerTipoCasillero() == BLINDADO){
				this->eliminarTesoroBlindado(casilleroActual);
			}
			this->casilleros->removerElemento(posicion);
			return;
		}
		posicion++;
	}
	throw std::out_of_range("El jugador no posee un casillero con las coordenadas indicadas");
}

void Jugador::eliminarTesoroInactivo(Casillero *tesoroInactivo) {
	this->tesorosInactivos->iniciarCursor();
	unsigned int posicion = 0;
	while (this->tesorosInactivos->avanzarCursor()) {
		Casillero *tesoroActual = this->tesorosInactivos->obtenerCursor();
		if (tesoroActual->compararCoordenadas(tesoroInactivo->obtenerCoordenadas())) {
			this->tesorosInactivos->removerElemento(posicion);
			return;
		}
		posicion++;
	}
	throw std::out_of_range("El jugador no posee el tesoro inactivo indicado");
}

void Jugador::eliminarTesoroBlindado(Casillero *tesoroBlindado){
	this->tesorosBlindados->iniciarCursor();
	unsigned int posicion = 0;
	while (this->tesorosBlindados->avanzarCursor()){
		Casillero *blindadoActual = this->tesorosBlindados->obtenerCursor();
		if (blindadoActual == tesoroBlindado){
			this->tesorosBlindados->removerElemento(posicion);
			return;
		}
		posicion++;
	}

}

void Jugador::vaciarCasilleros() {
	this->casilleros->iniciarCursor();
	while (this->casilleros->avanzarCursor()) {
        this->casilleros->obtenerCursor()->convertirAVacio(); //Al convertir el casillero a Vacio, ya se cambia el Id del jugador a 0.
	}

    this->tesorosInactivos->iniciarCursor();
    while (this->tesorosInactivos->avanzarCursor()) {
        this->tesorosInactivos->obtenerCursor()->convertirAVacio(); //Al convertir el casillero a Vacio, ya se cambia el Id del jugador a 0.
    }

	this->casilleros->limpiar(); //Hace que casilleros sea una lista vacía.
	this->tesorosInactivos->limpiar(); //Hace que tesorosInactivos sea una lista vacía.
}
