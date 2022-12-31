#include <random>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Collider.h"

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

    std::vector<Collider> collidersOther;

public:
    void Spawn(sf::Vector2i position)
    {
        int size = std::abs(50 * randomnumber());

        int xPos = position.x - size / 2;
        int yPos = position.y - size / 2;
        float xVelocity = 10 * randomnumber();
        float yVelocity = 10 * randomnumber();

        entities[nextSpawnIndex].Spawn(xPos, yPos, size, xVelocity, yVelocity);

        nextSpawnIndex = nextSpawnIndex++ % ((sizeof(entities) / sizeof(Entity)) - 1);
    }

    void Update()
    {
        for (Entity& e : entities)
        {
            e.Update(collidersOther);
        }
    }

    void Draw(sf::RenderWindow& window)
    {
        for (int i = sizeof(entities) / sizeof(Entity) - 1; i >= 0; i--)
        {
            entities[i].Draw(window);
        }
    }

    void AddCollider(Collider& otherCollider)
    {
        collidersOther.push_back(otherCollider);
    }
};

class Color
{
    // Default - hot pink
    int R = 255;
    int G = 105;
    int B = 180;
    int A = 255;

public:
    Color(int r, int g, int b, int a = 255)
    {
        R = r;
        G = g;
        B = b;
        A = a;
    }
};

class ColorPalette
{
private:
    std::vector<Color> colors;

public:
    Color Green = Color(0, 200, 83);
    Color Orange = Color(255, 109, 0);
    Color DeepPurple = Color(98, 0, 234);

    ColorPalette()
    {
        colors.push_back(Green);
        colors.push_back(Orange);
        colors.push_back(DeepPurple);
    }

    Color GetRandomColor()
    {
        int randomIndex = ((int)(randomnumber() * 10000)) % colors.size() - 1;

        return colors[randomIndex];
    }
};

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