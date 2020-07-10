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
		chase,      /*преследование*/
		scatter,    /*разбегание*/
		frightened, /*страх*/
		toHome,     /*на пути к дому*/
		inHome      /*сидит в домике*/
	};

	/*тип для паттеров поведения (волны): тип поведения, время поведения*/
	typedef std::vector<std::vector<std::pair<Ghost::modeType, float>>> patternMode;

	/*функция базового поиска пути возвращает данный тип*/
	typedef std::vector<std::pair<dirType, float>> distanceType;

	/*constructor / destructor */
	Ghost(const sf::Color& color, const float pos_x, const float pos_y);
	virtual ~Ghost();

	/*accessors*/
	const modeType& getMode();
	const bool isMoveDone(); /*дошло ли привидение до целевой точки?*/

	/*modifier*/
	void setMode(modeType mode);

	/*func*/
	static void loadStaticVar(); /*загрузка текстуры страха*/
	virtual void reload() = 0; /*обновление привидения после прохождения уровня*/
	void update(const Map* map, const Player* player, const float& dt);
protected:
	/*var*/
	sf::Vector2f targetCell; /*координаты центра целевой клетки*/
	modeType mode; /*тип текущего поведения*/

	/*init*/
	virtual void initVar() = 0;

	/*func*/
	virtual void updateTargetcell(const Player* player, const Map* map) = 0;

private:
	/*var*/
	static patternMode pattern; /*паттерны поведения привидений*/
	float frigthetenedTimer; /*таймер для режима страха*/
	static sf::Texture frightenedTexture; /*текстура для отображания состояния страха*/
	static sf::Texture toHomeTexture; /*текстура для отображания состояния движения в домик*/

	/*init*/
	void initSprite(const sf::Color& color, const float pos_x, const float pos_y);
	void initComponents(); /*инициализация хитбокса и анимаций*/
	void initTimers(); /*инициализация таймеров*/

	/*func*/
	void updateTimers(const float& dt); /*обновление таймеров*/
	void updateDirBase(distanceType& distance, const Map* map, const float& dt); /*определяются доступные направления для движения*/
	void updateDirRand(const Map* map, const float& dt); /*обновление направления, выбирается рандомное*/
	void updateDirMin(const Map* map, const float& dt); /*обновление направления, выбирается минимальное*/
	void updateMoveGhost(const Map* map, const float& dt);
	void updateAnimation(const float& dt); /*обновление анимации привидения*/

};

/*debug output*/
std::ostream& operator<<(std::ostream& os, const Ghost::modeType& mode);