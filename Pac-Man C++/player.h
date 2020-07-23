#pragma once

#include "entity.h"

class Player :
	public Entity
{
private:
	/*var*/
	sf::Sprite lifeSprite; /*спрайт отрисовки жизней*/
	int lifes; /*жизни игрока*/
	float timerDecrease; /*время, когда скорость уменьшается на 10%*/
	bool isDecrease; /*есть ли уменьшение скорости*/
	bool isDeath; /*производится ли анимация смерти*/
	bool isReload; /*нужно ли сбрасывать героя*/

	/*init*/
	void initVar();
	void initComponents();
	void initSprite();

	/*func*/
	void reloadPrivate();

	void updateReload();
	void updateTimer(const float& dt);
	void updateAnimation(const float& dt);
	void renderLifes(sf::RenderTarget* target);
public:
	Player();
	virtual ~Player();

	/*modifier*/
	void decLifes(); /*уменьшение числа жизней*/
	void setLifes(unsigned life); /*установление числа жизней*/
	void setDecreaseSpeed(); /*установление уменьшения скорости*/

	/*accessors*/
	const int& getLives() const; /*количество жизней*/
	bool isDeathDone() const;

	/*func*/
	void reload(); /*сброс героя после прохождения уровня*/

	void updateInput(const Map* map, const float& dt, const dirType dir);
	virtual void update(const Map* map, const float& dt);
	virtual void render(sf::RenderTarget* target);
};