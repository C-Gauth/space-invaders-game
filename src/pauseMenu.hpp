#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "menu.hpp"

class PauseMenu : public Menu
{
	sf::Text pauseTitle;

public:
	PauseMenu()
	{
		if (!font.loadFromFile("8BitMage.ttf"))
		{
			cout << "font missing\n";
		}

		//Paused at the top of the screen
		pauseTitle.setFont(font);
		pauseTitle.setFillColor(sf::Color::White);
		pauseTitle.setString("-Paused-");
		pauseTitle.setCharacterSize(80);
		pauseTitle.setPosition(730, 200);

		//resume
		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setString("Resume");
		menu[0].setCharacterSize(50);
		menu[0].setPosition(500, 400);

		//resest
		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Reset");
		menu[1].setCharacterSize(50);
		menu[1].setPosition(500, 500);

		//quit
		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Quit");
		menu[2].setCharacterSize(50);
		menu[2].setPosition(500, 600);

		menuClicked = 0;
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(pauseTitle);
		for (int i = 0; i < 3; ++i)
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
				menuClicked = 2;
			}
			menu[menuClicked].setFillColor(sf::Color::Red);
		}
	}
	void moveDown()
	{

		if (menuClicked + 1 <= 3)
		{

			menu[menuClicked].setFillColor(sf::Color::White);

			menuClicked++;
			if (menuClicked == 3)
			{
				menuClicked = 0;
			}
			menu[menuClicked].setFillColor(sf::Color::Red);
		}
	}

	int MenuPos()
	{
		return menuClicked;
	}

	void resetMenuClicked()
	{
		menu[menuClicked].setFillColor(sf::Color::White);
		menu[0].setFillColor(sf::Color::Red);

		menuClicked = 0;
	}

	~PauseMenu()
	{
	}
};

#endif