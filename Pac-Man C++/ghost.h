#pragma once

#include "entity.h"
#include "player.h"

/*������� �������� ������ ���� ���������� ������ ���*/
typedef std::vector<std::pair<dirType, float>> distanceType;

class Ghost :
	public Entity
{
public:
	enum class modeType
	{
		chase,      /*�������������*/
		scatter,    /*����������*/
		frightened, /*�����*/
		toHome,     /*�� ���� � ����*/
		inHome      /*����� � ������*/
	};

	Ghost(const sf::Color& color, const float pos_x, const float pos_y);
	virtual ~Ghost();

	/*accessors*/
	const modeType& getMode();
	const bool isMoveDone(); /*����� �� ���������� �� ������� �����?*/

	/*modifier*/
	void setMode(modeType mode);

	/*func*/
	static void loadStaticTexture(); /*�������� �������� ������*/
	virtual void reload() = 0; /*���������� ���������� ����� ����������� ������*/
	void update(const Map* map, const Player* player, const float& dt);
protected:
	/*var*/
	sf::Vector2f targetCell; /*���������� ������ ������� ������*/
	modeType mode; /*��� �������� ���������*/

	/*init*/
	void initSprite(const sf::Color& color, const float pos_x, const float pos_y);
	void initComponents(); /*������������� �������� � ��������*/
	virtual void initVar() = 0;
	virtual void initTimers() = 0;

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map) = 0;

	void updateDirRand(const Map* map, const float& dt); /*���������� �����������, ���������� ���������*/
	void updateDirMin(const Map* map, const float& dt); /*���������� �����������, ���������� �����������*/
	void updateMoveGhost(const Map* map, const float& dt);
	void updateAnimation(const float& dt); /*���������� �������� ����������*/

private:
	/*var*/
	static sf::Texture frightenedTexture; /*�������� ��� ����������� ��������� ������*/
	static sf::Texture toHomeTexture; /*�������� ��� ����������� ��������� �������� � �����*/

	/*func*/
	void updateDirBase(distanceType& distance, const Map* map, const float& dt); /*������������ ��������� ����������� ��� ��������*/

};

/*debug output*/
std::ostream& operator<<(std::ostream& os, const Ghost::modeType& mode);