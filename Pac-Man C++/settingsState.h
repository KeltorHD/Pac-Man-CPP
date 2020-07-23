#pragma once

#include "state.h"
#include "gui.h"

class SettingsState :
	public State
{
	/*Var*/
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*>buttons;
	gui::Slider* slider;
	sf::Text volumeText;
	float volume;

	/*init*/
	void initVariables();
	void initBackground();
	void initFonts();
	void initText();
	void initButtons();
	void initSlider();

	/*func*/
	void saveSettings();

	void updateText();
	void updateButtons();
	void renderButtons(sf::RenderTarget* target);
public:
	SettingsState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window);
	virtual ~SettingsState();

	/*func*/
	void update(const float& dt);
	void render();
};