#include "Random360ParticleSystem.h"
#include "ColorPalette.h"
#include "Rng.h"

Random360ParticleSystem::Random360ParticleSystem()
{
    particles = new Particle[NUMBER_OF_PARTICLES];
}

Random360ParticleSystem::Random360ParticleSystem(const Random360ParticleSystem& other)
{
    nextSpawnIndex = other.nextSpawnIndex;
    collidersOther = other.collidersOther;

    particles = new Particle[other.NUMBER_OF_PARTICLES];

    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        particles[i] = other.particles[i];
    }
}

Random360ParticleSystem& Random360ParticleSystem::operator=(const Random360ParticleSystem& other)
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

Random360ParticleSystem::~Random360ParticleSystem()
{
    delete[] particles;
}

void Random360ParticleSystem::Spawn(Vector2f position, Color color, int size)
{
    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        Vector2f velocity(randomnumber() * 10, randomnumber() * 10);

        BaseSpawn(position, velocity, size, color);
    }
}

int Random360ParticleSystem::GetNumberOfParticles()
{
    return NUMBER_OF_PARTICLES;
}