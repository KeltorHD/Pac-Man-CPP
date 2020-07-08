#pragma once

#include "map.h"
#include "player.h"
#include "blinky.h"

class Game
{
private:
	/*window*/
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::map<std::string, int> supportedKeys;

	/*map, player, enemy*/
	Map* map;
	Player* player;
	std::vector<Ghost*> enemy;

	/*Initialization*/
	void initVariables();
	void initWindow();
	void initKeys();
	void initEssence();

	/*func*/
	void updateCollisionEnemies(); /*обновление коллизии*/

public:
	Game();
	~Game();

	/*update*/
	void updateDt();
	void updateSFMLEvents();
	void updatePlayerInput();
	void update();

	/*render*/
	void render();

	/*core*/
	void run();
};