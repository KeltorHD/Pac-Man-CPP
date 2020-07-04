#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, 
	float offset_x, float offset_y, 
	float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	//this->hitbox.setOutlineThickness(-1.f);
	//this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{

}

/*accessors*/
const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

/*modifier*/
void HitboxComponent::setPosition(const sf::Vector2f& position)
{
	this->hitbox.setPosition(position);
	this->sprite.setPosition(position.x - this->offsetX, position.y - this->offsetY);
}

void HitboxComponent::setPosition(const float x, const float y)
{
	this->hitbox.setPosition(x, y);
	this->sprite.setPosition(x - this->offsetX, y - this->offsetY);
}

void HitboxComponent::move(const float x, const float y)
{
	this->hitbox.move(x, y);
}

/*func*/
void HitboxComponent::update()
{
	this->sprite.setPosition(this->hitbox.getPosition().x - this->offsetX, this->hitbox.getPosition().y - this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
