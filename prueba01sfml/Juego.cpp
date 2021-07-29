#include "Juego.h"
#include <SFML/Graphics.hpp>
#include "Bala.h"
#include "Enemigo.h"
#include "Entidad.h"

using namespace std;

Juego* Juego::instancia = 0;

Juego::Juego(){
}

void Juego::iniciar(){
    //instancia = juego;
}//iniciar

void Juego::update(){
    
}//update

bool Juego::juegoActivo(){
    return esActivo;
}

void Juego::crearBala(float x, float y, int tipoDisparo){ 
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("texturas/balas.png");
    Bala* b = new Bala(text, sf::Vector2u(4, 20), 0.05f, 500, x, y, tipoDisparo);
    listaEntidadesBase.push_back( (Entidad*)b );
}
void Juego::crearPlayer(){
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("texturas/ship.png");
    Player* player = new Player(text, sf::Vector2u(5, 2), 0.05f, 400, 600, 600);
    listaEntidadesBase.push_back((Entidad*)player);
}

void Juego::crearEnemigo(float x, float y, int tipoEnemigo){
    sf::Texture* text = new sf::Texture();
    switch (tipoEnemigo){
    case 1:
        text->loadFromFile("texturas/enemigo1.png");
        break;
    case 2:
        text->loadFromFile("texturas/enemigo2.png");
        break;
    case 3:
        text->loadFromFile("texturas/enemigo3.png");
        break;
    default:
        break;
    }
    
    Enemigo* enemigo = new Enemigo(text, sf::Vector2u(2, 1), 0.05f, 400, x, x, tipoEnemigo);
    listaEntidadesBase.push_back((Entidad*)enemigo);
}



Juego* Juego::getInstancia(){
    if ( instancia == 0 ) {
        instancia = new Juego();
    }
    return instancia;
}

//crearBala