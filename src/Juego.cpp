#include "Juego.h"

void Juego::establecerDatosIniciales(unsigned int &cantidadDeJugadores, unsigned int &cantidadDeTesoros, Vector<unsigned int> *dimensiones) {
	// Cantidad de jugadores
	do {
		try {
			cantidadDeJugadores = this->interacciones->pedirOpcion(MINIMO_JUGADORES, MAXIMO_JUGADORES, "Ingrese la cantidad de jugadores");
		} catch (out_of_range &e) {
			this->interacciones->mostrarTitulo(e.what());
		}
	} while (cantidadDeJugadores == 0);
	// Cantidad de tesoros
	do {
		try {
			cantidadDeTesoros = this->interacciones->pedirOpcion(MINIMO_TESOROS, MAXIMO_TESOROS, "Ingrese la cantidad de tesoros");
			this->objetivoTesoros = cantidadDeTesoros;
		} catch (out_of_range &e) {
			this->interacciones->mostrarTitulo(e.what());
		}
	} while (cantidadDeTesoros == 0);
	// Dimensiones
	bool dimensionesValidas = true;
	do {
		try {
			this->interacciones->pedirDimensiones(dimensiones);
			dimensionesValidas = true;
		} catch (const out_of_range &e) {
			this->interacciones->mostrarTitulo(e.what());
			dimensionesValidas = false;
		}
	} while (!dimensionesValidas);
}

Casillero* Juego::obtenerDestino(Jugador *jugador, string indicacion) {

	this->interacciones->mostrarTitulo(indicacion);

	Vector<unsigned int> *coordenadas = this->obtenerCoordenadasValidas(jugador);

	Casillero *destino = this->tablero->obtenerCasillero(coordenadas);

	delete coordenadas;
	return destino;
}

Vector<unsigned int>* Juego::obtenerCoordenadasValidas(Jugador *jugador) {

	Vector<unsigned int> *coordenadas = new Vector<unsigned int>(CANTIDAD_DIMENSIONES);

	while (true) {
		try {
			this->interacciones->pedirCoordenadas(this->tablero->obtenerAncho(), this->tablero->obtenerAlto(), this->tablero->obtenerProfundidad(),
					coordenadas);

		} catch (const logic_error &e) {
			this->interacciones->mostrarTitulo(e.what());
			continue;
		}

		try {
			jugador->obtenerCasilleroPropio(coordenadas);
			this->interacciones->mostrarTitulo("Las coordenadas corresponden a un casillero que ya es tuyo");

		} catch (const out_of_range &e) {
			/* Si atrapa una excepcion, el casillero no pertenece al jugador */
			return coordenadas;
		}
	}
}

void Juego::verificarTesorosDeJugadores() {
	unsigned int posicion = 0;
	while (posicion < this->jugadores->obtenerLongitud()) {
		Jugador *jugadorActual = jugadores->obtenerElemento(posicion);
		if (jugadorActual->obtenerCantidadTesorosActivos() == 0) {
			this->jugadores->removerElemento(posicion);
			this->interacciones->mostrarTitulo(this->interacciones->concatenar("Jugador ", jugadorActual->obtenerId(), " eliminado de la partida!"));

			delete jugadorActual;
		} else {
			posicion++;
		}
	}
}

bool Juego::validarCasillerosInactivos(Vector<Casillero*> *casillerosInactivos) {
	return (casillerosInactivos != NULL);
}

void Juego::validarIdJugador(unsigned int idJugador) {
	this->jugadores->iniciarCursor();
	while (this->jugadores->avanzarCursor()) {
		if (this->jugadores->obtenerCursor()->obtenerId() == idJugador) {
			return;
		}
	}
	throw logic_error("El jugador no esta en la lista");
}

Jugador* Juego::obtenerSiguienteJugador(unsigned int idJugadorActual) {

	if (this->jugadores->estaVacia()) {
		throw out_of_range("No hay jugadores en la partida");
	}

	// validar
	this->jugadores->iniciarCursor();

	while (this->jugadores->avanzarCursor()) {

		if (this->jugadores->obtenerCursor()->obtenerId() > idJugadorActual) {
			return this->jugadores->obtenerCursor();
		}

	}

	//Si llegamos hasta aca es porque se termino de iterar la lista de jugadores
	return this->jugadores->obtenerElemento(0);
}

unsigned int Juego::obtenerCantidadJugadores() {
	return (this->jugadores->obtenerLongitud());
}

Jugador* Juego::obtenerJugador(unsigned int idJugador) {
	Jugador *jugador;
	this->jugadores->iniciarCursor();
	while (jugadores->avanzarCursor()) {
		jugador = this->jugadores->obtenerCursor();
		if (jugador->obtenerId() == idJugador) {
			return jugador;
		}
	}
	throw out_of_range("El jugador no existe");
	return NULL;
}

Tablero* Juego::obtenerTablero() {
	return (this->tablero);
}

Jugador* Juego::obtenerJugadorConMasTesoros() {
	this->jugadores->iniciarCursor();
	this->jugadores->avanzarCursor();
	Jugador *jugadorConMasTesoros = this->jugadores->obtenerCursor();
	Jugador *jugadorActual;
	while (jugadores->avanzarCursor()) {
		jugadorActual = this->jugadores->obtenerCursor();
		if (jugadorConMasTesoros->obtenerCantidadTesorosObtenidos() < jugadorActual->obtenerCantidadTesorosObtenidos()) {
			jugadorConMasTesoros = jugadorActual;
		}
	}
	return jugadorConMasTesoros;
}

bool Juego::obtenerJuegoEnCurso() {

	if (this->obtenerCantidadJugadores() == 1) {
		return false;
	}

	Jugador *jugadorActual;
	this->jugadores->iniciarCursor();
	while (this->jugadores->avanzarCursor()) {
		jugadorActual = this->jugadores->obtenerCursor();
		if (jugadorActual->obtenerCantidadTesorosObtenidos() == this->objetivoTesoros) {

			return false;
		}
	}

	return true;
}

void Juego::validarCantidadDeJugadores(unsigned int cantidadDeJugadores) {
	if (cantidadDeJugadores < MINIMO_JUGADORES || cantidadDeJugadores > MAXIMO_JUGADORES) {
		throw out_of_range("La cantidad de jugadores fuera de rango");
	}
}

Juego::Juego() {
	this->interacciones = new Interacciones();

	unsigned int cantidadDeJugadores = 0;

	unsigned int cantidadDeTesoros = 0;

	Vector<unsigned int> *dimensiones = new Vector<unsigned int>(3);

	establecerDatosIniciales(cantidadDeJugadores, cantidadDeTesoros, dimensiones);

	try {
		this->interacciones->crearCarpetaTableros();
	} catch (...) {
		throw logic_error("No se pudo crear la carpeta de tableros");
	}

	inicializarJugadores(cantidadDeJugadores);

	inicializarTablero(dimensiones, cantidadDeTesoros);

	this->turno = new Turno(this->obtenerJugador(1)); //crea el turno 1, con el primer jugador
	this->juegoEnCurso = true;

	this->casillerosDestruidos = new Lista<Casillero*>;

	this->eliminaciones = new Pila<string>;

	delete dimensiones;
}

Juego::~Juego() {
	this->jugadores->iniciarCursor();
	while (this->jugadores->avanzarCursor()) {
		delete this->jugadores->obtenerCursor();
	}
	delete this->jugadores;

	this->casillerosDestruidos->limpiar();
	delete this->casillerosDestruidos;

	delete this->tablero;
	delete this->turno;
	delete this->interacciones;
	while (!this->eliminaciones->estaVacia()) {
		this->eliminaciones->desapilar();
	}
	delete this->eliminaciones;
}

void Juego::inicializarJugadores(unsigned int cantidadDeJugadores) {
	this->jugadores = new Lista<Jugador*>();
	Jugador *jugador;
	validarCantidadDeJugadores(cantidadDeJugadores);
	for (unsigned int id = 1; id <= cantidadDeJugadores; id++) {
		jugador = new Jugador(id);
		this->jugadores->agregarElemento(jugador);
		try {
			this->interacciones->crearCarpetaJugador(id);
		} catch (...) {
			throw logic_error("No se pudo crear la carpeta del jugador");
		}
	}
}

void Juego::inicializarTablero(Vector<unsigned int> *dimensiones, unsigned int cantidadDeTesoros) {
	unsigned int ancho = dimensiones->obtenerElemento(0);
	unsigned int alto = dimensiones->obtenerElemento(1);
	unsigned int profundidad = dimensiones->obtenerElemento(2);

	this->tablero = new Tablero(ancho, alto, profundidad, true);
	inicializarTesoros(cantidadDeTesoros);
}

void Juego::inicializarTesoros(unsigned int cantidadDeTesoros) {

	Jugador *jugador = NULL;
	Vector<unsigned int> *coordenadas = new Vector<unsigned int>(3);

	this->jugadores->iniciarCursor();
	while (this->jugadores->avanzarCursor()) {
		jugador = this->jugadores->obtenerCursor();
		generarTesorosAleatorios(jugador, coordenadas, cantidadDeTesoros);
	}
	delete coordenadas;
}

void Juego::generarTesorosAleatorios(Jugador *jugador, Vector<unsigned int> *coordenadas, unsigned int cantidadDeTesoros) {
	unsigned int ancho = this->tablero->obtenerAncho();
	unsigned int alto = this->tablero->obtenerAlto();
	unsigned int profundidad = this->tablero->obtenerProfundidad();

	unsigned int idJugador = jugador->obtenerId();
	for (unsigned int j = 0; j < cantidadDeTesoros; j++) {
		coordenadas->reemplazarElemento(0, rand() % ancho);
		coordenadas->reemplazarElemento(1, rand() % alto);
		coordenadas->reemplazarElemento(2, rand() % profundidad);
		Casillero *casilleroAleatorio = this->tablero->obtenerCasillero(coordenadas);
		while (casilleroAleatorio->obtenerTipoCasillero() != VACIO) {
			coordenadas->reemplazarElemento(0, rand() % ancho);
			coordenadas->reemplazarElemento(1, rand() % alto);
			coordenadas->reemplazarElemento(2, rand() % profundidad);
			casilleroAleatorio->reemplazarCoordenadas(coordenadas);
		}
		casilleroAleatorio->convertirATesoro(idJugador);
		jugador->agregarCasilleroPropio(casilleroAleatorio);
		jugador->aumentarTesoroActivo();
	}
}

bool Juego::sonCoordenadasPropias(Vector<unsigned int> *coordenadas, unsigned int idJugador) {

	Casillero *casillero = this->tablero->obtenerCasillero(coordenadas);
	return (casillero->obtenerIdJugador() == idJugador);
}

void Juego::jugarTurno(unsigned int turnoActual) {
	validarIdJugador(this->turno->obtenerJugadorActual()->obtenerId());
	actualizarInactivos();
	actualizarDestruidos();
	actualizarBlindados();
	unsigned int idJugador = this->turno->obtenerJugadorActual()->obtenerId();
	this->interacciones->mostrarTitulo(turnoActual, idJugador);
	mostrarProgresoDeTesorosPorObtener();
	mostrarCambios();

	try {
		mostrarCasilleros();
	} catch (const logic_error &e) {
		this->interacciones->mostrarTitulo(e.what());
	}

	this->sacarCarta();

	this->interacciones->mostrarMenu(this->turno->obtenerJugadorActual()->obtenerCasilleros());
	this->interacciones->mostrarMenu(this->turno->obtenerJugadorActual()->obtenerCartas());

	this->jugarEspia();
	this->jugarMina();
	this->jugarMoverTesoro();
	this->jugarCarta();
}

void Juego::mostrarJugadoresEliminados() {
	// Si pasa esto, se esta por comenzar una nueva ronda
	if (this->turno->obtenerJugadorActual()->obtenerId() == this->jugadores->obtenerElemento(0)->obtenerId()) {
		try {
			this->interacciones->mostrarJugadoresEliminados(this->eliminaciones);
		} catch (const logic_error &e) {
			this->interacciones->mostrarTitulo(e.what());
		}
	}
}

void Juego::avanzarTurno(Jugador *jugadorActual) {
	if (this->juegoEnCurso) {
		Jugador *jugadorSiguiente;
		try {
			jugadorSiguiente = this->obtenerSiguienteJugador(jugadorActual->obtenerId());
		} catch (out_of_range &e) {
			throw out_of_range("No hay mas jugadores");
		}

		this->turno->avanzarTurno();
		this->turno->reemplazarJugadorActual(jugadorSiguiente);

		if (this->jugadores->obtenerElemento(0)->obtenerId() == jugadorSiguiente->obtenerId()) {
			this->turno->avanzarRonda();
		}
	}
}

void Juego::actualizarJuego() {
	Jugador *jugadorActual;
	unsigned int turnoActual;

	while (this->juegoEnCurso) {

		turnoActual = this->turno->obtenerTurnoActual();
		jugadorActual = this->turno->obtenerJugadorActual();

		this->jugarTurno(turnoActual);

		this->eliminarJugadoresSinTesorosActivos();
		this->juegoEnCurso = obtenerJuegoEnCurso();
		// Avanza el turno y el jugador
		avanzarTurno(jugadorActual);
		this->mostrarJugadoresEliminados();
	}

	// Mostrar mensaje de fin de juego
	Jugador *ganador = this->obtenerJugadorConMasTesoros();
	unsigned int idJugadorGanador = ganador->obtenerId();
	this->interacciones->mostrarFinDeJuego(idJugadorGanador);

}

void Juego::actualizarInactivos() {
	Jugador *jugadorActual = this->turno->obtenerJugadorActual();
	Lista<Casillero*> *tesorosInactivos = jugadorActual->obtenerTesorosInactivos();
	Casillero *casilleroActual;

	tesorosInactivos->iniciarCursor();
	while (tesorosInactivos->avanzarCursor()) {
		casilleroActual = tesorosInactivos->obtenerCursor();
		if (casilleroActual->obtenerTipoCasillero() == INACTIVO) {
			actualizarCasilleroInactivo(casilleroActual, jugadorActual);
		}
	}
}

void Juego::actualizarBlindados() {
	Jugador *jugadorActual = this->turno->obtenerJugadorActual();
	Lista<Casillero*> *tesorosBlindados = jugadorActual->obtenerTesorosBlindados();
	Casillero *casilleroActual;

	tesorosBlindados->iniciarCursor();
	while (tesorosBlindados->avanzarCursor()) {
		casilleroActual = tesorosBlindados->obtenerCursor();
		if (casilleroActual->obtenerBlindadoHasta() < this->turno->obtenerTurnoActual()) {
			throw logic_error("Blindado no se ha actualizado en el turno correspondiente");

		} else if (casilleroActual->obtenerTipoCasillero() != BLINDADO) {
			throw logic_error("El casillero no es blindado");

		} else if (casilleroActual->obtenerBlindadoHasta() == this->turno->obtenerTurnoActual()) {
			casilleroActual->convertirATesoro(jugadorActual->obtenerId());
			jugadorActual->agregarCambio(this->interacciones->generarCambio(BLINDAJEPERDIDO, casilleroActual->obtenerCoordenadas()));
		}
	}
}

void Juego::actualizarCasilleroInactivo(Casillero *casillero, Jugador *jugador) {
	if (casillero->obtenerInactivoHasta() < this->turno->obtenerTurnoActual()) {
		throw logic_error("Inactivo no se ha actualizado en el turno correspondiente");
	} else if (casillero->obtenerInactivoHasta() == this->turno->obtenerTurnoActual()) {

		casillero->convertirAEspia(jugador->obtenerId());

		jugador->aumentarTesoroObtenido();

		jugador->agregarCambio(this->interacciones->generarCambio(ROBOFINALIZADO, casillero->obtenerCoordenadas()));
	}
}

void Juego::eliminarJugadoresSinTesorosActivos() {
	Jugador *jugadorActual;
	this->jugadores->iniciarCursor();
	unsigned int posicion = 0;
	unsigned int cantidadDeEliminados = 0;

	while (this->jugadores->avanzarCursor()) {
		jugadorActual = this->jugadores->obtenerCursor();
		if (jugadorActual->obtenerCantidadTesorosActivos() == 0) {

			cantidadDeEliminados += 1;

			this->eliminaciones->apilar(this->interacciones->concatenar("Jugador ", jugadorActual->obtenerId(), " ha sido eliminado de la partida"));

			delete jugadorActual;
			this->jugadores->removerElemento(posicion);
			this->jugadores->iniciarCursor();
			posicion = 0;

		} else {
			posicion++;
		}
	}

	this->interacciones->mostrarCantidadDeEliminados(cantidadDeEliminados);
}

void Juego::actualizarDestruidos() {
	Lista<Casillero*> *nuevosCasillerosDestruidos = new Lista<Casillero*>;

	Casillero *casilleroActual;
	this->casillerosDestruidos->iniciarCursor();
	while (this->casillerosDestruidos->avanzarCursor()) {
		casilleroActual = casillerosDestruidos->obtenerCursor();
		if (casilleroActual->obtenerInactivoHasta() < this->turno->obtenerTurnoActual()) {
			throw logic_error("Destruido no se ha actualizado en el turno correspondiente");

		} else if (casilleroActual->obtenerInactivoHasta() == this->turno->obtenerTurnoActual()) {
			casilleroActual->convertirAVacio();

		} else {
			nuevosCasillerosDestruidos->agregarElemento(casilleroActual);
		}
	}
	this->casillerosDestruidos->limpiar();
	delete this->casillerosDestruidos;
	this->casillerosDestruidos = nuevosCasillerosDestruidos;
}

void Juego::destruirCasillero(Casillero *aDestruir, Jugador *jugador, unsigned int destruidoHasta) {
	this->casillerosDestruidos->agregarElemento(aDestruir);

	jugador->eliminarCasilleroPropio(aDestruir);

	aDestruir->convertirADestruido(destruidoHasta);
}

void Juego::moverTesoro(Casillero *origen, Casillero *destino) {

	Jugador *jugadorActual = this->turno->obtenerJugadorActual();
	unsigned int idJugador = jugadorActual->obtenerId();
	Jugador *jugadorRival;
	string tipo;
	unsigned int inactivoHasta = this->turno->obtenerTurnoActual() + INACTIVIDAD_POR_ESPIA * this->obtenerCantidadJugadores();

	switch (destino->obtenerTipoCasillero()) {
		case TESORO:
			this->interacciones->mostrarTitulo("En esta ubicacion hay un tesoro de un rival");
			break;
		case PARTIDO:
			this->interacciones->mostrarTitulo("En esta ubicación se encuentra un tesoro partido de un rival");
			break;
		case BLINDADO:
			this->interacciones->mostrarTitulo("En esta ubicación se encuentra un tesoro blindado de un rival");
			break;
		case INACTIVO:
			this->interacciones->mostrarTitulo("Este destino esta INACTIVO temporalmente");
			break;
		case DESTRUIDO:
			this->interacciones->mostrarTitulo("Este destino esta DESTRUIDO");
			break;
		case VACIO:

			switch (origen->obtenerTipoCasillero()) {
				case TESORO:
					destino->convertirATesoro(idJugador);
					this->interacciones->mostrarTitulo("Moviste el tesoro");
					break;
				case PARTIDO:
					Casillero *asociadoAOrigen;
					asociadoAOrigen = origen->obtenerAsociado();

					destino->convertirAPartido(idJugador, asociadoAOrigen);
					asociadoAOrigen->convertirAPartido(idJugador, destino);

					this->interacciones->mostrarTitulo("Moviste el tesoro partido");
					break;
				case BLINDADO:
					destino->convertirABlindado(idJugador, origen->obtenerBlindadoHasta());
					this->interacciones->mostrarTitulo("Moviste el tesoro blindado");
					break;
			}
			origen->convertirAVacio();
			jugadorActual->eliminarCasilleroPropio(origen);
			jugadorActual->agregarCasilleroPropio(destino);
			break;

		case ESPIA:
			jugadorRival = obtenerJugador(destino->obtenerIdJugador());

			switch (origen->obtenerTipoCasillero()) {
				case TESORO:
					jugadorActual->disminuirTesoroActivo();

					destino->convertirAInactivo(jugadorRival->obtenerId(), inactivoHasta);

					jugadorRival->agregarCasilleroPropio(destino);

					this->interacciones->mostrarTitulo("Ha perdido un tesoro");
					this->guardarCambio(jugadorRival, ROBOINICIADO, destino->obtenerCoordenadas());

					jugadorActual->eliminarCasilleroPropio(origen);
					origen->convertirAVacio();

					break;
				case PARTIDO:
					Casillero *partePartido;
					partePartido = origen->obtenerAsociado();
					partePartido->convertirATesoro(idJugador);

					jugadorActual->eliminarCasilleroPropio(origen);
					origen->convertirAVacio();

					this->interacciones->mostrarTitulo("Ha perdido un tesoro partido");
					break;
				case BLINDADO:
					this->interacciones->mostrarTitulo("En este casillero se encuentra un espia rival");

					break;
			}

			break;

		case MINA:
			jugadorRival = obtenerJugador(destino->obtenerIdJugador());

			switch (origen->obtenerTipoCasillero()) {
				case TESORO:
					destino->convertirADestruido(((rand() % 3) + 1) * obtenerCantidadJugadores());

					jugadorActual->disminuirTesoroActivo();

					jugadorActual->eliminarCasilleroPropio(origen);

					jugadorRival->eliminarCasilleroPropio(destino);

					this->interacciones->mostrarTitulo("Su tesoro ha explotado sobre una mina");

					this->guardarCambio(jugadorRival, MINAPERDIDA, destino->obtenerCoordenadas());
					break;
				case PARTIDO:
					Casillero *partePartido;

					partePartido = origen->obtenerAsociado(); // Asume que el partido es del jugador

					destino->convertirADestruido(((rand() % 3) + 1) * obtenerCantidadJugadores());

					partePartido->convertirATesoro(idJugador);

					jugadorActual->eliminarCasilleroPropio(origen);

					jugadorRival->eliminarCasilleroPropio(destino);

					this->interacciones->mostrarTitulo("Su tesoro partido ha explotado sobre una mina");
					this->guardarCambio(jugadorRival, MINAPERDIDA, destino->obtenerCoordenadas());
					break;
				case BLINDADO:
					jugadorRival->eliminarCasilleroPropio(destino);

					origen->convertirATesoro(idJugador);

					this->interacciones->mostrarTitulo("Su tesoro ha explotado sobre una mina, pierde el blindaje y retorna");

					this->guardarCambio(jugadorRival, MINAPERDIDA, destino->obtenerCoordenadas());
			}
			origen->convertirAVacio();
			break;
	}
}

void Juego::agregarEspia(Casillero *destino) {

	Jugador *jugadorActual = this->turno->obtenerJugadorActual();

	unsigned int idJugador = jugadorActual->obtenerId();

	Jugador *jugadorRival = (destino->obtenerIdJugador() == ID_GLOBAL) ? (NULL) : (obtenerJugador(destino->obtenerIdJugador()));
	unsigned int inactivoHasta = this->turno->obtenerTurnoActual() + INACTIVIDAD_POR_ESPIA * this->obtenerCantidadJugadores();

	switch (destino->obtenerTipoCasillero()) {
		case VACIO:
			destino->convertirAEspia(idJugador);
			jugadorActual->agregarCasilleroPropio(destino);
			this->interacciones->mostrarTitulo("Espia agregado al tablero correctamente!");
			break;

		case TESORO:

			jugadorRival->eliminarCasilleroPropio(destino);

			destino->convertirAInactivo(idJugador, inactivoHasta);

			jugadorActual->agregarCasilleroPropio(destino);

			jugadorRival->disminuirTesoroActivo();

			this->interacciones->mostrarTitulo("Tesoro encontrado, tu espia comenzo a robarlo");
			this->guardarCambio(jugadorRival, TESOROPERDIDO, destino->obtenerCoordenadas());
			break;

		case ESPIA:
			jugadorRival->eliminarCasilleroPropio(destino);

			destino->convertirAVacio();

			this->interacciones->mostrarTitulo("Encontraste un espia enemigo, ambos espias fueron eliminados");
			this->guardarCambio(jugadorRival, ESPIAPERDIDO, destino->obtenerCoordenadas());
			break;

		case MINA:
			jugadorRival->eliminarCasilleroPropio(destino);
			destino->convertirAVacio();

			this->interacciones->mostrarTitulo("¡BOOM! Espia explotado");
			this->guardarCambio(jugadorRival, MINAPERDIDA, destino->obtenerCoordenadas());
			break;

		case BLINDADO:
			this->interacciones->mostrarTitulo("Este destino esta BLINDADO");
			break;

		case DESTRUIDO:
			this->interacciones->mostrarTitulo("Este destino esta DESTRUIDO");
			break;

		case INACTIVO:
			this->interacciones->mostrarTitulo("Este destino esta INACTIVO temporalmente");
			break;

		case PARTIDO:
			unsigned int idJugadorRival = destino->obtenerIdJugador();
			Casillero *partePartido;

			partePartido = destino->obtenerAsociado();

			jugadorRival->eliminarCasilleroPropio(destino);

			partePartido->convertirATesoro(idJugadorRival);

			destino->convertirAEspia(idJugador);

			this->interacciones->mostrarTitulo("Encontraste un tesoro partido");
			this->guardarCambio(jugadorRival, PARTIDOPERDIDO, destino->obtenerCoordenadas());
			break;
	}
}

void Juego::agregarMina(Casillero *destino) {
	/*
	 * Casos validos
	 Mina en Vacio -> se puede
	 Mina en Tesoro rival -> elimina al tesoro (ambos) -> inactivo dependiendo de la potencia
	 Mina en Espía rival -> elimina al espía rival (ambos) -> vacío
	 Mina en Mina -> se eliminan las minas (ambas) -> vacío
	 Mina en Partido -> lo elimina y la otra parte del tesoro partido se hace TESORO a la espera de ser robada
	 Mina en Blindado -> se elimina el blindaje y la mina no se coloca -> tesoro rival sin blindaje
	 */

	Jugador *jugadorActual = this->turno->obtenerJugadorActual();

	Jugador *jugadorRival = (destino->obtenerIdJugador() == ID_GLOBAL) ? (NULL) : (obtenerJugador(destino->obtenerIdJugador()));

	unsigned int idJugadorRival;

	unsigned int inactividadPorPotenciaDeMina = this->turno->obtenerTurnoActual() + ((rand() % INACTIVIDAD_POR_MINA) + 1) * obtenerCantidadJugadores(); // Puede ser de 1 a 3 rondas

	switch (destino->obtenerTipoCasillero()) {
		case VACIO:
			/*
			 * Estado Previo:
			 * Casillero es VACIO
			 *
			 * Estado Posterior:
			 * Casillero es MINA
			 */
			destino->convertirAMina(jugadorActual->obtenerId());

			jugadorActual->agregarCasilleroPropio(destino);

			this->interacciones->mostrarTitulo("Mina agregada al tablero correctamente");
			break;
		case TESORO:
			/*
			 * Estado Previo:
			 * Casillero es TESORO oponente
			 *
			 * Estado Posterior:
			 * Casillero es DESTRUIDO
			 * oponente tiene un tesoro y destino menos
			 */

			this->destruirCasillero(destino, jugadorRival, inactividadPorPotenciaDeMina);

			jugadorRival->disminuirTesoroActivo();

			this->interacciones->mostrarTurnosInactividad("Destruye un tesoro enemigo", inactividadPorPotenciaDeMina);

			this->guardarCambio(jugadorRival, TESOROPERDIDO, destino->obtenerCoordenadas());
			break;
		case ESPIA:
			/*
			 * Estado Previo:
			 * Casillero es ESPIA oponente
			 *
			 * Estado Posterior:
			 * Casillero es DESTRUIDO
			 * oponente tiene un espia y destino menos
			 */

			this->destruirCasillero(destino, jugadorRival, inactividadPorPotenciaDeMina);

			this->interacciones->mostrarTurnosInactividad("Destruye un espia enemiga", inactividadPorPotenciaDeMina);
			this->guardarCambio(jugadorRival, ESPIAPERDIDO, destino->obtenerCoordenadas());
			break;
		case MINA:
			/*
			 * Estado Previo:
			 * Casillero es MINA oponente
			 *
			 * Estado Posterior:
			 * Casillero es DESTRUIDO
			 * oponente tiene un destino menos
			 */

			this->destruirCasillero(destino, jugadorRival, inactividadPorPotenciaDeMina);

			this->interacciones->mostrarTurnosInactividad("Destruye una mina enemiga", inactividadPorPotenciaDeMina);

			this->guardarCambio(jugadorRival, MINAPERDIDA, destino->obtenerCoordenadas());
			break;
		case PARTIDO:
			/*
			 * Estado Previo:
			 * Casillero es PARTIDO oponente
			 *
			 * Estado Posterior:
			 * Casillero es DESTRUIDO
			 * oponente tiene un destino menos
			 * la otra parte de PARTIDO pasa a ser un TESORO
			 */

			Casillero *partePartido;
			partePartido = destino->obtenerAsociado();
			partePartido->convertirATesoro(jugadorRival->obtenerId());

			this->destruirCasillero(destino, jugadorRival, inactividadPorPotenciaDeMina);

			this->interacciones->mostrarTitulo("Explota la mina sobre parte de un tesoro rival, dejando el casillero Vacio");

			this->guardarCambio(jugadorRival, PARTIDOPERDIDO, destino->obtenerCoordenadas());
			break;
		case BLINDADO:
			/*
			 * Estado Previo:
			 * Casillero es BLINDADO oponente
			 *
			 * Estado Posterior:
			 * Casillero es TESORO oponente
			 */
			jugadorRival = obtenerJugador(destino->obtenerIdJugador());
			idJugadorRival = jugadorRival->obtenerId();

			destino->convertirATesoro(idJugadorRival); // Solo se puede blindar tesoros comunes
			this->interacciones->mostrarTitulo("Encuentra un tesoro Blindado oponente, dejando el destino como un Tesoro sin blindaje");
			this->guardarCambio(jugadorRival, BLINDAJEPERDIDO, destino->obtenerCoordenadas());
			break;
		case INACTIVO:
			/*
			 * Estado Previo:
			 * Casillero es INACTIVO (se esta robando un Tesoro)
			 *
			 * Estado Posterior:
			 * Casillero es DESTRUIDO
			 */
			this->destruirCasillero(destino, jugadorRival, inactividadPorPotenciaDeMina);

			this->interacciones->mostrarTurnosInactividad("Interrumpiste una captura", inactividadPorPotenciaDeMina);

			this->guardarCambio(jugadorRival, ROBOINTERRUMPIDO, destino->obtenerCoordenadas());
			break;
		case DESTRUIDO:

			destino->convertirADestruido(inactividadPorPotenciaDeMina);

			this->interacciones->mostrarTurnosInactividad("Destruiste la ubicacion", inactividadPorPotenciaDeMina);
			break;
	}
}

Casillero* Juego::obtenerTesoro(Jugador *jugador, string indicacion, bool cualquierTipo) {

	Lista<Casillero*> *casillerosFiltrados = (
			(cualquierTipo) ?
					(this->filtrarCasilleros(jugador->obtenerCasilleros(), TESORO, BLINDADO, PARTIDO)) :
					(this->filtrarCasilleros(jugador->obtenerCasilleros(), TESORO)));

	if (casillerosFiltrados->estaVacia()) {
		delete casillerosFiltrados;
		throw logic_error("No posees tesoros disponibles para elegir");
	}

	Casillero *aPartir = this->interacciones->elegirMenu(casillerosFiltrados, indicacion);

	while (aPartir == NULL) {
		this->interacciones->mostrarTitulo("No elegiste un tesoro valido");
		aPartir = this->interacciones->elegirMenu(casillerosFiltrados, indicacion);
	}

	delete casillerosFiltrados;
	return aPartir;
}

Lista<Casillero*>* Juego::filtrarCasilleros(Lista<Casillero*> *casilleros, unsigned int tipoAceptadoA, unsigned int tipoAceptadoB, unsigned int tipoAceptadoC) {

	Lista<Casillero*> *casillerosFiltrados = new Lista<Casillero*>();
	Casillero *casillero;
	unsigned int tipoCasillero;

	casilleros->iniciarCursor();

	while (casilleros->avanzarCursor()) {

		casillero = casilleros->obtenerCursor();

		tipoCasillero = casillero->obtenerTipoCasillero();

		if (tipoCasillero == tipoAceptadoA || tipoCasillero == tipoAceptadoB || tipoCasillero == tipoAceptadoC) {
			casillerosFiltrados->agregarElemento(casillero);
		}
	}
	return casillerosFiltrados;
}

void Juego::jugarMoverTesoro() {
	Jugador *jugador = this->turno->obtenerJugadorActual();

	try {
		if (!(this->interacciones->preguntar("¿Desea mover un tesoro?", "Si", "No"))) {
			throw logic_error("Ha elegido no mover un tesoro");
		}

		Casillero *origen = this->obtenerTesoro(jugador, "Selecciona un tesoro a mover", true);
		Casillero *destino = this->obtenerDestino(jugador, "Ingresa el casillero hacia donde va a mover el tesoro");
		moverTesoro(origen, destino);

	} catch (const logic_error &e) {
		this->interacciones->mostrarTitulo(e.what());
	}

}

void Juego::sacarCarta() {

	srand(time(NULL));
	Carta *carta = new Carta((unsigned int) rand() % CANTIDAD_CARTAS);
	Jugador *jugadorActual = this->turno->obtenerJugadorActual();
	this->interacciones->mostrarObtencionCarta(carta->obtenerTipoCarta());

	jugadorActual->agregarCarta(carta);

}

void Juego::jugarEspia() {
	Casillero *casillero = this->obtenerDestino(this->turno->obtenerJugadorActual(), "Ingresa el casillero donde quieres colocar tu espia");
	agregarEspia(casillero);
}

void Juego::jugarMina() {
	Casillero *casillero = this->obtenerDestino(this->turno->obtenerJugadorActual(), "Ingresa el casillero donde quieres colocar tu mina");
	agregarMina(casillero);
}

bool Juego::jugarCarta() {

	while (true) {

		try {
			if (!(this->interacciones->preguntar("¿Desea jugar una carta?", "Si", "No"))) {
				throw logic_error("Ha elegido no jugar una carta");
			}
		} catch (logic_error &e) {
			this->interacciones->mostrarTitulo(e.what());
			return false;
		}

		try {

			Carta *cartaJugada = this->interacciones->elegirMenu(this->turno->obtenerJugadorActual()->obtenerCartas());

			if (cartaJugada == NULL) {
				throw logic_error("Carta invalida!");
			}

			switch (cartaJugada->obtenerTipoCarta()) {
				case BLINDAR:
					jugarBlindaje();
					break;
				case REVELAR:
					jugarRadar();
					break;
				case PARTIRTESORO:
					jugarPartirTesoro();
					break;
				case TRACKEAR:
					jugarTrackearCasilla();
					break;
				case ROBARCARTA:
					jugarRobarCarta();
					break;
				case DUPLICARTURNO:
					jugarDobleTurno();
					break;
			}

			this->turno->obtenerJugadorActual()->eliminarCarta(cartaJugada->obtenerTipoCarta());
		} catch (logic_error &e) {
			this->interacciones->mostrarTitulo(e.what());
			continue;
		}
		break;
	}
	return true;
}

void Juego::jugarBlindaje() {

	unsigned int idJugador = this->turno->obtenerJugadorActual()->obtenerId();

	Casillero *posicionABlindar = this->obtenerTesoro(this->turno->obtenerJugadorActual(), "Selecciona un tesoro a blindar");

	if (posicionABlindar == NULL) {
		throw logic_error("Posicion invalida!");
	}

	if ((posicionABlindar->obtenerIdJugador()) != (idJugador)) {        //No deberia llegar a esto

		throw logic_error("Esa casilla no esta bajo control aliado!");

	}

	if ((posicionABlindar->obtenerTipoCasillero()) != TESORO) {

		throw logic_error("Esa casilla no tiene un tesoro aliado para blindar!");

	}

	unsigned int blindadoHasta = this->turno->obtenerTurnoActual() + DURACION_BLINDAJE * this->obtenerCantidadJugadores();
	posicionABlindar->convertirABlindado(idJugador, blindadoHasta);
	this->interacciones->mostrarTitulo("Tesoro blindado con exito!");
}

void Juego::jugarRadar() {
	unsigned int idJugador = this->turno->obtenerJugadorActual()->obtenerId();

	Casillero *destino = this->obtenerDestino(this->turno->obtenerJugadorActual(), "Seleccione un casillero para usar el radar");
	Casillero *casillero;

	int fil = destino->obtenerX();
	int col = destino->obtenerY();
	int prof = destino->obtenerZ();

	unsigned int tesorosDetectados = 0;

	for (int x = fil - 3; x < fil + 3; x++) {
		for (int y = col - 3; y < col + 3; y++) {
			for (int z = prof - 3; z < prof + 3; z++) {

				if ((x >= 0 && x < (int) tablero->obtenerAlto()) && (y >= 0 && y < (int) tablero->obtenerAncho())
						&& (z >= 0 && z < (int) tablero->obtenerProfundidad())) {

					casillero = this->tablero->obtenerCasillero(x, y, z);
					if ((casillero->obtenerTipoCasillero() == TESORO) && (casillero->obtenerIdJugador()) != idJugador) {
						tesorosDetectados++;
					}
				}
			}

		}
	}

	this->interacciones->mostrarTitulo(this->interacciones->concatenar("Se detectaron ", tesorosDetectados, " tesoros"));

}

void Juego::jugarPartirTesoro() {
	Jugador *jugador = this->turno->obtenerJugadorActual();
	unsigned int idJugador = jugador->obtenerId();

	Casillero *casilleroAPartir = this->obtenerTesoro(jugador, "Selecciona un tesoro a partir");
	Casillero *casilleroPartido = this->obtenerDestino(jugador, "Ingresa el casillero donde quieres colocar la otra mitad del tesoro");

	if ((casilleroPartido->obtenerTipoCasillero()) != VACIO) {
		throw logic_error("Esa casilla esta ocupada!");
	}

	casilleroAPartir->convertirAPartido(idJugador, casilleroPartido);
	casilleroPartido->convertirAPartido(idJugador, casilleroAPartir);

	this->turno->obtenerJugadorActual()->agregarCasilleroPropio(casilleroPartido);
	this->interacciones->mostrarTitulo("Tesoro partido con exito!");

}

bool Juego::_trackear(unsigned int stop, unsigned int *i, unsigned int *j, unsigned int *k) {
	unsigned int idJugador = this->turno->obtenerJugadorActual()->obtenerId();
	Casillero *casillero;
	unsigned int tipo = VACIO;

	for (unsigned int x = 0; x < this->tablero->obtenerAncho() - 1; x++) {
		for (unsigned int y = 0; y < this->tablero->obtenerAlto() - 1; y++) {
			for (unsigned int z = 0; z < tablero->obtenerProfundidad() - 1; z++) {
				casillero = this->tablero->obtenerCasillero(x, y, z);
				tipo = casillero->obtenerTipoCasillero();
				if (((tipo == TESORO) || (tipo == MINA) || (tipo == BLINDADO) || (tipo == PARTIDO)) && (casillero->obtenerIdJugador() != idJugador)) {

					if (stop > 0) {
						(*i) = x;
						(*j) = y;
						(*k) = z;
						stop--;
					} else if (stop == 0) {
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Juego::jugarTrackearCasilla() {
	unsigned int x, y, z = 0;

	srand((unsigned int) time(NULL));
	unsigned int stop = rand() % 4 + 1;
	if (!_trackear(stop, (&x), (&y), (&z))) {
		this->interacciones->mostrarTitulo("No se encontro nada");
	} else {
		this->interacciones->mostrarDeteccion("Se detecta algo", x, y, z);
	}
}

void Juego::jugarRobarCarta() {

	unsigned int idJugador = this->turno->obtenerJugadorActual()->obtenerId();
	Jugador *jugadorARobar = this->interacciones->elegirMenu(this->jugadores, idJugador, "Jugadores Activos");

//Nota: si no puedo hacer funcionar el menu voy a hacer que throwee si elegis un jugador eliminado y listo

	if (jugadorARobar->obtenerId() == idJugador) {
		throw logic_error("No podes robarte cartas a vos mismo!");
	}
	Jugador *jugadorQueRoba = this->obtenerJugador(idJugador);

	if (jugadorARobar->obtenerCantidadDeCartas() == 0) {
		this->interacciones->mostrarTitulo("El jugador no tenia cartas para robar");
		return;
	}
	Carta *cartaRobada = jugadorARobar->obtenerCartaRandom();
	unsigned int tipoRobada = cartaRobada->obtenerTipoCarta();

	jugadorQueRoba->agregarCarta(new Carta(tipoRobada));
	jugadorARobar->eliminarCarta(tipoRobada);

	this->interacciones->mostrarRoboCarta(tipoRobada);

}

void Juego::jugarDobleTurno() {
	unsigned int idJugador = this->turno->obtenerJugadorActual()->obtenerId();
	unsigned int turno = this->turno->obtenerTurnoActual();
	this->interacciones->mostrarTitulo("Doble turno activado!");
	this->interacciones->mostrarTitulo(turno, idJugador);

//Desde aca, se copian de JugarTurno las acciones que se decida que se puede tomar en un doble turno, no se puede
//jugar otra carta o sacar otra carta del mazo. Tampoco se actualiza el estado del juego

	jugarMoverTesoro();
	jugarEspia();
	jugarMina();
}

void Juego::guardarCambio(Jugador *jugador, unsigned int tipoCambio, Vector<unsigned int> *coordenadas) {
	jugador->agregarCambio((this->interacciones->generarCambio(tipoCambio, coordenadas)));
}

void Juego::mostrarCasilleros() {
	bool exportar = this->interacciones->preguntar("¿Exportar tablero?", "Si", "No");
	Jugador *jugador = this->turno->obtenerJugadorActual();
	Lista<Casillero*> *casilleros = jugador->obtenerCasilleros();

	while (exportar) {
		try {
			this->exportarTablero(casilleros);
		} catch (const logic_error &e) {
			this->interacciones->mostrarTitulo(e.what());
			break;
		}
		exportar = this->interacciones->preguntar("Tableros exportados correctamente. ¿Desea exportar nuevamente?", "Si", "No");
	}

}

void Juego::exportarTablero(Lista<Casillero*> *casilleros) {
	Casillero *casillero = this->interacciones->elegirMenu(casilleros);
	if (casillero == NULL) {
		throw logic_error("No se pudo exportar el casillero");
	}
	this->interacciones->exportar(casillero->obtenerPlanoXY());
	this->interacciones->exportar(casillero->obtenerPlanoXZ());
	this->interacciones->exportar(casillero->obtenerPlanoYZ());
}

void Juego::mostrarCambios() {
	Jugador *jugadorActual = this->turno->obtenerJugadorActual();
	try {
		Pila<string> *cambios = jugadorActual->obtenerCambios();
		this->interacciones->mostrarMenu(cambios);
	} catch (const logic_error &e) {
		this->interacciones->mostrarTitulo(e.what());
	}
}

void Juego::mostrarProgresoDeTesorosPorObtener() {
	Jugador *jugador = this->turno->obtenerJugadorActual();
	Lista<Casillero*> *casilleros = jugador->obtenerCasilleros();

	casilleros->iniciarCursor();
	while (casilleros->avanzarCursor()) {
		Casillero *casillero = casilleros->obtenerCursor();
		if (casillero->obtenerTipoCasillero() == INACTIVO) {
			this->interacciones->mostrarProgresoRobo(casillero->obtenerX(), casillero->obtenerY(), casillero->obtenerZ(), casillero->obtenerInactivoHasta());
		}

	}
}
