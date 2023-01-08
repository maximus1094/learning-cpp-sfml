#pragma once

#include <SFML/Graphics.hpp>

#include "BaseParticleSystem.h"

class ExplosiveParticleSystem : public BaseParticleSystem
{
public:
    static const int NUMBER_OF_PARTICLES = 10;

    ExplosiveParticleSystem();

    // Copy
    ExplosiveParticleSystem(const ExplosiveParticleSystem& other);

    // Assignment
    ExplosiveParticleSystem& operator=(const ExplosiveParticleSystem& other);

    // Destructor
    ~ExplosiveParticleSystem();

    void Spawn(Vector2f position, Color color, int size);

    int GetNumberOfParticles() override;
};