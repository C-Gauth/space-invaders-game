#include "classes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

void debugPrint(sf::RenderWindow& window); //helper to debug
vector<Enemy> AllEnemies;				   // global enemy list

int main()
{
	//window setup
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Space Invaders", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	// Set up clock for enemy shooting
	sf::Clock enemyShootClock;
	float enemyShootTime = 1.f; // time between enemy shots in seconds
	sf::Clock enemySpawnClock;
	float enemySpawnTime = 3.f; // time between enemy spawnings
	//game variables
	uint enemyLimit = 4;
	bool paused = false;

	//player ship
	Ship playerShip("ship2.png");

	// Create enemies
	Enemy enemy1("enemy2.png");
	Enemy enemy2("enemy2.png");
	AllEnemies.push_back(enemy1);
	AllEnemies.push_back(enemy2);
	srand(time(NULL));
	enemy1.setPosition(sf::Vector2f(100, 0));
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
			//player bullet loop
			for (auto bullet : playerShip.bullets)
			{
				window.draw(bullet);
			}
			// enemy spawn loop
			if (enemySpawnClock.getElapsedTime().asSeconds() > enemySpawnTime && AllEnemies.size() <= enemyLimit)
			{
				Enemy thisEnemy("enemy2.png");
				AllEnemies.push_back(thisEnemy);
				thisEnemy.setPosition(sf::Vector2f(rand() % window.getSize().x, 0));
			}
			// enemy shoot loop
			if (enemyShootClock.getElapsedTime().asSeconds() > enemyShootTime)
			{

				for (auto& enemy : AllEnemies) // for all enemies
				{
					enemy.createBullet(); // shoot
				}
				enemyShootClock.restart();
			}
			//enemy update loop
			auto it = AllEnemies.begin();
			while (it != AllEnemies.end())
			{
				auto& thisEnemy = *it;
				thisEnemy.move();
				if (thisEnemy.getPosition().y > window.getSize().y)
				{
					it = AllEnemies.erase(it);
					continue;
				}
				thisEnemy.updateBullets(window.getSize().y);
				window.draw(thisEnemy);
				for (auto enemyBullet : thisEnemy.enemyBullets)
				{
					window.draw(enemyBullet);
				}
				++it;
			}
			//update the window
			window.display();

		} //end of the game logic

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
