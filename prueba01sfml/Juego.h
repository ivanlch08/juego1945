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
private:
	static Juego* instancia;
	bool esActivo = true;
	float deltaTime = 0.0f;
	//sf::Clock clock;
	vector<Player*> listaEntidades;
	
private:
	Juego();
public:
	void iniciar();
	void update();
	bool juegoActivo();
	void crearBala(float x, float y, int tipoDisparo, sf::Vector2f* direccion);
	void crearPlayer();
	void crearEnemigo(float x, float y, int tipoEnemigo);

	static Juego* getInstancia();
};