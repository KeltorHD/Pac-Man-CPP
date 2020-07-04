#ifndef GAME_H

#include "Map.h"
#include "player.h"

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

	/*Initialization*/
	void initVariables();
	void initWindow();
	void initKeys();
	void initEssence();

public:
	Game();
	~Game();

	/*update*/
	void updateDt();
	void updateSFMLEvents();
	void updatePlayerInput();
	void updatePlayerMove();
	void update();

	/*render*/
	void render();

	/*core*/
	void run();
};

#endif // !GAME_H