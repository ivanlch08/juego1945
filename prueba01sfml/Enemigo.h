#include "Entidad.h"
#include <SFML/Graphics.hpp>

#pragma once
class Enemigo : public Entidad {
private:
	int tipoEnemigo;
	float velocidad = 400;
	int ESTADO_ACTUAL = 0;
	sf::Vector2f* posicionAleatoria = new sf::Vector2f(0.f, 0.f);;
public:
	int const static ESTADO_INICIO_DISPARO = 1;
	int const static ESTADO_DISPARO = 2;
	int const static ESTADO_INICIO_MOVERSE = 3;
	int const static ESTADO_MOVERSE = 4;
	
public:
	Enemigo(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int tipoEnemigo);
	~Enemigo();
	void Update(float deltaTime) override;
	void inicioMoverse();
	void moverse(float deltaTime);
	void inicioDisparar();
	void disparar();
	
};