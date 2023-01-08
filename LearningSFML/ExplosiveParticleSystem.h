#pragma once

#include <SFML/Graphics.hpp>

#include "BaseParticleSystem.h"

class ExplosiveParticleSystem : public BaseParticleSystem
{
public:
    static const int NUMBER_OF_PARTICLES = 10;

    ExplosiveParticleSystem();

    void Spawn(Vector2f position);
};