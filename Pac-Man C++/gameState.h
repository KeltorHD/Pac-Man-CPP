#pragma once

#include "state.h"
#include "map.h"
#include "player.h"
#include "blinky.h"
#include "pinky.h"
#include "inky.h"
#include "clyde.h"

class GameState :
	public State
{
private:
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
	void initFont();
	void initScore();
	void initText();
	void initEssence();

	/*update*/
	void updatePlayerInput(const float& dt); /*����������� ����������������� �����*/
	void updateEntity(const float& dt); /*���������� ���������*/
	void updateFrightened(); /*���������� ��������*/
	void updateFood(); /*���������� ��������� ������� ����*/
	void updateCollisionEnemies(); /*���������� ��������*/
	void updateLevel(); /*���������� ������*/
	void updateText();

	/*render*/
	void renderText(sf::RenderTarget* target);

	/*func*/
	void saveStats();
public:
	GameState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	/*func*/
	void render(sf::RenderTarget* target);
	void update(const float& dt);
};