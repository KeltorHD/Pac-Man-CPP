#include "stdafx.h"
#include "player.h"

void Player::initVar()
{
	this->speed = 75.f;
	this->current = dirType::none;
	this->next = dirType::none;
}

void Player::initComponents()
{
	this->animationComponent = new AnimationComponent(this->sprite, this->animTexture);
	this->hitboxComponent = new HitboxComponent(this->sprite, 4, 4, 16, 16);
}

void Player::initSprite()
{
	this->animTexture.loadFromFile("Images/sprites.png");
	this->sprite.setTexture(this->animTexture);
	this->sprite.setTextureRect(sf::IntRect(0, 0, 24, 24));
	this->sprite.setPosition(START_POS_X, START_POS_Y);
}

Player::Player()
	: Entity()
{
	this->initVar();
	this->initSprite();
	this->initComponents();

	this->animationComponent->addAnimation("eat", 15.f, 0, 0, 5, 0, 24, 24);
}

Player::~Player()
{
	delete this->animationComponent;
	delete this->hitboxComponent;
}

void Player::setDir(dirType dir)
{
	if (this->current == dirType::none)
		this->current = dir;
	else if (this->current != dir) 
		this->next = dir;
}

void Player::setPosition(float x, float y)
{
	this->sprite.setPosition(x, y);
}

void Player::clearDir()
{
	this->current = this->next;
	this->next = dirType::none;
}

void Player::clearDir(dirType dir)
{
	this->current = dir;
	this->next = dirType::none;
}

const dirType& Player::getCurDir()
{
	return this->current;
}

const dirType& Player::getNextDir()
{
	return this->next;
}

const sf::Vector2f& Player::getPosition()
{
	return this->hitboxComponent->getPosition();
}

const sf::Vector2f& Player::getPosition(const dirType& dir)
{
	switch (dir)
	{
	case dirType::left:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y );
	case dirType::right:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH,
			this->hitboxComponent->getPosition().y);
	case dirType::up:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	case dirType::down:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y + TILE_WIDTH);
	case dirType::none:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	}
}

const sf::Vector2f Player::getNextPosition(const float& dt)
{
	switch (this->current)
	{
	case dirType::left:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x - dt * this->speed,
			this->hitboxComponent->getPosition().y);
	case dirType::right:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH + dt * this->speed,
			this->hitboxComponent->getPosition().y);
	case dirType::up:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y - dt * this->speed);
	case dirType::down:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y + TILE_WIDTH + dt * this->speed);
	case dirType::none:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	}
}

const sf::Vector2f Player::getNextPosition(const dirType& dir, const float& dt)
{
	switch (dir)
	{
	case dirType::left:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x - dt * this->speed,
			this->hitboxComponent->getPosition().y + TILE_WIDTH / 2);
	case dirType::right:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH + dt * this->speed,
			this->hitboxComponent->getPosition().y + TILE_WIDTH / 2);
	case dirType::up:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH / 2,
			this->hitboxComponent->getPosition().y - dt * this->speed);
	case dirType::down:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x + TILE_WIDTH / 2,
			this->hitboxComponent->getPosition().y + TILE_WIDTH + dt * this->speed);
	case dirType::none:
		return sf::Vector2f(
			this->hitboxComponent->getPosition().x,
			this->hitboxComponent->getPosition().y);
	}
}

const float Player::getMovingRange(const float& dt)
{
	return dt* this->speed;
}

void Player::move(const float& dt)
{
	if (this->current != dirType::none)
	{
		switch (this->current)
		{
		case dirType::left:
			this->hitboxComponent->move(-dt * this->speed, 0);
			break;
		case dirType::right:
			this->hitboxComponent->move(dt * this->speed, 0);
			break;
		case dirType::up:
			this->hitboxComponent->move(0, -dt * this->speed);
			break;
		case dirType::down:
			this->hitboxComponent->move(0, dt * this->speed);
			break;
		}
	}
}

void Player::moveToBorder()
{
	switch (this->current)
	{
	case dirType::left:
		this->hitboxComponent->setPosition
		(
			int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH,
			this->hitboxComponent->getPosition().y
		);
		break;
	case dirType::right:
		this->hitboxComponent->setPosition
		(
			(int(this->hitboxComponent->getPosition().x) % TILE_WIDTH > 0) ? 
			((int(this->hitboxComponent->getPosition().x / TILE_WIDTH) + 1) * TILE_WIDTH) : 
			(int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH),
			this->hitboxComponent->getPosition().y
		);
		break;
	case dirType::up:
		this->hitboxComponent->setPosition
		(
			int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH,
			int(this->hitboxComponent->getPosition().y / TILE_WIDTH) * TILE_WIDTH
		);
		break;
	case dirType::down:
		this->hitboxComponent->setPosition
		(
			int(this->hitboxComponent->getPosition().x / TILE_WIDTH) * TILE_WIDTH,
			(int(this->hitboxComponent->getPosition().y) % TILE_WIDTH > 0) ?
			((int(this->hitboxComponent->getPosition().y / TILE_WIDTH) + 1) * TILE_WIDTH) :
			(int(this->hitboxComponent->getPosition().y / TILE_WIDTH) * TILE_WIDTH)
		);
		break;
	}
}

void Player::update(const float& dt)
{
	//this->updateMove(dt);
	this->hitboxComponent->update();
	//this->animationComponent->play("eat", dt);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	this->hitboxComponent->render(*target);
}
