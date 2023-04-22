#include <iostream>
#include <vector>

using namespace std;

class Bullet : public sf::Drawable, public sf::Transformable
{
public:
	Bullet()
	{
		if (!texture.loadFromFile("bullet.png"))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		sprite.setTexture(texture);

		// Set hitbox size and position
		hitbox.setSize(sf::Vector2f(texture.getSize()));
		hitbox.setOrigin(hitbox.getSize() / 2.f);
		hitbox.setPosition(getPosition());
	}

	void move()
	{
		// Move bullet up
		sf::Vector2f position = getPosition();
		setPosition(sf::Vector2f(position.x, position.y - speed));
		hitbox.setPosition(position); // update hitbox position
		sprite.setPosition(position); // update sprite position
	}

	sf::FloatRect getHitbox() const
	{
		return hitbox.getGlobalBounds();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite, states);
	}

protected:
	float speed = 10.f;
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	sf::Texture texture;
};

////////////////////////////////////////////////////////////////////////////////////

class Ship : public sf::Drawable, public sf::Transformable
{

public:
	vector<Bullet> bullets; // vector to store bullets

	Ship()
	{
		if (!texture.loadFromFile("ship.png"))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		sprite.setTexture(texture);

		// Set hitbox size and position
		hitbox.setSize(sf::Vector2f(texture.getSize()));
		hitbox.setOrigin(hitbox.getSize() / 2.f);
		hitbox.setPosition(getPosition());
	}

	Ship(string pngName) // ship constructor given PNG image
	{
		if (!texture.loadFromFile(pngName))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		sprite.setTexture(texture);

		// Set hitbox size and position
		hitbox.setSize(sf::Vector2f(texture.getSize()));
		hitbox.setOrigin(hitbox.getSize() / 2.f);
		hitbox.setPosition(getPosition());
	}

	sf::FloatRect getHitbox() const // function to get the hitbox of the ship
	{
		return hitbox.getGlobalBounds();
	}

	void setPosition(sf::Vector2f position) // to move the ship
	{
		sf::Transformable::setPosition(position); // update position
		hitbox.setPosition(position);			  // update hitbox position
		sprite.setPosition(position);			  // update sprite position
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite, states);
	}

	sf::Sprite getSprite() //return sprite if needed
	{
		return sprite;
	};

	void createBullet() //make the bullet from the ship
	{
		Bullet bullet;
		sf::Vector2f bulletPos(getPosition().x - bullet.getHitbox().width / 2.f + getHitbox().width / 2.f, getPosition().y);
		bullet.setPosition(bulletPos);
		bullets.push_back(bullet);
	}
	void updateBullets()
	{
		for (size_t i = 0; i < bullets.size(); i++) //for all bullets a ship has
		{
			bullets[i].move();					//move the bullet I
			if (bullets[i].getPosition().y < 0) // remove bullet if it goes off screen
			{
				bullets.erase(bullets.begin() + i);
			}
		}
	}

protected:
	sf::RectangleShape hitbox; // hitbox of the ship
	sf::Sprite sprite;		   // sprite of the ship
	sf::Texture texture;	   //ship texture img
};

///////////////////////////////////////////////////////////////////////////////////

class Enemy : public sf::Drawable, public sf::Transformable
{
public:
	vector<Bullet> bullets; // vector to store bullets

	Enemy() //default const
	{
		if (!texture.loadFromFile("enemy.png"))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		sprite.setTexture(texture);

		// Set hitbox size and position
		hitbox.setSize(sf::Vector2f(texture.getSize()));
		hitbox.setOrigin(hitbox.getSize() / 2.f);
		hitbox.setPosition(getPosition());
	}

	Enemy(string filename) //custom design constructor
	{
		if (!texture.loadFromFile(filename))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		sprite.setTexture(texture);

		// Set hitbox size and position
		hitbox.setSize(sf::Vector2f(texture.getSize()));
		hitbox.setOrigin(hitbox.getSize() / 2.f);
		hitbox.setPosition(getPosition());
	}

	void move()
	{
		// Move enemy down
		sf::Vector2f position = getPosition();
		setPosition(sf::Vector2f(position.x, position.y + speed));
		hitbox.setPosition(position); // update hitbox position
		sprite.setPosition(position); // update sprite position
	}

	sf::FloatRect getHitbox() const
	{
		return hitbox.getGlobalBounds();
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(sprite, states);
	}

	void createBullet()
	{
		//Bullet newBullet(getPosition());
		//bullets.push_back(newBullet);
	}

	void updateBullets()
	{
		//for (auto& bullet : bullets)
		{
			//bullet.move(sf::Vector2f(0.f, speed)); // move bullet down
		}
	}

protected:
	float speed = 5.f;
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	sf::Texture texture;
};

//////////////////////////////////////////////////////////////////////////////////

/*
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
*/

/*
		else // draw the pause screen and buttons if the game is paused
		{
			window.setMouseCursorVisible(true); // show the cursor when paused

			window.draw(pauseScreen);
			window.draw(resumeText);
			window.draw(exitText);
			window.display();

		}
*/
