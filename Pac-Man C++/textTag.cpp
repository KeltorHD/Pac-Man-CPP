#include "stdafx.h"
#include "textTag.h"

TextTag::TextTag(sf::Font& font, unsigned charSize, sf::Color textColor)
{
	this->text.setFont(font);
	this->text.setCharacterSize(charSize);
	this->text.setFillColor(textColor);

	this->timer = TAG_TIME + 0.1f;
}

TextTag::~TextTag()
{
}

void TextTag::setNewTag(std::string text, const sf::Vector2f& pos)
{
	this->text.setString(text);
	this->text.setOrigin
	(
		this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.f,
		this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.f
	);
	this->text.setPosition(pos.x, pos.y);

	this->timer = 0.f;
}

void TextTag::update(const float& dt)
{
	if (this->timer <= TAG_TIME)
	{
		this->timer += dt;
	}
}

void TextTag::render(sf::RenderTarget* target)
{
	if (this->timer <= TAG_TIME)
	{
		target->draw(this->text);
	}
}
