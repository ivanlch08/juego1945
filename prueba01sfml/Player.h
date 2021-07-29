#include <SFML/Graphics.hpp>
#include "Animation.h"

#pragma once
class Player{
private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	int id;
	float tiempoTotal = 0;
	float lapsoBalas = 0;
	float tiempoUltimoDisparo = 0;
	int tipoDisparo = 0;
	bool botonVpresionado = false;
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y);
	~Player();
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
};

