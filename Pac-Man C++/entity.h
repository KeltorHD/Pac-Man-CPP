#pragma once

#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "map.h"

class Entity
{
protected:
	/*variable*/
	float speed; /*�������� ������������*/
	dirType current;
	dirType next;
	sf::Sprite sprite; /*������ ��������*/
	sf::Texture baseTexture; /*�������� ��� ��������*/

	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

	void updateMove(const Map* map, const float& dt); /*�������� �������� �� �����������*/
public:
	Entity(float speed, dirType current, dirType next);
	virtual ~Entity();

	/*modefier*/
	void setDir(dirType dir); /*����������� ����������� ��������*/
	void setPosition(float x, float y); /*���������� ������� ��������*/
	void clearDir(); /*������� ���������� ����������� � �������*/
	void clearDir(dirType dir); /*�������� �����������, ���������� � ������� dir*/

	/*accessors*/
	const dirType& getCurDir() const; /*����������� �������� ��������*/
	const dirType& getNextDir() const; /*����������� ���������� ��������*/
	const sf::Vector2f getCenterPosition() const; /*��������� ������ ��������*/
	const sf::Vector2f& getPosition() const; /*��������� ������� ������ �������� ������� ��������*/
	const sf::Vector2f getPosition(const dirType& dir) const; /*��������� ������� ��������� ������� �� ����������� ������������� ��������*/
	const sf::Vector2f getNextPosition(const float& dt) const; /*��������� ��������� ������� � ������ �������� ����������� ��������*/
	const sf::Vector2f getNextPosition(const dirType& dir, const float& dt) const; /*� ������ ������������� �����������*/

	/*func*/
	void move(const float& dt); /*��������� �� �������� �����������*/
	void moveToBorder(); /*������� � ������� ������*/

	virtual void render(sf::RenderTarget* target); /*��������� ��������*/
};