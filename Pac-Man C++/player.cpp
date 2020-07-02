#include "stdafx.h"
#include "player.h"

void Player::initVar()
{
	this->speed = 50.f;
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

void Player::updateMove(const float& dt)
{
	if (this->current != dirType::none)
	{
		switch (this->current)
		{
		case dirType::left:
			this->sprite.move(-dt * this->speed, 0);
			break;
		case dirType::right:
			this->sprite.move(dt * this->speed, 0);
			break;
		case dirType::up:
			this->sprite.move(0, -dt * this->speed);
			break;
		case dirType::down:
			this->sprite.move(0, dt * this->speed);
			break;
		}
	}
}

Player::Player()
	: Enemy()
{
	this->initVar();
	this->initSprite();
	this->initComponents();

	//this->animationComponent->addAnimation("eat", 15.f, 0, 0, 5, 0, 24, 24);
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
	this->next = dir;
}

void Player::update(const float& dt)
{
	this->updateMove(dt);
	this->hitboxComponent->update();
	//this->animationComponent->play("eat", dt);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	this->hitboxComponent->render(*target);
}
