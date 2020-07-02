#ifndef ENEMY_H
#define ENEMY_H

#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Enemy
{
protected:
	/*variable*/
	sf::Sprite sprite; /*спрайт сущности*/
	sf::Texture animTexture; /*текстура для анимации*/

	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;

	virtual void initSprite() = 0;
public:
	Enemy();
	virtual ~Enemy();

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};



#endif // !ENEMY_H