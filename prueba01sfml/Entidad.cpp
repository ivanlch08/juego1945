#include "Entidad.h"
#include <iostream>
#include "Juego.h"

Entidad::Entidad(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y):
	animation(texture, imageCount, switchTime) {

	static int IDS = 0;
	this->id = IDS++;
	
	this->speed = speed;

	body.setSize(sf::Vector2f(100.f, 100.f));
	body.setPosition(sf::Vector2f(x, y));
	body.setTexture(texture);
}

Entidad::~Entidad(){
}

void Entidad::Update(float deltaTime){
	std::cout << "metodo sobreescrito" << endl;
}

void Entidad::Draw(sf::RenderWindow& window){
	window.draw(body);
}

void Entidad::UpdateAnim(float deltaTime){
	animation.update(0, deltaTime, idAnimacion);
	body.setTextureRect(animation.uvRect);
}
