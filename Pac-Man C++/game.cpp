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
	this->enemy.push_back(new Blinky());
}

void Game::updateCollisionEnemies()
{
	for (auto& i : this->enemy)
	{
		
		if (this->map->isEqual(i->getCenterPosition(), this->player->getCenterPosition()))
		{
			/*reload player, enemies, level--*/
			this->player->reload();
			for (auto& i : this->enemy)
			{
				//i.reload();
			}
			this->player->decLifes(); /*уменьшение жизней*/
			break;
		}
	}
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
	delete this->player;
	for (auto& i: this->enemy)
	{
		delete i;
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
		/*нужно ли изменять направления прямо сейчас?*/
		if (!this->map->isWall /*не в стену ли идем?*/
		(
			int(this->player->getNextPosition(dir, this->dt).x / TILE_WIDTH),
			int(this->player->getNextPosition(dir, this->dt).y / TILE_WIDTH)
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
			if (isChange) /*меняем направление, так как положение совпадает с клетками*/
			{
				if (isPerpendicularDir(dir, this->player->getCurDir()))
					this->player->moveToBorder();
				this->player->clearDir(dir);
			}
			else /*запоминаем позицию, так как положение не совпадает с клетками*/
			{
				this->player->setDir(dir);
			}
		}
		else /*запоминаем направление*/
		{
			this->player->setDir(dir);
		}
	}
}

void Game::update()
{
	/*update engine*/
	this->updateSFMLEvents();
	this->updatePlayerInput();

	/*update entity*/
	this->player->update(this->map, this->dt);
	for (auto& i : this->enemy)
	{
		i->update(this->map, this->player, this->dt);
	}

	/*обновление съеденной игроком еды*/
	int swtch = this->map->updateFood(this->player->getPosition());
	if (swtch == 1)
	{
		this->player->incEat();
	}
	else if (swtch == 2)
	{
		this->player->incEner();
		/*выставление призракам режима разбегания*/
	}

	if (!this->map->getCountEat())
	{
		/*reload, level++*/
		this->map->reload();
		this->player->reload();
	}

	/*collision*/
	this->updateCollisionEnemies();
}

void Game::render()
{
	/*clear window*/
	this->window->clear();

	/*render items*/
	this->map->render(this->window);
	this->player->render(this->window);
	for (auto& i : this->enemy)
	{
		i->render(this->window);
	}

	/*present*/
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
