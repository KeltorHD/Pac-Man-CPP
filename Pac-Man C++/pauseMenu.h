#pragma once

#include "gui.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text menuText;

	sf::RectangleShape background;
	sf::RectangleShape container;


	std::map<std::string, gui::Button*> buttons;

public:
	PauseMenu(sf::Font& font);
	virtual ~PauseMenu();

	/*accessors*/
	std::map<std::string, gui::Button*>& getButton();

	/*func*/
	const bool isButtonPressed(const std::string key);
	void addButton(const float y, const float width, const float height, const unsigned charSize, const std::string text);
	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget* target);
};

