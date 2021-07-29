#include "Enemigo.h"

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
	
}
