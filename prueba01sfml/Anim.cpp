#include "Anim.h"
#include <iostream>

using namespace std;

Anim::Anim(bool _loopeable, int _id, float _switchTime){
	loopeable = _loopeable;
	id = _id;
	switchTime = _switchTime;
	this->reiniciar();
}

Anim::~Anim()
{
}

void Anim::addCuadro(int x, int y){
	sf::Vector2u vec = sf::Vector2u(x, y);
	this->listaCuadros.push_back(vec);
}

void Anim::reiniciar(){
	this->time = 0;
	this->pos = 0;
	this->finalizado = false;
}

sf::Vector2u Anim::obtenerCuadro(float deltaTime){
	if (loopeable == false && finalizado == true) {
		return listaCuadros[pos];
	}

	time += deltaTime;
	if (time >= switchTime) {
		time -= switchTime;
		pos++;
		if ( pos >= listaCuadros.size() ) {
			if (loopeable == true) {
				pos = 0;
			}else {
				finalizado = true;
				pos--;
			}
		}
		
	}

	return listaCuadros[pos];
}
