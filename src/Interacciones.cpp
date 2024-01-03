#include "Interacciones.h"

std::string Interacciones::generarRutaTablero(unsigned int idJugador, unsigned int perspectiva, unsigned int fila, unsigned int columna,
		unsigned int profundidad) {

	std::ostringstream ruta;
	std::string plano = "";

	switch (perspectiva) {
		case 1:
			plano = "xz";
			break;
		case 2:
			plano = "yz";
			break;
		default:
			plano = "xy";
	}

	ruta << "tableros/jugador-" << idJugador << "/" << plano << "_" << fila + 1 << "_" << columna + 1 << "_" << profundidad + 1 << ".bmp";

	return ruta.str();
}

std::string Interacciones::generarRutaJugador(unsigned int idJugador) {

	std::ostringstream ruta;
	ruta << "tableros/jugador-" << idJugador << "/";
	return ruta.str();
}

bool Interacciones::crearCarpetaJugador(unsigned int idJugador) {
	return mkdir((this->generarRutaJugador(idJugador).c_str()), 0777) == 0;
}

bool Interacciones::crearCarpetaTableros() {
	std::ostringstream ruta;
	ruta << "tableros/";
	return mkdir(((ruta.str()).c_str()), 0777) == 0;
}



Interacciones::Interacciones() {
}

Interacciones::~Interacciones() {
}

void Interacciones::limpiarBufer() {
	cin.clear();
	cin.ignore(10000, '\n');
}

string Interacciones::pasarAMinuscula(string cadena) {

	string cadenaEnMinuscula = "";

	for (unsigned int i = 0; i < cadena.length(); ++i) {
		char caracter = cadena[i];
		if ('A' <= caracter && caracter <= 'Z') {
			caracter = 'a' + (caracter - 'A');
		}
		cadenaEnMinuscula += caracter;
	}
	return cadenaEnMinuscula;
}

void Interacciones::validarExistencia(Lista<Casillero*> *casilleros) const {
	if (casilleros == NULL || (casilleros->estaVacia())) {
		throw logic_error("La estructura esta vacia o no existe");
	}
}

void Interacciones::validarExistencia(Lista<Carta*> *cartas) const {
	if (cartas == NULL || (cartas->estaVacia())) {
		throw logic_error("La estructura esta vacia o no existe");
	}
}

void Interacciones::validarExistencia(Lista<Jugador*> *jugadores) const {
	if (jugadores == NULL || (jugadores->estaVacia())) {
		throw logic_error("La estructura esta vacia o no existe");
	}
}

void Interacciones::validarExistencia(Pila<string> *cambios) const {
	if (cambios == NULL || (cambios->estaVacia())) {
		throw logic_error("La estructura esta vacia o no existe");
	}
}

void Interacciones::validarPosicion(unsigned int x, unsigned int y, unsigned int z, unsigned int ancho, unsigned int alto, unsigned int profundidad) const {
	if (!((x < ancho) && (y < alto) && (z < profundidad))) {
		throw out_of_range("La posicion no pertenece al tablero");
	}
}

void Interacciones::validarDimensiones(unsigned int ancho, unsigned int alto, unsigned int profundidad) const {

	bool validacionMinimoDimension = (MINIMO_DIMENSION <= ancho) && (MINIMO_DIMENSION <= alto) && (MINIMO_DIMENSION <= profundidad);
	bool validacionMaximoDimension = (MAXIMO_DIMENSION >= ancho) && (MAXIMO_DIMENSION >= alto) && (MAXIMO_DIMENSION >= profundidad);

	if (!validacionMinimoDimension || !validacionMaximoDimension) {
		throw out_of_range("Las dimensiones son invalidas");
	}
}

void Interacciones::validarLongitud(Lista<unsigned int> *estructura, unsigned int longitud) const {
	if (estructura == NULL) {
		throw logic_error("No existe la estructura");
	} else if (estructura->obtenerLongitud() != longitud) {
		throw out_of_range("La estructura no posee la longitud buscada");
	}
}

void Interacciones::validarLongitud(Vector<unsigned int> *estructura, unsigned int longitud) const {
	if (estructura == NULL) {
		throw logic_error("No existe la estructura");
	} else if (estructura->obtenerLongitud() != longitud) {
		throw out_of_range("La estructura no posee la longitud buscada");
	}
}

string Interacciones::concatenar(string primerMensaje, unsigned int valor, string segundoMensaje) {
	ostringstream cadena;
	cadena << primerMensaje << valor << segundoMensaje;
	return cadena.str();
}

string Interacciones::concatenar(string primerMensaje, string segundoMensaje) {
	ostringstream cadena;
	cadena << primerMensaje << segundoMensaje;
	return cadena.str();
}

string Interacciones::generarPregunta(string pregunta, string respuestaA, string respuestaB) {
	ostringstream cadena;
	cadena << pregunta << " (" << respuestaA << "/" << respuestaB << "): ";
	cadena.str(this->agregarSangria(cadena.str()));
	cadena << "\n";
	return cadena.str();
}

string Interacciones::generarOpcion(unsigned int desde, unsigned int hasta, string pregunta) {
	ostringstream cadena;
	cadena << pregunta << " (Entre " << desde << " y " << hasta << "): ";
	cadena.str(this->agregarSangria(cadena.str()));
	cadena << "\n";
	return cadena.str();
}

string Interacciones::generarOpcion(Casillero *casillero, unsigned int opcion) {

	ostringstream cadena;
	cadena << opcion << ") Tipo: " << this->generarNombreCasillero((casillero->obtenerTipoCasillero())) << " | Coordenadas: (" << (casillero->obtenerX() + 1)
			<< ", " << (casillero->obtenerY() + 1) << ", " << (casillero->obtenerZ() + 1) << ")";
	cadena.str(this->centrar(cadena.str()));
	cadena << "\n";
	return cadena.str();
}

string Interacciones::generarOpcion(Carta *carta, unsigned int opcion) {

	ostringstream cadena;
	cadena << opcion << ") Tipo: " << this->generarNombreCarta((carta->obtenerTipoCarta()));
	cadena.str(this->centrar(cadena.str()));
	cadena << "\n";
	return cadena.str();
}

string Interacciones::generarOpcion(Jugador *jugador) {
	ostringstream cadena;
	cadena << jugador->obtenerId() << ") Jugador " << jugador->obtenerId();
	cadena.str(this->centrar(cadena.str()));
	cadena << "\n";
	return cadena.str();
}

string Interacciones::centrar(string titulo, bool conGuiones) {

	unsigned int longitudMensaje = (titulo.length() + 2);

	if (longitudMensaje > ANCHO_CONSOLA) {
		throw out_of_range("La longitud del mensaje supera el límite permitido");
	}

	// Calcula la cantidad de guiones en cada lado
	int rellenoInicio = (ANCHO_CONSOLA - longitudMensaje) / 2;
	int rellenoFinal = ANCHO_CONSOLA - longitudMensaje - rellenoInicio;
	char relleno = (conGuiones) ? ('-') : (' ');

	ostringstream cadena;
	cadena << string(rellenoInicio, relleno) << " " << titulo << " " << string(rellenoFinal, relleno);
	return cadena.str();
}

string Interacciones::agregarSangria(string titulo) {

	unsigned int longitudMensaje = (titulo.length() + 2);

	if (longitudMensaje > ANCHO_CONSOLA) {
		throw out_of_range("La longitud del mensaje supera el límite permitido");
	}

	// Calcula la cantidad de guiones en cada lado
	int sangria = (ANCHO_CONSOLA - longitudMensaje) / 2;

	ostringstream cadena;
	cadena << string(sangria, ' ') << " " << titulo;
	return cadena.str();
}

string Interacciones::agregarEspaciado(string titulo, unsigned int espaciado) {
	ostringstream cadena;
	cadena << string(espaciado, '\n') << titulo << string(espaciado, '\n');
	return cadena.str();
}

string Interacciones::generarNombreCasillero(unsigned int tipoCasillero) {

	switch (tipoCasillero) {
		case VACIO:
			return "Vacio";
		case TESORO:
			return "Tesoro";
		case ESPIA:
			return "Espia";
		case INACTIVO:
			return "Inactivo";
		case BLINDADO:
			return "Blindado";
		case MINA:
			return "Mina";
		case PARTIDO:
			return "Tesoro Partido";
		case DESTRUIDO:
			return "Destruido";
		default:
			throw out_of_range("El tipo de casillero buscado no existe");
	}
}

string Interacciones::generarNombreCarta(unsigned int tipoCarta) {

	switch (tipoCarta) {
		case BLINDAR:
			return "Blindaje";

		case REVELAR:
			return "Revelar";
		case PARTIRTESORO:
			return "Partir Tesoro";
		case ROBARCARTA:
			return "Robar Carta";
		case DUPLICARTURNO:
			return "Doble turno";
		case TRACKEAR:
			return "Trackear";
		default:
			throw out_of_range("El tipo de carta buscado no existe");
	}
}

void Interacciones::pedirDimensiones(Vector<unsigned int> *dimensiones) {

	this->validarLongitud(dimensiones);
	unsigned int ancho, alto, profundidad;

	this->mostrarMensaje(this->generarOpcion(MINIMO_DIMENSION, MAXIMO_DIMENSION, "Ingrese el ancho del tablero"));
	cin >> ancho;

	this->mostrarMensaje(this->generarOpcion(MINIMO_DIMENSION, MAXIMO_DIMENSION, "Ingrese el alto del tablero"));
	cin >> alto;

	this->mostrarMensaje(this->generarOpcion(MINIMO_DIMENSION, MAXIMO_DIMENSION, "Ingrese la profundidad del tablero"));
	cin >> profundidad;

	this->limpiarBufer();
	this->validarDimensiones(ancho, alto, profundidad);

	dimensiones->reemplazarElemento(0, ancho);
	dimensiones->reemplazarElemento(1, alto);
	dimensiones->reemplazarElemento(2, profundidad);

}

void Interacciones::pedirCoordenadas(unsigned int ancho, unsigned int alto, unsigned int profundidad, Vector<unsigned int> *coordenadas) {

	this->validarLongitud(coordenadas);

	unsigned int x, y, z;

	this->mostrarMensaje(this->generarOpcion(1, ancho, "Ingrese la coordenada X"));
	cin >> x;

	this->mostrarMensaje(this->generarOpcion(1, alto, "Ingrese la coordenada Y"));
	cin >> y;

	this->mostrarMensaje(this->generarOpcion(1, profundidad, "Ingrese la coordenada Z"));
	cin >> z;

	this->limpiarBufer();
	this->validarPosicion((x - 1), (y - 1), (z - 1), ancho, alto, profundidad);

	coordenadas->reemplazarElemento(0, (x - 1));
	coordenadas->reemplazarElemento(1, (y - 1));
	coordenadas->reemplazarElemento(2, (z - 1));
}

unsigned int Interacciones::pedirOpcion(unsigned int desde, unsigned int hasta, string pregunta) {

	unsigned int opcion;

	this->mostrarMensaje(this->generarOpcion(desde, hasta, pregunta));
	cin >> opcion;

	this->limpiarBufer();
	if (!(desde <= opcion && opcion <= hasta)) {
		throw out_of_range("La opcion elegida no es valida");
	}

	return opcion;
}

bool Interacciones::preguntar(string pregunta, string respuestaA, string respuestaB) {

	string respuesta = "";
	this->mostrarMensaje(this->generarPregunta(pregunta, respuestaA, respuestaB));
	cin >> respuesta;

	string respuestaEnMinuscula = this->pasarAMinuscula(respuesta);
	string respuestaAEnMinuscula = this->pasarAMinuscula(respuestaA);
	string respuestaBEnMinuscula = this->pasarAMinuscula(respuestaB);

	if (respuestaEnMinuscula == respuestaAEnMinuscula) {
		return true;
	} else if (respuestaEnMinuscula == respuestaBEnMinuscula) {
		return false;
	} else {
		throw logic_error("La respuesta ingresada no es valida");
	}
}

void Interacciones::mostrarMensaje(string mensaje) {
	cout << mensaje;
}

void Interacciones::mostrarMensaje(unsigned int valor) {
	cout << valor;
}

string Interacciones::generarTitulo(unsigned int turno, unsigned int idJugador) {
	ostringstream cadena;
	cadena << "TESORO BINARIO ---- TURNO: " << turno << " JUGADOR " << idJugador;
	return this->agregarEspaciado(this->centrar(cadena.str(), true), ESPACIADO_TITULO);
}

string Interacciones::generarTitulo(string titulo, unsigned int espaciado, bool conGuiones) {
	return this->agregarEspaciado(this->centrar(titulo, true), espaciado);
}

void Interacciones::mostrarFinDeMenu() {
	this->mostrarMensaje(this->concatenar("\n", (this->agregarEspaciado(string(ANCHO_CONSOLA, '-'), ESPACIADO_SIMPLE))));
}

Casillero* Interacciones::elegirMenu(Lista<Casillero*> *casilleros, string indicacion) {

	this->mostrarMenu(casilleros);

	unsigned int opcion;
	try {
		opcion = this->pedirOpcion(1, (casilleros->obtenerLongitud()), indicacion);
		return casilleros->obtenerElemento(opcion - 1);
	} catch (out_of_range &e) {
		return NULL;
	}
}

Carta* Interacciones::elegirMenu(Lista<Carta*> *cartas, string indicacion) {

	this->mostrarMenu(cartas);

	unsigned int opcion;
	try {
		cout << endl;
		opcion = this->pedirOpcion(1, (cartas->obtenerLongitud()), indicacion);
		return cartas->obtenerElemento(opcion - 1);
	} catch (out_of_range &e) {
		return NULL;
	}
}

Jugador* Interacciones::elegirMenu(Lista<Jugador*> *jugadores, unsigned int idJugador, string indicacion) {

	this->mostrarMenu(jugadores, idJugador, indicacion);

	unsigned int idPrimerOpcion =
			(jugadores->obtenerElemento(0)->obtenerId() == idJugador) ?
					(jugadores->obtenerElemento(1)->obtenerId()) : (jugadores->obtenerElemento(0)->obtenerId());
	unsigned int idUltimoJugador = jugadores->obtenerElemento(jugadores->obtenerLongitud() - 1)->obtenerId();
	unsigned int idUltimaOpcion =
			(idUltimoJugador == idJugador) ? (jugadores->obtenerElemento(jugadores->obtenerLongitud() - 2)->obtenerId()) : (idUltimoJugador);

	unsigned int opcion;
	try {
		cout << endl;
		opcion = this->pedirOpcion(idPrimerOpcion, idUltimaOpcion, indicacion);
		return jugadores->obtenerElemento(opcion - 1);
	} catch (out_of_range &e) {
		return NULL;
	}
}

void Interacciones::mostrarTitulo(unsigned int turno, unsigned int idJugador) {
	this->mostrarMensaje(this->generarTitulo(turno, idJugador));
}

void Interacciones::mostrarTitulo(string titulo, unsigned int espaciado, bool conGuiones) {
	this->mostrarMensaje(this->generarTitulo(titulo, espaciado, true));
}

void Interacciones::mostrarMenu(Lista<Casillero*> *casilleros, string titulo) {

	this->validarExistencia(casilleros);

	this->mostrarTitulo(titulo);

	Casillero *casillero;
	unsigned int opcion = 0;

	casilleros->iniciarCursor();

	while (casilleros->avanzarCursor()) {
		opcion++;
		casillero = casilleros->obtenerCursor();
		this->mostrarMensaje(this->generarOpcion(casillero, opcion));
	}
	this->mostrarFinDeMenu();
}

void Interacciones::mostrarMenu(Lista<Carta*> *cartas, string titulo) {

	this->validarExistencia(cartas);

	this->mostrarTitulo(titulo);

	Carta *carta;
	unsigned int opcion = 0;

	cartas->iniciarCursor();

	while (cartas->avanzarCursor()) {
		opcion++;
		carta = cartas->obtenerCursor();
		this->mostrarMensaje(this->generarOpcion(carta, opcion));
	}
	this->mostrarFinDeMenu();
}

void Interacciones::mostrarMenu(Lista<Jugador*> *jugadores, unsigned int idJugador, string titulo) {

	this->validarExistencia(jugadores);

	this->mostrarTitulo(titulo);

	Jugador *jugador;

	jugadores->iniciarCursor();

	while (jugadores->avanzarCursor()) {
		jugador = jugadores->obtenerCursor();
		if (jugador->obtenerId() != idJugador) {
			this->mostrarMensaje(this->generarOpcion(jugador));
		}
	}
	this->mostrarFinDeMenu();
}

void Interacciones::mostrarMenu(Pila<string> *cambios, string titulo) {

	try {
		this->validarExistencia(cambios);
	} catch (const logic_error &e) {
		throw logic_error("No hay cambios registrados");
	}

	this->mostrarTitulo(titulo);
	while (!(cambios->estaVacia())) {
		this->mostrarMensaje(cambios->desapilar());
	}
	this->mostrarFinDeMenu();
}

void Interacciones::mostrarJugadoresEliminados(Pila<string> *cambios, string titulo) {
    if (cambios == NULL) {
        throw logic_error("La estructura no existe");
    }

    if (cambios->estaVacia()) {
        this->mostrarTitulo("No hubo eliminaciones en la ronda anterior");
    } else {
        this->mostrarTitulo(titulo);
        while (!(cambios->estaVacia())) {
            this->mostrarMensaje(this->agregarEspaciado(this->centrar(cambios->desapilar(), true), ESPACIADO_SIMPLE));
        }
    }
    this->mostrarFinDeMenu();
}

void Interacciones::mostrarCantidadDeEliminados(unsigned int cantidadDeEliminados) {
    if (cantidadDeEliminados == 1) {
        this->mostrarTitulo("Se ha eliminado un jugador");
    } else if (cantidadDeEliminados > 1) {
        this->mostrarTitulo(concatenar("Se han eliminado ", cantidadDeEliminados, " jugadores"));
    }
}

void Interacciones::mostrarProgresoRobo(unsigned int x, unsigned int y, unsigned int z, unsigned int turnosRestantes) {
	ostringstream cadena;
	cadena << "El robo en la posicion: (" << (x + 1) << "," << (y + 1) << "," << (z + 1) << ") finaliza en " << turnosRestantes << " turnos";
	this->mostrarTitulo(cadena.str());
	cadena.str("");
}

void Interacciones::mostrarFinDeJuego(unsigned int idJugador) {
	ostringstream cadena;
	cadena << "Juego terminado. Ha ganado el jugador " << idJugador;
	this->mostrarTitulo(cadena.str(), ESPACIADO_TITULO);
}

void Interacciones::mostrarObtencionCarta(unsigned int tipoCarta) {
	ostringstream cadena;
	cadena << "Nueva carta obtenida: " << this->generarNombreCarta(tipoCarta);
	this->mostrarTitulo(cadena.str(), ESPACIADO_NOTIFICACION);
	cadena.str("");
}

void Interacciones::mostrarRoboCarta(unsigned int tipoCarta) {
	ostringstream cadena;
	cadena << "Carta robada: " << this->generarNombreCarta(tipoCarta);
	this->mostrarTitulo(cadena.str(), ESPACIADO_NOTIFICACION);
	cadena.str("");
}

void Interacciones::mostrarTurnosInactividad(string mensaje, unsigned int hasta) {
	ostringstream cadena;
	cadena << mensaje << ", el casillero queda inactivo por " << hasta << " turnos";
	this->mostrarTitulo(cadena.str());
	cadena.str("");
}

void Interacciones::mostrarDeteccion(string mensaje, unsigned int x, unsigned int y, unsigned int z) {
	ostringstream cadena;
	cadena << mensaje << " en la posicion (" << (x + 1) << "," << (y + 1) << "," << (z + 1) << ")";
	this->mostrarTitulo(cadena.str());
	cadena.str("");
}

string Interacciones::generarCambio(unsigned int tipo, Vector<unsigned int> *coordenadas) {

	std::ostringstream cadena;
	string titulo = "";

	switch (tipo) {
		case ELIMINACION:
			return this->generarTitulo("Jugador eliminado");
		case CARTAROBADA:
			return this->generarTitulo("Carta robada");
		case TESOROPERDIDO:
			titulo = "Tesoro perdido";
			break;
		case ESPIAPERDIDO:
			titulo = "Espia perdido";
			break;
		case MINAPERDIDA:
			titulo = "Mina perdida";
			break;
		case BLINDAJEPERDIDO:
			titulo = "Blindaje perdido";
			break;
		case PARTIDOPERDIDO:
			titulo = "Tesoro partido perdido";
			break;
		case ROBOINICIADO:
			titulo = "Robo iniciado";
			break;
		case ROBOFINALIZADO:
			titulo = "Robo finalizado";
			break;
		case ROBOINTERRUMPIDO:
			titulo = "Robo interrumpido";
			break;
		default:
			throw out_of_range("El tipo de cambio buscado no existe");
	}

	this->validarLongitud(coordenadas);
	unsigned int x = coordenadas->obtenerElemento(0);
	unsigned int y = coordenadas->obtenerElemento(1);
	unsigned int z = coordenadas->obtenerElemento(2);

	cadena << titulo << " en la posicion (" << (x + 1) << "," << (y + 1) << "," << (z + 1) << ")";
	cadena.str(this->centrar(cadena.str()));
	cadena << "\n";
	return cadena.str();
}

void Interacciones::exportar(Plano *plano) {

    std::string ruta;

    int dimensionTablero = 6, dimensionCasillero = 64;

    int filaCentral = plano->obtenerFilaCentral(), columnaCentral = plano->obtenerColumnaCentral();
    int filaOrigen = plano->obtenerFilaOrigen(), columnaOrigen = plano->obtenerColumnaOrigen();

    /* Correcciones necesarias ya que el tablero se imprime desde la esquina superior izquierda */
    int correccionFila = filaOrigen + (dimensionTablero - 1) - 1;
    int correccionColumna = columnaOrigen - 1;
    int filaReal, columnaReal;

    /*
     * Genera un tablero de 6x6 celdas con tamaño de 384x384 pixeles.
     * (Incluye los cabezales, en la sexta fila y columna, para mostrar el número de fila/columna).
     */
    BMP tableroBmp;
    tableroBmp.SetSize(dimensionTablero * dimensionCasillero, dimensionTablero * dimensionCasillero);

    /* Indicador de fila o columna */
    RGBApixel colorIndicador = { 255, 255, 255 };
    char indicador[4];

    /* Perspectiva (XY,XZ,YZ) del plano */
    int perspectiva = plano->obtenerPerspectiva();

    /* Imagen a mostrar en el casillero */
    BMP *imagen;

    /* Carga las imágenes desde la carpeta "assets" */
    BMP vacio, espia, mina, tesoro, inactivo, blindado, partido, destruido;
    BMP fondo, iconoXY, iconoXZ, iconoYZ;
    BMP vacioCentral, espiaCentral, minaCentral, tesoroCentral, inactivoCentral, blindadoCentral, partidoCentral, destruidoCentral;

    vacio.ReadFromFile("assets/vacio.bmp");
    tesoro.ReadFromFile("assets/tesoro.bmp");
    espia.ReadFromFile("assets/espia.bmp");
    inactivo.ReadFromFile("assets/inactivo.bmp");
    blindado.ReadFromFile("assets/blindado.bmp");
    mina.ReadFromFile("assets/mina.bmp");
    partido.ReadFromFile("assets/partido.bmp");
    destruido.ReadFromFile("assets/destruido.bmp");

    vacioCentral.ReadFromFile("assets/vacio_central.bmp");
    tesoroCentral.ReadFromFile("assets/tesoro_central.bmp");
    espiaCentral.ReadFromFile("assets/espia_central.bmp");
    inactivoCentral.ReadFromFile("assets/inactivo_central.bmp");
    blindadoCentral.ReadFromFile("assets/blindado_central.bmp");
    minaCentral.ReadFromFile("assets/mina_central.bmp");
    partidoCentral.ReadFromFile("assets/partido_central.bmp");
    destruidoCentral.ReadFromFile("assets/destruido_central.bmp");

    fondo.ReadFromFile("assets/fondo.bmp");
    iconoXY.ReadFromFile("assets/icono_xy.bmp");
    iconoXZ.ReadFromFile("assets/icono_xz.bmp");
    iconoYZ.ReadFromFile("assets/icono_yz.bmp");

    Casillero *casillero = plano->obtenerCasillero(filaCentral, columnaCentral);
    unsigned int tipoCasillero;
    unsigned int idJugador = casillero->obtenerIdJugador();

    // Copia las imagenes en todas las celdas del tablero, según corresponda
    for (int fila = 0; fila < dimensionTablero; fila++) {
        for (int columna = 0; columna < dimensionTablero; columna++) {

            /*
             * Accede a los casilleros, manteniendo una de las variables fija,
             * para así poder mostrar los 3 planos.
             * La correccion permite armar un 5x5 alrededor del casillero principal
             * y corre el 5x5 en caso de que no se pueda dejar el casillero principal exactamente en el centro.
             */
            if (fila == (dimensionTablero - 1) || columna == 0) {
                tipoCasillero = (fila == (dimensionTablero - 1) && columna == 0) ? 9 : 8;
            } else {
                filaReal = correccionFila - fila;
                columnaReal = correccionColumna + columna;

                /* Se reemplaza el puntero a Casillero por puntero al Casillero actual */
                casillero = plano->obtenerCasillero(filaReal, columnaReal);
                if ((casillero->obtenerIdJugador() != idJugador) && (casillero->obtenerIdJugador() != ID_GLOBAL)) {
                    tipoCasillero = VACIO;
                } else {
                    tipoCasillero = casillero->obtenerTipoCasillero();
                }
            }

            /* Modifica el tipo de imagen a mostrar, en base al tipoCasillero del Casillero actual */
            switch (tipoCasillero) {
                case VACIO:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&vacioCentral) : (&vacio);
                    break;
                case TESORO:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&tesoroCentral) : (&tesoro);
                    break;
                case ESPIA:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&espiaCentral) : (&espia);
                    break;
                case INACTIVO:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&inactivoCentral) : (&inactivo);
                    break;
                case BLINDADO:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&blindadoCentral) : (&blindado);
                    break;
                case MINA:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&minaCentral) : (&mina);
                    break;
                case PARTIDO:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&partidoCentral) : (&partido);
                    break;
                case DESTRUIDO:
                    imagen = (filaReal == filaCentral && columnaReal == columnaCentral) ? (&destruidoCentral) : (&destruido);
                    break;
                case 8:
                    /* Fondo del cuadrante que indica el número de fila o columna */
                    imagen = &fondo;
                    break;
                case 9:
                    /* Cuadrante que indica la variable de la fila y columna (X,Y o Z) según perspectiva del plano */
                    switch (perspectiva) {
                        case (XY):
                            imagen = &iconoXY;
                            break;
                        case (XZ):
                            imagen = &iconoXZ;
                            break;
                        case (YZ):
                            imagen = &iconoYZ;
                            break;
                    }
                    break;
                default:
                    throw std::logic_error("El tipo de casillero a mostrar no es valido");
            }

            // Copia cada pixel de la imagen en el cuadrante correspondiente
            for (int x = 0; x < dimensionCasillero; ++x) {
                for (int y = 0; y < dimensionCasillero; ++y) {
                    tableroBmp(columna * dimensionCasillero + y, fila * dimensionCasillero + x)->Red = (*imagen)(y, x)->Red;
                    tableroBmp(columna * dimensionCasillero + y, fila * dimensionCasillero + x)->Green = (*imagen)(y, x)->Green;
                    tableroBmp(columna * dimensionCasillero + y, fila * dimensionCasillero + x)->Blue = (*imagen)(y, x)->Blue;
                }
            }

            if (fila == (dimensionTablero - 1) && columna != 0) {

                /* Imprime el número de columna en el cuadrante correspondiente */
                sprintf(indicador, "%d", (correccionColumna + columna + 1));
                PrintString(tableroBmp, indicador, columna * dimensionCasillero + 25, fila * dimensionCasillero + 19, 26, colorIndicador);

            } else if (columna == 0 && fila != (dimensionTablero - 1)) {

                /* Imprime el número de fila en el cuadrante correspondiente */
                sprintf(indicador, "%d", (correccionFila - fila + 1));
                PrintString(tableroBmp, indicador, columna * dimensionCasillero + 25, fila * dimensionCasillero + 19, 26, colorIndicador);
            }
        }
    }

    // Guarda el tablero en un archivo BMP del jugador correspondiente
    ruta = this->generarRutaTablero(idJugador, perspectiva, columnaCentral, filaCentral, (plano->obtenerProfundidad()));
    tableroBmp.WriteToFile(ruta.c_str());
}
