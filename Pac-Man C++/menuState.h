#pragma once

#include "gameState.h"
#include "gui.h"

class MenuState :
	public State
{
private:
	/*Var*/
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*>buttons;

	/*Func*/
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
public:
	MenuState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window);
	virtual ~MenuState();

	//func

	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target);
	void render();
};