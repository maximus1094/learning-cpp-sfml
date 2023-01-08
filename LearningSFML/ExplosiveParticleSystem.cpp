#include "ExplosiveParticleSystem.h"
#include "ColorPalette.h"
#include "Rng.h"

ExplosiveParticleSystem::ExplosiveParticleSystem()
{
    particles = new Particle[NUMBER_OF_PARTICLES];
}

void ExplosiveParticleSystem::Spawn(Vector2f position)
{
    Color color = ColorPalette().GetRandomColor();

    for (int i = 0; i < 5; i++)
    {
        Vector2f velocity(randomnumber() * 10, randomnumber() * 10);

        int size = std::abs(50 * randomnumber());

        BaseSpawn(position, velocity, size, color);
    }
}