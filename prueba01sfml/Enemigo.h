#include "Entidad.h"
#include <SFML/Graphics.hpp>

#pragma once
class Enemigo : public Entidad {
private:
	int tipoEnemigo;
public:
	Enemigo(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int tipoEnemigo);
	~Enemigo();
	void Update(float deltaTime) override;
};