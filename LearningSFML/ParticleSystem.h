#pragma once

#include "Particle.h"

class ParticleSystem
{
private:
    Particle entities[20];
    int nextSpawnIndex = 0;

    std::vector<Collider> collidersOther;

public:
    void Spawn(sf::Vector2i position);

    void Update();

    void Draw(sf::RenderWindow& window);

    void AddCollider(Collider& otherCollider);
};