#include <SFML/Graphics.hpp>
#include "Animation.h"


#pragma once
class Entidad{
public:
	sf::RectangleShape body;
	Animation animation;
	int id;
	float speed;
	int idAnimacion;
public:
	Entidad(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y);
	~Entidad();
	virtual void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void UpdateAnim(float deltaTime);
};

