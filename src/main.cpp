#include <SFML/Graphics.hpp>
#include <cmath>

int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Space Invaders", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false);

	sf::Texture shipTexture;
	shipTexture.loadFromFile("ship.png");

	sf::Sprite shipSprite(shipTexture);
	sf::Vector2u windowSize = window.getSize();
	float xPos = windowSize.x / 2.f;
	float yPos = 0.9f * windowSize.y;
	shipSprite.setPosition(xPos, yPos);

	float shipSpeed = 5.f;

	bool paused = false;

	// create the pause screen rectangle
	sf::RectangleShape pauseScreen(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
	pauseScreen.setFillColor(sf::Color(0, 0, 0, 128)); // semi-transparent black background for the pause screen
	pauseScreen.setOrigin(pauseScreen.getSize() / 2.f);
	pauseScreen.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text resumeText("Resume", font, 250);
	resumeText.setFillColor(sf::Color::White);
	resumeText.setPosition(windowSize.x / 2.f - resumeText.getLocalBounds().width / 2.f, windowSize.y / 2.f - 50);

	sf::Text exitText("Exit Game", font, 250);
	exitText.setFillColor(sf::Color::White);
	exitText.setPosition(windowSize.x / 2.f - exitText.getLocalBounds().width / 2.f, windowSize.y / 2.f + 50);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				paused = !paused;
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && paused)
			{
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				if (resumeText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					paused = false;
				}
				else if (exitText.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
				{
					window.close();
				}
			}
		}

		if (!paused)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			window.setMouseCursorVisible(false); // dont show the cursor when not paused

			float dx = mousePosition.x - shipSprite.getPosition().x;
			float dy = mousePosition.y - shipSprite.getPosition().y;

			float distance = std::sqrt(dx * dx + dy * dy);

			if (distance != 0)
			{
				dx /= distance;
				dy /= distance;
			}

			shipSprite.move(shipSpeed * dx, shipSpeed * dy);

			window.clear();
			window.draw(shipSprite);
			window.display();
		}
		else // draw the pause screen and buttons if the game is paused
		{
			window.setMouseCursorVisible(true); // show the cursor when paused
			window.draw(pauseScreen);
			window.draw(resumeText);
			window.draw(exitText);
			window.display();
		}
	}

	return 0;
}