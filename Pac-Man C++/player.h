#pragma once

#include "entity.h"

class Player :
	public Entity
{
private:
	/*var*/
	sf::Sprite lifeSprite; /*спрайт отрисовки жизней*/
	int lifes; /*жизни игрока*/

	/*init*/
	void initVar();
	void initComponents();
	void initSprite();

	/*func*/
	void updateAnimation(const float& dt);
	void renderLifes(sf::RenderTarget* target);
public:
	Player();
	virtual ~Player();

	/*modifier*/
	void decLifes(); /*уменьшение числа жизней*/

	/*accessors*/
	const int& getLives() const; /*количество жизней*/

	/*func*/
	void reload(); /*сброс героя после прохождения уровня*/

	virtual void update(const Map* map, const float& dt);
	virtual void render(sf::RenderTarget* target);
};