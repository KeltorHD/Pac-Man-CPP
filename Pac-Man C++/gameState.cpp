#include "stdafx.h"
#include "gameState.h"

void GameState::initFont()
{
	if (!this->font.loadFromFile("Font/atari.ttf"))
		throw "NOT COULD LOAD FONT";
}

void GameState::initScore()
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

void GameState::initText()
{
	this->scoreText = new sf::Text(std::to_string(this->score), font, 16);
	this->scoreText->setFillColor(sf::Color(222, 222, 255));
	this->scoreText->setPosition(112, 24);
	this->maxScoreText = new sf::Text(std::to_string(this->maxScore), font, 16);
	this->maxScoreText->setFillColor(sf::Color(222, 222, 255));
	this->maxScoreText->setPosition(336, 24);
}


void GameState::initEssence()
{
	this->map = new Map();
	this->player = new Player();
	Ghost::loadStaticVar(); /*загрузка статической текстуры*/
	this->enemy.push_back(new Blinky());
	this->enemy.push_back(new Pinky());
	this->enemy.push_back(new Inky());
	this->enemy.push_back(new Clyde());
}

void GameState::updateCollisionEnemies()
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

void GameState::updateLevel()
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

void GameState::updateText()
{
	this->scoreText->setString(std::to_string(this->score));
	this->maxScoreText->setString(std::to_string((this->score > this->maxScore) ? this->score : this->maxScore));

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
GameState::GameState(const std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(supportedKeys, states)
{
	this->initFont();
	this->initScore();
	this->initText();
	this->initEssence();
}

GameState::~GameState()
{
	this->saveStats();
	delete this->map;
	delete this->player;
	for (auto& i : this->enemy)
	{
		delete i;
	}
	delete this->scoreText;
	delete this->maxScoreText;
}

void GameState::updatePlayerInput(const float& dt)
{
	dirType dir = dirType::none;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("W"))))
	{
		dir = dirType::up;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("S"))))
	{
		dir = dirType::down;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("A"))))
	{
		dir = dirType::left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->supportedKeys->at("D"))))
	{
		dir = dirType::right;
	}

	if (dir != dirType::none && dir != player->getCurDir())
	{
		/*нужно ли изменять направления прямо сейчас?*/
		if (!this->map->isWall /*не в стену ли идем?*/
		(
			int(this->player->getNextPosition(dir, dt).x / TILE_WIDTH),
			int(this->player->getNextPosition(dir, dt).y / TILE_WIDTH)
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

void GameState::updateEntity(const float& dt)
{
	this->player->update(this->map, dt);
	if (dynamic_cast<Inky*>(this->enemy[2]))
		dynamic_cast<Inky*>(this->enemy[2])->updateTargetCell(this->player, this->enemy[0]);
	for (auto& i : this->enemy)
	{
		i->update(this->map, this->player, dt);
	}
}

void GameState::updateFrightened()
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

void GameState::updateFood()
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

void GameState::renderText(sf::RenderTarget* target)
{
	target->draw(*this->scoreText);
	target->draw(*this->maxScoreText);
}

void GameState::saveStats()
{
	std::ofstream ofs;
	ofs.open("Config/statistics.st");
	if (!ofs.is_open())
		throw "COULD NOT SAVE STATISTICS";
	ofs << ((this->score > this->maxScore) ? this->score : this->maxScore);
	ofs.close();
}

void GameState::update(const float& dt)
{
	if (this->player->getLives())
	{
		/*Input*/
		this->updatePlayerInput(dt);

		/*update entity*/
		this->updateEntity(dt);

		/*collision*/
		this->updateCollisionEnemies();
		this->updateFrightened();

		this->updateFood();
		this->updateLevel();
		this->updateText();
	}
	else
	{
		this->quit = true;
	}
}

void GameState::render(sf::RenderTarget* target)
{
	/*render items*/
	this->map->render(target);
	this->renderText(target);
	this->player->render(target);
	for (auto& i : this->enemy)
	{
		i->render(target);
	}
}