#pragma once

#include <SFML/Graphics.hpp>
#include "Collider.h"
#include "Vector2f.h"
#include "Particle.h"
#include "Color.h"

class BaseParticleSystem
{
protected:
    int nextSpawnIndex = 0;
    std::vector<Collider> collidersOther;
    Particle* particles;

public:
    void Update();

    void Draw(sf::RenderWindow& window);

    void AddCollider(Collider& otherCollider);

protected:
    void BaseSpawn(Vector2f position, Vector2f velocity, int size, Color color);

    virtual int GetNumberOfParticles() = 0;
};