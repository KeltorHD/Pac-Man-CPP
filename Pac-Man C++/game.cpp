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
	this->player = new Player();
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

void Game::updatePlayerInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("W"))))
	{
		this->player->setDir(dirType::up);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("S"))))
	{
		this->player->setDir(dirType::down);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("A"))))
	{
		this->player->setDir(dirType::left);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("D"))))
	{
		this->player->setDir(dirType::right);
	}
}

void Game::update()
{
	this->updateSFMLEvents();
	this->updatePlayerInput();
	this->player->update(this->dt);
}

void Game::render()
{
	this->window->clear();

	/*render items*/
	this->map->render(this->window);
	this->player->render(this->window);

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
