#pragma once

#include "ghost.h"

class Blinky :
	public Ghost
{
public:
	Blinky();
	virtual ~Blinky();

	/*func*/
	virtual void reload(const int& level);
private:
	/*var*/

	/*init*/
	virtual void initVar();

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map);
};