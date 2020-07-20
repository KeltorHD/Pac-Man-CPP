#pragma once

#include "state.h"
#include "soundManager.h"
#include "map.h"
#include "player.h"
#include "pauseMenu.h"
#include "textTag.h"
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
	SoundManager* soundManager;
	TextTag* textTag;
	Map* map;
	Player* player;
	std::vector<Ghost*> enemy;
	long long score; /*общий счет*/
	long long maxScore; /*максимальный счет*/
	int ghostScore = POINT_GHOST; /*счет за съедание призрака*/
	PauseMenu* pmenu; /*меню паузы*/
	sf::Texture loseTexture;
	sf::Sprite loseSprite;
	int level; /*уровень в игре*/

	/*text*/
	sf::Text* scoreText;
	sf::Text* maxScoreText;

	/*Initialization*/
	void initVar();
	void initSoundManager();
	void initFont();
	void initTextTag();
	void initScore();
	void initText();
	void initLoseSprite();
	void initEssence();
	void initPauseMenu();

	/*update*/
	void updatePauseMenuButtons(); /*обновление кнопок в меню паузы*/
	void updatePlayerInput(const float& dt); /*обвновление пользовательского ввода*/
	void updateEntity(const float& dt); /*обновление сущностей*/
	void updateFrightened(); /*обновление музыки и очков при страхе привидений*/
	void updateFood(); /*обновление съеденной игроком пищи*/
	void updateCollisionEnemies(); /*обновление коллизии*/
	void updateLevel(); /*обновление уровня*/
	void updateText();

	/*render*/
	void renderText(sf::RenderTarget* target);

	/*func*/
	void saveStats();
	void reloadGame();
public:
	GameState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window);
	virtual ~GameState();

	/*func*/
	void render();
	void update(const float& dt);
};