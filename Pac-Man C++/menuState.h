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

	/*init*/
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();

	/*func*/
	void updateButtons();
	void renderButtons(sf::RenderTarget* target);
public:
	MenuState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window);
	virtual ~MenuState();

	/*func*/
	void update(const float& dt);
	void render();
};