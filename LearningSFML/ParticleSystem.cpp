#include <math.h>

#include "ParticleSystem.h"
#include "ColorPalette.h"
#include "Rng.h"

void ParticleSystem::Spawn(sf::Vector2i position, sf::Vector2f direction)
{
    // Spawn explosive particles (bigger), and regular small particles.
    // Explosive particles shouldn't despawn? There will be way more small ones that explosive.

    double pi = atan(1) * 4;
    

    Color color = ColorPalette().GetRandomColor();

    for (int i = 0; i < 3; i++)
    {
        // random angle offset
        double angle = randomnumber(-15, 15);
        double radians = (angle * pi) / 180;

        double x = direction.x * std::cos(radians) - direction.y * std::sin(radians);
        double y = direction.x * std::sin(radians) + direction.y * std::cos(radians);


        int size = std::abs(50 * randomnumber());

        int xPos = position.x - size / 2;
        int yPos = position.y - size / 2;

        entities[nextSpawnIndex].Spawn(xPos, yPos, size, x, y, color);

        nextSpawnIndex = nextSpawnIndex++ % ((sizeof(entities) / sizeof(Particle)) - 1);
    }
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