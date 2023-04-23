#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

using namespace std;

class Bullet : public sf::Drawable, public sf::Transformable
{
public:
	int dmg;

	Bullet()
	{
		dmg = 20;
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

	sf::Sprite getSprite() //return sprite if needed
	{
		return sprite;
	};

protected:
	float speed = 10.f;
	sf::RectangleShape hitbox;
	sf::Sprite sprite;
	sf::Texture texture;
};

//////////////////////////////////////////////////////////////////////////////////

class enemyBullet : public Bullet
{
public:
	void move()
	{
		// Move bullet down
		sf::Vector2f position = getPosition();
		setPosition(sf::Vector2f(position.x, position.y - bulletSpeed));
		hitbox.setPosition(position); // update hitbox position
		sprite.setPosition(position); // update sprite position
	}

protected:
	float bulletSpeed = 10.f;
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

	bool isColliding(const sf::Sprite& otherSprite) const
	{
		// Get the bounding boxes of the two sprites
		sf::FloatRect playerBounds = sprite.getGlobalBounds();
		sf::FloatRect otherBounds = otherSprite.getGlobalBounds();

		// Check if the bounding boxes intersect
		if (playerBounds.intersects(otherBounds))
		{
			return true;
		}

		return false;
	}

private:
	sf::RectangleShape hitbox; // hitbox of the ship
	sf::Sprite sprite;		   // sprite of the ship
	sf::Texture texture;	   //ship texture img
};

///////////////////////////////////////////////////////////////////////////////////

class Enemy : public sf::Drawable, public sf::Transformable
{
public:
	vector<enemyBullet> enemyBullets; // vector to store bullets
	int health;

	Enemy() //default const/ different pic/ + window
	{
		if (!Etexture.loadFromFile("enemy2.png"))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		Esprite.setTexture(Etexture);
		health = 100;

		// Set hitbox size and position
		Ehitbox.setSize(sf::Vector2f(Etexture.getSize()));
		Ehitbox.setOrigin(Ehitbox.getSize() / 2.f);
		Ehitbox.setPosition(getPosition());
	}

	Enemy(string file) //const for custom bullet
	{
		if (!Etexture.loadFromFile(file))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		Esprite.setTexture(Etexture);
		health = 100;

		// Set hitbox size and position
		Ehitbox.setSize(sf::Vector2f(Etexture.getSize()));
		Ehitbox.setOrigin(Ehitbox.getSize() / 2.f);
		Ehitbox.setPosition(getPosition());
	}

	void move()
	{
		// move enemy down
		sf::Vector2f position = getPosition();
		setPosition(sf::Vector2f(position.x, position.y + speed));
		Ehitbox.setPosition(position); // update hitbox position
		Esprite.setPosition(position); // update sprite position
	}

	void updateBullets(float bound)
	{
		for (size_t i = 0; i < enemyBullets.size(); i++) //for all bullets a ship has
		{
			enemyBullets[i].move();						 //move the bullet I
			if (enemyBullets[i].getPosition().y > bound) // remove bullet if it goes off screen
			{
				enemyBullets.erase(enemyBullets.begin() + i);
			}
		}
	}

	void createBullet() //make the bullet from the ship
	{
		enemyBullet enemyBullet;
		sf::Vector2f bulletPos(getPosition().x - enemyBullet.getHitbox().width / 2.f + getHitbox().width / 2.f, getPosition().y);
		enemyBullet.setPosition(bulletPos);
		enemyBullets.push_back(enemyBullet);
	}

	sf::FloatRect getHitbox() const // function to get the hitbox of the ship
	{
		return Ehitbox.getGlobalBounds();
	}

	sf::Sprite getSprite() //return sprite if needed
	{
		return Esprite;
	};

	void setPosition(sf::Vector2f position) // to move the ship
	{
		sf::Transformable::setPosition(position); // update position
		Ehitbox.setPosition(position);			  // update hitbox position
		Esprite.setPosition(position);			  // update sprite position
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(Esprite, states);
	}

	virtual ~Enemy()
	{}

	bool isColliding(const sf::Sprite& otherSprite) const
	{
		// Get the bounding boxes of the two sprites
		sf::FloatRect playerBounds = Esprite.getGlobalBounds();
		sf::FloatRect otherBounds = otherSprite.getGlobalBounds();

		// Check if the bounding boxes intersect
		if (playerBounds.intersects(otherBounds))
		{
			return true;
		}

		return false;
	}

protected:
	float speed = 5.f;
	sf::RectangleShape Ehitbox;
	sf::Sprite Esprite;
	sf::Texture Etexture;
};

//////////////////////////////////////////////////////////////////////////////////

class deathParticles : public sf::Drawable, public sf::Transformable
{
public:
	deathParticles()
	{
		if (!texture.loadFromFile("particles.png"))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		sprite.setTexture(texture);
	}

	deathParticles(string file)
	{
		if (!texture.loadFromFile(file))
		{
			std::cerr << "Error loading texture\n";
			exit(1);
		}
		sprite.setTexture(texture);
	}

	void setPosition(sf::Vector2f position) // to move the ship
	{
		sf::Transformable::setPosition(position); // update position
		sprite.setPosition(position);			  // update sprite position
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform(); // combine the transform of the particle system with the transform of the parent
		states.texture = NULL;				// we don't need a texture because we're drawing vertices
		target.draw(sprite, states);		// draw the vertex array
	}

private:
	sf::Sprite sprite;
	sf::Texture texture;
};
