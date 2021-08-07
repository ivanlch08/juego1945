#include "Bala.h"
#include <iostream>
#include	 "Juego.h"

Bala::Bala(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int _tipoDisparo, sf::Vector2f* dir) :
	Entidad(texture, imageCount, switchTime, speed, x, y) {
	
	tipoDisparo = _tipoDisparo;
	idAnimacion = 0;
	direccion = dir;

	//cout << "x: " << direccion->x << ", y: " << direccion->y << endl;

	body.setSize(sf::Vector2f(50.f, 50.f));
	body.setOrigin(sf::Vector2f(25.f, 25.f));
	if ( _tipoDisparo == 1 ) {
		body.setFillColor(sf::Color::Cyan);
	}

	int tipoSprite = _tipoDisparo;
	Anim* idle = new Anim(true, 0, 0.05f);
	idle->addCuadro(0, tipoSprite);
	idle->addCuadro(1, tipoSprite);
	idle->addCuadro(2, tipoSprite);
	idle->addCuadro(3, tipoSprite);
	/*
	tipoSprite = 16;
	Anim* idle2 = new Anim(true, 1, 0.05f);
	idle2->addCuadro(0, tipoSprite);
	idle2->addCuadro(1, tipoSprite);
	idle2->addCuadro(2, tipoSprite);
	idle2->addCuadro(3, tipoSprite);
	*/
	animation.listaAnims.push_back(idle);
	//animation.listaAnims.push_back(idle2);

	animation.animActual = idle;
}

Bala::~Bala(){
	delete direccion;
}

void Bala::Update(float deltaTime) {
	contadorTiempoVida += deltaTime;

	sf::Vector2f avance(direccion->x, direccion->y);
	avance *= speed * deltaTime;
	body.move(avance);	
	//validar si hay colision
	

	if (tipoDisparo == 1) {
		Juego* juego = Juego::getInstancia();
		sf::FloatRect boundingBox = body.getGlobalBounds();
		//es bala disparada por player, mirar enemigos
		for (int k = 0; k < juego->listaEntidadesEnemigos.size(); k++) {
			Entidad* enemigo = juego->listaEntidadesEnemigos[k];
			sf::FloatRect boundingBoxEnemigo = enemigo->body.getGlobalBounds();
			if (boundingBox.intersects(boundingBoxEnemigo)) {
				juego->registrarEliminar(enemigo);
				juego->registrarEliminar(this);
				juego->notificarEnemigoDestruido();
				juego->listaEntidadesEnemigos.erase(
					juego->listaEntidadesEnemigos.begin() + k
				);
				juego->crearExplosion(body.getPosition().x, body.getPosition().y);
				break;
			}
		}
	}
	else {
		//es bala disparada por enemigo, mirar colision con player
		Juego* juego = Juego::getInstancia();
		sf::FloatRect boundingBox = body.getGlobalBounds();
		sf::FloatRect boundingBoxPlayer = juego->player->body.getGlobalBounds();
		if (boundingBox.intersects(boundingBoxPlayer)) {
			//cout << "colision!" << endl;
			
		}
	}
	
	//si tiempo de vida supera 8 segundos, eliminar entity
	if ( contadorTiempoVida >= 8.f ) {
		Juego* juego = Juego::getInstancia();
		juego->registrarEliminar(this);
	}
}//
