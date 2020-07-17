#include "stdafx.h"
#include "pauseMenu.h"

PauseMenu::PauseMenu(sf::Font& font)
	: font(font)
{
	/*init background*/
	this->background.setSize(
		sf::Vector2f
		(
			GAME_WIDTH,
			GAME_HEIGHT
		)
	);
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	this->container.setSize(
		sf::Vector2f
		(
			GAME_WIDTH / 2.f,
			GAME_HEIGHT
		)
	);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(
		GAME_WIDTH / 2.f - this->container.getSize().x / 2.f,
		0.f);

	//init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(222, 222, 255));
	this->menuText.setCharacterSize(18);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20.f
	);
}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButton()
{
	return this->buttons;
}

/*func*/

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(
	const float y,
	const float width, const float height,
	const unsigned charSize,
	const std::string text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[text] = new gui::Button(
		x, y, width, height,
		text, this->font, charSize,
		0.f,
		sf::Color(222, 222, 255), sf::Color::White, sf::Color(222, 222, 255),
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color(222, 222, 255), sf::Color::White, sf::Color(222, 222, 255));
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePosWindow);
	}
}

void PauseMenu::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target->draw(this->menuText);
}