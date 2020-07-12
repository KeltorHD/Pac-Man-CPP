#include "stdafx.h"
#include "clyde.h"

Clyde::Clyde()
	: Ghost(sf::Color(255, 184, 81, 255), CLYDE_POS_X, CLYDE_POS_Y, CLYDE_SPEED)
{
	this->initVar();
}

Clyde::~Clyde()
{
}

void Clyde::reload()
{
	this->hitboxComponent->setPosition(CLYDE_POS_X + 6, CLYDE_POS_Y + 6);
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
	this->animationComponent->setTextureSheet(this->baseTexture);
	this->patternCounter = 0;
	this->patternTimer = 0.f;
}

void Clyde::initVar()
{
	/*начинаем в домике*/
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
}

void Clyde::updateTargetcell(const Player* player, const Map* map)
{
	if (this->mode == modeType::chase)
	{
		if (map->distance(this->getCenterPosition(), player->getCenterPosition()) <= 8 * TILE_WIDTH)
		{
			this->targetCell.x = 0;
			this->targetCell.y = GAME_ROW * TILE_WIDTH;
		}
		else
		{
			this->targetCell.x = player->getCenterPosition().x;
			this->targetCell.y = player->getCenterPosition().y;
		}
	}
	else if (this->mode == modeType::scatter)
	{
		/*левый нижний угол*/
		this->targetCell.x = 0;
		this->targetCell.y = GAME_ROW * TILE_WIDTH;
	}
	else if (this->mode == modeType::toHome)
	{
		this->targetCell.x = 14 * TILE_WIDTH + TILE_WIDTH / 2;
		this->targetCell.y = 14 * TILE_WIDTH + TILE_WIDTH / 2;
	}
}

void Clyde::updateHouse(const Map* map)
{
	if (map->getCountEat() <= 2 * COUNT_EAT / 3 && this->mode == modeType::inHome)
	{
		this->setMode(modeType::outHome);
	}
}