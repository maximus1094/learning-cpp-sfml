#include <iostream>
#include <SFML/Graphics.hpp>

#include "Rng.h"
#include "Collider.h"
#include "ParticleSystem.h"

class Entity
{
protected:
    int XPos, YPos;
    sf::Shape* Shape;
    
public:
    bool Spawned;

    ~Entity()
    {
        delete Shape;
    }

    void Draw(sf::RenderWindow& window)
    {
        if (Spawned)
        {
            window.draw(*Shape);
        }
    }

    int GetX()
    {
        return XPos;
    }

    int GetY()
    {
        return YPos;
    }

    sf::Shape* GetShape()
    {
        return Shape;
    }
};

class Player : public Entity
{
public:
    Player(int size)
    {
        sf::CircleShape* circle = new sf::CircleShape();

        circle->setRadius(size);
        circle->setFillColor(sf::Color(207, 216, 220));

        Shape = circle;
        Spawned = false;
    }

    void Spawn(int xPos, int yPos)
    {
        XPos = xPos;
        YPos = yPos;

        sf::CircleShape* circle = reinterpret_cast<sf::CircleShape*>(Shape);

        circle->setPosition(XPos, YPos);

        Spawned = true;
    }
};

class Crate : public Entity
{
public:
    Crate(int xPos, int yPos, int size)
    {
        XPos = xPos;
        YPos = yPos;
        
        sf::RectangleShape* rectangle = new sf::RectangleShape();

        rectangle->setSize(sf::Vector2f(size, size));
        rectangle->setFillColor(sf::Color::White);
        rectangle->setOutlineColor(sf::Color(200, 200, 200, 255));
        rectangle->setOutlineThickness(1);

        rectangle->setPosition(sf::Vector2f(xPos - size / 2, yPos - size / 2));

        Shape = rectangle;
        Spawned = true;
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Square");
    window.setFramerateLimit(60);

    sf::Event event;

    // compoments to draw
    Player player(15);
    ParticleSystem particleSystem;
    
    Crate crateTop((800 / 4) * 3, (600 / 4) * 3, 100);
    Crate crateBottom((800 / 4) * 3, (600 / 4), 100);

    Collider boxColliderCrateTop(*reinterpret_cast<sf::RectangleShape*>(crateTop.GetShape()));
    Collider boxColliderCrateBottom(*reinterpret_cast<sf::RectangleShape*>(crateBottom.GetShape()));

    particleSystem.AddCollider(boxColliderCrateTop);
    particleSystem.AddCollider(boxColliderCrateBottom);

    sf::Vector2i lastSpawnPosition;

    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {

                window.close();
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                float xVelocity = 10 * randomnumber();
                float yVelocity = 10 * randomnumber();

                float x = (mousePosition.x - player.GetX());
                float y = (mousePosition.y - player.GetY());

                sf::Vector2f particleVelocity(x / 10, y / 10);

                if (player.Spawned && std::abs(lastSpawnPosition.x - mousePosition.x) > 10)
                {
                    particleSystem.Spawn(sf::Vector2i(player.GetX(), player.GetY()), particleVelocity);
                }
                else if (std::abs(lastSpawnPosition.x - mousePosition.x) > 10)
                {
                    particleSystem.Spawn(mousePosition, particleVelocity);

                    lastSpawnPosition = mousePosition;
                }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                player.Spawn(mousePosition.x, mousePosition.y);
            }
        }

        particleSystem.Update();

        window.clear(sf::Color::White);

        crateTop.Draw(window);
        crateBottom.Draw(window);
        player.Draw(window);
        particleSystem.Draw(window);

        window.display();
    }

    return 0;
}