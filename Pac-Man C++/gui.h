#pragma once

namespace gui
{
	class Button
	{
	private:
		enum class state
		{
			BTN_BASE,   /*обычное состо€ние*/
			BTN_HOVER,  /*наведена мышь*/
			BTN_ACTIVE  /*ктопка нажата*/
		};

		sf::RectangleShape border;
		sf::RectangleShape front;
		const sf::Font& font;
		state btnState;
		sf::Text text;

		sf::Color base_text;
		sf::Color hover_text;
		sf::Color active_text;

		sf::Color base_front;
		sf::Color hover_front;
		sf::Color active_front;

		sf::Color base_border;
		sf::Color hover_border;
		sf::Color active_border;
	public:
		Button(
			const float pos_x, const float pos_y,
			const float width, const float heigth,
			const std::string text, const sf::Font& font,
			unsigned char_size, unsigned border_width,
			sf::Color base_text, sf::Color hover_text, sf::Color active_text,
			sf::Color base_front, sf::Color hover_front, sf::Color active_front,
			sf::Color base_border, sf::Color hover_border, sf::Color active_border
		);
		~Button();

		/*accessors*/
		bool isPressed() const;

		/*update/render*/
		void update(const sf::Vector2i& mousePosWindow);
		void render(sf::RenderTarget* target);
	};

	class Slider
	{
	private:
		sf::RectangleShape slider;
		sf::RectangleShape axis;

		int xCoord;
		int yCoord;
		
		int minValue;
		int maxValue;
		
		int axisWidth;
		int axisHeight;
		int sliderWidth;
		int sliderHeight;

		float sliderValue;

	public:
		Slider(float x, float y, int min, int max, int axisWidth, int axisHeight, int sliderWidth, int sliderHeight);
		~Slider();

		/*accessors*/
		float getSliderValue();

		/*modifier*/
		void setSliderPercentValue(float value);

		/*func*/
		void update(sf::RenderWindow* target);
		void render(sf::RenderTarget* target);
	};
}