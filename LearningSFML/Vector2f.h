#pragma once

#include <SFML/Graphics.hpp>

struct Vector2f
{
	float X, Y;

	Vector2f();
	Vector2f(float x, float y);
	Vector2f(sf::Vector2i sfVector);

	Vector2f Normalize();

	Vector2f Minus(Vector2f other);

	Vector2f Multiply(float value);

	std::string ToString();
};