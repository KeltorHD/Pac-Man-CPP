
namespace gui
{
	class Button
	{
	private:
		sf::RectangleShape shape;
		sf::Font& font;
		sf::Text text;

	public:
		Button(
			const float pos_x, const float pos_y,
			const float width, const float heigth,
			const std::string text, const sf::Font& font
		);
		~Button();

		/*accessors*/
		bool isPressed() const;

		/*update/render*/
		void update(const float& dt);
		void render(sf::RenderTarget* target);
	};
}