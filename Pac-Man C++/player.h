#pragma once

#include "entity.h"

class Player :
	public Entity
{
private:
	/*var*/
	sf::Sprite lifeSprite; /*������ ��������� ������*/
	int lifes; /*����� ������*/

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
	void decLifes(); /*���������� ����� ������*/

	/*accessors*/
	const int& getLives() const; /*���������� ������*/

	/*func*/
	void reload(); /*����� ����� ����� ����������� ������*/

	virtual void update(const Map* map, const float& dt);
	virtual void render(sf::RenderTarget* target);
};