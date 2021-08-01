#include "Entidad.h"
#include <SFML/Graphics.hpp>

#pragma once
class Explosion : public Entidad {
private:
	float contadorTiempoVida = 0;
public:
	Explosion(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x, float y);
	~Explosion();
	void Update(float deltaTime) override;
};