#include "stdafx.h"
#include "game.h"

void Game::initVariables()
{
	this->window = nullptr;

	this->dt = 0;
}

/*Initializer func*/
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), GAME_TITLE);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int value = 0;
		while (ifs >> key >> value)
		{
			this->supportedKeys[key] = value;
		}
	}

	ifs.close();

	/*Debug*/
	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initStates()
{
	this->states.push(new MenuState(&this->supportedKeys, &this->states, this->window));
}

/*Constructor*/
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
	delete this->window;
}


/*func*/
void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	/*update engine*/
	this->updateSFMLEvents();

	if (!this->states.empty())
		// && this->window->hasFocus())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else /*App end*/
	{
		this->window->close();
	}
}

void Game::render()
{
	this->window->clear();

	/*render items*/
	if (!this->states.empty())
	{
		this->states.top()->render();
	}

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}
}