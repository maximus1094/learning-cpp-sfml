#include <iostream>
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "ParticleSystem.h"


class Crate
{
    int XPos, YPos;
    int Size;
    sf::RectangleShape Shape;

public:
    Crate(int xPos, int yPos, int size)
    {
        XPos = xPos;
        YPos = yPos;
        Size = size;

        Shape.setSize(sf::Vector2f(size, size));
        Shape.setFillColor(sf::Color::White);
        Shape.setOutlineColor(sf::Color(200, 200, 200, 255));
        Shape.setOutlineThickness(1);

        Shape.setPosition(sf::Vector2f(xPos - size / 2, yPos - size / 2));
    }

    sf::RectangleShape GetShape()
    {
        return Shape;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Square");
    window.setFramerateLimit(60);

    sf::Event event;

    // compoments to draw
    ParticleSystem particleSystem;
    
    Crate crateTop((800 / 4) * 3, (600 / 4) * 3, 100);
    Crate crateBottom((800 / 4) * 3, (600 / 4), 100);

    Collider boxColliderCrateTop(crateTop.GetShape());
    Collider boxColliderCrateBottom(crateBottom.GetShape());

    particleSystem.AddCollider(boxColliderCrateTop);
    particleSystem.AddCollider(boxColliderCrateBottom);

    sf::Vector2i lastSpawnPosition;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }

            if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (std::abs(lastSpawnPosition.x - mousePosition.x) > 10)
                {
                    particleSystem.Spawn(mousePosition);

                    lastSpawnPosition = mousePosition;
                }
            }
        }

        particleSystem.Update();

        window.clear(sf::Color::White);

        particleSystem.Draw(window);

        window.draw(crateTop.GetShape());
        window.draw(crateBottom.GetShape());

        window.display();
    }

    return 0;
}