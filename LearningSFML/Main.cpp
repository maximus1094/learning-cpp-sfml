#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>

#include "Rng.h"
#include "Vector2f.h"
#include "Collider.h"
#include "Entity.h"
#include "ParticleSystem.h"
#include "Random360ParticleSystem.h"
#include "ColorPalette.h"


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
	Color StartColor = ColorPalette().GetRandomColor();
	Color EndColor = ColorPalette().White;
	ParticleSystem ParticleSystem;

	std::chrono::steady_clock::time_point lastShot;

public:
	Player(int size, std::vector<Collider>& worldColliders)
	{
		StartColor = ColorPalette().GetRandomColor();
		EndColor = Color(207, 216, 220);

		Shape = sf::CircleShape();

		Shape.setRadius(size);
		Shape.setFillColor(sf::Color(EndColor.R, EndColor.G, EndColor.B));

		ParticleSystem.AddCollider(worldColliders[0]);
		ParticleSystem.AddCollider(worldColliders[1]);
	}

	void Spawn(Vector2f position, Color spawnColor)
	{
		StartColor = spawnColor;

		Shape.setFillColor(sf::Color(spawnColor.R, spawnColor.G, spawnColor.B));

		Position = position;

		Shape.setPosition(position.X - Shape.getRadius(), position.Y - Shape.getRadius());

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

		Vector2f mousePositionPlayerOrigin = mousePosition.Subtract(Position);
		Vector2f normalized = mousePositionPlayerOrigin.Normalize();

		int velocityScale = 10;
		int positionScale = 30;

		Vector2f mousePlayerDifference = mousePosition
			.Subtract(Position)
			.Normalize()
			.Multiply(positionScale);

		Vector2f particleOrigin = Position.Add(mousePlayerDifference);

		ParticleSystem.Spawn(particleOrigin, normalized.Multiply(velocityScale));

		lastShot = std::chrono::high_resolution_clock::now();
	}

	void Update()
	{
		if (Spawned)
		{
			ParticleSystem.Update();

			sf::Color fillColor = Shape.getFillColor();

			sf::Uint8 r = (EndColor.R - fillColor.r) * 0.025 + fillColor.r;
			sf::Uint8 g = (EndColor.G - fillColor.g) * 0.025 + fillColor.g;
			sf::Uint8 b = (EndColor.B - fillColor.b) * 0.025 + fillColor.b;

			sf::Color c(r, g, b, 255);

			Shape.setFillColor(c);
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

	Random360ParticleSystem explosiveParticleSystem;
	explosiveParticleSystem.AddCollider(boxColliderCrateTop);
	explosiveParticleSystem.AddCollider(boxColliderCrateBottom);

	bool canSpawnPlayer = true;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {

				window.close();
			}
			else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
			{
				canSpawnPlayer = true;
			}
		}

		Vector2f mousePosition = Vector2f(sf::Mouse::getPosition(window));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			player.Shoot(mousePosition);
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && canSpawnPlayer)
		{
			int size = randomnumber(10, 20);

			Color spawnColor = ColorPalette().GetRandomColor();

			explosiveParticleSystem.Spawn(mousePosition, spawnColor, size);

			player.Spawn(mousePosition, spawnColor);

			canSpawnPlayer = false;
		}

		explosiveParticleSystem.Update();
		player.Update();
		
		window.clear(sf::Color::White);

		crateTop.Draw(window);
		crateBottom.Draw(window);
		player.Draw(window);
		explosiveParticleSystem.Draw(window);

		window.display();
	}

	return 0;
}