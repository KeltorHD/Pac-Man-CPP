#include "stdafx.h"
#include "blinky.h"

Blinky::Blinky()
	: Ghost(sf::Color::Red, BLINKY_POS_X, BLINKY_POS_Y)
{
	this->initVar();
	this->initTimers();
}

Blinky::~Blinky()
{
	delete this->hitboxComponent;
	delete this->animationComponent;
}

void Blinky::reload()
{
	this->hitboxComponent->setPosition(BLINKY_POS_X + 6, BLINKY_POS_Y + 6);
	this->setDir(dirType::left);
	this->setMode(modeType::chase);
}

void Blinky::initVar()
{
	this->mode = modeType::chase; /*�������� � ������ �������������*/
	this->current = dirType::left;
}

void Blinky::initTimers()
{
}

void Blinky::updateTargetcell(const Player* player, const Map* map)
{
	if (this->mode == modeType::chase)
	{
		/*������� � ������ �� �������*/
		this->targetCell.x = float((int(player->getPosition().x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
		this->targetCell.y = float((int(player->getPosition().y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
	}
	else if (this->mode == modeType::scatter)
	{
		if (map->getCountEat() >= (COUNT_EAT / 4))
		{
			this->targetCell.x = TILE_WIDTH * (GAME_COL - 1);
			this->targetCell.y = 0;
		}
		else
		{
			/*������� � ������ �� �������*/
			this->targetCell.x = float((int(player->getPosition().x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
			this->targetCell.y = float((int(player->getPosition().y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
		}
	}
	else if (this->mode == modeType::toHome)
	{
		this->targetCell.x = 14 * TILE_WIDTH;
		this->targetCell.y = 14 * TILE_WIDTH;
	}
}