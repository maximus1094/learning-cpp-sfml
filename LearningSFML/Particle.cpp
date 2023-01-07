#include <SFML/Graphics.hpp>
#include <chrono>

#include "Particle.h"
#include "ColorPalette.h"

//0, 230, 118

Particle::Particle()
{
    lifeTime = 2.0f;
    isActive = false;

    position = sf::Vector2f(0, 0);
    size = sf::Vector2f(50, 50);

    Color color = ColorPalette().GetRandomColor();

    startColor = sf::Color(color.R, color.G, color.B);
    endColor = sf::Color::White;

    rectangle.setSize(size);
    rectangle.setFillColor(startColor);
}

void Particle::Spawn(int xPosition, int yPosition, int size, float xVelocity, float yVelocity, Color color)
{
    position = sf::Vector2f(xPosition, yPosition);
    rectangle.setPosition(position);
    rectangle.setSize(sf::Vector2f(size, size));
    velocity = sf::Vector2f(xVelocity, yVelocity);

    startColor = sf::Color(color.R, color.G, color.B);
    rectangle.setFillColor(startColor);
    spawnTime = std::chrono::high_resolution_clock::now();

    isActive = true;
}

void Particle::Update(std::vector<Collider> collidersOther)
{
    if (isActive)
    {
        auto currentTime = std::chrono::high_resolution_clock::now();

        std::chrono::duration<float> duration = (currentTime - spawnTime);

        float newX = position.x + velocity.x;
        float newY = position.y + velocity.y;

        position = sf::Vector2f(newX, newY);
        rectangle.setPosition(position);

        bool collided = false;
        for (Collider& c : collidersOther)
        {
            // x: 340, 460, y: 240, 360

            if (velocity.x > 0 &&
                // crossing x moving right
                position.x + size.x > c.xPosition &&
                position.x < c.xPosition &&
                
                // within y bounds
                position.y + size.y > c.yPosition &&
                position.y < c.yPosition + c.size ||
                
                velocity.x < 0 &&
                // crossing x moving left
                position.x < c.xPosition + c.size &&
                position.x + size.x > c.xPosition + c.size &&
                
                // within y bounds
                position.y + size.y > c.yPosition&&
                position.y < c.yPosition + c.size)
            {
                velocity.x *= -1;
                collided = true;
            }

            if (velocity.y > 0 &&
                // crossing y moving bottom
                position.y + size.y > c.yPosition &&
                position.y < c.yPosition &&

                // within x bounds
                position.x + size.x > c.xPosition &&
                position.x < c.xPosition + c.size ||

                velocity.y < 0 &&
                // crossing y moving top
                position.y < c.yPosition + c.size &&
                position.y + size.y > c.yPosition + c.size &&

                // within x bounds
                position.x + size.x > c.xPosition &&
                position.x < c.xPosition + c.size)
            {
                velocity.y *= -1;
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

        sf::Uint8 r = (endColor.r - fillColor.r) * 0.05 + fillColor.r;
        sf::Uint8 g = (endColor.g - fillColor.g) * 0.05 + fillColor.g;
        sf::Uint8 b = (endColor.b - fillColor.b) * 0.05 + fillColor.b;

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