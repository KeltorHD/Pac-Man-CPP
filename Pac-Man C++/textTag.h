#pragma once

class TextTag
{
private:
	/*var*/
	sf::Text text;
	float timer;

public:
	TextTag(sf::Font& font, unsigned charSize, sf::Color textColor);
	~TextTag();

	/*func*/
	void setNewTag(std::string text, const sf::Vector2f& pos);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};