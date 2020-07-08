#pragma once

#include "ghost.h"

class Blinky :
	public Ghost
{
public:
	Blinky();
	virtual ~Blinky();

	/*func*/
	virtual void update(const Map* map, const Player* player, const float& dt);
	virtual void render(sf::RenderTarget* target);
private:
	/*var*/

	/*init*/
	virtual void initSprite();
	virtual void initComponents();
	virtual void initVar();
	virtual void initTimers();

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map);
};