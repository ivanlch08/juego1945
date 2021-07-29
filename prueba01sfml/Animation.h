#include <SFML/Graphics.hpp>
#include "Anim.h"

#pragma once
class Animation{
private:
public:
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animation();

	void update(int row, float deltaTime, int idAnim);
	
private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
	float totalTime;
	float switchTime;
	float finalizado = false;
	
public:
	sf::IntRect uvRect;
	Anim* animActual;
	vector<Anim*> listaAnims;
};