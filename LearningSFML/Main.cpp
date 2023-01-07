#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Rng.h"
#include "Vector2f.h"
#include "Collider.h"
#include "ParticleSystem.h"

class Entity
{
protected:
	Vector2f Position;
	bool Spawned;

public:
	virtual void Draw(sf::RenderWindow& window) = 0;

	Vector2f GetPosition()
	{
		return Position;
	}

	bool GetSpawned()
	{
		return Spawned;
	}
};

class Player : public Entity
{
private:
	sf::CircleShape Shape;

public:
	Player(int size)
	{
		Shape = sf::CircleShape();

		Shape.setRadius(size);
		Shape.setFillColor(sf::Color(207, 216, 220));

		Spawned = false;
	}

	void Spawn(Vector2f position)
	{
		Position = position;

		Shape.setPosition(Position.X, Position.Y);

		Spawned = true;
	}

	void Draw(sf::RenderWindow& window) override
	{
		if (Spawned)
		{
			window.draw(Shape);
		}
	}

	sf::CircleShape GetShape()
	{
		return Shape;
	}
};

class Crate : public Entity
{
private:
	sf::RectangleShape Shape;

public:
	Crate(Vector2f position, int size)
	{
		Position = position;

		Shape = sf::RectangleShape();

		Shape.setSize(sf::Vector2f(size, size));
		Shape.setFillColor(sf::Color::White);
		Shape.setOutlineColor(sf::Color(200, 200, 200, 255));
		Shape.setOutlineThickness(1);

		Shape.setPosition(sf::Vector2f(position.X - size / 2, position.Y - size / 2));

		Spawned = true;
	}

	void Draw(sf::RenderWindow& window) override
	{
		if (Spawned)
		{
			window.draw(Shape);
		}
	}

	sf::RectangleShape GetShape()
	{
		return Shape;
	}
};

int main()
{
	using namespace std::literals::chrono_literals;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Square");
	window.setFramerateLimit(60);

	sf::Event event;

	// compoments to draw
	Player player(15);
	ParticleSystem particleSystem;

	Crate crateTop(Vector2f((800 / 4) * 3, (600 / 4) * 3), 100);
	Crate crateBottom(Vector2f((800 / 4) * 3, (600 / 4)), 100);

	Collider boxColliderCrateTop(crateTop.GetShape());
	Collider boxColliderCrateBottom(crateBottom.GetShape());

	particleSystem.AddCollider(boxColliderCrateTop);
	particleSystem.AddCollider(boxColliderCrateBottom);

	auto start = std::chrono::high_resolution_clock::now();

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}

		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> durationS = end - start;

		Vector2f mousePosition = Vector2f(sf::Mouse::getPosition(window));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && durationS.count() > 0.1f) //  && event.type == sf::Event::MouseMoved
		{
			Vector2f mousePositionPlayerOrigin = mousePosition.Minus(player.GetPosition());
			Vector2f normalized = mousePositionPlayerOrigin.Normalize();
	
			sf::Vector2f particleVelocity(normalized.X * 10, normalized.Y * 10);

			std::cout << normalized.ToString() << std::endl;

			if (player.GetSpawned())
			{
				particleSystem.Spawn(sf::Vector2i(player.GetPosition().X, player.GetPosition().Y), particleVelocity);
			}

			start = std::chrono::high_resolution_clock::now();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			player.Spawn(mousePosition);
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