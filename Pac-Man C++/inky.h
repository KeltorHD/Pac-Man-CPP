#pragma once

#include "ghost.h"

class Inky :
	public Ghost
{
public:
	Inky();
	virtual ~Inky();

	/*func*/
	void updateTargetCell(const Player* player, const Ghost* ghost);
	virtual void reload();
private:
	/*var*/

	/*init*/
	virtual void initVar();

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map);
	void updateHouse(const Map* map); /*не нужно ли выходить из домика*/
};

