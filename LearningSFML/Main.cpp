#include <iostream>
#include <SFML/Graphics.hpp>

#include "Collider.h"
#include "ParticleSystem.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Square");
    window.setFramerateLimit(60);

    sf::Event event;

    // compoments to draw
    ParticleSystem particleSystem;
    
    int boxSize = 120;
    sf::RectangleShape box;
    box.setSize(sf::Vector2f(boxSize, boxSize));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color(200, 200, 200, 255));
    box.setOutlineThickness(1);
    box.setPosition(sf::Vector2f(800 / 2 - boxSize / 2, 600 / 2 - boxSize / 2));
    
    Collider boxCollider(box);

    particleSystem.AddCollider(boxCollider);

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

        window.draw(box);

        window.display();
    }

    return 0;
}