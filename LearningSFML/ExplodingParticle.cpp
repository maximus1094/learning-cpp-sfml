#include "ExplodingParticle.h"

void ExplodingParticle::OnCollision(bool horizontalCollision)
{
	explosive.Spawn(Position, StartColor);

    if (horizontalCollision)
    {
        velocity.x *= -1;
    }
    else
    {
        velocity.y *= -1;
    }
}

void ExplodingParticle::Update(std::vector<Collider> collidersOther)
{
    Particle::Update(collidersOther);

    explosive.Update();
}

void ExplodingParticle::Draw(sf::RenderWindow& window)
{
    Particle::Draw(window);

    explosive.Draw(window);
}