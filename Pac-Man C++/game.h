#pragma once

#include "map.h"
#include "player.h"
#include "blinky.h"
#include "pinky.h"
#include "inky.h"
#include "clyde.h"

class Game
{
private:
	/*window*/
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::map<std::string, int> supportedKeys;
	sf::Font font; /*шрифт для вывода счета*/

	/*map, player, enemy*/
	Map* map;
	Player* player;
	std::vector<Ghost*> enemy;
	long long score; /*общий счет*/
	long long maxScore; /*максимальный счет*/
	int ghostScore = POINT_GHOST; /*счет за съедание призрака*/

	/*text*/
	sf::Text* scoreText;
	sf::Text* maxScoreText;

	/*Initialization*/
	void initVariables();
	void initFont();
	void initScore();
	void initText();
	void initWindow();
	void initKeys();
	void initEssence();

	/*update*/
	void updateDt();
	void updateSFMLEvents();
	void updatePlayerInput(); /*обвновление пользовательского ввода*/
	void updateEntity(); /*обновление сущностей*/
	void updateFrightened(); /*обновление таймеров*/
	void updateFood(); /*обновление съеденной игроком пищи*/
	void updateCollisionEnemies(); /*обновление коллизии*/
	void updateLevel(); /*обновление уровня*/
	void updateText();
	void update();

	/*render*/
	void renderText();
	void render();

	/*func*/
	void saveStats();

public:
	Game();
	~Game();

	/*core*/
	void run();
};