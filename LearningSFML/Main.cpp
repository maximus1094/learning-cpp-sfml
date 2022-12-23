#include <random>
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>

double randomnumber() {
    // Making rng static ensures that it stays the same
    // Between different invocations of the function
    static std::default_random_engine rng;

    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    return dist(rng);
}

class Entity
{
private:
    sf::RectangleShape rectangle;
    sf::Vector2f position;
    sf::Vector2f size;

    sf::Vector2f velocity;

    sf::Color startColor;
    sf::Color endColor;

    bool isActive = false;
    float lifeTime = 2.0f; // seconds
    std::chrono::time_point<std::chrono::steady_clock> spawnTime;

public:
    Entity()
    {
        position = sf::Vector2f(0, 0);        
        size = sf::Vector2f(50, 50);

        float r = std::abs(255 * randomnumber());
        float g = std::abs(255 * randomnumber());
        float b = std::abs(255 * randomnumber());

        startColor = sf::Color(r, g, b);
        endColor = sf::Color::Black;
        
        rectangle.setSize(size);
        rectangle.setFillColor(startColor);
    }

    void SetPosition(int xVelocity, int yVelocity)
    {
        position = sf::Vector2f(xVelocity, yVelocity);
        rectangle.setPosition(position);
    }

    void SetSize(int size)
    {
        rectangle.setSize(sf::Vector2f(size, size));
    }

    void SetVelocity(float xVelocity, float yVelocity)
    {
        velocity = sf::Vector2f(xVelocity, yVelocity);
    }

    void Update()
    {
        if (isActive)
        {
            auto currentTime = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float> duration = (currentTime - spawnTime);

            float newX = position.x + velocity.x;
            float newY = position.y + velocity.y;

            position = sf::Vector2f(newX, newY);
            rectangle.setPosition(position);

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

    void SetActive()
    {
        rectangle.setFillColor(startColor);
        spawnTime = std::chrono::high_resolution_clock::now();
        
        isActive = true;
    }

    void Draw(sf::RenderWindow& window)
    {
        if (isActive)
        {
            window.draw(rectangle);
        }
    }
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Square");
    window.setFramerateLimit(60);

    sf::Event event;

    Entity entities[20];

    int currentEntity = 0;

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
                    int size = std::abs(50 * randomnumber());

                    int x = mousePosition.x - size / 2;
                    int y = mousePosition.y - size / 2;

                    entities[currentEntity].SetSize(size);
                    entities[currentEntity].SetPosition(x, y);
                    entities[currentEntity].SetVelocity(10 * randomnumber(), 10 * randomnumber());
                    entities[currentEntity].SetActive();

                    currentEntity = currentEntity++ % 9;

                    lastSpawnPosition = mousePosition;
                }
            }
        }

        for (Entity& e : entities)
        {
            e.Update();
        }

        window.clear();

        for (int i = sizeof(entities) / sizeof(Entity) - 1; i >= 0; i--)
        {
            entities[i].Draw(window);
        }

        window.display();
    }

    return 0;
}