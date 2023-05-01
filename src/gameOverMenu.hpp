#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "menu.hpp"

class GameOver : public Menu
{

	sf::Text gameOverTitle;
	sf::Text ScoreRes;
	int score = 0;

public:
	GameOver()
	{

		if (!font.loadFromFile("8BitMage.ttf"))
		{
			cout << "font missing\n";
		}

		//Paused at the top of the screen
		gameOverTitle.setFont(font);
		gameOverTitle.setFillColor(sf::Color::Red);
		gameOverTitle.setString("*Game Over*");
		gameOverTitle.setCharacterSize(90);
		gameOverTitle.setPosition(650, 100);

		//resume
		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Blue);
		menu[0].setString("Reset");
		menu[0].setCharacterSize(50);
		menu[0].setPosition(830, 500);

		//quit
		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Quit");
		menu[1].setCharacterSize(50);
		menu[1].setPosition(850, 550);

		//quit
		/*menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Quit");
		menu[2].setCharacterSize(50);
		menu[2].setPosition(855, 500);*/

		menuClicked = 0;
	}

	void setupScore(int score)
	{

		ScoreRes.setFont(font);
		ScoreRes.setFillColor(sf::Color::White);
		ScoreRes.setString("Score: " + std::to_string(score));
		ScoreRes.setCharacterSize(60);
		ScoreRes.setPosition(750, 250);
	}

	void draw(sf::RenderWindow& window)
	{
		window.draw(gameOverTitle);

		window.draw(ScoreRes);
		for (int i = 0; i < 2; ++i)
		{
			window.draw(menu[i]);
		}
	}
	void moveUp()
	{

		if (menuClicked - 1 >= 0)
		{
			menu[menuClicked].setFillColor(sf::Color::White);

			menuClicked--;
			if (menuClicked == -1)
			{
				menuClicked = 1;
			}
			menu[menuClicked].setFillColor(sf::Color::Blue);
		}
	}
	void moveDown()
	{

		if (menuClicked + 1 <= 2)
		{

			menu[menuClicked].setFillColor(sf::Color::White);

			menuClicked++;
			if (menuClicked == 2)
			{
				menuClicked = 0;
			}
			menu[menuClicked].setFillColor(sf::Color::Blue);
		}
	}

	int MenuPos()
	{
		return menuClicked;
	}

	void resetMenuClicked()
	{
		menuClicked = 0;
	}

	~GameOver()
	{
	}
};

#endif