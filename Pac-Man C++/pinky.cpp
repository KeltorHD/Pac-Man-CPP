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

void Pinky::reload(const int& level)
{
	Ghost::reload(level);

	this->hitboxComponent->setPosition(PINKY_POS_X + 6, PINKY_POS_Y + 6);
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
	this->animationComponent->setTextureSheet(this->baseTexture);
	this->patternCounter = 0;
	this->patternTimer = 0.f;

	if (level == 1)
	{
		this->speed = PINKY_SPEED;
		this->loadPatternFromFile();
	}
}

void Pinky::initVar()
{
	/*начинаем в домике*/
	this->current = dirType::none;
	this->next = dirType::none;
	this->mode = modeType::inHome;
}

void Pinky::updateTargetcell(const Player* player, const Map* map)
{
	if (this->mode == modeType::chase)
	{
		/*выбираем клетку за игроком +4*/
		sf::Vector2f tmp = getNextCoordWidthDir(player->getCenterPosition(), player->getCurDir(), 4);
		this->targetCell.x = tmp.x;
		this->targetCell.y = tmp.y;
	}
	else if (this->mode == modeType::scatter)
	{
		/*левый верхний угол*/
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