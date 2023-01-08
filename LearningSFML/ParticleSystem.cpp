#include <math.h>

#include "ParticleSystem.h"
#include "ColorPalette.h"
#include "Rng.h"


ParticleSystem::ParticleSystem()
{
    particles = new Particle[NUMBER_OF_PARTICLES];
}

ParticleSystem::ParticleSystem(const ParticleSystem& other)
{
    nextSpawnIndex = other.nextSpawnIndex;
    collidersOther = other.collidersOther;
    
    particles = new Particle[other.NUMBER_OF_PARTICLES];
    
    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        particles[i] = other.particles[i];
    }
}

ParticleSystem& ParticleSystem::operator=(const ParticleSystem& other)
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

ParticleSystem::~ParticleSystem()
{
    delete[] particles;
}

void ParticleSystem::Spawn(Vector2f position, Vector2f velocity)
{
    // Spawn explosive particles (bigger), and regular small particles.
    // Explosive particles shouldn't despawn? There will be way more small ones that explosive.

    double pi = atan(1) * 4;
    
    Color color = ColorPalette().GetRandomColor();

    for (int i = 0; i < 5; i++)
    {
        // random angle offset
        double angle = randomnumber(-15, 15);
        double radians = (angle * pi) / 180;

        double x = velocity.X * std::cos(radians) - velocity.Y * std::sin(radians);
        double y = velocity.X * std::sin(radians) + velocity.Y * std::cos(radians);

        int size = std::abs(50 * randomnumber());

        BaseSpawn(position.Minus(Vector2f(size / 2, size / 2)), Vector2f(x, y), size, color);
    }
}

int ParticleSystem::GetNumberOfParticles()
{
    return NUMBER_OF_PARTICLES;
}