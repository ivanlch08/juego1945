#include "Entidad.h"
#include <SFML/Graphics.hpp>

#pragma once
class Bala : public Entidad {
private:
	int tipoDisparo;
public:
	Bala(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	Bala(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int tipoDisparo);

	void Update(float deltaTime) override;
};
