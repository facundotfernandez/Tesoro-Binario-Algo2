#ifndef JUGADOR_H
#define JUGADOR_H

#include "Pila.h"
#include "Lista.h"
#include "Casillero.h"
#include "Vector.h"
#include "Carta.h"
#include <string>

class Jugador {
private:
	Pila<std::string> *cambios;
	unsigned int id;
	unsigned int cantidadTesorosActivos;
	unsigned int cantidadTesorosObtenidos;

	/*Almacena todas los casilleros donde el jugador tiene o bien un tesoro, un espía o una mina.*/
	Lista<Casillero*> *casilleros;

	/*Almacena todas los casilleros donde el jugador tiene o bien un tesoros inactivos*/
	Lista<Casillero*> *tesorosInactivos;

	/*Almacena todas los casilleros donde el jugador tiene o bien un tesoro blindado*/
	Lista<Casillero*> *tesorosBlindados;
	/*Cartas que tiene el jugador en su mano.*/	
	Lista<Carta*> *cartasDisponibles;

	/*
	 pre: el tesoroInactivo debe estar en la lista de tesorosInactivos.
	 post: elimina el tesoroInactivo a la lista de tesorosInactivos. Si el tesoroInactivo no pertenece
	 		a la lista de tesorosInactivos, devuelve error (out_of_range).
	 */
	void eliminarTesoroInactivo(Casillero *tesoroInactivo);
	/*
	 pre: el tesoroBlindado debe estar en la lista de tesorosBlindados.
	 post: elimina el tesoroBlindado a la lista de tesorosBlindados. Si el tesoroBlindado no pertenece
	 		a la lista de tesorosBlindados, devuelve error (out_of_range).
	 */
	void eliminarTesoroBlindado(Casillero *tesoroBlindado);

public:
	/*
	 pre: -
	 post: Crea el jugador identificado como id sin cartas, ni tesoros, ni ninguna casilla propia.
	 */
	Jugador(unsigned int id);

	/*
	 pre: -
	 post: -
	 */
	virtual ~Jugador();

	/*
	 pre: -
	 post: devuelve el identificador asignado al jugador.
	 */
	unsigned int obtenerId();

    /*
     * pre: -
     * post: Devuelve la lista de casilleros del jugador
     */
	Lista<Casillero*>* obtenerCasilleros();

	/*
	 pre: -
	 post: devuelve la cantidad de casilleros que posee el jugador.
	 */
	unsigned int obtenerCantidadDeCasilleros();

	/*
	 pre: -
	 post: devuelve la cantidad de cartas que posee el jugador.
	 */
	unsigned int obtenerCantidadDeCartas();

	/*
	 pre: 
	 post: Devuelve la cantidad de tesoros activos que tiene el jugador.
	 */
	unsigned int obtenerCantidadTesorosActivos();

	/*
	 pre: 
	 post: Devuelve la cantidad de tesoros inactivos que tiene el jugador.
	 */
	unsigned int obtenerCantidadTesorosInactivos();

	

	/*
	 pre: -
	 post: Devuelve la cantidad de tesoros obtenidos que tiene el jugador.
	 */
	unsigned int obtenerCantidadTesorosObtenidos();

	/*
	 pre: El jugador debe poseer una carta del tipo solicitado
	 post: Devuelve la primer carta del tipo que tiene el jugador si existe o error (out_of_range).
	 */
	Carta* obtenerCarta(unsigned int tipoCarta);

	/*
	 pre: Las coordenadas del casillero ingresadas deben pertenecer a un casillero priopio.
	 post: Devuelve el casillero propio que tiene las coordenadas ingresadas si es propiedad del jugador o error (out_of_range).
	 */
	Casillero* obtenerCasilleroPropio(Vector<unsigned int> *coordenada);

	/*
	 * Pre: -
	 * Post: Devuelve una lista de las cartas del jugador
	 */
	Lista <Carta*>* obtenerCartas();

	/*
	 pre: -
	 post:  Devuelve una lista con un puntero a todos los casilleros con tesoros inactivos que posee el jugador.
	 */
	Lista<Casillero*>* obtenerTesorosInactivos();
	/*
	pre: -
	post: Devuelve una lista con un puntero a todos los casilleros con tesoros inactivos que posee el jugador.
	*/
	Lista<Casillero*>* obtenerTesorosBlindados();


	/*
	 pre: -
	 post:  Devuelve una carta random de la mano del jugador. No elimina la carta de la mano del jugador. Devuelve NULL en caso de que el jugador no tenga ninguna carta.
	 */
	Carta* obtenerCartaRandom();

	/*
	 * Pre: -
	 * Post: Devuelve la lista de cambios.
	 */
	Pila<std::string>* obtenerCambios();

	/*
	 pre: -
	 post: Reemplaza la cantidad de tesoros activos del jugador por el valor ingresado.
	 */
	void reemplazarTesorosActivos(unsigned int cantidadActivos);

	/*
	 pre: -
	 post: Reemplaza la cantidad de tesoros obtenidos del jugador por el valor ingresado.
	 */
	void reemplazarTesorosObtenidos(unsigned int cantidadObtenidos);

	/*
	 pre: -
	 post: Le asigna al jugador el identificador ingresado.
	 */
	void reemplazarId(unsigned int id);

	/*
	 pre: El jugador debe poseer al menos una carta del tipo seleccionado.
	 post: Elimina la carta del tipo solicitado (liberando la memoria) y coloca la nueva carta ingresada por parámetro.
	 		Si no existe una carta del tipo indicado devuelve error (out_of_range).
	 */
	void reemplazarCarta(unsigned int tipoCarta, Carta *carta);

	/*
	 pre: -
	 post: aumenta en uno la cantidad de tesoros activos.
	 */
	void aumentarTesoroActivo();

	/*
	 pre: -
	 post: aumenta en uno la cantidad de tesoros obtenidos.
	 */
	void aumentarTesoroObtenido();

	/*
	 pre: La cantidad de tesoros activos no puede ser menor que 1.
	 post: Disminuye en uno la cantidad de tesoros activos.
	 */
	void disminuirTesoroActivo();

	/*
	 pre: La cantidad de tesoros obtenidos no puede ser menor que 1.
	 post: Disminuye en uno la cantidad de tesoros obtenidos.
	 */
	void disminuirTesoroObtenidos();

	/*
	 pre: -
	 post: Agrega el tesoroInactivo a la lista de tesorosInactivos. En caso de ya pertenecer a dicha lista no hace nada.
	 */
	void agregarTesoroInactivo(Casillero *tesoroInactivo);
	
	/*
	 pre: -
	 post: Agrega el tesoroBlindado a la lista de tesorosBlindados. En caso de ay pertencer a dicha lista no hace nada.
	*/
	void agregarTesoroBlindado(Casillero *tesoroBlindado);
	
	/*
	 pre: -
	 post: agrega una carta al final de la mano del jugador.
	 */
	void agregarCarta(Carta *carta);

	/*
	 pre: No se puede agregar un casillero que ya esté en la lista.
	 post: Agrega el casilleroPropio al final de la lista casillerosPropios. Si el casilleroPropio ya está en la lista devuevle error (logic_error).
	 		Actualiza la lista de tesorosInactivos.
	 */
	void agregarCasilleroPropio(Casillero *casilleroPropio);

	/*
	 * Pre: -
	 * Post: agrega un cambio a la pila de cambios a mostrar
	 */
	void agregarCambio(std::string cambio);

	/*
	 pre: El jugador debe poseer al menos una carta del tipo ingresado.
	 post: Elimina la primer carta del tipo ingresado (liberando la memoria) de la mano de cartas del jugador.
	 		Si no posee una carta del tipo indicado devuelve error (out_of_range).
	 */
	void eliminarCarta(unsigned int tipoCarta);

    /*
	 pre: Las coordenadas del casillero ingresadas deben pertenecer a un casillero priopio. En caso de no serlo retorna error (out_of_range).
	 post: elimina de la lista (no borra al casillero de la memoria) de casilleros propios el casillero que tiene las coordenadas indicadas.
	 		Actualiza la lista de tesorosInactivos.
	 */
    void eliminarCasilleroPropio(Casillero * aEliminar);

	/*
	 pre: Las coordenadas del casillero ingresadas deben pertenecer a un casillero priopio. En caso de no serlo retorna error (out_of_range).
	 post: elimina de la lista (no borra al casillero de la memoria) de casilleros propios el casillero que tiene las coordenadas indicadas.
	 		Actualiza la lista de tesorosInactivos.
	 */
	void eliminarCasilleroPropio(Vector<unsigned int> *coordenada);


	/*
	pre: -
	post: Vacia todos los casilleros asociados al jugador y pone el id del jugador asociado al casillero en 0.
			Elimina la lista de casilleros y tesoros inactivos del jugador.
	*/
	void vaciarCasilleros();
};

#endif
