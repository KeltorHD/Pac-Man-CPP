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
	sf::Font font; /*����� ��� ������ �����*/

	/*map, player, enemy*/
	Map* map;
	Player* player;
	std::vector<Ghost*> enemy;
	long long score; /*����� ����*/
	long long maxScore; /*������������ ����*/
	int ghostScore = POINT_GHOST; /*���� �� �������� ��������*/

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
	void updatePlayerInput(); /*����������� ����������������� �����*/
	void updateEntity(); /*���������� ���������*/
	void updateFrightened(); /*���������� ��������*/
	void updateFood(); /*���������� ��������� ������� ����*/
	void updateCollisionEnemies(); /*���������� ��������*/
	void updateLevel(); /*���������� ������*/
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