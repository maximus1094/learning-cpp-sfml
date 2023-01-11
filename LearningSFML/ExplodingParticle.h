#pragma once

#include "Random360ParticleSystem.h"

class ExplodingParticle : public Particle
{
private:
	Random360ParticleSystem explosive;

public:
	void Update(std::vector<Collider> collidersOther) override;
	void Draw(sf::RenderWindow& window) override;

private:
	void OnCollision(bool horizontalCollision) override;
};