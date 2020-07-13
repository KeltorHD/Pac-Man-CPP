#pragma once

#include "menuState.h"

class Game
{
private:
	/*window*/
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::map<std::string, int> supportedKeys;
	std::stack<State*> states;

	/*Initialization*/
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

	/*update*/
	void updateDt();
	void updateSFMLEvents();
	void update();

	/*render*/
	void render();

public:
	Game();
	~Game();

	/*core*/
	void run();
};