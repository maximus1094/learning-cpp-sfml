#include "ParticleSystem.h"
#include "Rng.h"

void ParticleSystem::Spawn(sf::Vector2i position, sf::Vector2f velocity)
{
    int size = std::abs(50 * randomnumber());

    int xPos = position.x - size / 2;
    int yPos = position.y - size / 2;

    entities[nextSpawnIndex].Spawn(xPos, yPos, size, velocity.x, velocity.y);

    nextSpawnIndex = nextSpawnIndex++ % ((sizeof(entities) / sizeof(Particle)) - 1);
}

void ParticleSystem::Update()
{
    for (Particle& e : entities)
    {
        e.Update(collidersOther);
    }
}

void ParticleSystem::Draw(sf::RenderWindow& window)
{
    for (int i = sizeof(entities) / sizeof(Particle) - 1; i >= 0; i--)
    {
        entities[i].Draw(window);
    }
}

void ParticleSystem::AddCollider(Collider& otherCollider)
{
    collidersOther.push_back(otherCollider);
}