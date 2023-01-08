#pragma once

#include "ExplosiveParticleSystem.h"

class ExplodingParticle : public Particle
{
private:
	ExplosiveParticleSystem explosive;

public:
	void Update(std::vector<Collider> collidersOther) override;
	void Draw(sf::RenderWindow& window) override;

private:
	void OnCollision(bool horizontalCollision) override;
};