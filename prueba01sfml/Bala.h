#include "Entidad.h"
#include <SFML/Graphics.hpp>

#pragma once
class Bala : public Entidad {
private:
	
public:
	Bala(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int tipoDisparo);
	~Bala();
	void Update(float deltaTime) override;
};
