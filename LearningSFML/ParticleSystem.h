#pragma once

#include "BaseParticleSystem.h"

class ParticleSystem : public BaseParticleSystem
{
public:
    static const int NUMBER_OF_PARTICLES = 50;
    
    ParticleSystem();
    
    // Copy
    ParticleSystem(const ParticleSystem& other);

    // Assignment
    ParticleSystem& operator=(const ParticleSystem& other);

    // Destructor
    ~ParticleSystem();

    void Spawn(Vector2f position, Vector2f velocity);

    virtual int GetNumberOfParticles();
};