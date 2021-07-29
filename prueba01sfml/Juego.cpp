#include "Juego.h"
#include <SFML/Graphics.hpp>
#include "Bala.h"
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
Juego* Juego::getInstancia(){
    if ( instancia == 0 ) {
        instancia = new Juego();
    }
    return instancia;
}

//crearBala