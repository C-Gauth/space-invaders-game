#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Menu
{
protected:
	sf::Font font;
	sf::Text menu[3];

	int menuClicked;

public:
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
};

#endif