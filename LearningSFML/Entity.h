#pragma once

#include "Vector2f.h"

class Entity
{
protected:
	Vector2f Position;
	bool Spawned = false;

public:
	virtual void Draw(sf::RenderWindow& window) = 0;

	Vector2f GetPosition();

	bool GetSpawned();
};