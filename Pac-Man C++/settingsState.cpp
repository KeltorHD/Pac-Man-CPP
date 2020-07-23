#include "stdafx.h"
#include "settingsState.h"

void SettingsState::initVariables()
{
	this->volume = 0.f;
	std::ifstream ifs;
	ifs.open("Config/settings.ini");
	if (!ifs.is_open())
		throw "COULD NOT LOAD SETTINGS";
	ifs >> this->volume;
	ifs.close();
}

void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(GAME_WIDTH, GAME_HEIGHT));
	if (!this->backgroundTexture.loadFromFile("Images/background.png"))
	{
		throw "NOT COULD LOAD BACKGROUND";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Font/atari.ttf"))
		throw("NOT COULD LOAD FONT");
}

void SettingsState::initText()
{
	this->volumeText.setFont(this->font);
	this->volumeText.setCharacterSize(14);
	this->volumeText.setFillColor(sf::Color(222, 222, 255));
	this->volumeText.setOrigin
	(
		this->volumeText.getLocalBounds().left,
		this->volumeText.getLocalBounds().top + this->volumeText.getLocalBounds().height / 2.f
	);
	this->volumeText.setPosition(20.f, GAME_HEIGHT / 2.f - 8.f);
	this->volumeText.setString("Volume: " + std::to_string(int(this->volume)));
}

void SettingsState::initButtons()
{
	/*magic constants*/
	float width = GAME_WIDTH / 3;
	float height = GAME_HEIGHT / 12;
	float pos_x = GAME_WIDTH / 3;
	float pos_y = GAME_HEIGHT / 2 - height;
	float offset = height / 2.f;
	this->buttons[SAVE] = new gui::Button
	(
		pos_x, pos_y + height * 2 + offset * 2, width, height,
		SAVE, this->font, 16, 2,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255),
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255)
	);
	this->buttons[EXIT] = new gui::Button
	(
		pos_x, pos_y + height * 3 + offset * 3, width, height,
		EXIT, this->font, 16, 2,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255),
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255)
	);
}

void SettingsState::initSlider()
{
	this->slider = new gui::Slider(200, GAME_HEIGHT / 2, 0, 100, 200, 15, 15, 50);
	this->slider->setSliderPercentValue(this->volume);
}

SettingsState::SettingsState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window)
	: State(supportedKeys, states, window)
{
	this->initBackground();
	this->initVariables();
	this->initFonts();
	this->initText();
	this->initButtons();
	this->initSlider();
}

SettingsState::~SettingsState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	delete this->slider;
}

void SettingsState::saveSettings()
{
	std::ofstream ofs;
	ofs.open("Config/settings.ini");
	if (!ofs.is_open())
		throw "COULD NOT LOAD SETTINGS";
	ofs << this->volume;
	ofs.close();
}

void SettingsState::updateText()
{
	this->volumeText.setString("Volume: " + std::to_string(int(this->volume)));
}

void SettingsState::updateButtons()
{
	/*Updates all the buttons in this state*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	/*Save*/
	if (this->buttons[SAVE]->isPressed() && this->getKeyTime())
	{
		this->saveSettings();
	}

	/*Quit the game*/
	if (this->buttons[EXIT]->isPressed() && this->getKeyTime())
	{
		this->endState();
	}
}

void SettingsState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateKeyTime(dt);

	this->updateButtons();
	this->slider->update(this->window);
	this->volume = this->slider->getSliderValue();
	this->updateText();
}

void SettingsState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::render()
{
	this->window->draw(this->background);
	this->window->draw(this->volumeText);
	this->slider->render(this->window);
	this->renderButtons(this->window);
}