#include "classes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Space Invaders", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	bool paused = false;

	Ship playerShip;

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
						case sf::Keyboard::Escape:
							paused = !paused;
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
								Bullet bullet;
								bullet.setPosition(playerShip.getPosition());
								playerShip.bullets.push_back(bullet);
							}
							break;

						default:
							break;
					}
				default:
					break;
			}
		}

		if (!paused)
		{
			window.setMouseCursorVisible(false);
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			playerShip.setPosition(sf::Vector2f(mousePosition.x - playerShip.getSprite().getGlobalBounds().width / 2.f, mousePosition.y - playerShip.getSprite().getGlobalBounds().height / 2.f));

			window.clear();
			//window.draw(playerShip);
			window.display();
			for (auto& bullet : playerShip.bullets)
			{
				window.draw(bullet);
			}
			playerShip.updateBullets();
		}

		else
		{
			window.setMouseCursorVisible(true);
		}
	}

	return 0;
}