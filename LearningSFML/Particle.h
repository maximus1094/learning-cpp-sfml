#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "Collider.h"

class Particle
{
private:
    sf::RectangleShape rectangle;
    sf::Vector2f position;
    sf::Vector2f size;

    sf::Vector2f velocity;

    sf::Color startColor;
    sf::Color endColor;

    bool isActive;
    float lifeTime;
    std::chrono::time_point<std::chrono::steady_clock> spawnTime;

public:
    Particle();

    void Spawn(int xPosition, int yPosition, int size, float xVelocity, float yVelocity);
    void Update(std::vector<Collider> collidersOther);
    void Draw(sf::RenderWindow& window);
};