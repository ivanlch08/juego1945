#include <SFML/Graphics.hpp>

#pragma once
class VectorUtil{
public:
	static sf::Vector2f normalize(const sf::Vector2f& source);
	static float magnitud(const sf::Vector2f& source);
};

