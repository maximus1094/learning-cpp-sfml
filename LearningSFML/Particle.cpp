#include <SFML/Graphics.hpp>
#include <chrono>

#include "Particle.h"
#include "ColorPalette.h"


Particle::Particle()
{
    lifeTime = 2.0f;
    isActive = false;

    Position = Vector2f(0, 0);
    size = sf::Vector2f(50, 50);

    StartColor = ColorPalette().GetRandomColor();
    EndColor = ColorPalette().White;

    rectangle.setSize(size);
    rectangle.setFillColor(sf::Color(StartColor.R, StartColor.G, StartColor.B));
}

void Particle::Spawn(Vector2f position, int size, float xVelocity, float yVelocity, Color color)
{
    Position = position;
    StartColor = color;

    rectangle.setPosition(sf::Vector2f(position.X, position.Y));
    rectangle.setSize(sf::Vector2f(size, size));
    velocity = sf::Vector2f(xVelocity, yVelocity);

    rectangle.setFillColor(sf::Color(StartColor.R, StartColor.G, StartColor.B));
    spawnTime = std::chrono::high_resolution_clock::now();

    isActive = true;
}

void Particle::Update(std::vector<Collider> collidersOther)
{
    if (isActive)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> duration = (currentTime - spawnTime);

        float newX = Position.X + velocity.x;
        float newY = Position.Y + velocity.y;

        Position = Vector2f(newX, newY);
        rectangle.setPosition(sf::Vector2f(Position.X, Position.Y));

        bool collided = false;
        for (Collider& c : collidersOther)
        {
            // x: 340, 460, y: 240, 360

            if (velocity.x > 0 &&
                // crossing x moving right
                Position.X + size.x > c.xPosition &&
                Position.X < c.xPosition &&
                
                // within y bounds
                Position.Y + size.y > c.yPosition &&
                Position.Y < c.yPosition + c.size ||
                
                velocity.x < 0 &&
                // crossing x moving left
                Position.X < c.xPosition + c.size &&
                Position.X + size.x > c.xPosition + c.size &&
                
                // within y bounds
                Position.Y + size.y > c.yPosition&&
                Position.Y < c.yPosition + c.size)
            {
                OnCollision(true);
                
                collided = true;
            }

            if (velocity.y > 0 &&
                // crossing y moving bottom
                Position.Y + size.y > c.yPosition &&
                Position.Y < c.yPosition &&

                // within x bounds
                Position.X + size.x > c.xPosition &&
                Position.X < c.xPosition + c.size ||

                velocity.y < 0 &&
                // crossing y moving top
                Position.Y < c.yPosition + c.size &&
                Position.Y + size.y > c.yPosition + c.size &&

                // within x bounds
                Position.X + size.x > c.xPosition &&
                Position.X < c.xPosition + c.size)
            {
                OnCollision(false);

                collided = true;
            }

            if (collided)
            {
                break;
            }
        }

        auto dc = duration.count();

        sf::Uint8 multiplier = (duration.count() / lifeTime);

        sf::Color fillColor = rectangle.getFillColor();

        sf::Uint8 r = (EndColor.R - fillColor.r) * 0.025 + fillColor.r;
        sf::Uint8 g = (EndColor.G - fillColor.g) * 0.025 + fillColor.g;
        sf::Uint8 b = (EndColor.B - fillColor.b) * 0.025 + fillColor.b;

        sf::Color c(r, g, b, 255);

        rectangle.setFillColor(c);
    }
}

void Particle::Draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(rectangle);
    }
}

void Particle::OnCollision(bool horizontalCollision)
{
    if (horizontalCollision)
    {
        velocity.x *= -1;
    }
    else
    {
        velocity.y *= -1;
    }
}