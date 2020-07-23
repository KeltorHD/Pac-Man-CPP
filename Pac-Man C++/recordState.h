#pragma once

#include "state.h"
#include "gui.h"

class RecordState
	: public State
{
private:
	/*Var*/
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;
	sf::Text* text;
	int maxScore;

	gui::Button* backToMenu;

	/*init*/
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButton();

	/*func*/
	void updateButton();
	void renderButton(sf::RenderTarget* target);
public:
	RecordState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window);
	virtual ~RecordState();

	/*func*/
	void update(const float& dt);
	void render();
};