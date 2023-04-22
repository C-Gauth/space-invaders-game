#include "classes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>

void debugPrint(sf::RenderWindow& window);

int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Space Invaders", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);
	bool paused = false;
	// Set up clock for enemy shooting
	sf::Clock enemyShootClock;
	float enemyShootTime = 3.f; // time between enemy shots in seconds

	//player ship
	Ship playerShip("ship2.png");

	// Create enemies
	Enemy enemy1("enemy2.png");
	Enemy enemy2("enemy2.png");
	srand(time(NULL));
	enemy1.setPosition(sf::Vector2f(rand() % window.getSize().x, 0));
	enemy2.setPosition(sf::Vector2f(rand() % window.getSize().x, 0));

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					switch (event.key.code)
					{
						//pause on escape
						case sf::Keyboard::Escape:
							paused = !paused;
							break;

						//Shoot on space (or mouse)
						case sf::Keyboard::Space:
							playerShip.createBullet();
							break;

						default:
							break;
					}
					break;

				case sf::Event::MouseButtonPressed:
					switch (event.mouseButton.button)
					{
						case sf::Mouse::Left:
							if (paused)
							{
								// code for resume and exit buttons
							}
							if (!paused)
							{
								// Shoot bullet
								playerShip.createBullet();
							}
							break;

						default:
							break;
					}
				default:
					break;
			}
		}

		if (!paused) //game logic
		{
			window.setMouseCursorVisible(false);
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			playerShip.setPosition(sf::Vector2f(mousePosition.x - playerShip.getSprite().getGlobalBounds().width / 2.f, mousePosition.y - playerShip.getSprite().getGlobalBounds().height / 2.f));
			playerShip.updateBullets();
			window.clear();
			window.draw(playerShip);
			for (auto bullet : playerShip.bullets)
			{
				window.draw(bullet);
			}
			// Update enemies and their bullets
			enemy1.move();
			//enemy2.move();
			if (enemyShootClock.getElapsedTime().asSeconds() > enemyShootTime)
			{
				enemy1.createBullet();
				enemy2.createBullet();
				enemyShootClock.restart();
			}
			enemy1.updateBullets();
			enemy2.updateBullets();
			window.draw(enemy1);
			window.draw(enemy2);
			for (auto bullet : enemy1.bullets)
			{
				window.draw(bullet);
			}
			for (auto bullet : enemy2.bullets)
			{
				window.draw(bullet);
			}
			window.display();
		}

		else
		{
			window.setMouseCursorVisible(true);
		}
	}

	return 0;
}

void debugPrint(sf::RenderWindow& window) //fucntion to debug
{
	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text debugText("This is a debug message", font, 20);
	debugText.setFillColor(sf::Color::Red);
	debugText.setPosition(100, 100);
	window.draw(debugText);
}