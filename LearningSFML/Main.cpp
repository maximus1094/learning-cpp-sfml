#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Entity.h"

double randomnumber() {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static std::default_random_engine rng;

    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    return dist(rng);
}

class ParticleSystem
{
    Entity entities[20];
    int nextSpawnIndex = 0;

public:
    void Spawn(sf::Vector2i position)
    {
        int size = std::abs(50 * randomnumber());

        int xPos = position.x - size / 2;
        int yPos = position.y - size / 2;
        float xVelocity = 10 * randomnumber();
        float yVelocity = 10 * randomnumber();

        entities[nextSpawnIndex].Spawn(xPos, yPos, size, xVelocity, yVelocity);

        nextSpawnIndex = nextSpawnIndex++ % 19;
    }

    void Update()
    {
        for (Entity& e : entities)
        {
            e.Update();
        }
    }

    void Draw(sf::RenderWindow& window)
    {
        for (int i = sizeof(entities) / sizeof(Entity) - 1; i >= 0; i--)
        {
            entities[i].Draw(window);
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Square");
    window.setFramerateLimit(60);

    sf::Event event;

    ParticleSystem particleSystem;

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

        window.clear();

        particleSystem.Draw(window);

        window.display();
    }

    return 0;
}