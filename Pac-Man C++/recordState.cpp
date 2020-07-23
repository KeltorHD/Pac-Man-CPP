#include "stdafx.h"
#include "recordState.h"

void RecordState::initVariables()
{
	std::ifstream ifs;
	ifs.open("Config/statistics.st");
	if (!ifs.is_open())
		throw "COULD NOT LOAD STATISTICS";
	this->maxScore = 0;
	ifs >> maxScore;
	ifs.close();
}

void RecordState::initBackground()
{
	this->background.setSize(sf::Vector2f(GAME_WIDTH, GAME_HEIGHT));
	if (!this->backgroundTexture.loadFromFile("Images/background_record.png"))
	{
		throw "NOT COULD LOAD BACKGROUND";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void RecordState::initFonts()
{
	if (!this->font.loadFromFile("Font/atari.ttf"))
		throw("NOT COULD LOAD FONT");
}

void RecordState::initText()
{
	this->text = new sf::Text(std::to_string(this->maxScore), font, 24);
	this->text->setFillColor(sf::Color(222, 222, 255));
	this->text->setOrigin
	(
		this->text->getLocalBounds().left + this->text->getLocalBounds().width / 2.f,
		this->text->getLocalBounds().top + this->text->getLocalBounds().height / 2.f
	);
	this->text->setPosition(GAME_WIDTH / 2.f, 125.f);
}

void RecordState::initButton()
{
	/*magic constants*/
	float width = GAME_WIDTH / 3;
	float height = GAME_HEIGHT / 12;
	float pos_x = GAME_WIDTH / 3;
	float pos_y = GAME_HEIGHT / 2 - height;
	float offset = height / 2.f;
	this->backToMenu = new gui::Button
	(
		pos_x, pos_y + height * 3 + offset * 3, width, height,
		EXIT, this->font, 16, 2,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255),
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::White, sf::Color(222, 222, 255), sf::Color(222, 222, 255)
	);
}

RecordState::RecordState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states, sf::RenderWindow* window)
	: State(supportedKeys, states, window)
{
	this->initBackground();
	this->initVariables();
	this->initFonts();
	this->initText();
	this->initButton();
}

RecordState::~RecordState()
{
	delete this->backToMenu;
	delete this->text;
}

void RecordState::updateButton()
{
	/*Updates all the buttons in this state*/

	this->backToMenu->update(this->mousePosWindow);

	
	/*Back to menu*/
	if (this->backToMenu->isPressed())
	{
		this->endState();
	}
}

void RecordState::update(const float& dt)
{
	this->updateMousePosition();

	this->updateButton();
}

void RecordState::renderButton(sf::RenderTarget* target)
{
	this->backToMenu->render(target);
}

void RecordState::render()
{
	this->window->draw(this->background);
	this->window->draw(*this->text);
	this->renderButton(this->window);
}