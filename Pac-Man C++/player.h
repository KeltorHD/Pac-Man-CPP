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
	void clearDir(); /*перенос следующего направления в текущее*/
	void clearDir(dirType dir); /*очищение направлений, добавление в текущее dir*/

	/*get*/
	const dirType& getCurDir();
	const dirType& getNextDir();
	const sf::Vector2f& getPosition();
	const sf::Vector2f& getPosition(const dirType& dir); /*получение позиции ближайшей стороны по направлению передаваемого движения*/
	const sf::Vector2f getNextPosition(const float& dt);
	const sf::Vector2f getNextPosition(const dirType& dir, const float& dt); /*с учетом передаваемого направления*/
	const float getMovingRange(const float& dt);

	/*func*/
	void move(const float& dt);
	void moveToBorder(); /*подойти к границе кубика*/

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif // !PLAYER_H
