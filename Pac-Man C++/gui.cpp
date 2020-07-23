#include "stdafx.h"
#include "gui.h"

//BUTTON
gui::Button::Button(const float pos_x, const float pos_y, 
	const float width, const float heigth, 
	const std::string text, const sf::Font& font, 
	unsigned char_size, unsigned border_width,
	sf::Color base_text, sf::Color hover_text, sf::Color active_text, 
	sf::Color base_front, sf::Color hover_front, sf::Color active_front, 
	sf::Color base_border, sf::Color hover_border, sf::Color active_border)
	:font(font)
{
	this->btnState = state::BTN_BASE;

	this->border.setSize(sf::Vector2f(width, heigth));
	this->border.setFillColor(base_border);
	this->border.setPosition(pos_x, pos_y);

	this->front.setSize(sf::Vector2f(width - 2 * border_width, heigth - 2 * border_width));
	this->front.setPosition(pos_x + border_width, pos_y + border_width);
	this->front.setFillColor(base_front);
	
	this->text.setString(text);
	this->text.setCharacterSize(char_size);
	this->text.setFont(this->font);
	this->text.setFillColor(base_text);
	this->text.setOrigin
	(
		this->text.getLocalBounds().left + this->text.getLocalBounds().width / 2.f,
		this->text.getLocalBounds().top + this->text.getLocalBounds().height / 2.f
	);
	this->text.setPosition(pos_x + width / 2.f, pos_y + heigth / 2.f);

	this->base_text = base_text;
	this->hover_text = hover_text;
	this->active_text = active_text;

	this->base_front = base_front;
	this->hover_front = hover_front;
	this->active_front = active_front;

	this->base_border = base_border;
	this->hover_border = hover_border;
	this->active_border = active_border;
}

gui::Button::~Button()
{
}

bool gui::Button::isPressed() const
{
	return this->btnState == state::BTN_ACTIVE;
}

void gui::Button::update(const sf::Vector2i& mousePosWindow)
{
	/*normal state*/
	this->btnState = state::BTN_BASE;

	/*hover*/
	if (this->front.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->btnState = state::BTN_HOVER;

		/*pressed*/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->btnState = state::BTN_ACTIVE;
		}
	}

	/*fill color*/
	switch (this->btnState)
	{
	case state::BTN_BASE:
		this->front.setFillColor(this->base_front);
		this->border.setOutlineColor(this->base_border);
		this->text.setFillColor(this->base_text);
		break;
	case state::BTN_HOVER:
		this->front.setFillColor(this->hover_front);
		this->border.setOutlineColor(this->hover_border);
		this->text.setFillColor(this->hover_text);
		break;
	case state::BTN_ACTIVE:
		this->front.setFillColor(this->active_front);
		this->border.setOutlineColor(this->active_border);
		this->text.setFillColor(this->active_text);
		break;
	default:
		this->front.setFillColor(sf::Color::Red);
		this->border.setOutlineColor(sf::Color::Blue);
		this->text.setFillColor(sf::Color::White);
		break;
	}
}

void gui::Button::render(sf::RenderTarget* target)
{
	target->draw(this->border);
	target->draw(this->front);
	target->draw(this->text);
}


//SLIDER
gui::Slider::Slider(float x, float y, int min, int max, int axisWidth, int axisHeight, int sliderWidth, int sliderHeight)
{
	this->axisWidth = axisWidth;
	this->axisHeight = axisHeight;
	this->sliderWidth = sliderWidth;
	this->sliderHeight = sliderHeight;

	this->xCoord = int(x);
	this->yCoord = int(y);

	axis.setPosition(x, y);
	axis.setOrigin(0.f, axisHeight / 2.f);
	axis.setSize(sf::Vector2f(float(axisWidth), float(axisHeight)));
	axis.setFillColor(sf::Color(63, 63, 63));
	slider.setPosition(x, y);
	slider.setOrigin(sliderWidth / 2.f, sliderHeight / 2.f);
	slider.setSize(sf::Vector2f(float(sliderWidth), float(sliderHeight)));
	slider.setFillColor(sf::Color(192, 192, 192));

	this->sliderValue = float(max);
	this->minValue = min;
	this->maxValue = max;
}

gui::Slider::~Slider()
{
}

float gui::Slider::getSliderValue()
{
	return this->sliderValue;
}

void gui::Slider::setSliderPercentValue(float value)
{
	if (value >= 0 && value <= 100)
	{
		sliderValue = value / 100 * maxValue;
		slider.setPosition(xCoord + (axisWidth * value / 100.f), float(yCoord));
	}
}

void gui::Slider::update(sf::RenderWindow* target)
{
	if (this->slider.getGlobalBounds().contains(float(sf::Mouse::getPosition(*target).x), float(sf::Mouse::getPosition(*target).y))
		&& sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		if (sf::Mouse::getPosition(*target).x >= this->xCoord && sf::Mouse::getPosition(*target).x <= this->xCoord + this->axisWidth)
		{
			this->slider.setPosition(float(sf::Mouse::getPosition(*target).x), float(this->yCoord));
			this->sliderValue = (this->minValue + ((this->slider.getPosition().x - this->xCoord) / this->axisWidth * (this->maxValue - this->minValue)));
		}
	}
}

void gui::Slider::render(sf::RenderTarget* target)
{
	target->draw(this->axis);
	target->draw(this->slider);
}
