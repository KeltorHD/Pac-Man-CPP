#include "stdafx.h"
#include "inky.h"

Inky::Inky()
	: Ghost(sf::Color(0, 255, 255, 255), INKY_POS_X, INKY_POS_Y, INKY_SPEED)
{
	this->initVar();
}

Inky::~Inky()
{
}

void Inky::updateTargetCell(const Player* player, const Ghost* ghost)
{
	if (this->mode == modeType::chase)
	{
		/*выбираем клетку за игроком +2*/
		sf::Vector2f tmp = getNextCoordWidthDir(player->getCenterPosition(), player->getCurDir(), 2);
		this->targetCell.x = 2 * ghost->getCenterPosition().x - tmp.x;
		this->targetCell.y = 2 * ghost->getCenterPosition().y - tmp.y;
	}
}

void Inky::reload()
{
	this->hitboxComponent->setPosition(INKY_POS_X + 6, INKY_POS_Y + 6);
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
	this->animationComponent->setTextureSheet(this->baseTexture);
	this->patternCounter = 0;
	this->patternTimer = 0.f;
}

void Inky::initVar()
{
	/*начинаем в домике*/
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
}

void Inky::updateTargetcell(const Player* player, const Map* map)
{
	if (this->mode == modeType::scatter)
	{
		/*левый верхний угол*/
		this->targetCell.x = GAME_COL * TILE_WIDTH;
		this->targetCell.y = GAME_ROW * TILE_WIDTH;
	}
	else if (this->mode == modeType::toHome)
	{
		this->targetCell.x = 14 * TILE_WIDTH + TILE_WIDTH / 2;
		this->targetCell.y = 14 * TILE_WIDTH + TILE_WIDTH / 2;
	}
}

void Inky::updateHouse(const Map* map)
{
	if (map->getCountEat() <= COUNT_EAT - 30 && this->mode == modeType::inHome)
	{
		this->setMode(modeType::outHome);
	}
}