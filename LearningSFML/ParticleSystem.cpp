#include <math.h>

#include "ParticleSystem.h"
#include "ColorPalette.h"
#include "Rng.h"


ParticleSystem::ParticleSystem()
{
    particles = new Particle[NUMBER_OF_PARTICLES];
    explodingParticles = new ExplodingParticle[NUMBER_OF_EXPLODING_PARTICLES];
}

ParticleSystem::ParticleSystem(const ParticleSystem& other)
{
    nextSpawnIndex = other.nextSpawnIndex;
    collidersOther = other.collidersOther;
    
    particles = new Particle[other.NUMBER_OF_PARTICLES];
    explodingParticles = new ExplodingParticle[NUMBER_OF_EXPLODING_PARTICLES];
    
    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        particles[i] = other.particles[i];
    }

    for (int i = 0; i < NUMBER_OF_EXPLODING_PARTICLES; i++)
    {
        explodingParticles[i] = other.explodingParticles[i];
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

    for (int i = 0; i < NUMBER_OF_EXPLODING_PARTICLES; i++)
    {
        explodingParticles[i] = other.explodingParticles[i];
    }
}

ParticleSystem::~ParticleSystem()
{
    delete[] particles;
    delete[] explodingParticles;
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

        int size = randomnumber(10, 20);

        BaseSpawn(position.Minus(Vector2f(size / 2, size / 2)), Vector2f(x, y), size, color);
    }

    for (int i = 0; i < 3; i++)
    {
        // random angle offset
        double angle = randomnumber(-15, 15);
        double radians = (angle * pi) / 180;

        double x = velocity.X * std::cos(radians) - velocity.Y * std::sin(radians);
        double y = velocity.X * std::sin(radians) + velocity.Y * std::cos(radians);

        int size = randomnumber(25, 50);

        // Spawning explosive particles.
        explodingParticles[nextExplosiveSpawnIndex].Spawn(
            position.Minus(Vector2f(size / 2, size / 2)),
            size,
            x,
            y,
            color);

        nextExplosiveSpawnIndex = nextExplosiveSpawnIndex++ % (NUMBER_OF_EXPLODING_PARTICLES - 1);
    }
}

int ParticleSystem::GetNumberOfParticles()
{
    return NUMBER_OF_PARTICLES;
}

void ParticleSystem::Update()
{
    BaseParticleSystem::Update();

    for (int i = 0; i < NUMBER_OF_EXPLODING_PARTICLES; i++)
    {
        explodingParticles[i].Update(collidersOther);
    }
}

void ParticleSystem::Draw(sf::RenderWindow& window)
{
    BaseParticleSystem::Draw(window);

    for (int i = 0; i < NUMBER_OF_EXPLODING_PARTICLES; i++)
    {
        explodingParticles[i].Draw(window);
    }
}