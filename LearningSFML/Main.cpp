#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Rng.h"
#include "Vector2f.h"
#include "Collider.h"
#include "Entity.h"
#include "ParticleSystem.h"


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

class Player : public Entity
{
private:
	sf::CircleShape Shape;
	ParticleSystem ParticleSystem;

	std::chrono::steady_clock::time_point lastShot;

public:
	Player(int size, std::vector<Collider>& worldColliders)
	{
		Shape = sf::CircleShape();

		Shape.setRadius(size);
		Shape.setFillColor(sf::Color(207, 216, 220));

		ParticleSystem.AddCollider(worldColliders[0]);
		ParticleSystem.AddCollider(worldColliders[1]);
	}

	void Spawn(Vector2f position)
	{
		Position = Vector2f(position.X - Shape.getRadius(), position.Y - Shape.getRadius());

		Shape.setPosition(Position.X, Position.Y);

		Spawned = true;
	}
	
	void Shoot(Vector2f mousePosition)
	{
		if (!Spawned)
		{
			return;
		}

		auto now = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> durationS = now - lastShot;

		if (durationS.count() < 0.08f)
		{
			return;
		}

		Vector2f mousePositionPlayerOrigin = mousePosition.Minus(Position);
		Vector2f normalized = mousePositionPlayerOrigin.Normalize();

		int scale = 10;

		ParticleSystem.Spawn(Position, normalized.Multiply(scale));

		lastShot = std::chrono::high_resolution_clock::now();
	}

	void Update()
	{
		if (Spawned)
		{
			ParticleSystem.Update();
		}
	}

	void Draw(sf::RenderWindow& window) override
	{
		if (Spawned)
		{
			window.draw(Shape);

			ParticleSystem.Draw(window);
		}
	}

	sf::CircleShape GetShape()
	{
		return Shape;
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Square");
	window.setFramerateLimit(60);

	sf::Event event;

	Crate crateTop(Vector2f((800 / 4) * 3, (600 / 4) * 3), 100);
	Crate crateBottom(Vector2f((800 / 4) * 3, (600 / 4)), 100);

	std::vector<Collider> worldColliders;

	Collider boxColliderCrateTop(crateTop.GetShape());
	Collider boxColliderCrateBottom(crateBottom.GetShape());

	worldColliders.push_back(boxColliderCrateTop);
	worldColliders.push_back(boxColliderCrateBottom);

	Player player(15, worldColliders);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
		}

		Vector2f mousePosition = Vector2f(sf::Mouse::getPosition(window));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player.Shoot(mousePosition);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		{
			player.Spawn(mousePosition);
		}

		player.Update();
		
		window.clear(sf::Color::White);

		crateTop.Draw(window);
		crateBottom.Draw(window);
		player.Draw(window);

		window.display();
	}

	return 0;
}