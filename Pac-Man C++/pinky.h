#pragma once

#include "ghost.h"

class Pinky : 
	public Ghost
{
public:
	Pinky();
	virtual ~Pinky();

	/*func*/
	virtual void reload();
private:
	/*var*/

	/*init*/
	virtual void initVar();

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map);
	void updateHouse(const Map* map); /*не нужно ли выходить из домика*/
};