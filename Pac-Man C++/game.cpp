#include "stdafx.h"
#include "game.h"

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
	dirType dir = dirType::none;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("W"))))
	{
		dir = dirType::up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("S"))))
	{
		dir = dirType::down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("A"))))
	{
		dir = dirType::left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys.at("D"))))
	{
		dir = dirType::right;
	}
	
	if (dir != dirType::none && dir != player->getCurDir())
	{
		/*����� �� �������� ����������� ����� ������?*/
		if (!this->map->isWall /*�� � ����� �� ����?*/
		(
			this->player->getNextPosition(dir, this->dt).x / TILE_WIDTH,
			this->player->getNextPosition(dir, this->dt).y / TILE_WIDTH
		))
		{
			bool isChange = false;
			switch (dir)
			{
			case dirType::left:
			case dirType::right:
				if (int(this->player->getPosition().y) % TILE_WIDTH == 0)
					isChange = true;
				break;
			case dirType::up:
			case dirType::down:
				if (int(this->player->getPosition().x) % TILE_WIDTH == 0)
					isChange = true;
				break;
			}
			if (isChange) /*������ �����������, ��� ��� ��������� ��������� � ��������*/
			{
				if (isPerpendicular(dir, this->player->getCurDir()))
					this->player->moveToBorder();
				this->player->clearDir(dir);
			}
			else /*���������� �������, ��� ��� ��������� �� ��������� � ��������*/
			{
				this->player->setDir(dir);
			}
		}
		else /*���������� �����������*/
		{
			this->player->setDir(dir);
		}
	}
}

void Game::updatePlayerMove()
{
	int next_x = this->player->getNextPosition(this->player->getNextDir(), this->dt).x;
	int next_y = this->player->getNextPosition(this->player->getNextDir(), this->dt).y;

	/*��������: ����� �� �������� ����������� ��������*/
	if (this->player->getNextDir() != dirType::none)
	{
		/*��������: ��������� ������� - �� �����?*/
		if (!this->map->isWall
		(
			next_x / TILE_WIDTH,
			next_y / TILE_WIDTH
		))
		{
			/*���������, ���������� �� �� ������ � ��������*/
			bool isChange = false;
			switch (this->player->getNextDir())
			{
			case dirType::left:
			case dirType::right:
				if (int(this->player->getPosition().y) % TILE_WIDTH == 0)
					isChange = true;
				break;
			case dirType::up:
			case dirType::down:
				if (int(this->player->getPosition().x) % TILE_WIDTH == 0)
					isChange = true;
				break;
			}
			if (isChange)
			{
				this->player->moveToBorder(); /*���������� � ������� ������*/
				this->player->clearDir();
			}
		}
	}

	/*��������: ����� �� ���������� �������� � ������� �������*/
	if (this->player->getCurDir() != dirType::none)
	{
		/*���� ��������� ������� ������ ��������� � �����*/
		if (this->map->isWall
		(
			this->player->getNextPosition(this->dt).x / TILE_WIDTH,
			this->player->getNextPosition(this->dt).y / TILE_WIDTH
		))
		{
			this->player->moveToBorder(); /*���������� � ������� ������*/
			this->player->clearDir();
		}
		else
		{
			this->player->move(dt);
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();
	this->updatePlayerInput();
	this->updatePlayerMove();
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
