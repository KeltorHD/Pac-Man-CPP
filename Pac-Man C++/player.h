#pragma once

#include "entity.h"

class Player :
	public Entity
{
private:
	/*var*/
	sf::Sprite lifeSprite; /*спрайт отрисовки жизней*/
	size_t eat; /*количество съеденной пищи*/
	size_t ener; /*количество съеденных энерджайзеров*/
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
	void incEat(); /*увеличение числа съеденной пищи*/
	void incEner(); /*увеличение числа съеденных энерджайзеров*/
	void decLifes(); /*уменьшение числа жизней*/

	/*accessors*/
	const size_t& getCountEat(); /*количество съеденной пищи*/

	/*func*/
	void reload(); /*сброс героя после прохождения уровня*/

	virtual void update(const Map* map, const float& dt);
	virtual void render(sf::RenderTarget* target);
};