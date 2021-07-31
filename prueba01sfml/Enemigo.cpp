#include "Enemigo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "VectorUtil.h"

Enemigo::Enemigo(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int _tipoEnemigo):
	Entidad(texture, imageCount, switchTime, speed, x, y) {
	tipoEnemigo = _tipoEnemigo;
	idAnimacion = 0;

	switch (_tipoEnemigo){
	case 1:
		body.setSize(sf::Vector2f(100.f, 100.f));
		body.setOrigin(sf::Vector2f(50.f, 50.f));
		break;
	case 2:
		body.setSize(sf::Vector2f(50.f, 50.f));
		body.setOrigin(sf::Vector2f(25.f, 25.f));
		break;
	case 3:
		body.setSize(sf::Vector2f(30.f, 30.f));
		body.setOrigin(sf::Vector2f(15.f, 15.f));
		break;
	default:
		body.setSize(sf::Vector2f(100.f, 100.f));
		body.setOrigin(sf::Vector2f(50.f, 50.f));
		break;
	}

	Anim* idle = new Anim(true, 0, 0.05f);
	idle->addCuadro(0, 0);
	idle->addCuadro(1, 0);

	animation.listaAnims.push_back(idle);

	animation.animActual = idle;
}

Enemigo::~Enemigo(){
}

void Enemigo::Update(float deltaTime){
	//cada cierto tiempo cambia de posicion
	//dispara cierta cantidad de veces en esa posicion
	//vuelve a cambiar de posicion
	switch (ESTADO_ACTUAL){
	case 0:
		ESTADO_ACTUAL = ESTADO_INICIO_MOVERSE;
		break;
	case ESTADO_INICIO_MOVERSE:
		inicioMoverse();
		break;
	case ESTADO_MOVERSE:
		moverse(deltaTime);
		break;
	case ESTADO_INICIO_DISPARO:
		inicioDisparar();
		break;
	case ESTADO_DISPARO:
		disparar();
		break;
	default:
		break;
	}
}
void Enemigo::inicioMoverse(){
	//obtener una posicion destino aleatoria
	delete posicionAleatoria;
	
	float a = 1.0;

	float maxTam = 800;
	float x = (float(rand()) / float((RAND_MAX)) * a) * maxTam;
	maxTam = 400;
	float y = (float(rand()) / float((RAND_MAX)) * a) * maxTam;
	
	posicionAleatoria = new sf::Vector2f(x, y);
	//body.setPosition( *(posicionAleatoria) );
	//body.setPosition(sf::Vector2f(0.f, 0.f));
	ESTADO_ACTUAL = ESTADO_MOVERSE;
}
void Enemigo::moverse(float deltaTime){
	float x = posicionAleatoria->x - body.getPosition().x;
	float y = posicionAleatoria->y - body.getPosition().y;
	
	
	sf::Vector2f direccion(x, y);
	float magnitud = VectorUtil::magnitud(direccion);

	if (  magnitud < 10.f ) {
		ESTADO_ACTUAL = ESTADO_INICIO_MOVERSE;
	}
	
	direccion = VectorUtil::normalize(direccion);
	
	direccion *= deltaTime * velocidad;
	body.move(direccion);
}

void Enemigo::inicioDisparar(){
}

void Enemigo::disparar(){
}

