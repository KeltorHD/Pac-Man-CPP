#include "stdafx.h"
#include "menuState.h"

void MenuState::initVariables()
{

}

void MenuState::initBackground()
{
	/*this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));
	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		throw "ERROR::MenuState::FAILED_LOAD_BACKGROUND";
	}
	this->background.setTexture(&this->backgroundTexture);*/
}

void MenuState::initFonts()
{
	if (!this->font.loadFromFile("Font/atari.ttf"))
		throw("NOT COULD LOAD FONT");
}

void MenuState::initButtons()
{
	/*magic constants*/
	float width = GAME_WIDTH / 3;
	float height = GAME_HEIGHT / 12;
	float pos_x = GAME_WIDTH / 3;
	float pos_y = GAME_HEIGHT / 2 - height;
	float offset = height / 2.f;
	this->buttons[PLAY] = new gui::Button
	(
		pos_x, pos_y, width, height,
		PLAY, this->font, 16, 2,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255),
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255)
	);
	this->buttons[RECORD] = new gui::Button
	(
		pos_x, pos_y + height + offset, width, height,
		RECORD, this->font, 16, 2,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255),
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255)
	);
	this->buttons[SETTINGS] = new gui::Button
	(
		pos_x, pos_y + height * 2 + offset * 2, width, height,
		SETTINGS, this->font, 16, 2,
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

MenuState::MenuState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window)
	: State(supportedKeys, states, window)
{
	this->initBackground();
	this->initVariables();
	this->initFonts();
	this->initButtons();
}

MenuState::~MenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MenuState::updateInput(const float& dt)
{

}

void MenuState::updateButtons()
{
	/*Updates all the buttons in this state*/

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	/*New game*/
	if (this->buttons[PLAY]->isPressed())
	{
		this->states->push(new GameState(this->supportedKeys, this->states, this->window));
	}


	/*Quit the game*/
	if (this->buttons[EXIT]->isPressed())
	{
		this->endState();
	}
}

void MenuState::update(const float& dt)
{
	this->updateMousePosition();
	this->updateInput(dt);

	this->updateButtons();
}

void MenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MenuState::render()
{
	//this->window->draw(this->background);
	this->renderButtons(this->window);
}