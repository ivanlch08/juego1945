#include "Player.h"
#include "Juego.h"
#include <iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.f, 100.f));
	body.setPosition(sf::Vector2f(200.f, 200.f));
	body.setTexture(texture);

	static int IDS = 0;
	this->id = IDS++;
	//std::cout << "id: " << this->id << std::endl;

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

}//cons

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(100.f, 100.f));
	body.setPosition(sf::Vector2f(x, y));
	body.setTexture(texture);

	body.setOrigin(sf::Vector2f(50.f, 50.f));
	
	static int IDS = 0;
	this->id = IDS++;

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
}

Player::~Player()
{
}

void Player::Update(float deltaTime){
	int idAnim = 0;
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
			Juego::getInstancia()->crearBala( body.getPosition().x, body.getPosition().y, tipoDisparo);
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
		movement.x -= speedTemp * deltaTime;
		idAnim = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		movement.x += speedTemp * deltaTime;
		idAnim = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		movement.y -= speedTemp * deltaTime;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		movement.y += speedTemp * deltaTime;
	}
	
	else {
		if (movement.x > 0.0f) {
			faceRight = true;
		}else {
			faceRight = false;
		}
	}
	animation.update(row, deltaTime, idAnim);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}//update

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}