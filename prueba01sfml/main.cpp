#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Juego.h"

#include "Bala.h"

using namespace std;



int main() {
    srand((unsigned int)time(NULL));
    Juego* juego = Juego::getInstancia();
    juego->iniciar();

    sf::RenderWindow win(sf::VideoMode(800, 800), "1945");
    juego->window = &win;

    juego->crearPlayer();
    juego->crearEnemigo(400, 400, 1);
    juego->crearEnemigo(400, 400, 2);
    //juego->crearEnemigo(400, 400, 3);
    
    
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
        
        
        juego->window->display();
    }//while

	return 0;
}//main
