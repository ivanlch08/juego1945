#include <SFML/Graphics.hpp>

using namespace std;

#pragma once
class Anim{
private:
	vector<sf::Vector2u> listaCuadros;
	float time = 0;
	int pos = 0;
	float switchTime;
	bool finalizado = false;
public:
	bool loopeable = true;
	int id;
public:
	Anim(bool loopeable, int id, float _switchTime);
	~Anim();
	void addCuadro(int x, int y);
	void reiniciar();
	sf::Vector2u obtenerCuadro(float deltaTime);
};

