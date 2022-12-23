#include <SFML/Graphics.hpp>

#include "Collider.h"

Collider::Collider(sf::RectangleShape square)
{
    xPosition = square.getPosition().x;
    yPosition = square.getPosition().y;

    size = square.getSize().x;
}