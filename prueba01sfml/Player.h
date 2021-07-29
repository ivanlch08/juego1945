#include <SFML/Graphics.hpp>
#include "Entidad.h"

#pragma once
class Player : public Entidad {
private:
	float tiempoTotal = 0;
	float lapsoBalas = 0;
	float tiempoUltimoDisparo = 0;
	int tipoDisparo = 0;
	bool botonVpresionado = false;
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y);
	~Player();
	void Update(float deltaTime) override;
};

