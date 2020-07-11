#pragma once
#include "ghost.h"
class Clyde :
	public Ghost
{
public:
	Clyde();
	virtual ~Clyde();

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