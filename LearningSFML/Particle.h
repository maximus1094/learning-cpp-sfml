#pragma once

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>

#include "Color.h"
#include "Collider.h"
#include "Vector2f.h"

class Particle
{
private:
    sf::RectangleShape rectangle;
    sf::Vector2f m_size;

    bool isActive;
    float lifeTime;
    std::chrono::time_point<std::chrono::steady_clock> spawnTime;

protected:
    sf::Vector2f velocity;
    Vector2f Position;
    Color StartColor;
    Color EndColor;

public:
    Particle();

    void Spawn(Vector2f position, int size, float xVelocity, float yVelocity, Color color);
    virtual void Update(std::vector<Collider> collidersOther);
    virtual void Draw(sf::RenderWindow& window);

private:
    // True - horizonal, False - vertical.
    virtual void OnCollision(bool horizontalCollision);
};