#include "stdafx.h"
#include "blinky.h"

Blinky::Blinky()
	: Ghost()
{
	this->initSprite();
	this->initVar();
	this->initComponents();
	this->initTimers();
}

Blinky::~Blinky()
{
	delete this->hitboxComponent;
	delete this->animationComponent;
}

void Blinky::update(const Map* map, const Player* player, const float& dt)
{
	this->updateTargetcell(player, map);
	this->updateMoveGhost(map, dt);
	this->hitboxComponent->update();
}

void Blinky::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	this->hitboxComponent->render(*target);
}

void Blinky::initSprite()
{
	if (!this->animTexture.loadFromFile("Images/blinky.png"))
		throw "NOT COULD LOAD BLINKY TEXTURE";

	this->sprite.setTexture(this->animTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 28, 28));
	this->sprite.setPosition(BLINKY_POS_X, BLINKY_POS_Y);
}

void Blinky::initComponents()
{
	this->animationComponent = new AnimationComponent(this->sprite, this->animTexture);
	this->hitboxComponent = new HitboxComponent(this->sprite, 6, 6, 16, 16);
}

void Blinky::initVar()
{
	this->mode = modeType::chase;
	this->speed = 75.f;
}

void Blinky::initTimers()
{
}

void Blinky::updateTargetcell(const Player* player, const Map* map)
{
	if (this->mode == modeType::chase)
	{
		/*следуем в клетку за игроком*/
		this->targetCell.x = float((int(player->getPosition().x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
		this->targetCell.y = float((int(player->getPosition().y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
	}
	else if (this->mode == modeType::frightened)
	{
		if (map->getCountEat() >= (3 * COUNT_EAT / 4))
		{
			this->targetCell.x = GAME_COL - 1;
			this->targetCell.y = 0;
		}
		else
		{
			/*следуем в клетку за игроком*/
			this->targetCell.x = float((int(player->getPosition().x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
			this->targetCell.y = float((int(player->getPosition().y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2);
		}
	}
}
