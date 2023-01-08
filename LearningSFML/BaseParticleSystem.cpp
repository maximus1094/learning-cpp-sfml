#include "BaseParticleSystem.h"
#include "Particle.h"

#include <iostream>

void BaseParticleSystem::Update()
{
    for (int i = 0; i < GetNumberOfParticles(); i++)
    {
        particles[i].Update(collidersOther);
    }
}

void BaseParticleSystem::Draw(sf::RenderWindow& window)
{
    for (int i = GetNumberOfParticles() - 1; i >= 0; i--)
    {
        particles[i].Draw(window);
    }
}

void BaseParticleSystem::AddCollider(Collider& otherCollider)
{
    collidersOther.push_back(otherCollider);
}

void BaseParticleSystem::BaseSpawn(Vector2f position, Vector2f velocity, int size, Color color)
{
    particles[nextSpawnIndex].Spawn(position.X, position.Y, size, velocity.X, velocity.Y, color);

    nextSpawnIndex = nextSpawnIndex++ % (GetNumberOfParticles() - 1);
}