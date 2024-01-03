#ifndef INTERACCIONES_H_
#define INTERACCIONES_H_

using namespace std;

#include "../easy-bmp/EasyBMP_Font.h"
#include <sys/stat.h>
#include <sstream>
#include <iostream>
#include "Plano.h"
#include "Lista.h"
#include "Jugador.h"
#include "Casillero.h"
#include "Carta.h"

class Interacciones {

private:

	/*
	 * pre : -
	 * post: Libera los datos guardados en el bufer de memoria.
	 */
	void limpiarBufer();

	/*
	 * pre : La estructura debe existir y no estar vacía (@throws logic_error).
	 * post: -
	 */
	void validarExistencia(Lista<Casillero*> *casilleros) const;

	/*
	 * pre : La estructura debe existir y no estar vacía (@throws logic_error).
	 * post: -
	 */
	void validarExistencia(Lista<Carta*> *cartas) const;

	/*
	 * pre : La estructura debe existir y no estar vacía (@throws logic_error).
	 * post: -
	 */
	void validarExistencia(Lista<Jugador*> *jugadores) const;

	/*
	 * pre : La estructura debe existir y no estar vacía (@throws logic_error).
	 * post: -
	 */
	void validarExistencia(Pila<string> *cambios) const;

	/*
	 * pre : La posición pertenece a las dimensiones dadas (@throws out_of_range).
	 * post: -
	 */
	void validarPosicion(unsigned int x, unsigned int y, unsigned int z, unsigned int ancho, unsigned int alto, unsigned int profundidad) const;

	/*
	 * pre : Las dimensiones pertenecen al rango de dimensiones permitido (@throws out_of_range).
	 * post: -
	 */
	void validarDimensiones(unsigned int ancho, unsigned int alto, unsigned int profundidad) const;

	/*
	 * pre : El puntero a la estructura NO debe ser nulo (@throws logic_error).
	 * 		 La estructura dada tiene la longitud buscada (@throws out_of_range).
	 * post: -
	 */
	void validarLongitud(Vector<unsigned int> *estructura, unsigned int longitud = CANTIDAD_DIMENSIONES) const;

	/*
	 * pre : El puntero a la estructura NO debe ser nulo (@throws logic_error).
	 * 		 La estructura dada tiene la longitud buscada (@throws out_of_range).
	 * post: -
	 */
	void validarLongitud(Lista<unsigned int> *estructura, unsigned int longitud = CANTIDAD_DIMENSIONES) const;

	/*
	 * pre : -
	 * post: Devuelve una cadena equivalente a la dada pero completamente en minúscula.
	 */
	string pasarAMinuscula(string cadena);

	/*
	 * pre : -
	 * post: Genera la información del casillero formateada con su tipo y coordenadas.
	 */
	string generarInformacion(Casillero *casillero);

	/*
	 * pre : -
	 * post: Genera la información de la carta formateada con su tipo.
	 */
	string generarInformacion(Carta *carta);

	/*
	 * pre : -
	 * post: Genera la información de una opción de menú desplegable.
	 */
	string generarOpcion(unsigned int desde, unsigned int hasta, string pregunta);

	/*
	 * pre : -
	 * post: Genera la información de una opción de menú desplegable.
	 */
	string generarOpcion(Jugador *jugador);

	/*
	 * pre : -
	 * post: Genera la información de una opción de menú desplegable.
	 */
	string generarOpcion(Casillero *casillero, unsigned int opcion);

	/*
	 * pre : -
	 * post: Genera la información de una opción de menú desplegable.
	 */
	string generarOpcion(Carta *carta, unsigned int opcion);

	/*
	 * pre : -
	 * post: Genera una pregunta con formato.
	 */
	string generarPregunta(string pregunta, string respuestaA, string respuestaB);

	/*
	 * pre : -
	 * post: Genera una cadena alineada al centro en la consola.
	 */
	string centrar(string titulo, bool conGuiones = false);

	/*
	 * pre : -
	 * post: Genera una cadena con sangría agregada.
	 */
	string agregarSangria(string titulo);

	/*
	 * pre : -
	 * post: Genera una cadena con espaciado agregado.
	 */
	string agregarEspaciado(string titulo, unsigned int espaciado = ESPACIADO_SIMPLE);

	/*
	 * pre : -
	 * post: Genera un titulo con formato.
	 */
	string generarTitulo(string titulo, unsigned int espaciado = ESPACIADO_SIMPLE, bool conGuiones = false);

	/*
	 * pre : -
	 * post: Muestra una linea que indica el fin de un menú desplegable.
	 */
	void mostrarFinDeMenu();


	/*
	 * pre : -
	 * post: Concatena dos mensajes, luego devuelve la cadena completa.
	 */
	string concatenar(string primerMensaje, string segundoMensaje);

	/*
	 * pre : -
	 * post: Genera la cadena de texto correspondiente a la ruta al tablero del jugador, según su perspectiva y idJugador dados.
	 */
	std::string generarRutaTablero(unsigned int idJugador, unsigned int perspectiva, unsigned int fila, unsigned int columna, unsigned int profundidad);

	/*
	 * pre : -
	 * post: Genera la cadena de texto correspondiente a la ruta a la carpeta que contiene los tableros del jugador, según su idJugador dado.
	 */
	std::string generarRutaJugador(unsigned int idJugador);

public:

	/*
	 * pre : -
	 * post: Inicializa una instancia de Interacciones.
	 */
	Interacciones();

	/*
	 * pre : -
	 * post: Libera los recursos asociados a Interacciones.
	 */
	virtual ~Interacciones();

	/*
	 * pre : La carpeta 'tableros/' debe existir.
	 * post: Crea el directorio del jugador correspondiente dentro de la carpeta 'tableros/'.
	 */
	bool crearCarpetaJugador(unsigned int idJugador);

	/*
	 * pre : -
	 * post: Crea el directorio'tableros/'.
	 */
	bool crearCarpetaTableros();

	/*
	 * pre : La carpeta del jugador en cuestión ya debe existir dentro de la carpeta "tableros", con formato "jugador-<idJugador>" (@throws EasyBMPwarnings).
	 * post: Crea tres tableros (Planos XY,XZ,YZ con el Casillero en el centro) en formato BMP, a partir del Tablero y Casillero dados, y lo guarda en la carpeta del jugador correspondiente.
	 */
	void exportar(Plano *plano);

	/*
	 * pre : El puntero a la estructura NO debe ser nulo (@throws logic_error).
	 * 		 La estructura dada debe tener 3 elementos (@throws out_of_range).
	 * post: Pide dimensiones al usuario, reemplaza los elementos del vector recibido en caso de que las dimensiones ingresadas sean válidas.
	 *   	 Las dimensiones ingresadas por el usuario deben ser mayores al mínimo permitido (@throws out_of_range).
	 */
	void pedirDimensiones(Vector<unsigned int> *dimensiones);

	/*

	 * pre : -
	 * post: Pide, al usuario, coordenadas que correspondan a una posición válida, CREA UN PUNTERO a un Vector de coordenadas y lo devuelve.
	 * 		 Las coordenadas recibidas del usuario deben corresponder a una posicion valida (@throws out_of_range).
	 * 		 El vector dado debe tener longitud igual a 3 (@throws out_of_range).
	 * 		 Corrige con "-1" las coordenadas ingresadas por el usuario, para coincidir con el criterio del desarrollo.
	 */
	void pedirCoordenadas(unsigned int ancho, unsigned int alto, unsigned int profundidad, Vector<unsigned int> *coordenadas);

	/*
	 * pre : -
	 * post: Pide un numero correspondiente a posiciones que se encuentre entre los numeros dados (@throws out_of_range).
	 * 		 Devuelve la opción elegida
	 */
	unsigned int pedirOpcion(unsigned int desde, unsigned int hasta, string pregunta = "Ingrese la opcion elegida");

	/*
	 * pre : -
	 * post: Concatena dos mensajes y un valor en el medio, luego devuelve la cadena completa.
	 */
	string concatenar(string primerMensaje, unsigned int valor, string segundoMensaje);

	/*
	 * pre : -
	 * post: Realiza una pregunta dada, al usuario, y verifica si dicha respuesta es igual a alguna de las esperadas.
	 * 		 Devuelve true si equivale a la respuestaA, false si corresponde a B y falla si la opcion no es válida (@throws logic_error).
	 */
	bool preguntar(string pregunta, string respuestaA, string respuestaB);

	/*
	 * pre : -
	 * post: Imprime por consola un mensaje para el usuario.
	 */
	void mostrarMensaje(string mensaje);

	/*
	 * pre : -
	 * post: Imprime por consola un valor para el usuario.
	 */
	void mostrarMensaje(unsigned int valor);

	/*
	 * pre : -
	 * post: Genera un titulo del turno, con formato.
	 */
	string generarTitulo(unsigned int turno, unsigned int idJugador);

	/*
	 * pre : -
	 * post: Imprime por consola un titulo.
	 */
	void mostrarTitulo(string titulo, unsigned int espaciado = ESPACIADO_SIMPLE, bool conGuiones = false);

	/*
	 * pre : -
	 * post: Imprime por consola un titulo para el turno, con el turno y idJugador dados.
	 */
	void mostrarTitulo(unsigned int turno, unsigned int idJugador);

	/*
	 * pre : -
	 * post: Muestra un menu desplegable con los casilleros propios del jugador, le solicita al jugador que elija uno y devuelve un puntero al casillero elegido en la lista de casilleros.
	 * 		 La opción elegida debe estar entre las ofrecidas (@throws out_of_range).
	 * 		 Si no es válida, devuelve NULL.
	 */
	Casillero* elegirMenu(Lista<Casillero*> *casilleros, string indicacion = "Selecciona un casillero");

	/*
	 * pre : -
	 * post: Muestra un menu desplegable con las cartas del jugador y devuelve un puntero a la carta elegida de su mano.
	 * 		 La opción elegida debe estar entre las ofrecidas (@throws out_of_range).
	 * 		 Si no es válida, devuelve NULL.
	 */
	Carta* elegirMenu(Lista<Carta*> *cartas, string indicacion = "Selecciona una carta");

	/*
	 * pre : -
	 * post: Muestra un menu desplegable con los jugadores dados y devuelve un puntero al jugador enemigo elegido.
	 * 		 La opción elegida debe estar entre las ofrecidas (@throws out_of_range).
	 * 		 Si no es válida, devuelve NULL.
	 */
	Jugador* elegirMenu(Lista<Jugador*> *jugadores, unsigned int idJugador, string indicacion);

	/*
	 * pre : -
	 * post: Muestra un menu desplegable con los casilleros dados.
	 */
	void mostrarMenu(Lista<Casillero*> *casilleros, string titulo = "Casilleros");

	/*
	 * pre : -
	 * post: Muestra un menu desplegable con las cartas dadas.
	 */
	void mostrarMenu(Lista<Carta*> *cartas, string titulo = "Cartas");

	/*
	 * pre : -
	 * post: Muestra un menu desplegable con los jugadores dados.
	 */
	void mostrarMenu(Lista<Jugador*> *jugadores, unsigned int idJugador, string titulo = "Jugadores");

	/*
	 * pre : -
	 * post: Muestra un menu desplegable con los cambios dados.
	 */
	void mostrarMenu(Pila<string> *cambios, string titulo = "Cambios registrados");

    /*
     * pre:  cambios es una pila no vacia
     * post: Muestra los jugadores que fueron eliminados, identificados por su id
     */
    void mostrarJugadoresEliminados(Pila<string> *cambios, string titulo = "Cambios globales registrados");

    /*
     * pre:
     * post: Muestra un titulo anunciando la cantidadDeEliminados, si es que hubo
     */
    void mostrarCantidadDeEliminados(unsigned int cantidadDeEliminados);

    /*
	 * pre : El tipo buscado debe existir (@throws out_of_range).
	 * post: Genera el titulo del Casillero según su tipo.
	 */
	string generarNombreCasillero(unsigned int tipo);

	/*
	 * pre : El tipo buscado debe existir (@throws out_of_range).
	 * post: Genera el titulo de la Carta según su tipo.
	 */
	string generarNombreCarta(unsigned int tipo);

	/*
	 * pre : -
	 * post: Muestra la cantidad de turnos restantes de un robo o una destrucción.
	 */
	void mostrarProgresoRobo(unsigned int x, unsigned int y, unsigned int z, unsigned int turnosRestantes);

	/*
	 * pre : -
	 * post: Muestra un mensaje de fin de juego con el ganador dado.
	 */
	void mostrarFinDeJuego(unsigned int idJugador);

	/*
	 * pre : -
	 * post: Muestra un aviso de obtención de una carta.
	 */
	void mostrarObtencionCarta(unsigned int tipoCarta);

	/*
	 * pre : -
	 * post: Muestra un aviso de robo de una carta.
	 */
	void mostrarRoboCarta(unsigned int tipoCarta);

	/*
	 * pre : -
	 * post: Muestra un aviso de turnos restantes por inactividad.
	 */
	void mostrarTurnosInactividad(string mensaje, unsigned int hasta);

	/*
	 * pre : -
	 * post: Muestra un aviso de deteccion en la posicion dada.
	 */
	void mostrarDeteccion(string mensaje, unsigned int x, unsigned int y, unsigned int z);

	/*
	 * pre : -
	 * post: Genera una cadena con las informacion correspondiente a un cambio registrado.
	 */
	string generarCambio(unsigned int tipo, Vector<unsigned int> *coordenadas = NULL);

};

#endif /* INTERACCIONES_H_ */

