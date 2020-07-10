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

	/*update*/
	void updateDt();
	void updateSFMLEvents();
	void updatePlayerInput(); /*����������� ����������������� �����*/
	void updateFood(); /*���������� ��������� ������� ����*/
	void updateCollisionEnemies(); /*���������� ��������*/
	void updateLevel(); /*���������� ������*/
	void update();

	/*render*/
	void render();

public:
	Game();
	~Game();

	/*core*/
	void run();
};