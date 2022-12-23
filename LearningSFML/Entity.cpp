#include <SFML/Graphics.hpp>
#include <chrono>
#include "Entity.h"

Entity::Entity()
{
    lifeTime = 2.0f;
    isActive = false;

    position = sf::Vector2f(0, 0);
    size = sf::Vector2f(50, 50);

    startColor = sf::Color(255, 165, 0);
    endColor = sf::Color::Black;

    rectangle.setSize(size);
    rectangle.setFillColor(startColor);
}

void Entity::Spawn(int xPosition, int yPosition, int size, float xVelocity, float yVelocity)
{
    position = sf::Vector2f(xPosition, yPosition);
    rectangle.setPosition(position);
    rectangle.setSize(sf::Vector2f(size, size));
    velocity = sf::Vector2f(xVelocity, yVelocity);

    rectangle.setFillColor(startColor);
    spawnTime = std::chrono::high_resolution_clock::now();

    isActive = true;
}

void Entity::Update()
{
    if (isActive)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> duration = (currentTime - spawnTime);

        float newX = position.x + velocity.x;
        float newY = position.y + velocity.y;

        position = sf::Vector2f(newX, newY);
        rectangle.setPosition(position);

        auto dc = duration.count();

        sf::Uint8 multiplier = (duration.count() / lifeTime);

        sf::Color fillColor = rectangle.getFillColor();

        sf::Uint8 r = (endColor.r - fillColor.r) * 0.05 + fillColor.r;
        sf::Uint8 g = (endColor.g - fillColor.g) * 0.05 + fillColor.g;
        sf::Uint8 b = (endColor.b - fillColor.b) * 0.05 + fillColor.b;

        sf::Color c(r, g, b, 255);

        rectangle.setFillColor(c);
    }
}

void Entity::Draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(rectangle);
    }
}