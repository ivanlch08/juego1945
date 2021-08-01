#include "VectorUtil.h"
#define PI      3.14159265359
#define RAD2DEG 57.2957795056
#define DEG2RAD 0.01745329252

sf::Vector2f VectorUtil::normalize(const sf::Vector2f& source) {
	if (source.x == 0 && source.y == 0) {
		return sf::Vector2f(0, 0);
	}
	float length = magnitud(source);
	if (length != 0) {
		return sf::Vector2f(source.x / length, source.y / length);
	}
}

sf::Vector2f VectorUtil::rotar(const sf::Vector2f& v, float angulo) {
	if (v.x == 0 && v.y == 0) {
		return sf::Vector2f(0, 0);
	}
	const float rad = DEG2RAD * angulo;
	const float sin0 = sin(rad);
	const float cos0 = cos(rad);

	float x = v.x * cos0 + v.y * -sin0;
	float y = v.x * sin0 + v.y * cos0;

	return sf::Vector2f(x, y);
}

float VectorUtil::magnitud(const sf::Vector2f& source)
{
	float length = sqrt((source.x * source.x) + (source.y * source.y));
	return length;
}
