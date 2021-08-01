#include "Entidad.h"
#include <SFML/Graphics.hpp>

#pragma once
class Bala : public Entidad {
private:
	sf::Vector2f* direccion;
	int tipoDisparo = 0;
	float contadorTiempoVida = 0;
public:
	Bala(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int tipoDisparo, sf::Vector2f* direccion);
	~Bala();
	void Update(float deltaTime) override;
};
