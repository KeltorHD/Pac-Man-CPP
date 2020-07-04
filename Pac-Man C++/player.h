#ifndef PLAYER_H

#include "entity.h"

class Player :
	public Entity
{
private:
	/*var*/
	float speed;
	dirType current;
	dirType next;

	/*init*/
	void initVar();
	void initComponents();
	virtual void initSprite();

	/*func*/

public:
	Player();
	virtual ~Player();

	/*modifier*/
	void setDir(dirType dir);
	void setPosition(float x, float y);
	void clearDir(); /*������� ���������� ����������� � �������*/
	void clearDir(dirType dir); /*�������� �����������, ���������� � ������� dir*/

	/*get*/
	const dirType& getCurDir();
	const dirType& getNextDir();
	const sf::Vector2f& getPosition();
	const sf::Vector2f& getPosition(const dirType& dir); /*��������� ������� ��������� ������� �� ����������� ������������� ��������*/
	const sf::Vector2f getNextPosition(const float& dt);
	const sf::Vector2f getNextPosition(const dirType& dir, const float& dt); /*� ������ ������������� �����������*/
	const float getMovingRange(const float& dt);

	/*func*/
	void move(const float& dt);
	void moveToBorder(); /*������� � ������� ������*/

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif // !PLAYER_H
