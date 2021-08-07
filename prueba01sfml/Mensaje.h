#include "Entidad.h"
#include <SFML/Graphics.hpp>

#pragma once
class Mensaje : public Entidad {
private:
	float contadorTiempoMensaje = 0;
	float duracionMensaje = 0;
public:
	Mensaje(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x, float y, int tipoMensaje, float duracionMensaje);
	~Mensaje();
	void Update(float deltaTime) override;

};