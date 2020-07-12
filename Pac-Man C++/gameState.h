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
	void initFont();
	void initScore();
	void initText();
	void initEssence();

	/*update*/
	void updatePlayerInput(const float& dt); /*обвновление пользовательского ввода*/
	void updateEntity(const float& dt); /*обновление сущностей*/
	void updateFrightened(); /*обновление таймеров*/
	void updateFood(); /*обновление съеденной игроком пищи*/
	void updateCollisionEnemies(); /*обновление коллизии*/
	void updateLevel(); /*обновление уровня*/
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