#include "Turno.h"
#include "Jugador.h"
#include "Interacciones.h"
#include "Vector.h"
#include "Carta.h"
#include "Constantes.h"
#include <string>

#ifndef NULL
#define NULL 0
#endif /* NULL*/

class Juego {
private:
	Tablero *tablero;
	Turno *turno;
	Lista<Jugador*> *jugadores;
	Lista<Casillero*> *casillerosDestruidos;
	Pila<string> *eliminaciones;
	Interacciones *interacciones;
	bool juegoEnCurso;
	unsigned int objetivoTesoros;

	/*
	 * pre : dimensiones es un vector de 3 posiciones
	 * post: Pide los datos iniciales para armar el Juego.
	 *       a cantidadDeJugadores se le va a asignar un numero entre MINIMA_CANTIDAD_DE_JUGADORES y MAXIMA_CANTIDAD_DE_JUGADORES
	 *       a cantidadDeTesoros se le va a asignar un numero entre MINIMA_CANTIDAD_DE_TESOROS y MAXIMA_CANTIDAD_DE_TESOROS
	 *       a dimensiones se le asignaran coordenadas entre MINIMO_DIMENSION y MAXIMO_DIMENSION
	 */
	void establecerDatosIniciales(unsigned int &cantidadDeJugadores, unsigned int &cantidadDeTesoros, Vector<unsigned int> *dimensiones);

	/*
	 * pre : -
	 * post: Pide al Jugador coordenadas. Se asegura de que no pertenezca al jugador y que sea una coordenada dentro del
	 *       tablero. Si no lo es, pide reingreso de datos.
	 */
	Vector<unsigned int>* obtenerCoordenadasValidas(Jugador *jugador);

	/*
	 * pre:
	 * post: Verifica la cantidad de tesoros de los jugadores, si no tiene tesoros se lo elimina de la partida
	 */
	void verificarTesorosDeJugadores();

	/*
	 * pre: -
	 * post: Retorna FALSE si el vector es NULO, de lo contrario retorna TRUE
	 */
	bool validarCasillerosInactivos(Vector<Casillero*> *casillerosInactivos);

	/*
	 * pre : cantidadDeTesoros es un numero positivo
	 * post: Verifica que la cantidad de jugadores sea mayor a 2 y menor a 5 (@throws out_of_range).
	 */
	static void validarCantidadDeJugadores(unsigned int cantidadDeJugadores);

	/*
	 * pre: El jugador esta en la lista (@throws logic_error)
	 * post: verifica que el jugador este en la lista de jugadores
	 */
	void validarIdJugador(unsigned int idJugador);

	/*
	 * Pre:  Al menos hay un jugador en la partida
	 * Post: Obtiene el siguiente jugador en la lista de jugadores.
	 * 		 Si el jugador actual es el ultimo de la lista, se devuelve el primero como el siguiente
	 * 		 Si el jugador actual es cualquier otro, se devuelve el siguiente jugador (con id mayor al actual)
	 * 		 Si no hay un jugador en la partida, arroja una excepcion de tipo out_of_range
	 */
	Jugador* obtenerSiguienteJugador(unsigned int idJugadorActual);

	/*
	 * Pre:  La lista de jugadores no esta vacia
	 * Post: Retorna al jugador con mas tesoros obtenidos
	 */
	Jugador* obtenerJugadorConMasTesoros();

	/*
	 * Pre: -
	 * Post: Retorna FALSE si: hay 1 jugador en la partida o algun jugador llego a los tesoros requeridos para ganar.
	 * 		 Del caso contrario retorna TRUE.
	 */
	bool obtenerJuegoEnCurso();

	/*
	 * pre : cantidadDeTesoros es un numero positivo
	 * post: Inicializa la lista de jugadores con la cantidad de jugadores dada, con su ID desde 1.
	 */
	void inicializarJugadores(unsigned int cantidadDeJugadores);

	/*
	 * pre : cantidadDeTesoros es un numero positivo
	 * post: Inicializa la cantidad de tesoros de cada jugador en posiciones aleatorias del tablero.
	 */
	void inicializarTesoros(unsigned int cantidadDeTesoros);

	/*
	 * pre: jugador esta vivo y en el juego
	 * post: Coloca los tesoros de forma aleatoria en el tablero. Recibe al jugador a quien le perteneceran los
	 *       tesoros; un vector de coordenadas en el cual se colocara cada tesoro
	 */
	void generarTesorosAleatorios(Jugador *jugador, Vector<unsigned int> *coordenadas, unsigned int cantidadDeTesoros);

	/* pre : dimensiones es un vector de 3 posiciones, cantidadDeTesoros es un numero positivo
	 * post: Inicializa el tablero con las dimensiones dadas y la cantidad de tesoros dada.
	 */
	void inicializarTablero(Vector<unsigned int> *dimensiones, unsigned int cantidadDeTesoros);

	/*
	 * pre : coordenadas es un vector de 3 posiciones, idJugador pertenece a un jugador de la partida
	 * post: Valida si el casillero ingresado pertenece al id del jugador ingresado, si pertenece devuelve true, si no pertenece
	 * devuelve false.
	 */
	bool sonCoordenadasPropias(Vector<unsigned int> *coordenadas, unsigned int idJugador);

	/*
	 * Pre:  Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * Post: Si algun casillero del jugador ha llegado al turno donde debe dejar de ser INACTIVO, se convierte a VACIO
	 */
	void actualizarInactivos();

	/*
	 * Pre : Tiene que ser un casillero de tipo INACTIVO
	 * Post: Convierte a vacio el casillero del jugador
	 */
	void actualizarCasilleroInactivo(Casillero *casillero, Jugador *jugador);

	/*
	 * Pre: -
	 * Post: Si algun casillero del trablero ha llegado al turno donde debe dejar de ser DESTRUIDO, se convierte a VACIO
	 */
	void actualizarDestruidos();

	/*
	 *Pre: -
	 *Post: Si algun casillero ha llegado al turno donde debe dejar de estar BLINDADO, se convierte a VACIO
	 */
	void actualizarBlindados();

	/*
	 * Pre: Casillero aDestuir pertenece al jugador. destuidoHasta describe el turno en el cual pasa de DESTRUIDO a VACIO
	 * Post: se agrega el casillero como DESTRUIDO a casillerosDestruidos, se elimina el casillero del jugador
	 */
	void destruirCasillero(Casillero *aDestruir, Jugador *jugador, unsigned int destruidoHasta);

	/*
	 * Pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * Post: Mueve un tesoro, pide reingreso de datos si se trata de jugar un Espia fuera del tablero
	 */
	void jugarMoverTesoro();

	/*
	 * pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * post: Mueve el tesoro correspondiente seleccionado por el jugador, y hace las acciones necesarias dependiendo cada caso.
	 */
	void moverTesoro(Casillero *origen, Casillero *destino);

	/*
	 * pre : Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * post: Juega el espia, pide reingreso de datos si se trata de jugar un Espia fuera del tablero
	 */
	void jugarEspia();

	/*
	 * Pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * Post: Juega el espia, pide reingreso de datos si se trata de jugar un Espia fuera del tablero
	 */
	void jugarMina();

	/*
	 * Pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * Post: Agrega el espia al tablero con las coordenadas proporcionadas y hace las acciones necesarias
	 * dependiendo de la ubicacion dada
	 */
	void agregarEspia(Casillero *destino);

	/*
	 * pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 *      las coordenadas son validas (no pertenecen al jugador y se encuentran dentro del tablero)
	 * post: Exporta la mina al tablero con las coordenadas dadas y hace las acciones necesarias
	 */
	void agregarMina(Casillero *destino);

	/*
	 *pre : Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 *post: Ejecuta la funcionalidad de la carta especificada sobre el estado del juego
	 */
	bool jugarCarta();

	/*
	 * Pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * Post: Saca una carta del mazo y la agrega a la mano del jugador
	 */
	void sacarCarta();

	/*
	 * pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * post: Recorre el tablero, buscando objetos a detectar hasta que encuentre una cantidad igual a stop.
	 *       devuelve mediante punteros la ultima ubicacion donde encontró algo. Devuelve true si encontró algo y false si no encontró nada
	 */
	bool _trackear(unsigned int stop, unsigned int *i, unsigned int *j, unsigned int *k);

	/*
	 * pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * post: Juega la carta trackear casilla, alterando el tablero de forma acorde
	 */
	void jugarTrackearCasilla();

	/*
	 * pre : -
	 * post: Juega la carta partir tesoro, alterando el tablero de forma acorde
	 */

	void jugarPartirTesoro();

	/*
	 * pre : -
	 * post: Juega la carta radar, alterando el tablero de forma acorde
	 */

	void jugarRadar();

	/*
	 * pre : -
	 * post: Juega la carta blindaje, alterando el tablero de forma acorde
	 */

	void jugarBlindaje();

	/*
	 * pre : Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * post: Juega la carta robar carta, ajustando de forma acorde la cantidad de cartas de cada jugador
	 */
	void jugarRobarCarta();

	/*
	 * pre : Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * post: Juega la carta doble turno, reiniciando el turno del jugador actual
	 */
	void jugarDobleTurno();

	/*
	 * Pre: -
	 * Post: Se muestra por pantalla los turnos que le faltan a los tesoros encontrados del Jugador para obtenerlos
	 */
	void mostrarProgresoDeTesorosPorObtener();

	/*
	 * Pre: -
	 * Post: Elimina jugadores de la partida (de la lista) en el caso de que tengan 0 tesoros activos.
	 */
	void eliminarJugadoresSinTesorosActivos();

	/*
	 * Pre: -
	 * Post: Muestra los jugadores eliminados de la partida si es que hay
	 */
	void mostrarJugadoresEliminados();

	/*
	 * Pre: -
	 * Post: Muestra los cambios que sufrio/hizo el jugador durante la ronda junto la cantidad de veces que se realizo el mismo
	 */
	void mostrarCambios();

	/*
	 * Pre: -
	 * Post: Agrega un cambio a la pila de cambios del jugador indicado
	 */
	void guardarCambio(Jugador *jugador, unsigned int tipoCambio, Vector<unsigned int> *coordenadas);

	/*
	 * Pre:
	 * Post: Se mostraran los casilleros mientras el jugador actual lo desee
	 */
	void mostrarCasilleros();

	/*
	 * pre : -
	 * post: CREA una nueva lista que contenga solamente los casilleros filtrados según el o los tipos aceptados.
	 */
	Lista<Casillero*>* filtrarCasilleros(Lista<Casillero*> *casilleros, unsigned int tipoAceptadoA, unsigned int tipoAceptadoB = VACIO,
			unsigned int tipoAceptadoC = VACIO);

	Casillero* obtenerTesoro(Jugador *jugador, string indicacion, bool cualquierTipo = false);

	Casillero* obtenerDestino(Jugador *jugador, string indicacion);

public:
	/*
	 * Pre: -
	 * Post: Inicializa la cantidad de jugadores, y establece ID en cada jugador.
	 *       Inicializa el tablero y coloca los tesoros de forma aleatoria para cada jugador
	 *       Inicializa la lista de casillerosDestruidos como vacia
	 */
	Juego();

	/*
	 * Pre: -
	 * Post: Libera los recursos asociados a la partida.
	 */
	virtual ~Juego();

	/*
	 * Pre: -
	 * Post: Devuelve la cantidad de jugadores de la partida.
	 */
	unsigned int obtenerCantidadJugadores();

	/*
	 *Pre:- idJugadorActual es un numero positivo
	 *Post: Devuelve el jugador especificado por su ID.
	 */
	Jugador* obtenerJugador(unsigned int idJugadorActual);

	/*
	 * Pre:
	 * Post: Devuelve un puntero al tablero
	 */
	Tablero* obtenerTablero();

	/*
	 * Pre: Usa al jugador actual, guardado en turno. Si no pertenece (@throws logic_error)
	 * Post: Crea preguntas necesarias, guarda en el vector de registros los futuros cambios para actualizar
	 */
	void jugarTurno(unsigned int turnoActual);

	/*
	 * Pre: jugadorActual es un puntero a un jugador existente en jugadores
	 * Post: Avanza el turno al siguiente jugador y, si esta en el jugdaor N, avanza la ronda tambien
	 */
	void avanzarTurno(Jugador *jugadorActual);

	/*
	 * Pre:
	 * Post: Actualiza el tablero, actualiza nuevos cambios en la lista de jugadores, avanzamos al siguiente turno
	 */
	void actualizarJuego();

	/*
	 * Pre:-
	 * Post: Exporta Los 3 planos ortogonales centrados en un casillero a un archivo
	 */
	void exportarTablero(Lista<Casillero*> *casilleros);

};
