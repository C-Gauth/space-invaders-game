#include "classes.h"
#include "gameOverMenu.hpp"
#include "pauseMenu.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

void debugPrint(sf::RenderWindow& window); //helper to debug
vector<Enemy> AllEnemies;				   // global enemy list
sf::Texture enemyTexture;

int main()
{
	//window setup
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Space Invaders", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(60);

	// Load background texture and create Background object
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("background_04.png"))
	{
		// Handle error if texture file not found
	}
	Background background(window);

	//load enemy texture
	if (!enemyTexture.loadFromFile("enemy2.png"))
	{
		std::cout << "--ERROR loading enemy texture--";
	}

	//set up score
	sf::Font font;
	font.loadFromFile("8BitMage.ttf");
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(window.getSize().x - 100.f, 20.f);
	int score = 0;

	// Set up clock for enemy shooting
	sf::Clock enemyShootClock;
	float enemyShootTime = 1.f; // time between enemy shots in seconds
	sf::Clock enemySpawnClock;
	float enemySpawnTime = 4.f; // time between enemy spawnings
	//game variables
	uint enemyLimit = 4;
	bool paused = false;
	sf::Vector2i pausePosition;

	//player ship
	Ship playerShip("ship2.png");

	// Create enemies
	Enemy enemy1("enemy2.png");
	AllEnemies.push_back(enemy1);
	srand(time(NULL));

	// Set position for enemy 1
	enemy1.setPosition(sf::Vector2f(100, 0));

	//Pause Menu
	PauseMenu pMenu;
	int menupos;

	//Game over Menu
	GameOver gMenu;
	bool gOver = false;

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
							if (paused == false && gOver != true)
							{
								paused = !paused;	//flip
								window.clear();		// clear window
								pMenu.draw(window); // render pause menu
								window.display();	// update window

								pausePosition = sf::Mouse::getPosition(window); //get pause location
							}
							/*else //escape no longer unpauses game when paused
							{
								paused = !paused; //flip
								std::cout << "this one unpauses" << endl;
								//reset pausemenu clicked here
								pMenu.resetMenuClicked();
								sf::Mouse::setPosition(pausePosition, window); // return to pause location
							};*/
							break;

						//Shoot on space (or mouse)
						case sf::Keyboard::Space:
							playerShip.createBullet();
							break;

						case sf::Keyboard::W:
							if (paused == true)
							{
								pMenu.moveUp();
								window.clear();		// clear window
								pMenu.draw(window); // render pause menu
								window.display();	// update window
							}
							if (gOver == true && paused != true)
							{
								gMenu.moveUp();
								window.clear();		// clear window
								gMenu.draw(window); // render pause menu
								window.display();	// update window
							}
							break;

						case sf::Keyboard::S:
							if (paused == true)
							{
								pMenu.moveDown();
								window.clear();		// clear window
								pMenu.draw(window); // render pause menu
								window.display();	// update window
							}
							if (gOver == true && paused != true)
							{
								gMenu.moveDown();
								window.clear();		// clear window
								gMenu.draw(window); // render pause menu
								window.display();	// update window
							}
							break;
						case sf::Keyboard::Return:
							if (paused == true && gOver != true)
							{
								menupos = pMenu.MenuPos();
								if (menupos == 0) //resume from pause
								{
									paused = !paused;
									pMenu.resetMenuClicked();
									sf::Mouse::setPosition(pausePosition, window);
								}
								if (menupos == 1) //reset from pause
								{
									//reset here
									paused = !paused;
									playerShip.health = 100;
									score = 0;
									pMenu.resetMenuClicked();
									window.clear();
									window.draw(scoreText);
									scoreText.setString("Score: " + std::to_string(score));
									//clear eneimes here
									AllEnemies.clear();
									std::cout << "Enemies cleared";
									window.display();
								}
								if (menupos == 2) //quit from pause
								{
									window.close();
								}
							}

							if (gOver == true)
							{
								menupos = gMenu.MenuPos();
								if (menupos == 0) //reset
								{
									gOver = !gOver;
									playerShip.health = 100;
									score = 0;
									gMenu.resetMenuClicked(); //figure out reset here can just reset score and health
									window.clear();
									window.draw(scoreText);
									scoreText.setString("Score: " + std::to_string(score));
									//clear eneimes here
									AllEnemies.clear();
									window.display();
									//sf::Mouse::setPosition(pausePosition, window);
								}
								if (menupos == 1) //quit
								{
									//quits game
									window.close();
								}
							}

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
		if (!paused && gOver == false) //game logic
		{
			window.setMouseCursorVisible(false);
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			playerShip.setPosition(sf::Vector2f(mousePosition.x - playerShip.getSprite().getGlobalBounds().width / 2.f, mousePosition.y - playerShip.getSprite().getGlobalBounds().height / 2.f));
			playerShip.updateBullets();
			window.clear();
			window.draw(background);
			scoreText.setPosition(window.getSize().x - scoreText.getGlobalBounds().width - 20, 20);
			window.draw(scoreText);
			window.draw(playerShip);
			//player bullet loop
			for (auto& bullet : playerShip.bullets) // for all player bullets
			{
				for (auto it = AllEnemies.begin(); it != AllEnemies.end();) //for all enemies
				{
					if (it->isColliding(bullet.getSprite())) // if enemy is hit by bullet
					{

						it->health = it->health - bullet.dmg; //hurt them
						if (it->health <= 0)				  // if dead
						{
							deathParticles dParticles;
							dParticles.setPosition(it->getPosition());
							window.draw(dParticles);
							score += 3;
							scoreText.setString("Score: " + std::to_string(score));
							it = AllEnemies.erase(it); // remove the dead enemy
						}
						else
						{
							++it;
						}
						// ---------get rid of bullet?????-------
					}
					else
					{
						++it;
					}
				}
				window.draw(bullet);
			}
			// enemy spawn loop
			if (enemySpawnClock.getElapsedTime().asSeconds() > enemySpawnTime && AllEnemies.size() <= enemyLimit)
			{
				Enemy thisEnemy(enemyTexture);
				int halfEnemyWidth = thisEnemy.getSprite().getGlobalBounds().width / 2;
				int randomX = rand() % (window.getSize().x - 2 * halfEnemyWidth) + halfEnemyWidth;
				thisEnemy.setPosition(sf::Vector2f(randomX, 0));
				AllEnemies.push_back(thisEnemy);
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
			while (it != AllEnemies.end()) //iterate through all enemies
			{
				auto& thisEnemy = *it;
				thisEnemy.move();									// move the enemt
				if (thisEnemy.getPosition().y > window.getSize().y) // if out of bounds delete
				{
					it = AllEnemies.erase(it);
					continue;
				}
				thisEnemy.updateBullets(window.getSize().y);	// update bullets
				window.draw(thisEnemy);							// draw enemy
				for (auto enemyBullet : thisEnemy.enemyBullets) //for each bullet of this enemy
				{
					window.draw(enemyBullet); // draw it

					if (playerShip.isColliding(enemyBullet.getSprite())) // check for player colision
					{
						playerShip.health = playerShip.health - enemyBullet.dmg; // hurt player
						if (playerShip.health <= 0)
						{
							cout << "Game over! Health: " << playerShip.health << endl;
							//-----do something to end the game ----
							gOver = !gOver;
							//clear eneimes off here
							//AllEnemies.clear();
							gMenu.setupScore(score);
						}
						// --- do something to get rid of the bullet ----
					}
				}
				++it;
			}

			window.display();

		} //end of the game logic

		else if (gOver == true)
		{
			window.clear();		// clear window
			gMenu.draw(window); // render pause menu
			window.display();	// update window
			window.setMouseCursorVisible(true);
		}
		//try the draw gOverscreen here dont forget could just reset score and player health
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