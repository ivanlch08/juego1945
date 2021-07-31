#include "VectorUtil.h"

sf::Vector2f VectorUtil::normalize(const sf::Vector2f& source) {
	if (source.x == 0 && source.y == 0) {
		return sf::Vector2f(0, 0);
	}
	float length = magnitud(source);
	if (length != 0) {
		return sf::Vector2f(source.x / length, source.y / length);
	}
}

float VectorUtil::magnitud(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	return length;
}
