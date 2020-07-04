#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX;
	float offsetY;
public:
	HitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y, 
		float width, float height);
	virtual ~HitboxComponent();

	/*accessors*/
	const sf::Vector2f& getPosition() const;

	/*modifiers*/
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);
	void move(const float x, const float y);

	/*func*/
	void update();
	void render(sf::RenderTarget& target);
};


#endif // !HITBOXCOMPONENT_H