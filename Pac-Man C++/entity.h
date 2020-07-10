#pragma once

#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "map.h"

class Entity
{
protected:
	/*variable*/
	float speed; /*скорость передвижения*/
	dirType current;
	dirType next;
	sf::Sprite sprite; /*спрайт сущности*/
	sf::Texture baseTexture; /*текстура для анимации*/

	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

	void updateMove(const Map* map, const float& dt); /*движение сущности по направлению*/
public:
	Entity(float speed, dirType current, dirType next);
	virtual ~Entity();

	/*modefier*/
	void setDir(dirType dir); /*запоминание направления движения*/
	void setPosition(float x, float y); /*установить позицию хитбокса*/
	void clearDir(); /*перенос следующего направления в текущее*/
	void clearDir(dirType dir); /*очищение направлений, добавление в текущее dir*/

	/*accessors*/
	const dirType& getCurDir() const; /*направление текущего движения*/
	const dirType& getNextDir() const; /*направление следующего движения*/
	const sf::Vector2f getCenterPosition() const; /*получение центра хитбокса*/
	const sf::Vector2f& getPosition() const; /*получение позиции левого верхнего пикселя хитбокса*/
	const sf::Vector2f getPosition(const dirType& dir) const; /*получение позиции ближайшей стороны по направлению передаваемого движения*/
	const sf::Vector2f getNextPosition(const float& dt) const; /*получение следующей позиции с учетом текущего направления движения*/
	const sf::Vector2f getNextPosition(const dirType& dir, const float& dt) const; /*с учетом передаваемого направления*/

	/*func*/
	void move(const float& dt); /*двигаться по текущему направлению*/
	void moveToBorder(); /*подойти к границе кубика*/

	virtual void render(sf::RenderTarget* target); /*отрисовка сущности*/
};