#include "Juego.h"
#include <SFML/Graphics.hpp>
#include "Bala.h"
#include "Enemigo.h"
#include "Entidad.h"
#include "Explosion.h"
#include "Mensaje.h"

using namespace std;

Juego* Juego::instancia = 0;

Juego::Juego(){
}

void Juego::iniciar(){
    //instancia = juego;
}//iniciar

void Juego::update(float deltaTime){
    //vericiar cambio de niveles
    switch (ESTADO_ACTUAL){
    case 0:
        ESTADO_ACTUAL = ESTADO_INICIAR_NIVEL;
        break;
    case ESTADO_INICIAR_NIVEL:
        iniciarNivel();
        break;
    case ESTADO_NIVEL_1:
        nivel01(deltaTime);
        break;
    case ESTADO_NIVEL_2:
        nivel02(deltaTime);
        break;
    case ESTADO_NIVEL_3:
        nivel03(deltaTime);
        break;
    case ESTADO_VERIFICAR_FIN_NIVEL:
        verificarFinNivel(deltaTime);
        break;
    case ESTADO_FIN:
        break;
    default:
        break;
    }

}//update

bool Juego::juegoActivo(){
    return esActivo;
}

void Juego::crearBala(float x, float y, int tipoDisparo, sf::Vector2f* direccion, float velocidad){
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("texturas/balas.png");
    Bala* b = new Bala(text, sf::Vector2u(4, 20), 0.05f, velocidad, x, y, tipoDisparo, direccion);
    listaEntidadesBase.push_back( (Entidad*)b );
}
void Juego::crearExplosion(float x, float y){
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("texturas/explosion.png");
    sf::Vector2f* dir = new sf::Vector2f(0,1);
    //(sf::Texture * texture, sf::Vector2u imageCount, float switchTime, float speed, float x, float y, int tipoDisparo, sf::Vector2f * direccion) :
    Explosion* ex = new Explosion ( text, sf::Vector2u(5, 1), 0.05f, x, y);
    listaEntidadesBase.push_back((Entidad*)ex);
}

void Juego::crearPlayer(){
    sf::Texture* text = new sf::Texture();
    text->loadFromFile("texturas/ship.png");
    player = new Player(text, sf::Vector2u(5, 2), 0.05f, 400, 400, 700);
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
    
    Enemigo* enemigo = new Enemigo(text, sf::Vector2u(2, 1), 0.05f, 400, x, y, tipoEnemigo);
    listaEntidadesBase.push_back((Entidad*)enemigo);
    listaEntidadesEnemigos.push_back((Entidad*)enemigo);
}

void Juego::registrarEliminar(Entidad* entidad){
    listaEntidadesEliminar.push_back(entidad);
}

Juego* Juego::getInstancia(){
    if ( instancia == 0 ) {
        instancia = new Juego();
    }
    return instancia;
}

void Juego::verificarFinNivel(float deltaTime){
    cout << "verificarFinNivel.." << endl;
    if (totalEnemigos <= 0) {
        //nivel finalizado
        cout << "Nivel finalizado.." << endl;
        nivelActual++;
        ESTADO_ACTUAL = ESTADO_INICIAR_NIVEL;
        if (nivelActual < 3) {
            mostrarImagen(1, 2);//imagen next level
        } else {
            mostrarImagen(2, 300);//imagen gameover
        }
    }
}

void Juego::juegoFinalizado(float deltaTime) {
    cout << "Juego finalizado!" << endl;
}

void Juego::notificarEnemigoDestruido(){
    totalEnemigos--;
}

void Juego::iniciarNivel() {
    contadorTiempoNivel1 = 0;
    contadorTiempoNivel2 = 0;
    contadorTiempoNivel3 = 0;
    switch (nivelActual) {
    case 0:
        lapsoTiempo1 = 3.f;
        cantidadEnemigosTipo1 = 5;
        totalEnemigos = cantidadEnemigosTipo1;
        ESTADO_ACTUAL = ESTADO_NIVEL_1;
        break;
    case 1:
        lapsoTiempo1 = 3.f;
        lapsoTiempo2 = 5.f;
        cantidadEnemigosTipo1 = 5;
        cantidadEnemigosTipo2 = 5;
        totalEnemigos = cantidadEnemigosTipo1 + cantidadEnemigosTipo2;
        ESTADO_ACTUAL = ESTADO_NIVEL_2;
        break;
    case 2:
        lapsoTiempo1 = 3.f;
        lapsoTiempo2 = 5.f;
        lapsoTiempo3 = 8.f;
        cantidadEnemigosTipo1 = 5;
        cantidadEnemigosTipo2 = 5;
        cantidadEnemigosTipo3 = 3;
        totalEnemigos = cantidadEnemigosTipo1 + cantidadEnemigosTipo2 + cantidadEnemigosTipo3;
        ESTADO_ACTUAL = ESTADO_NIVEL_3;
        break;
    case 3:
        ESTADO_ACTUAL = ESTADO_FIN;
        break;
    default:
        break;
    }
}

void Juego::nivel01(float deltaTime) {
    contadorTiempoNivel1 += deltaTime;

    if ( contadorTiempoNivel1 > lapsoTiempo1 && cantidadEnemigosTipo1 > 0) {
        contadorTiempoNivel1 -= lapsoTiempo1;

        Juego* juego = Juego::getInstancia();
        juego->crearEnemigo(-100, -100, 1);
        cantidadEnemigosTipo1--;
    }
    if (totalEnemigos <= 0) {
        ESTADO_ACTUAL = ESTADO_VERIFICAR_FIN_NIVEL;
    }
}
void Juego::nivel02(float deltaTime) {
    contadorTiempoNivel1 += deltaTime;
    contadorTiempoNivel2 += deltaTime;

    if (contadorTiempoNivel1 > lapsoTiempo1 && cantidadEnemigosTipo1 > 0) {
        contadorTiempoNivel1 -= lapsoTiempo1;

        Juego* juego = Juego::getInstancia();
        juego->crearEnemigo(-100, -100, 1);
        cantidadEnemigosTipo1--;
    }
    if (contadorTiempoNivel2 > lapsoTiempo2 && cantidadEnemigosTipo2 > 0) {
        contadorTiempoNivel2 -= lapsoTiempo2;

        Juego* juego = Juego::getInstancia();
        juego->crearEnemigo(400, -200, 2);
        cantidadEnemigosTipo2--;
    }
    if (totalEnemigos <= 0) {
        ESTADO_ACTUAL = ESTADO_VERIFICAR_FIN_NIVEL;
    }
}
void Juego::nivel03(float deltaTime) {
    contadorTiempoNivel1 += deltaTime;
    contadorTiempoNivel2 += deltaTime;
    contadorTiempoNivel3 += deltaTime;

    if (contadorTiempoNivel1 > lapsoTiempo1 && cantidadEnemigosTipo1 > 0) {
        contadorTiempoNivel1 -= lapsoTiempo1;

        Juego* juego = Juego::getInstancia();
        juego->crearEnemigo(400, -200, 1);
        cantidadEnemigosTipo1--;
    }
    if (contadorTiempoNivel2 > lapsoTiempo2 && cantidadEnemigosTipo2 > 0) {
        contadorTiempoNivel2 -= lapsoTiempo2;

        Juego* juego = Juego::getInstancia();
        juego->crearEnemigo(500, -200, 2);
        cantidadEnemigosTipo2--;
    }
    if (contadorTiempoNivel3 > lapsoTiempo3 && cantidadEnemigosTipo3 > 0) {
        contadorTiempoNivel3 -= lapsoTiempo3;

        Juego* juego = Juego::getInstancia();
        juego->crearEnemigo(800, -400, 3);
        cantidadEnemigosTipo3--;
    }
    if (totalEnemigos <= 0) {
        ESTADO_ACTUAL = ESTADO_VERIFICAR_FIN_NIVEL;
    }
}

void Juego::mostrarImagen(int tipoMensaje, float duracion){
    sf::Texture* text = new sf::Texture();
    if ( tipoMensaje == 1 ) {
        text->loadFromFile("texturas/nextLevel.png");
    } else if (tipoMensaje == 2) {
        text->loadFromFile("texturas/gameOver.png");
    } else if (tipoMensaje == 3) {
        text->loadFromFile("texturas/19452.png");
    } else if (tipoMensaje == 4) {
        text->loadFromFile("texturas/fondo2.png");
    }
    Mensaje* mensaje = new Mensaje(text, sf::Vector2u(1, 1), 0.05f, 400, 100, tipoMensaje, duracion);
    listaEntidadesBase.push_back((Entidad*)mensaje);
}
