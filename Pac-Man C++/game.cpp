#include "stdafx.h"
#include "game.h"

void Game::initVariables()
{
	this->window = NULL;

	this->dt = 0;
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Font/atari.ttf"))
		throw "NOT COULD LOAD FONT";
}

void Game::initScore()
{
	this->score = 0;
	this->maxScore = 0;

	std::ifstream ifs;
	ifs.open("Config/statistics.st");
	if (!ifs.is_open())
		throw "COULD NOT LOAD STATISTICS";
	ifs >> this->maxScore;
	ifs.close();
}

void Game::initText()
{
	this->scoreText = new sf::Text(std::to_string(this->score), font, 16);
	this->scoreText->setFillColor(sf::Color(222, 222, 255));
	this->scoreText->setPosition(112, 24);
	this->maxScoreText = new sf::Text(std::to_string(this->maxScore), font, 16);
	this->maxScoreText->setFillColor(sf::Color(222, 222, 255));
	this->maxScoreText->setPosition(336, 24);
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
	Ghost::loadStaticVar(); /*загрузка статической текстуры*/
	this->enemy.push_back(new Blinky());
	this->enemy.push_back(new Pinky());
	this->enemy.push_back(new Clyde());
}

void Game::updateCollisionEnemies()
{
	for (auto& i : this->enemy)
	{
		if (this->map->isEqual(i->getCenterPosition(), this->player->getCenterPosition()))
		{
			if (i->isFrightened())
			{
				/*добавление очков за съеденное привидение*/
				this->score += this->ghostScore;
				this->ghostScore *= 2;
				i->setModeToHome();
			}
			else if (i->isNotMatherial())
			{
				continue;
			}
			else
			{
				/*reload player, enemies, level--*/
				this->player->reload();
				for (auto& i : this->enemy)
				{
					i->reload();
				}
				this->player->decLifes(); /*уменьшение жизней*/
				break;
			}
		}
	}
}

void Game::updateLevel()
{
	if (!this->map->getCountEat())
	{
		/*reload, level++*/
		this->map->reload();
		this->player->reload();
		for (auto& i : this->enemy)
		{
			i->reload();
		}
	}
}

void Game::updateText()
{
	this->scoreText->setString(std::to_string(this->score));
	this->maxScoreText->setString(std::to_string((this->score>this->maxScore) ? this->score : this->maxScore));

	this->scoreText->setOrigin
	(
		this->scoreText->getLocalBounds().left + this->scoreText->getLocalBounds().width / 2.f,
		this->scoreText->getLocalBounds().top
	);
	this->maxScoreText->setOrigin
	(
		this->maxScoreText->getLocalBounds().left + this->maxScoreText->getLocalBounds().width / 2.f,
		this->maxScoreText->getLocalBounds().top
	);
}

/*Constructor*/
Game::Game()
{
	this->initVariables();
	this->initFont();
	this->initScore();
	this->initText();
	this->initWindow();
	this->initKeys();
	this->initEssence();
}

Game::~Game()
{
	this->saveStats();
	delete this->map;
	delete this->player;
	for (auto& i: this->enemy)
	{
		delete i;
	}
	delete this->scoreText;
	delete this->maxScoreText;
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

void Game::updateFrightened()
{
	bool tmp = false;
	for (auto& i : this->enemy)
	{
		if (i->isFrightened())
		{
			tmp = true;
			break;
		}
	}

	if (!tmp)
	{
		this->ghostScore = POINT_GHOST;
	}
}

void Game::updateFood()
{
	/*обновление съеденной игроком еды*/
	int swtch = this->map->updateFood(this->player->getPosition());
	if (swtch == 1)
	{
		/*добавление очков*/
		this->score += POINT_EAT;
	}
	else if (swtch == 2)
	{
		/*добавление очков*/
		this->score += POINT_ENER;
		/*выставление призракам режима разбегания*/
		for (auto& i : this->enemy)
		{
			i->setModeFrightened();
		}
		this->ghostScore = POINT_GHOST;
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

	/*collision*/
	this->updateCollisionEnemies();
	this->updateFrightened();
	
	this->updateFood();
	this->updateLevel();
	this->updateText();
}

void Game::renderText()
{
	this->window->draw(*this->scoreText);
	this->window->draw(*this->maxScoreText);
}

void Game::render()
{
	/*clear window*/
	this->window->clear();

	/*render items*/
	this->map->render(this->window);
	this->renderText();
	this->player->render(this->window);
	for (auto& i : this->enemy)
	{
		i->render(this->window);
	}

	/*present*/
	this->window->display();
}

void Game::saveStats()
{
	std::ofstream ofs;
	ofs.open("Config/statistics.st");
	if (!ofs.is_open())
		throw "COULD NOT SAVE STATISTICS";
	ofs << ((this->score > this->maxScore) ? this->score : this->maxScore);
	ofs.close();
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