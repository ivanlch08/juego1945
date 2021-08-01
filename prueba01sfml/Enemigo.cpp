#include "Enemigo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "VectorUtil.h"
#include "Juego.h"

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
		disparar(deltaTime);
		break;
	default:
		break;
	}
}
void Enemigo::inicioMoverse(){
	//obtener una posicion destino aleatoria
	//tipoEnemigo = 1: eje x siempre es el mismo del player
	delete posicionAleatoria;
	
	float a = 1.0;

	float maxTam = 800;
	float x = 0;
	if ( tipoEnemigo == 1 ) {
		x = Juego::getInstancia()->player->body.getPosition().x;
	}else {
		x = (float(rand()) / float((RAND_MAX)) * a) * maxTam;
	}
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
		ESTADO_ACTUAL = ESTADO_INICIO_DISPARO;
	}
	
	direccion = VectorUtil::normalize(direccion);
	
	direccion *= deltaTime * velocidad;
	body.move(direccion);
}

void Enemigo::inicioDisparar(){
	//reiniciar contadores
	contadorDisparos = 0;
	contadorLapsoDisparo = 0;
	ESTADO_ACTUAL = ESTADO_DISPARO;
}

void Enemigo::disparar(float deltaTime){
	switch (tipoEnemigo){
	case 1:
		dispararEstilo01(deltaTime);
		break;
	case 2:
		dispararEstilo02(deltaTime);
		break;
	case 3:
		dispararEstilo03(deltaTime);
		break;
	default:
		break;
	}
}//disparar

void Enemigo::dispararEstilo01(float deltaTime){
	float tiempoDisparo = 0.1f;
	contadorLapsoDisparo += deltaTime;
	if (contadorLapsoDisparo >= tiempoDisparo) {
		contadorLapsoDisparo -= tiempoDisparo;

		//disparar 3 veces
		Juego* juego = Juego::getInstancia();
		sf::Vector2f d = juego->player->body.getPosition() - body.getPosition();
		//cout << "dx: " << d.x << ", dy: " << d.y << endl;
		//sf::Vector2f norm = VectorUtil::normalize(d);
		//cout << "nx: " << norm.x << ", ny: " << norm.y << endl;
		sf::Vector2f* dir = new sf::Vector2f(0, 1);
		juego->crearBala(body.getPosition().x, body.getPosition().y, 0, dir, 600);
		contadorDisparos++;

		if (contadorDisparos >= 3) {
			ESTADO_ACTUAL = ESTADO_INICIO_MOVERSE;
		}

	}
}

void Enemigo::dispararEstilo02(float deltaTime){
	float tiempoDisparo = 0.2f;
	contadorLapsoDisparo += deltaTime;
	if (contadorLapsoDisparo >= tiempoDisparo) {
		contadorLapsoDisparo -= tiempoDisparo;

		//disparar 3 veces
		Juego* juego = Juego::getInstancia();
		sf::Vector2f d = juego->player->body.getPosition() - body.getPosition();
		sf::Vector2f norm = VectorUtil::normalize(d);
		sf::Vector2f* dir = new sf::Vector2f(norm.x, norm.y);
		
		juego->crearBala(body.getPosition().x, body.getPosition().y, 2, dir, 400);
		contadorDisparos++;

		if (contadorDisparos >= 1) {
			ESTADO_ACTUAL = ESTADO_INICIO_MOVERSE;
		}

	}
}

void Enemigo::dispararEstilo03(float deltaTime){
	//hacer una rotacion de 360 disparando cada cierto intervalo
	int cantidadDisparos = 15;
	float tiempoDisparo = 0.025f;
	contadorLapsoDisparo += deltaTime;
	if (contadorLapsoDisparo >= tiempoDisparo) {
		contadorLapsoDisparo -= tiempoDisparo;

		//calcular rotacion
		float avance = (float)((float)contadorDisparos / (float)cantidadDisparos);
		float grados = 360.f * avance;

		//disparar 3 veces
		Juego* juego = Juego::getInstancia();
		sf::Vector2f d(0, 1);
		sf::Vector2f norm = VectorUtil::rotar(d, grados);
		sf::Vector2f* dir = new sf::Vector2f(norm.x, norm.y);

		juego->crearBala(body.getPosition().x, body.getPosition().y, 6, dir, 200);
		contadorDisparos++;

		if (contadorDisparos >= cantidadDisparos) {
			ESTADO_ACTUAL = ESTADO_INICIO_MOVERSE;
		}

	}
}
