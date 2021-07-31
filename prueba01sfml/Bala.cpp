#include "Bala.h"
#include <iostream>

Bala::Bala(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int _tipoDisparo, sf::Vector2f* dir) :
	Entidad(texture, imageCount, switchTime, speed, x, y) {
	
	idAnimacion = _tipoDisparo;
	direccion = dir;
	body.setSize(sf::Vector2f(50.f, 50.f));
	body.setOrigin(sf::Vector2f(25.f, 25.f));

	int tipoSprite = 1;
	Anim* idle = new Anim(true, 0, 0.05f);
	idle->addCuadro(0, tipoSprite);
	idle->addCuadro(1, tipoSprite);
	idle->addCuadro(2, tipoSprite);
	idle->addCuadro(3, tipoSprite);

	tipoSprite = 16;
	Anim* idle2 = new Anim(true, 1, 0.05f);
	idle2->addCuadro(0, tipoSprite);
	idle2->addCuadro(1, tipoSprite);
	idle2->addCuadro(2, tipoSprite);
	idle2->addCuadro(3, tipoSprite);

	animation.listaAnims.push_back(idle);
	animation.listaAnims.push_back(idle2);

	animation.animActual = idle;
}

Bala::~Bala(){
	delete direccion;
}

void Bala::Update(float deltaTime) {
	sf::Vector2f avance(direccion->x, direccion->y);
	avance *= speed * deltaTime;
	body.move(avance);

	
}//
