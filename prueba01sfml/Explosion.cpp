#include "Explosion.h"
#include "Juego.h"

Explosion::Explosion(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float x, float y):
	Entidad(texture, imageCount, switchTime, 0, x, y) {
	//explosion.png
	idAnimacion = 0;

	body.setSize(sf::Vector2f(50.f, 50.f));
	body.setOrigin(sf::Vector2f(25.f, 25.f));

	int tipoSprite = 0;
	Anim* idle = new Anim(true, 0, 0.05f);
	idle->addCuadro(0, tipoSprite);
	idle->addCuadro(1, tipoSprite);
	idle->addCuadro(2, tipoSprite);
	idle->addCuadro(3, tipoSprite);
	idle->addCuadro(4, tipoSprite);

	animation.listaAnims.push_back(idle);

	animation.animActual = idle;
}

Explosion::~Explosion(){
}

void Explosion::Update(float deltaTime){
	contadorTiempoVida += deltaTime;

	if (contadorTiempoVida >= 2.f) {
		Juego* juego = Juego::getInstancia();
		juego->registrarEliminar(this);
	}	
}
