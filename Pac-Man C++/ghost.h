#pragma once

#include "entity.h"
#include "player.h"

class Ghost :
	public Entity
{
public:
	enum class modeType
	{
		chase,      /*�������������*/
		scatter,    /*����������*/
		frightened, /*�����*/
	};

	Ghost();
	virtual ~Ghost();

	/*accessors*/
	const modeType& getMode();

	/*modifier*/
	void setMode(modeType mode);

	/*func*/
	virtual void update(const Map* map, const Player* player, const float& dt) = 0;

protected:
	/*var*/
	sf::Vector2f targetCell; /*���������� ������ ������� ������*/
	modeType mode; /*��� �������� ���������*/

	/*init*/
	virtual void initVar() = 0;
	virtual void initTimers() = 0;

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map) = 0;

	void updateDir(const Map* map, const float& dt);
	void updateMoveGhost(const Map* map, const float& dt);
};