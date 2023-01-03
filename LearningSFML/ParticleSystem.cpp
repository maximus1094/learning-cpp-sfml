#include "ParticleSystem.h"
#include "Rng.h"

void ParticleSystem::Spawn(sf::Vector2i position)
{
    int size = std::abs(50 * randomnumber());

    int xPos = position.x - size / 2;
    int yPos = position.y - size / 2;
    float xVelocity = 10 * randomnumber();
    float yVelocity = 10 * randomnumber();

    entities[nextSpawnIndex].Spawn(xPos, yPos, size, xVelocity, yVelocity);

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