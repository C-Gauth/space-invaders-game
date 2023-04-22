#include "classes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

void debugPrint(sf::RenderWindow& window);

int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Space Invaders", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	bool paused = false;

	Ship playerShip("ship2.png");

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