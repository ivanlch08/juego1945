#include "Player.h"
#include "Juego.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y) :
	Entidad(texture, imageCount, switchTime, speed, x, y) {
	
	body.setSize(sf::Vector2f(100.f, 100.f));
	body.setPosition(sf::Vector2f(200.f, 200.f));

	body.setOrigin(sf::Vector2f(50.f, 50.f));

	//temporal
	Anim* idle = new Anim(true, 0, 0.05f);
	idle->addCuadro(2, 0);
	idle->addCuadro(2, 1);
	animation.listaAnims.push_back(idle);

	Anim* izq = new Anim(true, 1, 0.05f);
	izq->addCuadro(0, 0);
	izq->addCuadro(0, 1);
	animation.listaAnims.push_back(izq);

	Anim* der = new Anim(true, 2, 0.05f);
	der->addCuadro(4, 0);
	der->addCuadro(4, 1);
	animation.listaAnims.push_back(der);

	animation.animActual = idle;

	lapsoBalas = 0.3f;
}//cons

Player::~Player(){
}

void Player::Update(float deltaTime){
	idAnimacion = 0;
	sf::Vector2f movement(0.0f, 0.0f);
	float speedTemp = speed;

	tiempoTotal += deltaTime;

	//turbo
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		speedTemp *= 2.f;
	}

	//disparo
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		float diferencia = tiempoTotal - tiempoUltimoDisparo;
		if ( diferencia > lapsoBalas ) {
			sf::Vector2f* dir = new sf::Vector2f(0,-1.f);
			Juego::getInstancia()->crearBala( body.getPosition().x, body.getPosition().y, 1, dir);
			tiempoUltimoDisparo = tiempoTotal;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V) && botonVpresionado == false) {
		tipoDisparo = tipoDisparo == 0 ? 1 : 0;
		botonVpresionado = true;
	}
	else {
		botonVpresionado = false;
	}

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ) {
		//verificar que no salga del limite
		if ( body.getPosition().x > 0 ) {
			movement.x -= speedTemp * deltaTime;
			idAnimacion = 1;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//verificar que no salga del limite
		if (body.getPosition().x < 800) {
			movement.x += speedTemp * deltaTime;
			idAnimacion = 2;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (body.getPosition().y > 0) {
			movement.y -= speedTemp * deltaTime;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (body.getPosition().y < 800) {
			movement.y += speedTemp * deltaTime;
		}
	}
	body.move(movement);
	//cout << "posx: " << body.getPosition().x << ", posy: " << body.getPosition().y << endl;
}//update
