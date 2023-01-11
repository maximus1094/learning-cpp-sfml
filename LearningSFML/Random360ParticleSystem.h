#pragma once

#include <SFML/Graphics.hpp>

#include "BaseParticleSystem.h"

class Random360ParticleSystem : public BaseParticleSystem
{
public:
    static const int NUMBER_OF_PARTICLES = 20;

    Random360ParticleSystem();

    // Copy
    Random360ParticleSystem(const Random360ParticleSystem& other);

    // Assignment
    Random360ParticleSystem& operator=(const Random360ParticleSystem& other);

    // Destructor
    ~Random360ParticleSystem();

    void Spawn(Vector2f position, Color color, int size);

    int GetNumberOfParticles() override;
};