#include "stdafx.h"
#include "blinky.h"

Blinky::Blinky()
	: Ghost(sf::Color::Red, BLINKY_POS_X, BLINKY_POS_Y, BLINKY_SPEED)
{
	this->initVar();
}

Blinky::~Blinky()
{
}

void Blinky::reload(const int& level)
{
	Ghost::reload(level);

	this->hitboxComponent->setPosition(BLINKY_POS_X + 6, BLINKY_POS_Y + 6);
	this->mode = this->pattern[0].first;
	this->setDir(dirType::left);

	if (level == 1)
	{
		this->speed = BLINKY_SPEED;
		this->loadPatternFromFile();
	}
}

void Blinky::initVar()
{
	/*начинаем в режиме преследования*/
	this->current = dirType::left;
}

void Blinky::updateTargetcell(const Player* player, const Map* map)
{
	if (this->mode == modeType::chase)
	{
		/*следуем в клетку за игроком*/
		this->targetCell.x = player->getCenterPosition().x;
		this->targetCell.y = player->getCenterPosition().y;
	}
	else if (this->mode == modeType::scatter)
	{
		if (map->getCountEat() >= (COUNT_EAT / 4))
		{
			this->targetCell.x = TILE_WIDTH * GAME_COL;
			this->targetCell.y = 0;
		}
		else
		{
			/*следуем в клетку за игроком*/
			this->targetCell.x = float((int(player->getPosition().x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
			this->targetCell.y = float((int(player->getPosition().y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
		}
	}
	else if (this->mode == modeType::toHome)
	{
		this->targetCell.x = 14 * TILE_WIDTH + TILE_WIDTH / 2;
		this->targetCell.y = 14 * TILE_WIDTH + TILE_WIDTH / 2;
	}
}