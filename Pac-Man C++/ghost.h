#pragma once

#include "entity.h"
#include "player.h"

/*функция базового поиска пути возвращает данный тип*/
typedef std::vector<std::pair<dirType, float>> distanceType;

class Ghost :
	public Entity
{
public:
	enum class modeType
	{
		chase,      /*преследование*/
		scatter,    /*разбегание*/
		frightened, /*страх*/
		toHome,     /*на пути к дому*/
		inHome      /*сидит в домике*/
	};

	Ghost(const sf::Color& color, const float pos_x, const float pos_y);
	virtual ~Ghost();

	/*accessors*/
	const modeType& getMode();
	const bool isMoveDone(); /*дошло ли привидение до целевой точки?*/

	/*modifier*/
	void setMode(modeType mode);

	/*func*/
	static void loadStaticTexture(); /*загрузка текстуры страха*/
	virtual void reload() = 0; /*обновление привидения после прохождения уровня*/
	void update(const Map* map, const Player* player, const float& dt);
protected:
	/*var*/
	sf::Vector2f targetCell; /*координаты центра целевой клетки*/
	modeType mode; /*тип текущего поведения*/

	/*init*/
	void initSprite(const sf::Color& color, const float pos_x, const float pos_y);
	void initComponents(); /*инициализация хитбокса и анимаций*/
	virtual void initVar() = 0;
	virtual void initTimers() = 0;

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map) = 0;

	void updateDirRand(const Map* map, const float& dt); /*обновление направления, выбирается рандомное*/
	void updateDirMin(const Map* map, const float& dt); /*обновление направления, выбирается минимальное*/
	void updateMoveGhost(const Map* map, const float& dt);
	void updateAnimation(const float& dt); /*обновление анимации привидения*/

private:
	/*var*/
	static sf::Texture frightenedTexture; /*текстура для отображания состояния страха*/
	static sf::Texture toHomeTexture; /*текстура для отображания состояния движения в домик*/

	/*func*/
	void updateDirBase(distanceType& distance, const Map* map, const float& dt); /*определяются доступные направления для движения*/

};

/*debug output*/
std::ostream& operator<<(std::ostream& os, const Ghost::modeType& mode);