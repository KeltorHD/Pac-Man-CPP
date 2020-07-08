#include "stdafx.h"
#include "ghost.h"

Ghost::Ghost()
	: Entity(75.f, dirType::left, dirType::none)
{
	this->targetCell = sf::Vector2f(0.f, 0.f);
	this->mode = modeType::chase;
}

Ghost::~Ghost()
{
}

const Ghost::modeType& Ghost::getMode()
{
	return this->mode;
}

void Ghost::setMode(modeType mode)
{
	this->mode = mode;
}

void Ghost::updateDir(const Map* map, const float& dt)
{
	/*центр следующей позиции привидения по текущему направлению*/
	sf::Vector2i next = 
	{
		(int(this->getNextPosition(this->current, dt).x) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2,
		(int(this->getNextPosition(this->current, dt).y) / TILE_WIDTH) * TILE_WIDTH + TILE_WIDTH / 2
	};

	/*следующая позиция стена?*/
	if (!map->isWall
	(
		next.x / TILE_WIDTH,
		next.y / TILE_WIDTH
	))
	{
		/*
		Находим из всех доступных сторон для движения ту, которая наиболее
		близка к целевой точке и не обратна к текущей стороне движения.
		Если число свободных путей равно 3-м, то не можем пойти наверх.
		Если все доступные пути равнозначно близки к целевой точке, то
		приоритеты располагаются таким образом:
		верхняя > левая > нижняя
		*/
		std::vector<std::pair<dirType, float>> distance; /*массив пар направление-расстояние*/
		dirType cur = this->current; /*проверяемое направление*/

		/*Первое направление*/
		sf::Vector2i tmpPos = getNextCoordWidthDir(next, cur);
		/*если следующая позиция по этому направлению не стена*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(conversion(tmpPos), this->targetCell) });
		}

		/*второе направление*/
		cur = getPerpendicularDir(cur); /*перпендикулярное направление*/
		tmpPos = getNextCoordWidthDir(next, cur);
		/*если следующая позиция по этому направлению не стена*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(conversion(tmpPos), this->targetCell) });
		}

		/*третье направление*/
		cur = getOppositeDir(cur); /*противоположное перпендикулярному направлению*/
		tmpPos = getNextCoordWidthDir(next, cur);
		/*если следующая позиция по этому направлению не стена*/
		if (!map->isWall
		(
			tmpPos.x / TILE_WIDTH,
			tmpPos.y / TILE_WIDTH
		))
		{
			distance.push_back({ cur, map->distance(conversion(tmpPos), this->targetCell) });
		}

		/*выбор направления по наименьшему расстоянию*/
		if (distance.size())
		{
			/*обработка особых клеток*/
			if (!map->isGhostUp(int(this->getNextPosition(this->current, dt).x) / TILE_WIDTH, int(this->getNextPosition(this->current, dt).y) / TILE_WIDTH))
			{
				distance.erase(std::remove_if(distance.begin(), distance.end(),
					[](auto& element) {return element.first == dirType::up; }), distance.end());
			}

			float minimum = 1000.f;
			dirType dir = dirType::none;
			for (size_t i = 0; i < distance.size(); i++)
			{
				if (distance[i].second < minimum)
				{
					minimum = distance[i].second;
					dir = distance[i].first;
				}
			}

			this->setDir(dir);
		}
	}
}

void Ghost::updateMoveGhost(const Map* map, const float& dt)
{
	if (this->mode == modeType::chase)
	{
		/*обновление направления движения по целевой точке*/
		this->updateDir(map, dt);
	}
	else if (this->mode == modeType::frightened)
	{

	}
	else if (this->mode == modeType::scatter)
	{

	}
	/*движение*/
	this->updateMove(map, dt);
}