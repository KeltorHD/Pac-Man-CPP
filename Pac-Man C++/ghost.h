#pragma once

#include "entity.h"
#include "player.h"

class Ghost :
	public Entity
{
public:
	/*types*/
	enum class modeType
	{
		chase,      /*�������������*/
		scatter,    /*����������*/
		frightened, /*�����*/
		toHome,     /*�� ���� � ����*/
		inHome,     /*����� � ������*/
		outHome     /*����� �� ������*/
	};

	/*��� ��� �������� ��������� (�����): ��� ���������, ����� ���������*/
	typedef std::vector<std::pair<Ghost::modeType, float>> patternMode;

	/*������� �������� ������ ���� ���������� ������ ���*/
	typedef std::vector<std::pair<dirType, float>> distanceType;

	/*constructor / destructor */
	Ghost(const sf::Color& color, const float pos_x, const float pos_y, const float speed);
	virtual ~Ghost();

	/*accessors*/
	const modeType& getMode() const;
	const bool isMoveDone() const; /*����� �� ���������� �� ������� �����?*/
	const bool isFrightened() const; /*� ��������� ������ �� �������*/
	const bool isNotMatherial() const; /*���� � ����������� ������ �����������*/

	/*modifier*/
	void setModeFrightened(); /*���������� ��������� ������*/
	void setModeToHome(); /*���������� ��������� ���� �����*/

	/*func*/
	static void loadStaticVar(); /*�������� �������� ������*/
	virtual void reload() = 0; /*���������� ���������� ����� ����������� ������*/
	void update(const Map* map, const Player* player, const float& dt);
protected:
	/*var*/
	static patternMode pattern; /*�������� ��������� ����������*/
	int patternCounter; /*��� ���������� ��������� ����������*/
	float patternTimer; /*������ ��� ����� ���������*/
	sf::Vector2f targetCell; /*���������� ������ ������� ������*/
	modeType mode; /*��� �������� ���������*/

	/*init*/
	virtual void initVar() = 0;

	/*func*/
	void setMode(modeType mode); /*���������� ������ � ����������*/

	virtual void updateTargetcell(const Player* player, const Map* map) = 0;
	virtual void updateHouse(const Map* map); /*����� �� �������� �� ������*/
private:
	/*var*/
	float frigthetenedTimer; /*������ ��� ������ ������*/
	static sf::Texture frightenedTexture; /*�������� ��� ����������� ��������� ������*/
	static sf::Texture toHomeTexture; /*�������� ��� ����������� ��������� �������� � �����*/

	/*init*/
	void initSprite(const sf::Color& color, const float pos_x, const float pos_y);
	void initComponents(); /*������������� �������� � ��������*/
	void initTimers(); /*������������� ��������*/

	/*func*/
	void updateHouseMove(const Map* map, const float& dt); /*���������� ������ �� ������*/
	void updateTimers(const float& dt); /*���������� ��������*/
	void updateDirBase(distanceType& distance, const Map* map, const float& dt); /*������������ ��������� ����������� ��� ��������*/
	void updateDirRand(const Map* map, const float& dt); /*���������� �����������, ���������� ���������*/
	void updateDirMin(const Map* map, const float& dt); /*���������� �����������, ���������� �����������*/
	void updateMoveGhost(const Map* map, const float& dt);
	void updateAnimation(const float& dt); /*���������� �������� ����������*/
};

/*debug output*/
std::ostream& operator<<(std::ostream& os, const Ghost::modeType& mode);