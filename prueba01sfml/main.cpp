#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Juego.h"

#include "Bala.h"

using namespace std;



int main() {
    Juego* juego = Juego::getInstancia();
    juego->iniciar();

    sf::RenderWindow win(sf::VideoMode(800, 600), "1945");
    juego->window = &win;

    
    sf::Texture playerTexture;
    playerTexture.loadFromFile("texturas/ship.png");

    vector<Player*> listaEntidades;
    
    Player player(&playerTexture, sf::Vector2u(5,2), 0.05f, 400, 500, 500);
    

    listaEntidades.push_back(&player);
    
    
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

        for (int i = 0; i < listaEntidades.size(); i++) {
            Player* entidad = listaEntidades[i];
            entidad->Update(deltaTime);
        }//for
        for (int i = 0; i < listaEntidades.size(); i++) {
            Player* entidad = listaEntidades[i];
            entidad->Draw((*(juego->window)));
        }//for

        for (int i = 0; i < juego->listaEntidadesBase.size(); i++) {
            Entidad* e = juego->listaEntidadesBase[i];
            e->Update(deltaTime);
        }//

        for (int i = 0; i < juego->listaEntidadesBase.size(); i++) {
            Entidad* e = juego->listaEntidadesBase[i];
            e->Draw((*(juego->window)));
        }//
        
        
        juego->window->display();
    }//while

	return 0;
}//main
