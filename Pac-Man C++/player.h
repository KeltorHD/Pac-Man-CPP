#pragma once
#include "enemy.h"
class Player :
	public Enemy
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
	void updateMove(const float& dt);
public:
	Player();
	virtual ~Player();

	/*modifier*/
	void setDir(dirType dir);

	/*func*/
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

