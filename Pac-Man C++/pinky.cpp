#include "stdafx.h"
#include "pinky.h"

Pinky::Pinky()
	: Ghost(sf::Color(255, 184, 255, 255), PINKY_POS_X, PINKY_POS_Y, PINKY_SPEED)
{
	this->initVar();
}

Pinky::~Pinky()
{
}

void Pinky::reload()
{
	this->hitboxComponent->setPosition(PINKY_POS_X + 6, PINKY_POS_Y + 6);
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
	this->animationComponent->setTextureSheet(this->baseTexture);
	this->patternCounter = 0;
	this->patternTimer = 0.f;
}

void Pinky::initVar()
{
	/*�������� � ������*/
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
}

void Pinky::updateTargetcell(const Player* player, const Map* map)
{
	if (this->mode == modeType::chase)
	{
		/*�������� ������ �� ������� +4*/
		this->targetCell.x = float((int(player->getPosition().x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH * 4 + TILE_WIDTH / 2);
		this->targetCell.y = float((int(player->getPosition().y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH * 4 + TILE_WIDTH / 2);
	}
	else if (this->mode == modeType::scatter)
	{
		/*����� ������� ����*/
		this->targetCell.x = 0;
		this->targetCell.y = 0;
	}
	else if (this->mode == modeType::toHome)
	{
		this->targetCell.x = 14 * TILE_WIDTH + TILE_WIDTH /2;
		this->targetCell.y = 14 * TILE_WIDTH + TILE_WIDTH / 2;
	}
}

void Pinky::updateHouse(const Map* map)
{
	if (map->getCountEat() <= COUNT_EAT && this->mode == modeType::inHome)
	{
		this->setMode(modeType::outHome);
	}
}