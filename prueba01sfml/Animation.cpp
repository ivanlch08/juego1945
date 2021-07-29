#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime){
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0;
	currentImage.x = 0;
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
	animActual = 0;
	
}

Animation::~Animation()
{
}

void Animation::update(int row, float deltaTime, int idAnim){
	bool cambioDeAnim = false;

	if (idAnim != animActual->id) {
		cambioDeAnim = true;
	}
	
	//temporal
	animActual = this->listaAnims[idAnim];
	if (cambioDeAnim == true) {
		animActual->reiniciar();
		totalTime = 0;
		currentImage.x = 0;
		currentImage.y = 0;
	}

	//procesoNuevo
	sf::Vector2u cuadro = animActual->obtenerCuadro(deltaTime);
	
	currentImage.x = cuadro.x;
	currentImage.y = cuadro.y;

	uvRect.top = currentImage.y * uvRect.height;

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.width = abs(uvRect.width);
	
}//update
