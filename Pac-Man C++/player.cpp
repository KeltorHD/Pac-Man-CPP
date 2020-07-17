#include "stdafx.h"
#include "player.h"

void Player::initVar()
{
	this->lifes = 2;
	this->current = dirType::left;
}

void Player::initComponents()
{
	this->animationComponent = new AnimationComponent(this->sprite, this->baseTexture);
	this->hitboxComponent = new HitboxComponent(this->sprite, 4, 4, 16, 16);
}

void Player::initSprite()
{
	this->baseTexture.loadFromFile("Images/sprites.png");
	this->sprite.setTexture(this->baseTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
	this->sprite.setPosition(START_POS_X, START_POS_Y);

	this->lifeSprite.setTexture(this->baseTexture);
	this->lifeSprite.setTextureRect(sf::IntRect(72, 0, -24, 24));
}

void Player::updateAnimation(const float& dt)
{
	switch (this->current)
	{
	case dirType::left:
		this->animationComponent->play("horizontal", dt);
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(24.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		break;
	case dirType::right:
		this->animationComponent->play("horizontal", dt);
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		break;
	case dirType::up:
		this->animationComponent->play("vertical", dt);
		if (this->sprite.getScale().y < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		break;
	case dirType::down:
		this->animationComponent->play("vertical", dt); 
		if (this->sprite.getScale().y > 0.f)
		{
			this->sprite.setOrigin(0.f, 24.f);
			this->sprite.setScale(1.f, -1.f);
		}
		break;
	case dirType::none:
		this->sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
		break;
	}
}

void Player::renderLifes(sf::RenderTarget* target)
{
	/*render sprite*/
	for (int i = 0; i < this->lifes; i++)
	{
		this->lifeSprite.setPosition(float(LIFES_POS_X + 36 * i), LIFES_POS_Y);
		target->draw(this->lifeSprite);
	}
}

Player::Player()
	: Entity(100.f, dirType::none, dirType::none)
{
	this->initVar();
	this->initSprite();
	this->initComponents();

	this->animationComponent->addAnimation("horizontal", 5.f, 0, 0, 5, 0, 24, 24);
	this->animationComponent->addAnimation("vertical", 5.f, 0, 1, 5, 1, 24, 24);
}

Player::~Player()
{
	delete this->animationComponent;
	delete this->hitboxComponent;
}

void Player::decLifes()
{
	this->lifes--;
}

void Player::setLifes(unsigned life)
{
	this->lifes = life;
}

const int& Player::getLives() const
{
	return this->lifes;
}

void Player::reload()
{
	this->hitboxComponent->setPosition(START_POS_X + 4, START_POS_Y + 4);
	this->clearDir(dirType::none);
}

void Player::updateInput(const Map* map, const float& dt, const dirType dir)
{
	if (dir != dirType::none && dir != this->current)
	{
		/*нужно ли изменять направления прямо сейчас?*/
		if (!map->isWall /*не в стену ли идем?*/
		(
			int(this->getNextPosition(dir, dt).x / TILE_WIDTH),
			int(this->getNextPosition(dir, dt).y / TILE_WIDTH)
		))
		{
			bool isChange = false;
			switch (dir)
			{
			case dirType::left:
			case dirType::right:
				if (int(this->getPosition().y) % TILE_WIDTH == 0)
					isChange = true;
				break;
			case dirType::up:
			case dirType::down:
				if (int(this->getPosition().x) % TILE_WIDTH == 0)
					isChange = true;
				break;
			}
			if (isChange) /*меняем направление, так как положение совпадает с клетками*/
			{
				if (isPerpendicularDir(dir, current))
					this->moveToBorder();
				this->clearDir(dir);
			}
			else /*запоминаем позицию, так как положение не совпадает с клетками*/
			{
				this->setDir(dir);
			}
		}
		else /*запоминаем направление*/
		{
			this->setDir(dir);
		}
	}
}

void Player::update(const Map* map, const float& dt)
{
	this->updateMove(map, dt); /*обновление позиции хитбокса*/
	this->hitboxComponent->update(); /*обновление позиции спрайта вслед за хитбоксом*/
	this->updateAnimation(dt);
}

void Player::render(sf::RenderTarget* target)
{
	Entity::render(target);
	this->renderLifes(target);
}
