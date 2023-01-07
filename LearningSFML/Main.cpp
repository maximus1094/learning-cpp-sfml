#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Rng.h"
#include "Collider.h"
#include "ParticleSystem.h"

struct Vector2f
{
	float X, Y;

	Vector2f() : X(0), Y(0) {};

	Vector2f(float x, float y)
	{
		X = x;
		Y = y;
	}

	Vector2f(sf::Vector2i sfVector)
	{
		X = sfVector.x;
		Y = sfVector.y;
	}

	Vector2f Normalize()
	{
		float length = std::sqrtf(std::powf(X, 2) + std::powf(Y, 2));
		float xNorm = X / length;
		float yNorm = Y / length;

		return Vector2f(xNorm, yNorm);
	}

	Vector2f Minus(Vector2f other)
	{
		return Vector2f(X - other.X, Y - other.Y);
	}

	std::string ToString()
	{
		return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
	}
};

class Entity
{
protected:
	Vector2f Position;

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

	Vector2f GetPosition()
	{
		return Position;
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

	void Spawn(Vector2f position)
	{
		Position = position;

		sf::CircleShape* circle = reinterpret_cast<sf::CircleShape*>(Shape);

		circle->setPosition(Position.X, Position.Y);

		Spawned = true;
	}
};

class Crate : public Entity
{
public:
	Crate(Vector2f position, int size)
	{
		Position = position;

		sf::RectangleShape* rectangle = new sf::RectangleShape();

		rectangle->setSize(sf::Vector2f(size, size));
		rectangle->setFillColor(sf::Color::White);
		rectangle->setOutlineColor(sf::Color(200, 200, 200, 255));
		rectangle->setOutlineThickness(1);

		rectangle->setPosition(sf::Vector2f(position.X - size / 2, position.Y - size / 2));

		Shape = rectangle;
		Spawned = true;
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

	Collider boxColliderCrateTop(*reinterpret_cast<sf::RectangleShape*>(crateTop.GetShape()));
	Collider boxColliderCrateBottom(*reinterpret_cast<sf::RectangleShape*>(crateBottom.GetShape()));

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

			if (player.Spawned)
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