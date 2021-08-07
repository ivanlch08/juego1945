#include "Mensaje.h"
#include "Juego.h"

Mensaje::Mensaje(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x, float y, int tipoMensaje, float _duracionMensaje) :
	Entidad(texture, imageCount, switchTime, speed, x, y) {
	idAnimacion = 0;
	duracionMensaje = _duracionMensaje;

	body.setPosition(x, y);

	switch (tipoMensaje) {
	case 1:
		//next level
		body.setSize(sf::Vector2f(200.f, 200.f));
		body.setOrigin(sf::Vector2f(100.f, 100.f));
		break;
	case 2:
		//game over
		body.setSize(sf::Vector2f(300.f, 150.f));
		body.setOrigin(sf::Vector2f(150.f, 75.f));
		break;
	case 3:
		//1945
		body.setSize(sf::Vector2f(300.f, 120.f));
		body.setOrigin(sf::Vector2f(150.f, 60.f));
		body.setFillColor(sf::Color::White);
		break;
	case 4:
		//imagen de fondo
		body.setPosition(0, 0);
		body.setSize(sf::Vector2f(800.f, 800.f));
		break;
	default:
		break;
	}
	

	Anim* idle = new Anim(true, 0, 5.f);
	idle->addCuadro(0, 0);

	animation.listaAnims.push_back(idle);

	animation.animActual = idle;
}

Mensaje::~Mensaje(){
}

void Mensaje::Update(float deltaTime){
	contadorTiempoMensaje += deltaTime;
	if (contadorTiempoMensaje >= duracionMensaje) {
		Juego* juego = Juego::getInstancia();
		juego->registrarEliminar(this);
	}
}
