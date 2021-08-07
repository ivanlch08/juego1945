#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Juego.h"

#include "Bala.h"

using namespace std;

void verificarEliminar() {
    Juego* juego = Juego::getInstancia();

    for (int k = 0; k < juego->listaEntidadesEliminar.size(); k++) {
        Entidad* elim = juego->listaEntidadesEliminar[k];
        int indiceElim = -1;
        for (int i = 0; i < juego->listaEntidadesBase.size(); i++) {
            Entidad* e = juego->listaEntidadesBase[i];
            if (e->id == elim->id) {
                //quitar de vector de eliminados
                juego->listaEntidadesEliminar.erase(
                    juego->listaEntidadesEliminar.begin() + k
                );
                k = -1;
                //registrar indice
                indiceElim = i;
                break;
            }
        }//
        if (indiceElim != -1) {
            Entidad* e = juego->listaEntidadesBase[indiceElim];
            juego->listaEntidadesBase.erase(
                juego->listaEntidadesBase.begin() + indiceElim
            );
            delete e;
        }
    }//

    
}

int main() {
    srand((unsigned int)time(NULL));
    Juego* juego = Juego::getInstancia();
    juego->iniciar();

    sf::RenderWindow win(sf::VideoMode(800, 800), "1945");
    juego->window = &win;

    juego->mostrarImagen(4, 30000);//imagen de fondo

    juego->crearPlayer();
    //juego->crearEnemigo(400, 400, 1);
    //juego->crearEnemigo(400, 400, 2);
    //juego->crearEnemigo(400, 400, 3);
    
    juego->mostrarImagen(3, 3);//imagen 1945
    
    //juego->mostrarImagen(1, 2);//imagen next level
    //juego->mostrarImagen(2, 300);//imagen gameover

    float deltaTime = 0.0f;
    float tiempoTotal = 0.0f;
    sf::Clock clock;

    
    while (juego->window->isOpen()){
        sf::Event vnt;
        deltaTime = clock.restart().asSeconds();

        while (juego->window->pollEvent(vnt)){
            if (vnt.type == sf::Event::Closed)
                juego->window->close();
            if (vnt.type == sf::Event::TextEntered) {
                if ( vnt.text.unicode < 128 ) {
                    //cout << "texto: " << vnt.text.unicode << endl;
                    //printf("%c", vnt.text.unicode);
                }
            }

        }//while eventos

        juego->window->clear( sf::Color::Black );

        for (int i = 0; i < juego->listaEntidadesBase.size(); i++) {
            Entidad* e = juego->listaEntidadesBase[i];
            e->Update(deltaTime);
        }//

        for (int i = 0; i < juego->listaEntidadesBase.size(); i++) {
            Entidad* e = juego->listaEntidadesBase[i];
            e->UpdateAnim(deltaTime);
            e->Draw((*(juego->window)));
        }//

        juego->update(deltaTime);
        
        //iterar entidades a eliminar
        verificarEliminar();

        juego->window->display();
    }//while

	return 0;
}//main
