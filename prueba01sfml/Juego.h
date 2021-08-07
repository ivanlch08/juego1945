#include "Player.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Entidad.h"

#pragma once
class Juego{
public:
	sf::RenderWindow* window;
	vector<Entidad*> listaEntidadesBase;
	vector<Entidad*> listaEntidadesEnemigos;
	vector<Entidad*> listaEntidadesEliminar;
	Player* player;
	int const static ESTADO_INICIAR_NIVEL = 1;
	int const static ESTADO_NIVEL_1 = 2;
	int const static ESTADO_NIVEL_2 = 3;
	int const static ESTADO_NIVEL_3 = 4;
	int const static ESTADO_VERIFICAR_FIN_NIVEL = 5;
	int const static ESTADO_FIN = 6;
private:
	static Juego* instancia;
	bool esActivo = true;
	float deltaTime = 0.0f;
	vector<Player*> listaEntidades;
	int cantidadEnemigosTipo1 = 0;
	int cantidadEnemigosTipo2 = 0;
	int cantidadEnemigosTipo3 = 0;
	float contadorTiempoNivel1 = 0;
	float contadorTiempoNivel2 = 0;
	float contadorTiempoNivel3 = 0;
	float lapsoTiempo1 = 1.f;
	float lapsoTiempo2 = 1.f;
	float lapsoTiempo3 = 1.f;
	float contadorReiniciarJuego = 0;
	int totalEnemigos = 0;
	int ESTADO_ACTUAL = 0;
	int nivelActual = 0;
private:
	Juego();
public:
	void iniciar();
	void update(float deltaTime);
	bool juegoActivo();
	void crearBala(float x, float y, int tipoDisparo, sf::Vector2f* direccion, float velocidad);
	void crearExplosion(float x, float y);
	void crearPlayer();
	void crearEnemigo(float x, float y, int tipoEnemigo);
	void registrarEliminar(Entidad* entidad);

	void iniciarNivel();

	void nivel01(float deltaTime);
	void nivel02(float deltaTime);
	void nivel03(float deltaTime);
	void juegoFinalizado(float deltaTime);

	void verificarFinNivel(float deltaTime);
	void notificarEnemigoDestruido();

	void mostrarImagen(int tipoMensaje, float duracion);

	static Juego* getInstancia();
};