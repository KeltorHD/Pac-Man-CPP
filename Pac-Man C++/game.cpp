#include "stdafx.h"
#include "game.h"

//Static func

void Game::initVariables()
{
	this->window = NULL;

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

void Game::initEssence()
{
	this->map = new Map();
}

/*Constructor*/
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initKeys();
	this->initEssence();
}

Game::~Game()
{
	delete this->map;
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
	this->updateSFMLEvents();

}

void Game::render()
{
	this->window->clear();

	/*render items*/
	this->map->render(window);

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
