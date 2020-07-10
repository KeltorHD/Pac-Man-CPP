#pragma once

#include "entity.h"

class Player :
	public Entity
{
private:
	/*var*/
	sf::Sprite lifeSprite; /*������ ��������� ������*/
	size_t eat; /*���������� ��������� ����*/
	size_t ener; /*���������� ��������� �������������*/
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
	void incEat(); /*���������� ����� ��������� ����*/
	void incEner(); /*���������� ����� ��������� �������������*/
	void decLifes(); /*���������� ����� ������*/

	/*accessors*/
	const size_t& getCountEat(); /*���������� ��������� ����*/

	/*func*/
	void reload(); /*����� ����� ����� ����������� ������*/

	virtual void update(const Map* map, const float& dt);
	virtual void render(sf::RenderTarget* target);
};