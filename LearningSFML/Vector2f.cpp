#include "Vector2f.h"

// Constructors
Vector2f::Vector2f() : X(0), Y(0) {};
Vector2f::Vector2f(float x, float y) : X(x), Y(y) {};
Vector2f::Vector2f(sf::Vector2i sfVector) : X(sfVector.x), Y(sfVector.y) {};

// Methods
Vector2f Vector2f::Normalize()
{
	float length = std::sqrtf(std::powf(X, 2) + std::powf(Y, 2));
	float xNorm = X / length;
	float yNorm = Y / length;

	return Vector2f(xNorm, yNorm);
}

Vector2f Vector2f::Add(Vector2f other)
{
	return Vector2f(X + other.X, Y + other.Y);
}

Vector2f Vector2f::Subtract(Vector2f other)
{
	return Vector2f(X - other.X, Y - other.Y);
}

Vector2f Vector2f::Multiply(float value)
{
	return Vector2f(X * value, Y * value);
}

std::string Vector2f::ToString()
{
	return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}