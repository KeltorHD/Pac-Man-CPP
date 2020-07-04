#ifndef ENEMY_H
#define ENEMY_H

#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity
{
protected:
	/*variable*/
	sf::Sprite sprite; /*������ ��������*/
	sf::Texture animTexture; /*�������� ��� ��������*/

	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

	virtual void initSprite() = 0;
public:
	Entity();
	virtual ~Entity();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};



#endif // !ENEMY_H