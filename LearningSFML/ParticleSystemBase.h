#pragma once

#include <SFML/Graphics.hpp>

class ParticleSystemBase
{
public:
    virtual void Spawn(sf::Vector2i position, sf::Vector2f direction) = 0;

    void Update();

    void Draw(sf::RenderWindow& window);
};