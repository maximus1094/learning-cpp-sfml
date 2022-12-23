#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
public:
    int xPosition, yPosition;
    int size; // square collider for now

    Collider(sf::RectangleShape square);
};