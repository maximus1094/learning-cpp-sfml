#pragma once

#include "BaseParticleSystem.h"
#include "ExplodingParticle.h"

class ParticleSystem : public BaseParticleSystem
{
private:
    ExplodingParticle* explodingParticles;
    int nextExplosiveSpawnIndex = 0;

public:
    static const int NUMBER_OF_PARTICLES = 50;
    static const int NUMBER_OF_EXPLODING_PARTICLES = 30;
    
    ParticleSystem();
    
    // Copy
    ParticleSystem(const ParticleSystem& other);

    // Assignment
    ParticleSystem& operator=(const ParticleSystem& other);

    // Destructor
    ~ParticleSystem();

    void Spawn(Vector2f position, Vector2f velocity);

    void Update() override;

    void Draw(sf::RenderWindow& window) override;

    virtual int GetNumberOfParticles();
};