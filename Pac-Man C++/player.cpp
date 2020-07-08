#include "stdafx.h"
#include "player.h"

void Player::initVar()
{
	this->lifes = 2;
	this->eat = 0;
	this->ener = 0;
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

void Player::renderLifes(sf::RenderTarget* target)
{
	sf::Sprite l;
	l.setTexture(this->animTexture);
	l.setTextureRect(sf::IntRect(72, 0, -24, 24));
	/*render sprite*/
	for (int i = 0; i < this->lifes; i++)
	{
		l.setPosition(float(LIFES_POS_X + 36 * i), LIFES_POS_Y);
		target->draw(l);
	}
}

Player::Player()
	: Entity(100.f, dirType::none, dirType::none)
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

void Player::incEat()
{
	this->eat++;
}

void Player::incEner()
{
	this->ener++;
	/*начало таймера уничтожения*/
}

void Player::decLifes()
{
	this->lifes--;
}

const size_t& Player::getCountEat()
{
	return this->eat;
}

void Player::reload()
{
	this->hitboxComponent->setPosition(START_POS_X + 4, START_POS_Y + 4);
	this->clearDir(dirType::none);
}

void Player::update(const Map* map, const float& dt)
{
	this->updateMove(map, dt); /*обновление позиции хитбокса*/
	this->hitboxComponent->update(); /*обновление позиции спрайта вслед за хитбоксом*/
	this->animationComponent->play("eat", dt);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->sprite);
	this->renderLifes(target);
	this->hitboxComponent->render(*target);
}
