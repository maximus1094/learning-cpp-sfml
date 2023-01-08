#include "ExplosiveParticleSystem.h"
#include "ColorPalette.h"
#include "Rng.h"

ExplosiveParticleSystem::ExplosiveParticleSystem()
{
    particles = new Particle[NUMBER_OF_PARTICLES];
}

ExplosiveParticleSystem::ExplosiveParticleSystem(const ExplosiveParticleSystem& other)
{
    nextSpawnIndex = other.nextSpawnIndex;
    collidersOther = other.collidersOther;

    particles = new Particle[other.NUMBER_OF_PARTICLES];

    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        particles[i] = other.particles[i];
    }
}

ExplosiveParticleSystem& ExplosiveParticleSystem::operator=(const ExplosiveParticleSystem& other)
{
    if (this == &other)
    {
        return *this;
    }

    nextSpawnIndex = other.nextSpawnIndex;
    collidersOther = other.collidersOther;

    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        particles[i] = other.particles[i];
    }
}

ExplosiveParticleSystem::~ExplosiveParticleSystem()
{
    delete[] particles;
}

void ExplosiveParticleSystem::Spawn(Vector2f position, Color color, int size)
{
    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        Vector2f velocity(randomnumber() * 10, randomnumber() * 10);

        BaseSpawn(position, velocity, size, color);
    }
}

int ExplosiveParticleSystem::GetNumberOfParticles()
{
    return NUMBER_OF_PARTICLES;
}